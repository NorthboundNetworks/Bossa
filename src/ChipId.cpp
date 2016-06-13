// ChipId.cpp
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


// Atmel systems-on-chip have a chip identification register,
// CHIPID_CIDR. This encodes a great deal of information which can be
// extracted by applying bit-masks. Unfortunately Atmel ran out of
// bits to code the processor ID itself. As a response with the
// SAM4-series Atmel added an extension register,
// CHIPID_EXID. Fortunately CHIPID_EXID is readable on the earlier
// processors and has value 0.
//
// This object contains both CHIPID_CIDR -- shorn of its extraneous
// fields -- and CHIPID_EXID. It allows Bossa to be simply upgraded
// from using only CHIPID_CIDR to using (CHIPID_CIDR, CHIPID_EXID).

#include <stdint.h>
#include <string.h>
#include <sstream>
#include <iomanip>
using namespace std;

#include "ChipId.h"


ChipId::ChipId(uint32_t in_cidr,
               uint32_t in_exid) {
    set(in_cidr, in_exid);
}

void ChipId::set(uint32_t in_cidr) {
    set(in_cidr, 0);
}

void ChipId::set(uint32_t in_cidr,
                 uint32_t in_exid) {
    cidr = in_cidr;
    exid = in_exid;
}


// It makes sense to ask if a ChipId is equal or not equal.  Not
// sure there's much sense in asking if a ChipId is less than or
// otherwise ordered.

bool ChipId::operator==(const ChipId& right) const {
    return (cidr == right.cidr) &&
           (exid == right.exid);
}

bool ChipId::operator!=(const ChipId& right) const {
    return !(cidr == right.cidr &&
             exid == right.exid);
}

// Comparison to a number is handy for porting code written  prior to
// extended IDs. That code read
//   chipId == 0x12345678
// Of course there must be no CHIPID_EXID for such a comparison to
// succeed.
// Existing code had lines like
//   chipId() != 0x285e0a60
// so the definition of != is false if there is no CHIPID_EXID.

bool ChipId::operator==(const uint32_t right) const {
    return (exid == 0 && cidr == right);
}

bool ChipId::operator!=(const uint32_t right) const {
    return (exid != 0 || cidr != right);
}

// Decode bit-fields in CHIPIDs
#define EXTRACT(var, lsb, mask) (((var) >> (lsb)) & (mask))

uint32_t ChipId::version() const {
    return EXTRACT(cidr,
                   CHIPID_CIDR_VERSION_LSB,
                   CHIPID_CIDR_VERSION_MASK);
}

uint8_t ChipId::eproc() const {
    return EXTRACT(cidr,
                   CHIPID_CIDR_EPROC_LSB,
                   CHIPID_CIDR_EPROC_MASK);
}

uint32_t ChipId::nvpsiz() const {
    return EXTRACT(cidr,
                   CHIPID_CIDR_NVPSIZ_LSB,
                   CHIPID_CIDR_NVPSIZ_MASK);
}

uint32_t ChipId::nvpsiz2() const {
    return EXTRACT(cidr,
                   CHIPID_CIDR_NVPSIZ2_LSB,
                   CHIPID_CIDR_NVPSIZ2_MASK);
}

uint32_t ChipId::sramsiz() const {
    return EXTRACT(cidr,
                   CHIPID_CIDR_SRAMSIZ_LSB,
                   CHIPID_CIDR_SRAMSIZ_MASK);
}

uint8_t ChipId::arch() const {
    return EXTRACT(cidr,
                   CHIPID_CIDR_ARCH_LSB,
                   CHIPID_CIDR_ARCH_MASK);
}

uint32_t ChipId::nvptyp() const {
    return EXTRACT(cidr,
                   CHIPID_CIDR_NVPTYP_LSB,
                   CHIPID_CIDR_NVPTYP_MASK);
}

// Extension register exists
bool ChipId::ext() const {
    return (1 == EXTRACT(cidr,
                         CHIPID_CIDR_VERSION_LSB,
                         CHIPID_CIDR_VERSION_MASK));
}

uint32_t ChipId::package_type() const {
    return EXTRACT(exid,
                   CHIPID_EXID_PACKAGE_TYPE_LSB,
                   CHIPID_EXID_PACKAGE_TYPE_MASK);
}

uint32_t ChipId::flash_size() const {
    return EXTRACT(exid,
                   CHIPID_EXID_FLASH_SIZE_LSB,
                   CHIPID_EXID_FLASH_SIZE_MASK);
}

uint32_t ChipId::product_number() const {
    return EXTRACT(exid,
                   CHIPID_EXID_PRODUCT_NUMBER_LSB,
                   CHIPID_EXID_PRODUCT_NUMBER_MASK);
}

// Give a CHIPID_CIDR suitable for identifying this model.
// So mask out EXT and VERSION.
uint32_t ChipId::identity() const {
    // Exclude EXT and VERSION
    return cidr & 0x7fffffe0;
}

// Return string representation
std::string ChipId::str() const {
    std::stringstream s;
    std::ios_base::fmtflags original_flags = s.flags();
    s.setf(ios_base::hex, ios_base::basefield);
    s.setf(ios_base::showbase);
    s << cidr;
    if (this->ext() || exid != 0) {
        s << "," << std::setw(8) << exid;
    }
    s.flags(original_flags);
    return s.str();
}


const char* ChipId::c_str() const {
    std::string s = ChipId::str();
    return s.c_str();
}
