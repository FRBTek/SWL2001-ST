/*!
 * \file      smtc_hal_gpio.c
 *
 * \brief     GPIO Hardware Abstraction Layer implementation
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
#include <stdint.h>   // C99 types
#include <stdbool.h>  // bool type

#include "smtc_hal_gpio.h"
#include "stm32u0xx_hal.h"

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE MACROS-----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE CONSTANTS -------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE TYPES -----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE VARIABLES -------------------------------------------------------
 */

/*!
 * Array holding attached IRQ gpio data context
 */
static hal_gpio_irq_t const* gpio_irq[16];

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DECLARATION -------------------------------------------
 */


/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS DEFINITION ---------------------------------------------
 */

//
// MCU input pin Handling
//

void hal_gpio_irq_attach( const hal_gpio_irq_t* irq )
{
    if( ( irq != NULL ) && ( irq->callback != NULL ) )
    {
        gpio_irq[( irq->pin ) & 0x0F] = irq;
    }
}

void hal_gpio_irq_deatach( const hal_gpio_irq_t* irq )
{
    if( irq != NULL )
    {
        gpio_irq[( irq->pin ) & 0x0F] = NULL;
    }
}

void hal_gpio_irq_enable( void )
{
    HAL_NVIC_EnableIRQ( EXTI0_IRQn );
    HAL_NVIC_EnableIRQ( EXTI1_IRQn );
    HAL_NVIC_EnableIRQ( EXTI2_IRQn );
    HAL_NVIC_EnableIRQ( EXTI3_IRQn );
    HAL_NVIC_EnableIRQ( EXTI4_IRQn );
    HAL_NVIC_EnableIRQ( EXTI9_5_IRQn );
    HAL_NVIC_EnableIRQ( EXTI15_10_IRQn );
}

void hal_gpio_irq_disable( void )
{
    HAL_NVIC_DisableIRQ( EXTI0_IRQn );
    HAL_NVIC_DisableIRQ( EXTI1_IRQn );
    HAL_NVIC_DisableIRQ( EXTI2_IRQn );
    HAL_NVIC_DisableIRQ( EXTI3_IRQn );
    HAL_NVIC_DisableIRQ( EXTI4_IRQn );
    HAL_NVIC_DisableIRQ( EXTI9_5_IRQn );
    HAL_NVIC_DisableIRQ( EXTI15_10_IRQn );
}

//
// MCU pin state control
//

void hal_gpio_set_value( const hal_gpio_pin_names_t pin, const uint32_t value )
{
    GPIO_TypeDef* gpio_port = ( GPIO_TypeDef* ) ( AHB2PERIPH_BASE + ( ( pin & 0xF0 ) << 6 ) );

    HAL_GPIO_WritePin( gpio_port, ( 1 << ( pin & 0x0F ) ), ( value != 0 ) ? GPIO_PIN_SET : GPIO_PIN_RESET );
}

uint32_t hal_gpio_get_value( const hal_gpio_pin_names_t pin )
{
    GPIO_TypeDef* gpio_port = ( GPIO_TypeDef* ) ( AHB2PERIPH_BASE + ( ( pin & 0xF0 ) << 6 ) );

    return ( HAL_GPIO_ReadPin( gpio_port, ( ( 1 << ( pin & 0x0F ) ) ) ) != GPIO_PIN_RESET ) ? 1 : 0;
}

void hal_gpio_clear_pending_irq( const hal_gpio_pin_names_t pin )
{
    switch( pin & 0x0F )
    {
    case 0:
        NVIC_ClearPendingIRQ( EXTI0_IRQn );
        break;
    case 1:
        NVIC_ClearPendingIRQ( EXTI1_IRQn );

        break;
    case 2:
        NVIC_ClearPendingIRQ( EXTI2_IRQn );
        break;
    case 3:
        NVIC_ClearPendingIRQ( EXTI3_IRQn );
        break;
    case 4:
        NVIC_ClearPendingIRQ( EXTI4_IRQn );
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        NVIC_ClearPendingIRQ( EXTI9_5_IRQn );
        break;
    default:
        NVIC_ClearPendingIRQ( EXTI15_10_IRQn );
        break;
    }
}

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DEFINITION --------------------------------------------
 */

void HAL_GPIO_EXTI_Callback( uint16_t gpio_pin )
{
    uint8_t callback_index = 0;

    if( gpio_pin > 0 )
    {
        while( gpio_pin != 0x01 )
        {
            gpio_pin = gpio_pin >> 1;
            callback_index++;
        }
    }

    if( ( gpio_irq[callback_index] != NULL ) && ( gpio_irq[callback_index]->callback != NULL ) )
    {
        gpio_irq[callback_index]->callback( gpio_irq[callback_index]->context );
    }
}

/* --- EOF ------------------------------------------------------------------ */
