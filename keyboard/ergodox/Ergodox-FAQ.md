Firmware
========

Q: Where to get binaries?
A:

Q: Where to get sources?
A:

Q: How to compile?
A:


Layouts
=======

description of layouts in base firmware binaries


Things TO-DO
============
- Flash NumLock led only when "numpad" layer is active
- Command (in terms of IS_COMMAND) to switch to no-leds mode
- Increase count of ACTION keys
- Fix command_state() onboard led: it should flash only when kbd in some specific mode (CONSOLE || MOUSE)
- ergodox_blink_all_leds() should save current state of leds, and restore after blink. initial state of all leds == off
- add support for pseudo-backlight (reversed LEDs) + docs/photo
- command to debug all LEDs (on/off/blink)
- proper (in-core) implementation of DEBUG_MATRIX_SCAN_RATE (non-Ergodox specific)
- proper (in-core) support for per-layer fn_actions[]

