# Bossa

## Why?

When booted from ROM Atmel's SAM-series systems-on-chip run a simple
ROM monitor named ‘SAM-BA’ (“SAM Boot Assistant”). This monitor can
read and alter memory, transfer data, and run a program.

Those functions can be used to transfer a file across RS-232 or USB
and, to write that file into flash, and to change the boot options to
start from flash.

Atmel distribute a graphical client program for the SAM-BA ROM
monitor, confusingly also named ‘SAM-BA’. That client program makes
flashing the SoC a matter of pressing buttons rather than typing hex
codes into a ROM monitor. The SAM-BA client is available as a binary
download for Windows and Linux running on the x86 and AMD64 CPU
architectures.

Bossa also implements a client program for the SAM-BA ROM
monitor. This program is licensed to you under the GNU General Public
License version 3 or later. Bossa is available for a wider range of
operating systems: Windows, Linux, MacOS and FreeBSD running on any of
their supported CPUs where you care to compile the C++ source code.


## History

This is a derivative of ShumaTech's BOSSA software
([web](http://www.shumatech.com/web/products/bossa),
[GitHub](https://github.com/shumatech/BOSSA)). Maintenance of that
project appears to have been abandoned. As a result this software was
taken from Debian Science Maintainers'
[repository](http://anonscm.debian.org/cgit/debian-science/packages/bossa.git).

The aim is to add support for the
[Zodiac FX](http://northboundnetworks.com/products/zodiac-fx)
OpenFlow switch. This is a SAM4-based board designed and sold by
[Northbound Networks](http://northboundnetworks.com/).

## Status

This software is not yet complete. The remaining work programme can be
found in the
[open issues with the ‘enhancement’ tag](https://github.com/NorthboundNetworks/Bossa/issues?utf8=%E2%9C%93&q=is%3Aopen+label%3Aenhancement+-label%3Awontfix+).

## Reporting issues and success

Please report bugs by
[searching GitHub's issue tracker](https://github.com/NorthboundNetworks/Bossa/issues?utf8=%E2%9C%93&q=is%3Aissue)
and adding a comment. Even simple ‘me too’ comments are valuable. If
there is no good match then
[create a new bug report](https://github.com/NorthboundNetworks/Bossa/issues/new?labels=bug).

It is impossible for the developers to own a wide enough range of
Atmel systems to cover all of the systems which Bossa claims to
support. Therefore we need your reports of success as well as reports
of failure. Look up the exact model of your system-on-chip, such as
‘SAM4E8C’ (which might also be known as ‘ATSAM4E8C-AU’ or
‘at91sam4e8-ek’). Search for a
[matching success report](https://github.com/NorthboundNetworks/Bossa/issues?utf8=%E2%9C%93&q=is%3Aissue+is%3Aclosed+label%3Asuccess)
and append a comment (don't re-open the ticket, all success reports
are closed). If there is no match for your model then
[create a new success report](https://github.com/NorthboundNetworks/Bossa/issues/new?labels=success).
Use the model, in capitals as above, as the name of the ‘issue’.

## Version numbering

The version numbering of Bossa is problematic. The
[README](https://raw.githubusercontent.com/shumatech/BOSSA/master/README)
of the distribution by ShumaTech claims to be version 1.2. However the
highest tag in the ShumaTech repository claims version 1.6.1-arduino.

Debian claims version 1.3, although perhaps that was simply an
increment of 1.2 to avoid an era bump, rather than evidence of a 1.3
release by ShumaTech.

I am inclined to claim version 2.0, not for any huge rise in
functionality, but to avoid the further confusion which would result
from claiming version 1.7.

## Contributing

Contributors are welcome.

The
[exposition](https://github.com/NorthboundNetworks/Bossa/blob/master/exposition.md)
describes the technology the code works with.

The simplest way to have your code incorporated is to use GitHub: fork
the
[NorthboundNetworks/Bossa](https://github.com/NorthboundNetworks/Bossa/)
repository, commit your changes, and make a
[Pull request](https://github.com/NorthboundNetworks/Bossa/compare).
For the moment, development is done in the ‘master’ branch.  We'll
base the *Release notes* on the text in your pull request.

If using GitHub is not desirable then
[raise an issue tagged as an ‘enhancement’](https://github.com/NorthboundNetworks/Bossa/issues/new?labels=enhancement)
and make a comment containing the patch or the details of how to
access the code. If you are including a patch then please attach it as
a file to prevent GitHub from mangling it.

If this is the first time you have made a pull request or an sent a
patch then we'll also need a statement in the pull request or issue
that “The code I submit meets the requirements of the
[Developer's Certififcate of Origin](https://www.kernel.org/doc/Documentation/SubmittingPatches)”.
This is the same Certificate as used by the Linux kernel.

> Developer's Certificate of Origin 1.1
>
> By making a contribution to this project, I certify that:
>
> (a) The contribution was created in whole or in part by me and I
>     have the right to submit it under the open source license
>     indicated in the file; or
>
> (b) The contribution is based upon previous work that, to the best
>     of my knowledge, is covered under an appropriate open source
>     license and I have the right under that license to submit that
>     work with modifications, whether created in whole or in part
>     by me, under the same open source license (unless I am
>     permitted to submit under a different license), as indicated
>     in the file; or
>
> (c) The contribution was provided directly to me by some other
>     person who certified (a), (b) or (c) and I have not modified
>     it.
>
> (d) I understand and agree that this project and the contribution
>     are public and that a record of the contribution (including all
>     personal information I submit with it, including my sign-off) is
>     maintained indefinitely and may be redistributed consistent with
>     this project or the open source license(s) involved.

## Release notes

### 2.0 Northbound Networks, vk5tu

In progress.

### 1.3 Debian

bossa (1.3~20120408-5) unstable; urgency=low

  [ Olly Betts ]
  * Update to use wxWidgets 3.0 (new patch: wx3.0-compat.patch)
    Closes: #751554
  * debian/control: Fix typo in bossa package description.

  * Scott Howard  Sun, 15 Jun 2014 20:53:24 -0400

bossa (1.3~20120408-4) unstable; urgency=low

  * Updated bossac manpage, thanks to Karl Lenz (Closes: #737280)

  * Scott Howard  Fri, 07 Mar 2014 11:18:01 -0500

bossa (1.3~20120408-3) unstable; urgency=low

  * Added `add-kfreebsd-platform-support.patch`
    - addsnkfreebsd support, thanks to Karl Lenz. (Closes: #737278)
  * added `no_X11_link.patch`
    - removed unused link with lX11, thanks lintian.

  * Scott Howard  Sat, 01 Feb 2014 12:38:43 -0500

bossa (1.3~20120408-2) unstable; urgency=low

  * Added a series of patches from arduino so bossa works with those
    devices. Many thanks to Karl Lenz for compiling Cristian Maglie's
    patches.
    -   `debian/patches/add-reset-command.patch`
    -   `debian/patches/allow-autoreset.patch`
    -   `debian/patches/flush-after-upload.patch`
    -   `debian/patches/override-usb-autodetection.patch`
    -   `debian/patches/uart-set-speed.patch`

  * Scott Howard  Wed, 29 Jan 2014 21:58:43 -0500


### 1.2 Shumatech

New features

* New BOSSA shell command line application to do basic memory, flash,
  and PIO diagnostics

* Workaround for SAM3U firmware bug

* Fixed a bug with setting boot to flash bit on SAM3 devices

Notes

* The OS X USB driver detects an Atmel device as a USB modem.  When
  prompted about a new network interface, click Cancel to continue.

* Some stability issues have been seen with the OS X USB driver using
  BOSSA.  When running BOSSA a second time to the same Atmel device,
  the USB driver can lock up causing BOSSA to freeze.  As a
  workaround, always disconnect and reconnect the Atmel device before
  running BOSSA again.

* The firmware inside of SAM3U devices has a bug where non-word flash
  reads return zero instead of the real data.  BOSSA implements a
  transparent workaround for flash operations that copies flash to
  SRAM before reading.  Direct reads using the BOSSA shell will see
  the bug.

* There are reports that the USB controller in some AMD-based systems
  has difficulty communicating with SAM devices.  The only known
  workaround is to use a different, preferrably Intel-based, system.
