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
