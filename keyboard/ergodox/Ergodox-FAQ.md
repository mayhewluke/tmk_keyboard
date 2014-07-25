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
2. Flash NumLock led only when "numpad" layer is active
3. Command (in terms of IS_COMMAND) to switch to no-leds mode
4. Increase count of ACTION keys
6. Fix command_state() onboard led: it should flash only when kbd in some specific mode (CONSOLE || MOUSE)
7. ergodox_blink_all_leds() should save current state of leds, and restore after blink. initial state of all leds == off
8. add support for pseudo-backlight (reversed LEDs) + docs/photo
9. command to debug all LEDs (on/off/blink)

