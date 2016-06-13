# Exposition

An exploration of various technologies relevant to the Bossa code.

# The SAM-BA ROM monitor

The SAM-BA ROM monitor runs when the Atmel SAM system-on-chip is
booted from ROM.

The ROM monitor has just enough function to be able to copy a program
to flash.

The ROM monitor is designed to be operated by a front-end program. It
is barely possible to operate the ROM monitor from a terminal
emulator; setting the register to boot next from flash is about as
much as can be tolerated.

## Connecting

The ROM monitor appears on both the UART0 RS-232 port (115,200bps, 8,
N, 1, no handshaking or control signals) and the USB bus (as a
Communications Device Class modem with PID:VID 0x03eb:0x6124).

Whichever port is available first is the only port the ROM monitor
will listen to for further commands. To indicate that the RS-232 port
available type `#`.


## Commands

Characters are not remotely echoed.

No carriage return is required after `#`.

Entered hexadecimal values have no leading `0x` or `:` between
half-words or any other decoration. Leading zeroes are accepted.

Upon an error there is no output.

### # — print prompt

Typing `#` alone has no effect. In both terminal mode and binary mode
the `>` prompt is printed.

### N — set normal mode

`N#`

Display data in binary. No prompt is displayed.

### T — set terminal  mode

`T#`

Display data in ASCII format. When a new command is expected a `>`
prompt is printed. Printed values are in hexadecimal prefixed by
`0x`. Entered hexadecimal values do not have any prefix.

### O — write byte to RAM memory or register

`O` *address* `,` *value* `#`

Write 8-bit *value* to the byte at 32-bit *address*.

*address* and *value* are hexadecimal text.

### o — read byte

`o` *address* `,#`

Read the 8-bit byte at 32-bit *address*.

*address* is hexadecimal text.

In binary mode the byte is displayed in binary.

In terminal mode the byte is displayed as hexadecimal text. For
example, `o00000000#` prints

```
0x00
```

### H — write half-word to RAM memory or register

`H` *address* `,` *value* `#`

Write 16-bit *value* to the half-word at 32-bit *address*.

*address* and *value* are hexadecimal text.

### h — read half-word

`h` *address* `,#`

Read the 16-bit half-word at 32-bit *address*.

*address* is hexadecimal text.

In binary mode the half-word is displayed in binary, starting with the
least significant byte.

In terminal mode the half-word is displayed as hexadecimal text with a
leading `0x`. For example, `h00000000#` prints

```
0x800
```

### W — write word to RAM memory or register

`W` *address* `,` *value* `#`

Write 32-bit *value* to the word at 32-bit *address*.

*address* and *value* are hexadecimal text.

### w — read word

`w` *address* `,#`

Read the 32-bit word at 32-bit *address*.

*address* is hexadecimal text.

In binary mode the word is displayed in binary, starting with the
least significant byte.

In terminal mode the word is displayed as hexadecimal text with a
leading `0x`. For example, `w00000000#` prints

```
0x20000800
```

### S — send file to memory, Host → RAM memory

`S` *address* `,#`

Take the file presented over the X-modem protocol, loading it into
RAM memory starting from *address*.

*address* is hexadecimal text.

### R — receive file from memory, ROM/RAM/flash memory → Host

`R` *address* `,` *byte_count* `#`

Transmit the memory starting from *address* for *byte_count* bytes
using the X-modem protocol.

*address* and *byte_count* are hexadecimal text.

The X-modem protocol initialises and times out very quickly. Too
quickly to use this feature manually from a terminal emulator. Upon
timeout or completion a `>` is printed.

### G — go

`G` *address* `#`

Execute code at *address*.

*address* is hexadecimal text.

### V — version

`V#`

The version of the ROM monitor is displayed in ASCII text. For example
`V#` prints:

```
v1.0 May 10 2012 18:12:25
```

## Known errata

### `R` using USB

The SAM firmware has a bug reading powers of 2 over 32 bytes via USB.
If that is the case, then read the first byte with `o` and then read
one less than the requested size using `R`.

### `S` using USB

The SAM firmware has a bug that if the command and X-modem binary data
are received in the same USB data packet, then the firmware gets
confused. Some operating systems will coalesce these into once USB
packet, and will need some mechanism to force the `S` to be sent in
its own USB packet.

## Futher information

See the chapter "SAM-BA Boot Program for SAM4E Microcontrollers" in
the SAM4E
[datasheet](http://www.atmel.com/products/microcontrollers/arm/sam4e.aspx?tab=documents).

# Chip identification — CHIPID_CIDR and CHIPID_EXID

The Atmel systems-on-chip have a register which allows the attributes
of the chip to be queried, and this indirectly gives the model of the
chip. This register is named `CHIPID_CIDR`.

That register has run out of space to describe newer models. An
extension register — `CHIPID_EXID` — is defined. That register is 0 if
read on earlier chips lacking `CHIPID_EXID`. When `CHIPID_EXID` is
valid, `CHIPID_CIDR.EXT` is 1. The extension register directly encodes
models rather than their attributes.

## CHIPID_CIDR

| Bit | Name      | Function                               |
|-----|-----------|----------------------------------------|
| MSB |           |                                        |
|  31 | `EXT`     | Extension register exists              |
|  30 | `NVPTYP`  | Nonvolatile program memory type        |
|  29 | `NVPTYP`  |                                        |
|  28 | `NVPTYP`  |                                        |
|  27 | `ARCH`    | Architecture                           |
|  26 | `ARCH`    |                                        |
|  25 | `ARCH`    |                                        |
|  24 | `ARCH`    |                                        |
|  23 | `ARCH`    |                                        |
|  22 | `ARCH`    |                                        |
|  21 | `ARCH`    |                                        |
|  20 | `ARCH`    |                                        |
|  19 | `SRAMSIZ` | Internal static RAM size               |
|  18 | `SRAMSIZ` |                                        |
|  17 | `SRAMSIZ` |                                        |
|  16 | `SRAMSIZ` |                                        |
|  15 | `NVPSIZ2` | Second nonvolatile program memory size |
|  14 | `NVPSIZ2` |                                        |
|  13 | `NVPSIZ2` |                                        |
|  12 | `NVPSIZ2` |                                        |
|  11 | `NVPSIZ`  | Nonvolatile program memory size        |
|  10 | `NVPSIZ`  |                                        |
|   9 | `NVPSIZ`  |                                        |
|   8 | `NVPSIZ`  |                                        |
|   7 | `EPROC`   | Embedded processor                     |
|   6 | `EPROC`   |                                        |
|   5 | `EPROC`   |                                        |
|   4 | `VERSION` | Version of the device                  |
|   3 | `VERSION` |                                        |
|   2 | `VERSION` |                                        |
|   1 | `VERSION` |                                        |
|   0 | `VERSION` |                                        |
| LSB |                                                    |

For a worked example, on the SAM4E8E `CHIPID_CIDR` is at 0x400e0740
and has value 0xa3cc0ce0:

| Field     | Hex  | Meaning                |
|-----------|------|------------------------|
| `EXT`     |  0x1 | `CHIPID_EXID` is valid |
| `NVPTYP`  |  0x2 | Flash exists           |
| `ARCH`    | 0x3c | SAM4                   |
| `SRAMSIZ` |  0xc | 128KB static RAM       |
| `NVPSIZ2` |  0x0 | No second flash bank   |
| `NVPSIZ`  |  0xc | 1024KB flash           |
| `EPROC`   |  0x7 | Cortex-M4              |
| `VERSION` |  0x0 | Version 0              |

## CHIPID_EXID

If `CHIPID_CIDR.EXT` == 0 then `CHIPID_EXID` == 0.

If `CHIPID_CIDR.EXT` == 1 then the fields of `CHIPID_EXID` are:

| Bit | Name           | Function                |
|-----|----------------|-------------------------|
| MSB |                |                         |
|  31 | `PRODUCT_ID`   | Product identifier      |
|  30 | `PRODUCT_ID`   |                         |
|  29 | `PRODUCT_ID`   |                         |
|  28 | `PRODUCT_ID`   |                         |
|  27 | `PRODUCT_ID`   |                         |
|  26 | `PRODUCT_ID`   |                         |
|  25 | `PRODUCT_ID`   |                         |
|  24 | `PRODUCT_ID`   |                         |
|  23 | `PRODUCT_ID`   |                         |
|  22 | `PRODUCT_ID`   |                         |
|  21 | `PRODUCT_ID`   |                         |
|  20 | `PRODUCT_ID`   |                         |
|  19 | `PRODUCT_ID`   |                         |
|  18 | `PRODUCT_ID`   |                         |
|  17 | `PRODUCT_ID`   |                         |
|  16 | `PRODUCT_ID`   |                         |
|  15 | `PRODUCT_ID`   |                         |
|  14 | `PRODUCT_ID`   |                         |
|  13 | `PRODUCT_ID`   |                         |
|  12 | `PRODUCT_ID`   |                         |
|  11 | `PRODUCT_ID`   |                         |
|  10 | `PRODUCT_ID`   |                         |
|   9 | `PRODUCT_ID`   |                         |
|   8 | `PRODUCT_ID`   |                         |
|   7 | `PRODUCT_ID`   |                         |
|   6 | `PRODUCT_ID`   |                         |
|   5 | `PRODUCT_ID`   |                         |
|   4 | `FLASH_SIZE`   |                         |
|   3 | `FLASH_SIZE`   | Flash memory size       |
|   2 | `FLASH_SIZE`   |                         |
|   1 | `PACKAGE_TYPE` | Semiconductor packaging |
|   0 | `PACKAGE_TYPE` |                         |
| LSB |                |                         |

For a worked example, on the SAM4E8E `CHIPID_EXID` is at 0x400e0744
and has value 0x120209:

| Field          | Hex     | Meaning         |
|----------------|---------|-----------------|
| `PRODUCT_ID`   | 0x12020 | SAM4E series    |
| `FLASH_SIZE`   |     0x2 | 512KB           |
| `PACKAGE_TYPE` |     0x1 | 100-pin package |

## Known errata

### `PRODUCT_ID` representation

`CHIPID_EXID.PRODUCT_ID` is assembled as if it occupies bits 3 to 31,
with the least significant bit always zero. That's a little weird, but
it seems to be the only way to get the same values as in Atmel's
documentation.

## Futher information

See the chapter "Chip identifier (CHIPID)" in the SAM4E
[datasheet](http://www.atmel.com/products/microcontrollers/arm/sam4e.aspx?tab=documents).
