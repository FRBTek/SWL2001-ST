/*!
 * \file      smtc_hal_rtc.c
 *
 * \brief     RTC Hardware Abstraction Layer implementation
 *
 * The Clear BSD License
 * Copyright Semtech Corporation 2021. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the disclaimer
 * below) provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Semtech corporation nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
 * THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SEMTECH CORPORATION BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <time.h>
#include "smtc_hal_rtc.h"

#include "stm32u0xx_hal.h"
#include "stm32u0xx_ll_rtc.h"
#include "smtc_hal_mcu.h"

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE MACROS-----------------------------------------------------------
 */

/*!
 * Calculates ceiling( X / N )
 */
#define DIVC( X, N ) ( ( ( X ) + ( N ) - 1 ) / ( N ) )

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE CONSTANTS -------------------------------------------------------
 */

/* clang-format off */

// sub-second number of bits
#define N_PREDIV_S                     10U

// Synchronous prediv
#define PREDIV_S                       ( ( 1U << N_PREDIV_S ) - 1U )

// Asynchronous prediv
#define PREDIV_A                       ( ( 1U << ( 15U - N_PREDIV_S ) ) - 1U )


// RTC Time base in us
#define USEC_NUMBER                    1000000U
#define MSEC_NUMBER                    ( USEC_NUMBER / 1000 )

#define COMMON_FACTOR                  3U
#define CONV_NUMER                     ( MSEC_NUMBER >> COMMON_FACTOR )
#define CONV_DENOM                     ( 1U << ( N_PREDIV_S - COMMON_FACTOR ) )

/*!
 * Days, Hours, Minutes and seconds
 */
#define DAYS_IN_LEAP_YEAR              ( ( uint32_t ) 366U )
#define DAYS_IN_YEAR                   ( ( uint32_t ) 365U )
#define SECONDS_IN_1DAY                ( ( uint32_t ) 86400U )
#define SECONDS_IN_1HOUR               ( ( uint32_t ) 3600U )
#define SECONDS_IN_1MINUTE             ( ( uint32_t ) 60U )
#define MINUTES_IN_1HOUR               ( ( uint32_t ) 60U )
#define HOURS_IN_1DAY                  ( ( uint32_t ) 24U )

/*!
 * Correction factors
 */
#define DAYS_IN_MONTH_CORRECTION_NORM  ( ( uint32_t ) 0x99AAA0 )
#define DAYS_IN_MONTH_CORRECTION_LEAP  ( ( uint32_t ) 0x445550 )

/* clang-format on */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE TYPES -----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE VARIABLES -------------------------------------------------------
 */

//TODO: check for extern
static RTC_HandleTypeDef hal_rtc_handle;
static uint32_t          offset_to_test_wrapping = 0;
/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DECLARATION -------------------------------------------
 */

/*!
 * Converts time in ticks to time in 100 us
 *
 * \param[IN] ticks Time in timer ticks
 * \retval milliseconds Time in 100 us
 */
static uint32_t rtc_tick_2_100us( const uint32_t tick );

/*!
 * Get the elapsed time in seconds and milliseconds since RTC initialization
 *
 * \param [OUT] milliseconds Number of milliseconds elapsed since RTC
 *                           initialization
 * \retval seconds           Number of seconds elapsed since RTC initialization
 */
static uint32_t rtc_get_calendar_time( uint16_t* milliseconds );

/*!
 * Get current full resolution RTC timestamp in ticks
 *
 * \retval timestamp_in_ticks Current timestamp in ticks
 */
static uint64_t rtc_get_timestamp_in_ticks( void );

/*!
 * Get current offset
 *
 *
 */
static uint32_t rtc_get_offset_to_test_wrapping( void );
/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS DEFINITION ---------------------------------------------
 */

uint32_t hal_rtc_get_time_s( void )
{
    uint16_t milliseconds = 0;
    return rtc_get_calendar_time( &milliseconds );
}

uint32_t hal_rtc_get_time_ms( void )
{
    uint32_t seconds             = 0;
    uint16_t milliseconds_div_10 = 0;

    seconds = rtc_get_calendar_time( &milliseconds_div_10 );

    return seconds * 1000 + ( milliseconds_div_10 / 10 );
}

void hal_rtc_set_offset_to_test_wrapping( uint32_t offset )
{
    offset_to_test_wrapping = offset;
}

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DEFINITION --------------------------------------------
 */

static uint32_t rtc_tick_2_100us( const uint32_t tick )
{
    uint32_t seconds    = tick >> N_PREDIV_S;
    uint32_t local_tick = tick & PREDIV_S;

    return ( uint32_t ) ( ( seconds * 10000 ) + ( ( local_tick * 10000 ) >> N_PREDIV_S ) );
}

static uint32_t rtc_get_calendar_time( uint16_t* milliseconds_div_10 )
{
    uint32_t ticks;

    uint64_t timestamp_in_ticks = rtc_get_timestamp_in_ticks( ) +
                                  ( uint64_t ) ( ( ( uint64_t ) rtc_get_offset_to_test_wrapping( ) ) << N_PREDIV_S );

    uint32_t seconds = ( uint32_t ) ( timestamp_in_ticks >> N_PREDIV_S );

    ticks = ( uint32_t ) timestamp_in_ticks & PREDIV_S;

    *milliseconds_div_10 = rtc_tick_2_100us( ticks );

    return seconds;
}

static uint64_t rtc_get_timestamp_in_ticks( void )
{
    uint64_t timestamp_in_ticks = 0;
    uint32_t correction;
    uint32_t seconds;

    RTC_TimeTypeDef time;
    RTC_DateTypeDef date;

    // Make sure it is correct due to asynchronous nature of RTC
    volatile uint32_t ssr;

    do
    {
        ssr = RTC->SSR;
        HAL_RTC_GetDate( &hal_rtc_handle, &date, RTC_FORMAT_BIN );
        HAL_RTC_GetTime( &hal_rtc_handle, &time, RTC_FORMAT_BIN );
    } while( ssr != RTC->SSR );

    // Calculate amount of elapsed days since 01/01/2000
    seconds = DIVC( ( DAYS_IN_YEAR * 3 + DAYS_IN_LEAP_YEAR ) * date.Year, 4 );

    correction = ( ( date.Year % 4 ) == 0 ) ? DAYS_IN_MONTH_CORRECTION_LEAP : DAYS_IN_MONTH_CORRECTION_NORM;

    seconds +=
        ( DIVC( ( date.Month - 1 ) * ( 30 + 31 ), 2 ) - ( ( ( correction >> ( ( date.Month - 1 ) * 2 ) ) & 0x03 ) ) );

    seconds += ( date.Date - 1 );

    // Convert from days to seconds
    seconds *= SECONDS_IN_1DAY;

    seconds += ( ( uint32_t ) time.Seconds + ( ( uint32_t ) time.Minutes * SECONDS_IN_1MINUTE ) +
                 ( ( uint32_t ) time.Hours * SECONDS_IN_1HOUR ) );

    timestamp_in_ticks = ( ( ( uint64_t ) seconds ) << N_PREDIV_S ) + ( PREDIV_S - time.SubSeconds );

    return timestamp_in_ticks;
}

static uint32_t rtc_get_offset_to_test_wrapping( void )
{
    return offset_to_test_wrapping;
}

/* --- EOF ------------------------------------------------------------------ */
