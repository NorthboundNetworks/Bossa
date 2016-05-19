# BOSSA

This is a derivative of ShumaTech's BOSSA software
([web](http://www.shumatech.com/web/products/bossa),
[GitHub](https://github.com/shumatech/BOSSA)). Maintenance of that
project appears to have been abandoned. As a result this software was
taken from Debian Science Maintainers'
[repository](http://anonscm.debian.org/cgit/debian-science/packages/bossa.git).

## Version numbering

The version numbering of the software is problematic. The
[README](https://raw.githubusercontent.com/shumatech/BOSSA/master/README)
of the ShumaTech claims to be version 1.2. However the highest tag in the
repository claims 1.6.1-arduino.

Debian claims 1.3, although perhaps that was simply an increment of
1.2 to avoid an era bump.

I am inclined to claim 2.0, not for any huge rise in functionality,
but to avoid any possible confusion with the ShumaTech software.

## Release notes

### 2.0 vk5tu

### 1.3 Debian

bossa (1.3~20120408-5) unstable; urgency=low

  [ Olly Betts ]
  * Update to use wxWidgets 3.0 (new patch: wx3.0-compat.patch)
    Closes: #751554
  * debian/control: Fix typo in bossa package description.

 -- Scott Howard <showard@debian.org>  Sun, 15 Jun 2014 20:53:24 -0400

bossa (1.3~20120408-4) unstable; urgency=low

  * Updated bossac manpage, thanks to Karl Lenz (Closes: #737280)

 -- Scott Howard <showard@debian.org>  Fri, 07 Mar 2014 11:18:01 -0500

bossa (1.3~20120408-3) unstable; urgency=low

  * Added add-kfreebsd-platform-support.patch
    - addsnkfreebsd support, thanks to Karl Lenz. (Closes: #737278)
  * added no_X11_link.patch
    - removed unused link with lX11, thanks lintian.

 -- Scott Howard <showard@debian.org>  Sat, 01 Feb 2014 12:38:43 -0500

bossa (1.3~20120408-2) unstable; urgency=low

  * Added a series of patches from arduino so bossa works with tose
    devices. Many thanks to Karl Lenz for compiling Cristian Maglie's
    patches.
    -   debian/patches/add-reset-command.patch
        debian/patches/allow-autoreset.patch
        debian/patches/flush-after-upload.patch
        debian/patches/override-usb-autodetection.patch
        debian/patches/uart-set-speed.patch

 -- Scott Howard <showard@debian.org>  Wed, 29 Jan 2014 21:58:43 -0500


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
