/*!
 * \file      smtc_hal_flash.h
 *
 * \brief     FLASH Hardware Abstraction Layer definition
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
#ifndef __SMTC_HAL_FLASH_H__
#define __SMTC_HAL_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <stdint.h>   // C99 types
#include <stdbool.h>  // bool type

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC MACROS -----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC CONSTANTS --------------------------------------------------------
 */
#define FLASH_PAGE_NUMBER 127 /* 127 pages available on U073 */

#define FLASH_USER_START_ADDR ADDR_FLASH_PAGE_0 /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR \
    FLASH_USER_START_ADDR + ( FLASH_PAGE_NUMBER * ADDR_FLASH_PAGE_SIZE ) - 1 /* End @ of user Flash area */

#define ADDR_FLASH_PAGE_SIZE ( ( uint32_t ) 0x00000800 ) /* Size of Page = 2 Kbytes */

#define FLASH_BYTE_EMPTY_CONTENT ( ( uint8_t ) 0xFF )
#define FLASH_PAGE_EMPTY_CONTENT ( ( uint64_t ) 0xFFFFFFFFFFFFFFFF )

#define FLASH_PAGE_ADDR( page ) FLASH_USER_START_ADDR + ( ( page ) * ADDR_FLASH_PAGE_SIZE )

/* Base address of the Flash s */
#define ADDR_FLASH_PAGE_0 ( ( uint32_t ) 0x08000000 )   /* Base @ of Page 0, 2 Kbytes */
#define ADDR_FLASH_PAGE_1 ( ( uint32_t ) 0x08000800 )   /* Base @ of Page 1, 2 Kbytes */
#define ADDR_FLASH_PAGE_2 ( ( uint32_t ) 0x08001000 )   /* Base @ of Page 2, 2 Kbytes */
#define ADDR_FLASH_PAGE_3 ( ( uint32_t ) 0x08001800 )   /* Base @ of Page 3, 2 Kbytes */
#define ADDR_FLASH_PAGE_4 ( ( uint32_t ) 0x08002000 )   /* Base @ of Page 4, 2 Kbytes */
#define ADDR_FLASH_PAGE_5 ( ( uint32_t ) 0x08002800 )   /* Base @ of Page 5, 2 Kbytes */
#define ADDR_FLASH_PAGE_6 ( ( uint32_t ) 0x08003000 )   /* Base @ of Page 6, 2 Kbytes */
#define ADDR_FLASH_PAGE_7 ( ( uint32_t ) 0x08003800 )   /* Base @ of Page 7, 2 Kbytes */
#define ADDR_FLASH_PAGE_8 ( ( uint32_t ) 0x08004000 )   /* Base @ of Page 8, 2 Kbytes */
#define ADDR_FLASH_PAGE_9 ( ( uint32_t ) 0x08004800 )   /* Base @ of Page 9, 2 Kbytes */
#define ADDR_FLASH_PAGE_10 ( ( uint32_t ) 0x08005000 )  /* Base @ of Page 10, 2 Kbytes */
#define ADDR_FLASH_PAGE_11 ( ( uint32_t ) 0x08005800 )  /* Base @ of Page 11, 2 Kbytes */
#define ADDR_FLASH_PAGE_12 ( ( uint32_t ) 0x08006000 )  /* Base @ of Page 12, 2 Kbytes */
#define ADDR_FLASH_PAGE_13 ( ( uint32_t ) 0x08006800 )  /* Base @ of Page 13, 2 Kbytes */
#define ADDR_FLASH_PAGE_14 ( ( uint32_t ) 0x08007000 )  /* Base @ of Page 14, 2 Kbytes */
#define ADDR_FLASH_PAGE_15 ( ( uint32_t ) 0x08007800 )  /* Base @ of Page 15, 2 Kbytes */
#define ADDR_FLASH_PAGE_16 ( ( uint32_t ) 0x08008000 )  /* Base @ of Page 16, 2 Kbytes */
#define ADDR_FLASH_PAGE_17 ( ( uint32_t ) 0x08008800 )  /* Base @ of Page 17, 2 Kbytes */
#define ADDR_FLASH_PAGE_18 ( ( uint32_t ) 0x08009000 )  /* Base @ of Page 18, 2 Kbytes */
#define ADDR_FLASH_PAGE_19 ( ( uint32_t ) 0x08009800 )  /* Base @ of Page 19, 2 Kbytes */
#define ADDR_FLASH_PAGE_20 ( ( uint32_t ) 0x0800A000 )  /* Base @ of Page 20, 2 Kbytes */
#define ADDR_FLASH_PAGE_21 ( ( uint32_t ) 0x0800A800 )  /* Base @ of Page 21, 2 Kbytes */
#define ADDR_FLASH_PAGE_22 ( ( uint32_t ) 0x0800B000 )  /* Base @ of Page 22, 2 Kbytes */
#define ADDR_FLASH_PAGE_23 ( ( uint32_t ) 0x0800B800 )  /* Base @ of Page 23, 2 Kbytes */
#define ADDR_FLASH_PAGE_24 ( ( uint32_t ) 0x0800C000 )  /* Base @ of Page 24, 2 Kbytes */
#define ADDR_FLASH_PAGE_25 ( ( uint32_t ) 0x0800C800 )  /* Base @ of Page 25, 2 Kbytes */
#define ADDR_FLASH_PAGE_26 ( ( uint32_t ) 0x0800D000 )  /* Base @ of Page 26, 2 Kbytes */
#define ADDR_FLASH_PAGE_27 ( ( uint32_t ) 0x0800D800 )  /* Base @ of Page 27, 2 Kbytes */
#define ADDR_FLASH_PAGE_28 ( ( uint32_t ) 0x0800E000 )  /* Base @ of Page 28, 2 Kbytes */
#define ADDR_FLASH_PAGE_29 ( ( uint32_t ) 0x0800E800 )  /* Base @ of Page 29, 2 Kbytes */
#define ADDR_FLASH_PAGE_30 ( ( uint32_t ) 0x0800F000 )  /* Base @ of Page 30, 2 Kbytes */
#define ADDR_FLASH_PAGE_31 ( ( uint32_t ) 0x0800F800 )  /* Base @ of Page 31, 2 Kbytes */
#define ADDR_FLASH_PAGE_32 ( ( uint32_t ) 0x08010000 )  /* Base @ of Page 32, 2 Kbytes */
#define ADDR_FLASH_PAGE_33 ( ( uint32_t ) 0x08010800 )  /* Base @ of Page 33, 2 Kbytes */
#define ADDR_FLASH_PAGE_34 ( ( uint32_t ) 0x08011000 )  /* Base @ of Page 34, 2 Kbytes */
#define ADDR_FLASH_PAGE_35 ( ( uint32_t ) 0x08011800 )  /* Base @ of Page 35, 2 Kbytes */
#define ADDR_FLASH_PAGE_36 ( ( uint32_t ) 0x08012000 )  /* Base @ of Page 36, 2 Kbytes */
#define ADDR_FLASH_PAGE_37 ( ( uint32_t ) 0x08012800 )  /* Base @ of Page 37, 2 Kbytes */
#define ADDR_FLASH_PAGE_38 ( ( uint32_t ) 0x08013000 )  /* Base @ of Page 38, 2 Kbytes */
#define ADDR_FLASH_PAGE_39 ( ( uint32_t ) 0x08013800 )  /* Base @ of Page 39, 2 Kbytes */
#define ADDR_FLASH_PAGE_40 ( ( uint32_t ) 0x08014000 )  /* Base @ of Page 40, 2 Kbytes */
#define ADDR_FLASH_PAGE_41 ( ( uint32_t ) 0x08014800 )  /* Base @ of Page 41, 2 Kbytes */
#define ADDR_FLASH_PAGE_42 ( ( uint32_t ) 0x08015000 )  /* Base @ of Page 42, 2 Kbytes */
#define ADDR_FLASH_PAGE_43 ( ( uint32_t ) 0x08015800 )  /* Base @ of Page 43, 2 Kbytes */
#define ADDR_FLASH_PAGE_44 ( ( uint32_t ) 0x08016000 )  /* Base @ of Page 44, 2 Kbytes */
#define ADDR_FLASH_PAGE_45 ( ( uint32_t ) 0x08016800 )  /* Base @ of Page 45, 2 Kbytes */
#define ADDR_FLASH_PAGE_46 ( ( uint32_t ) 0x08017000 )  /* Base @ of Page 46, 2 Kbytes */
#define ADDR_FLASH_PAGE_47 ( ( uint32_t ) 0x08017800 )  /* Base @ of Page 47, 2 Kbytes */
#define ADDR_FLASH_PAGE_48 ( ( uint32_t ) 0x08018000 )  /* Base @ of Page 48, 2 Kbytes */
#define ADDR_FLASH_PAGE_49 ( ( uint32_t ) 0x08018800 )  /* Base @ of Page 49, 2 Kbytes */
#define ADDR_FLASH_PAGE_50 ( ( uint32_t ) 0x08019000 )  /* Base @ of Page 50, 2 Kbytes */
#define ADDR_FLASH_PAGE_51 ( ( uint32_t ) 0x08019800 )  /* Base @ of Page 51, 2 Kbytes */
#define ADDR_FLASH_PAGE_52 ( ( uint32_t ) 0x0801A000 )  /* Base @ of Page 52, 2 Kbytes */
#define ADDR_FLASH_PAGE_53 ( ( uint32_t ) 0x0801A800 )  /* Base @ of Page 53, 2 Kbytes */
#define ADDR_FLASH_PAGE_54 ( ( uint32_t ) 0x0801B000 )  /* Base @ of Page 54, 2 Kbytes */
#define ADDR_FLASH_PAGE_55 ( ( uint32_t ) 0x0801B800 )  /* Base @ of Page 55, 2 Kbytes */
#define ADDR_FLASH_PAGE_56 ( ( uint32_t ) 0x0801C000 )  /* Base @ of Page 56, 2 Kbytes */
#define ADDR_FLASH_PAGE_57 ( ( uint32_t ) 0x0801C800 )  /* Base @ of Page 57, 2 Kbytes */
#define ADDR_FLASH_PAGE_58 ( ( uint32_t ) 0x0801D000 )  /* Base @ of Page 58, 2 Kbytes */
#define ADDR_FLASH_PAGE_59 ( ( uint32_t ) 0x0801D800 )  /* Base @ of Page 59, 2 Kbytes */
#define ADDR_FLASH_PAGE_60 ( ( uint32_t ) 0x0801E000 )  /* Base @ of Page 60, 2 Kbytes */
#define ADDR_FLASH_PAGE_61 ( ( uint32_t ) 0x0801E800 )  /* Base @ of Page 61, 2 Kbytes */
#define ADDR_FLASH_PAGE_62 ( ( uint32_t ) 0x0801F000 )  /* Base @ of Page 62, 2 Kbytes */
#define ADDR_FLASH_PAGE_63 ( ( uint32_t ) 0x0801F800 )  /* Base @ of Page 63, 2 Kbytes */
#define ADDR_FLASH_PAGE_64 ( ( uint32_t ) 0x08020000 )  /* Base @ of Page 64, 2 Kbytes */
#define ADDR_FLASH_PAGE_65 ( ( uint32_t ) 0x08020800 )  /* Base @ of Page 65, 2 Kbytes */
#define ADDR_FLASH_PAGE_66 ( ( uint32_t ) 0x08021000 )  /* Base @ of Page 66, 2 Kbytes */
#define ADDR_FLASH_PAGE_67 ( ( uint32_t ) 0x08021800 )  /* Base @ of Page 67, 2 Kbytes */
#define ADDR_FLASH_PAGE_68 ( ( uint32_t ) 0x08022000 )  /* Base @ of Page 68, 2 Kbytes */
#define ADDR_FLASH_PAGE_69 ( ( uint32_t ) 0x08022800 )  /* Base @ of Page 69, 2 Kbytes */
#define ADDR_FLASH_PAGE_70 ( ( uint32_t ) 0x08023000 )  /* Base @ of Page 70, 2 Kbytes */
#define ADDR_FLASH_PAGE_71 ( ( uint32_t ) 0x08023800 )  /* Base @ of Page 71, 2 Kbytes */
#define ADDR_FLASH_PAGE_72 ( ( uint32_t ) 0x08024000 )  /* Base @ of Page 72, 2 Kbytes */
#define ADDR_FLASH_PAGE_73 ( ( uint32_t ) 0x08024800 )  /* Base @ of Page 73, 2 Kbytes */
#define ADDR_FLASH_PAGE_74 ( ( uint32_t ) 0x08025000 )  /* Base @ of Page 74, 2 Kbytes */
#define ADDR_FLASH_PAGE_75 ( ( uint32_t ) 0x08025800 )  /* Base @ of Page 75, 2 Kbytes */
#define ADDR_FLASH_PAGE_76 ( ( uint32_t ) 0x08026000 )  /* Base @ of Page 76, 2 Kbytes */
#define ADDR_FLASH_PAGE_77 ( ( uint32_t ) 0x08026800 )  /* Base @ of Page 77, 2 Kbytes */
#define ADDR_FLASH_PAGE_78 ( ( uint32_t ) 0x08027000 )  /* Base @ of Page 78, 2 Kbytes */
#define ADDR_FLASH_PAGE_79 ( ( uint32_t ) 0x08027800 )  /* Base @ of Page 79, 2 Kbytes */
#define ADDR_FLASH_PAGE_80 ( ( uint32_t ) 0x08028000 )  /* Base @ of Page 80, 2 Kbytes */
#define ADDR_FLASH_PAGE_81 ( ( uint32_t ) 0x08028800 )  /* Base @ of Page 81, 2 Kbytes */
#define ADDR_FLASH_PAGE_82 ( ( uint32_t ) 0x08029000 )  /* Base @ of Page 82, 2 Kbytes */
#define ADDR_FLASH_PAGE_83 ( ( uint32_t ) 0x08029800 )  /* Base @ of Page 83, 2 Kbytes */
#define ADDR_FLASH_PAGE_84 ( ( uint32_t ) 0x0802A000 )  /* Base @ of Page 84, 2 Kbytes */
#define ADDR_FLASH_PAGE_85 ( ( uint32_t ) 0x0802A800 )  /* Base @ of Page 85, 2 Kbytes */
#define ADDR_FLASH_PAGE_86 ( ( uint32_t ) 0x0802B000 )  /* Base @ of Page 86, 2 Kbytes */
#define ADDR_FLASH_PAGE_87 ( ( uint32_t ) 0x0802B800 )  /* Base @ of Page 87, 2 Kbytes */
#define ADDR_FLASH_PAGE_88 ( ( uint32_t ) 0x0802C000 )  /* Base @ of Page 88, 2 Kbytes */
#define ADDR_FLASH_PAGE_89 ( ( uint32_t ) 0x0802C800 )  /* Base @ of Page 89, 2 Kbytes */
#define ADDR_FLASH_PAGE_90 ( ( uint32_t ) 0x0802D000 )  /* Base @ of Page 90, 2 Kbytes */
#define ADDR_FLASH_PAGE_91 ( ( uint32_t ) 0x0802D800 )  /* Base @ of Page 91, 2 Kbytes */
#define ADDR_FLASH_PAGE_92 ( ( uint32_t ) 0x0802E000 )  /* Base @ of Page 92, 2 Kbytes */
#define ADDR_FLASH_PAGE_93 ( ( uint32_t ) 0x0802E800 )  /* Base @ of Page 93, 2 Kbytes */
#define ADDR_FLASH_PAGE_94 ( ( uint32_t ) 0x0802F000 )  /* Base @ of Page 94, 2 Kbytes */
#define ADDR_FLASH_PAGE_95 ( ( uint32_t ) 0x0802E800 )  /* Base @ of Page 95, 2 Kbytes */
#define ADDR_FLASH_PAGE_96 ( ( uint32_t ) 0x08030000 )  /* Base @ of Page 96, 2 Kbytes */
#define ADDR_FLASH_PAGE_97 ( ( uint32_t ) 0x08030800 )  /* Base @ of Page 97, 2 Kbytes */
#define ADDR_FLASH_PAGE_98 ( ( uint32_t ) 0x08031000 )  /* Base @ of Page 98, 2 Kbytes */
#define ADDR_FLASH_PAGE_99 ( ( uint32_t ) 0x08031800 )  /* Base @ of Page 99, 2 Kbytes */
#define ADDR_FLASH_PAGE_100 ( ( uint32_t ) 0x08032000 ) /* Base @ of Page 100, 2 Kbytes */
#define ADDR_FLASH_PAGE_101 ( ( uint32_t ) 0x08032800 ) /* Base @ of Page 101, 2 Kbytes */
#define ADDR_FLASH_PAGE_102 ( ( uint32_t ) 0x08033000 ) /* Base @ of Page 102, 2 Kbytes */
#define ADDR_FLASH_PAGE_103 ( ( uint32_t ) 0x08033800 ) /* Base @ of Page 103, 2 Kbytes */
#define ADDR_FLASH_PAGE_104 ( ( uint32_t ) 0x08034000 ) /* Base @ of Page 104, 2 Kbytes */
#define ADDR_FLASH_PAGE_105 ( ( uint32_t ) 0x08034800 ) /* Base @ of Page 105, 2 Kbytes */
#define ADDR_FLASH_PAGE_106 ( ( uint32_t ) 0x08035000 ) /* Base @ of Page 106, 2 Kbytes */
#define ADDR_FLASH_PAGE_107 ( ( uint32_t ) 0x08035800 ) /* Base @ of Page 107, 2 Kbytes */
#define ADDR_FLASH_PAGE_108 ( ( uint32_t ) 0x08036000 ) /* Base @ of Page 108, 2 Kbytes */
#define ADDR_FLASH_PAGE_109 ( ( uint32_t ) 0x08036800 ) /* Base @ of Page 109, 2 Kbytes */
#define ADDR_FLASH_PAGE_110 ( ( uint32_t ) 0x08037000 ) /* Base @ of Page 110, 2 Kbytes */
#define ADDR_FLASH_PAGE_111 ( ( uint32_t ) 0x08037800 ) /* Base @ of Page 111, 2 Kbytes */
#define ADDR_FLASH_PAGE_112 ( ( uint32_t ) 0x08038000 ) /* Base @ of Page 112, 2 Kbytes */
#define ADDR_FLASH_PAGE_113 ( ( uint32_t ) 0x08038800 ) /* Base @ of Page 113, 2 Kbytes */
#define ADDR_FLASH_PAGE_114 ( ( uint32_t ) 0x08039000 ) /* Base @ of Page 114, 2 Kbytes */
#define ADDR_FLASH_PAGE_115 ( ( uint32_t ) 0x08039800 ) /* Base @ of Page 115, 2 Kbytes */
#define ADDR_FLASH_PAGE_116 ( ( uint32_t ) 0x0803A000 ) /* Base @ of Page 116, 2 Kbytes */
#define ADDR_FLASH_PAGE_117 ( ( uint32_t ) 0x0803A800 ) /* Base @ of Page 117, 2 Kbytes */
#define ADDR_FLASH_PAGE_118 ( ( uint32_t ) 0x0803B000 ) /* Base @ of Page 118, 2 Kbytes */
#define ADDR_FLASH_PAGE_119 ( ( uint32_t ) 0x0803B800 ) /* Base @ of Page 119, 2 Kbytes */
#define ADDR_FLASH_PAGE_120 ( ( uint32_t ) 0x0803C000 ) /* Base @ of Page 120, 2 Kbytes */
#define ADDR_FLASH_PAGE_121 ( ( uint32_t ) 0x0803C800 ) /* Base @ of Page 121, 2 Kbytes */
#define ADDR_FLASH_PAGE_122 ( ( uint32_t ) 0x0803D000 ) /* Base @ of Page 122, 2 Kbytes */
#define ADDR_FLASH_PAGE_123 ( ( uint32_t ) 0x0803D800 ) /* Base @ of Page 123, 2 Kbytes */
#define ADDR_FLASH_PAGE_124 ( ( uint32_t ) 0x0803E000 ) /* Base @ of Page 124, 2 Kbytes */
#define ADDR_FLASH_PAGE_125 ( ( uint32_t ) 0x0803E800 ) /* Base @ of Page 125, 2 Kbytes */
#define ADDR_FLASH_PAGE_126 ( ( uint32_t ) 0x0803F000 ) /* Base @ of Page 126, 2 Kbytes */
#define ADDR_FLASH_PAGE_127 ( ( uint32_t ) 0x0803E800 ) /* Base @ of Page 127, 2 Kbytes */

#define FLASH_OPERATION_MAX_RETRY 4

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC TYPES ------------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS PROTOTYPES ---------------------------------------------
 */

/*!
 * @brief return the size of one page in flash
 *
 * @return uint16_t Size
 */
uint16_t hal_flash_get_page_size( );

/**
 * @brief Erase a given nb page to the FLASH at the specified address.
 *
 * @param [in] addr FLASH address to start the erase
 * @param [in] nb_page the number of page to erase.
 * @return uint8_t status [SUCCESS, FAIL]
 */
uint8_t hal_flash_erase_page( uint32_t addr, uint8_t nb_page );

/**
 * @brief Writes the given buffer to the FLASH at the specified address.
 *
 * @param [in] addr FLASH address to write to
 * @param [in] buffer Pointer to the buffer to be written.
 * @param [in] size Size of the buffer to be written.
 * @return uint32_t status [Real_size_written, FAIL]
 */
uint32_t hal_flash_write_buffer( uint32_t addr, const uint8_t* buffer, uint32_t size );

/**
 * @brief Reads the FLASH at the specified address to the given buffer.
 *
 * @param [in]  addr    FLASH address to read from
 * @param [out] buffer  Pointer to the buffer to be written with read data.
 * @param [in]  size    Size of the buffer to be read.
 */
void hal_flash_read_buffer( uint32_t addr, uint8_t* buffer, uint32_t size );

#ifdef __cplusplus
}
#endif

#endif  // __SMTC_HAL_FLASH_H__

/* --- EOF ------------------------------------------------------------------ */
