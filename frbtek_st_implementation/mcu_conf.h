/*!
 * \file      modem_pinout.h
 *
 * \brief     modem specific pinout
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
#ifndef __MODEM_PIN_NAMES_H__
#define __MODEM_PIN_NAMES_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include "smtc_hal_gpio_pin_names.h"

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC MACROS -----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC CONSTANTS --------------------------------------------------------
 */

/********************************************************************************/
/*                         Application     dependant                            */
/********************************************************************************/
/* clang-format off */

//Peripheral handles
#define DEBUG_UART_HANDLE       huart2
#define RADIO_SPI_HANDLE        hspi1
#define TIMER_HANDLE            hlptim1
#define RTC_HANDLE              hrtc
#define RNG_HANDLE              hrng

#if(WATCHDOG == YES)
#define IWDG_HANDLE             iwdg
#endif

//Debug uart specific pinout for debug print
#define DEBUG_UART_TX           PA_2
#define DEBUG_UART_RX           PA_3

//Radio specific pinout and peripherals
#define RADIO_NRST              PA_0
#define RADIO_SPI_MOSI          PA_7
#define RADIO_SPI_MISO          PA_6
#define RADIO_SPI_SCLK          PA_5
#define RADIO_NSS               PA_8
#define RADIO_DIOX              PB_4
#define RADIO_BUSY_PIN          PB_3

#define SX126X_RADIO_RF_SWITCH_CTRL    PA_9

/* clang-format on */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC TYPES ------------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS PROTOTYPES ---------------------------------------------
 */
#ifdef __cplusplus
}
#endif

#endif  //__MODEM_PIN_NAMES_H__