// ChipId.h
//
// Written for Bossa <https://github.com/NorthboundNetworks/Bossa>.
// Copyright (C) Glen Turner, 2016. <http://www.gdt.id.au/~gdt/>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef CHIPID_H
#define CHIPID_H

#include <stdint.h>
#include <string>

// Information from datasheet.

// Version
// Location
#define CHIPID_CIDR_VERSION_LSB 0
#define CHIPID_CIDR_VERSION_MASK 0xf

// Embedded processor
// Location
#define CHIPID_CIDR_EPROC_LSB 5
#define CHIPID_CIDR_EPROC_MASK 0x7
// Values
// SAM x7
#define CHIPID_CIDR_EPROC_SAMX7 0
#define CHIPID_CIDR_EPROC_ARM946ES 1
#define CHIPID_CIDR_EPROC_ARM7TDMI 2
// Cortex-M3
#define CHIPID_CIDR_EPROC_CM3 3
#define CHIPID_CIDR_EPROC_ARM920T 4
#define CHIPID_CIDR_EPROC_ARM926EJS 5
// Cortex-A5
#define CHIPID_CIDR_EPROC_CA5 6
// Cortex-M4
#define CHIPID_CIDR_EPROC_CM4 7

// Non-volatile program memory size
// Location
#define CHIPID_CIDR_NVPSIZ_LSB 8
#define CHIPID_CIDR_NVPSIZ_MASK 0xf
// Values
#define CHIPID_CIDR_NVPSIZ_NONE 0
#define CHIPID_CIDR_NVPSIZ_8K 1
#define CHIPID_CIDR_NVPSIZ_16K 2
#define CHIPID_CIDR_NVPSIZ_32K 3
#define CHIPID_CIDR_NVPSIZ_64K 5
#define CHIPID_CIDR_NVPSIZ_128K 7
#define CHIPID_CIDR_NVPSIZ_160K 8
#define CHIPID_CIDR_NVPSIZ_256K 9
#define CHIPID_CIDR_NVPSIZ_512K 10
#define CHIPID_CIDR_NVPSIZ_1024K 12
#define CHIPID_CIDR_NVPSIZ_2048K 14

// Second non-volatile program memory size
// Location
#define CHIPID_CIDR_NVPSIZ2_LSB 12
#define CHIPID_CIDR_NVPSIZ2_MASK 0xf
// Values
#define CHIPID_CIDR_NVPSIZ2_NONE 0
#define CHIPID_CIDR_NVPSIZ2_8K 1
#define CHIPID_CIDR_NVPSIZ2_16K 2
#define CHIPID_CIDR_NVPSIZ2_32K 3
#define CHIPID_CIDR_NVPSIZ2_64K 5
#define CHIPID_CIDR_NVPSIZ2_128K 7
#define CHIPID_CIDR_NVPSIZ2_256K 9
#define CHIPID_CIDR_NVPSIZ2_512K 10
#define CHIPID_CIDR_NVPSIZ2_1024K 12
#define CHIPID_CIDR_NVPSIZ2_2048K 14

// Internal SRAM size
// Location
#define CHIPID_CIDR_SRAMSIZ_LSB 16
#define CHIPID_CIDR_SRAMSIZ_MASK 0xf
// Values
#define CHIPID_CIDR_SRAMSIZ_48K 0
#define CHIPID_CIDR_SRAMSIZ_192K 1
#define CHIPID_CIDR_SRAMSIZ_384K 2
#define CHIPID_CIDR_SRAMSIZ_6K 3
#define CHIPID_CIDR_SRAMSIZ_24K 4
#define CHIPID_CIDR_SRAMSIZ_80K 6
#define CHIPID_CIDR_SRAMSIZ_160K 7
#define CHIPID_CIDR_SRAMSIZ_8K 8
#define CHIPID_CIDR_SRAMSIZ_16K 9
#define CHIPID_CIDR_SRAMSIZ_32K 10
#define CHIPID_CIDR_SRAMSIZ_64K 11
#define CHIPID_CIDR_SRAMSIZ_128K 12
#define CHIPID_CIDR_SRAMSIZ_256K 13
#define CHIPID_CIDR_SRAMSIZ_96K 14
#define CHIPID_CIDR_SRAMSIZ_512K 15

// Architecture identifier
// Location
#define CHIPID_CIDR_ARCH_LSB 20
#define CHIPID_CIDR_ARCH_MASK 0xff
// Values
// SAM4E series
#define CHIPID_CIDR_ARCH_SAM4E 0x3c

// Nonvolatile program memory type
// Location
#define CHIPID_CIDR_NVPTYP_LSB 28
#define CHIPID_CIDR_NVPTYP_MASK 0x7
// Values
// ROM
#define CHIPID_CIDR_NVPTYP_ROM 0
// ROMless or on-chip flash
#define CHIPID_CIDR_NVPTYP_ROMLESS 1
// Extended flash memory
#define CHIPID_CIDR_NVPTYP_FLASH 2
// Rom and embedded flash memory
// - NVPSIZ is ROM size
// - NVPSIZ2 is flash size
#define CHIPID_CIDR_NVPTYP_ROM_FLASH 3
// SRAM emulating ROM
#define CHIPID_CIDR_NVPTYP_SRAM 4

// Extension register exists
// Location
#define CHIPID_CIDR_EXT_LSB 31
#define CHIPID_CIDR_EXT_MASK 0x1

// Package type
// Location
#define CHIPID_EXID_PACKAGE_TYPE_LSB 0
#define CHIPID_EXID_PACKAGE_TYPE_MASK 0x3
// Values
// Package 144
#define CHIPID_EXID_PACKAGE_TYPE_144 0
// Package 100
#define CHIPID_EXID_PACKAGE_TYPE_100 1

// Flash size
// Location
#define CHIPID_EXID_FLASH_SIZE_LSB 2
#define CHIPID_EXID_FLASH_SIZE_MASK 0x3
// Values
#define CHIPID_EXID_FLASH_SIZE_1024K 0
#define CHIPID_EXID_FLASH_SIZE_512K 2

// Product number
// Location
#define CHIPID_EXID_PRODUCT_NUMBER_LSB 5
#define CHIPID_EXID_PRODUCT_NUMBER_MASK 0x0000f000
// Values
// 0x0012_020 SAM4E product series
#define CHIPID_EXID_PRODUCT_NUMBER_SAM4E 0x00120020


class ChipId {
    uint32_t cidr;
    uint32_t exid;
 public:
    ChipId(uint32_t cidr = 0,
           uint32_t exid = 0);
    void set(uint32_t cidr);
    void set(uint32_t cidr,
             uint32_t exid);
    bool operator==(const ChipId& right) const;
    bool operator==(const uint32_t right) const;
    bool operator!=(const ChipId& right) const;
    bool operator!=(const uint32_t right) const;
    uint32_t version() const;
    uint8_t eproc() const;
    uint32_t nvpsiz() const;
    uint32_t nvpsiz2() const;
    uint32_t sramsiz() const;
    uint8_t arch() const;
    uint32_t nvptyp() const;
    bool ext() const;
    uint32_t package_type() const;
    uint32_t flash_size() const;
    uint32_t product_number() const;
    uint32_t identity() const;
    std::string str() const;
    const char *c_str() const;
};

#endif    // CHIPID_H
