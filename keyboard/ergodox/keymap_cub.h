static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Keymap: Default Layer in QWERTY
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |   ~    |   1  |   2  |   3  |   4  |   5  |   [  |           |   ]  |   6  |   7  |   8  |   9  |   0  |   =    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * | Tab    |   Q  |   W  |   E  |   R  |   T  | ~L1  |           | ~L3  |   Y  |   U  |   I  |   O  |   P  |   '    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | LShift |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | - FN14 |
     * |--------+------+------+------+------+------|  L0  |           | ~L4  |------+------+------+------+------+--------|
     * | LCtrl  |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | \ FN15 |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | ~L1  | ~L2  | Caps | LAlt | LGui |                                       |  Lft |  Up  |  Dn  | Rght | ~L4  |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        | +L2  | Home |       | PgUp | Del  |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |  End |       | PgDn |      |      |
     *                                 | BkSp |  ESC |------|       |------| Enter| Space|
     *                                 |      |      |  Spc |       | Ins  |      |      |
     *                                 `--------------------'       `--------------------'
     *
     *
     *
     ****************************************************************************************************
     *
     * Under XOrg, I use my own mapping from QWERTY to "Workman for Programmers"
     * See XOrg files in ./addons/ subdirectory.
     *
     * I have to do so, because of two things:
     * 1) my native language is Russian, and XOrg keymap for it is based on QWERTY layout
     * 2) I want to have non-standart shifted keys, like $ (as normal) and @ (as shifted), or _ and -
     *
     * And even if (2) could be solved using FN* keys (but there is limit in firmware for only 32 such
     * keys), then (1) can't be solved at firmware level at all.
     *
     * So, I have to stick with QWERTY as my main layout + my own XOrg keyboard layout for English.
     * But sometimes I have to input something when XOrg is not active - for example, in Linux console,
     * or in firmware console (while debugging firmware), or when keyboard is connected to not my computer.
     *
     * For such cases I have Layer5 :)
     * // hint: switch to Layer5 is only at Layer4
     *
     ****************************************************************************************************
     *
     *
     *
     * Keymap: Default Layer in Workman
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |   ~    |   ;  |   !  |   #  |   {  |   }  |   '  |           |   ^  |   [  |   ]  |   *  |   (  |   )  |   =    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * | Tab    |   Q  |   D  |   R  |   W  |   B  | ~L1  |           | ~L3  |   J  |   F  |   U  |   P  |   $  |   :    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | LShift |   A  |   S  |   H  |   T  |   G  |------|           |------|   Y  |   N  |   E  |   O  |   I  | _ FN14 |
     * |--------+------+------+------+------+------|  L0  |           | ~L4  |------+------+------+------+------+--------|
     * | LCtrl  |   Z  |   X  |   M  |   C  |   V  |      |           |      |   K  |   L  |   ,  |   .  |   /  | | FN15 |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | ~L1  | ~L2  | Caps | LAlt | LGui |                                       |  Lft |  Up  |  Dn  | Rght | ~L4  |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        | +L2  | Home |       | PgUp | Del  |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |  End |       | PgDn |      |      |
     *                                 | BkSp |  ESC |------|       |------| Enter| Space|
     *                                 |      |      |  Spc |       | Ins  |      |      |
     *                                 `--------------------'       `--------------------'
     *
     * Keymap: Default Layer in Workman / with Shift
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |   `    |   1  |   2  |   3  |   4  |   5  |   "  |           |   \  |   6  |   7  |   8  |   9  |   0  |   +    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * | Tab    |   Q  |   D  |   R  |   W  |   B  | ~L1  |           | ~L3  |   J  |   F  |   U  |   P  |   @  |   %    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | LShift |   A  |   S  |   H  |   T  |   G  |------|           |------|   Y  |   N  |   E  |   O  |   I  | - FN14 |
     * |--------+------+------+------+------+------|  L0  |           | ~L4  |------+------+------+------+------+--------|
     * | LCtrl  |   Z  |   X  |   M  |   C  |   V  |      |           |      |   K  |   L  |   ,  |   .  |   /  | & FN15 |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | ~L1  | ~L2  | Caps | LAlt | LGui |                                       |  Lft |  Up  |  Dn  | Rght | ~L4  |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        | +L2  | Home |       | PgUp | Del  |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |  End |       | PgDn |      |      |
     *                                 | BkSp |  ESC |------|       |------| Enter| Space|
     *                                 |      |      |  Spc |       | Ins  |      |      |
     *                                 `--------------------'       `--------------------'
     *
     */

    KEYMAP(  // layout: layer 0: default
        // left hand
        GRV, 1,   2,   3,   4,   5,   LBRC,
        TAB, Q,   W,   E,   R,   T,   FN1,
        FN16,FN20,S,   D,   F,   G,
        LCTL,Z,   X,   C,   FN19,B,   FN0,
        FN1, FN6, CAPS,LALT,FN17,
                                      FN2, HOME,
                                           END,
                                 FN8, FN9, FN10,
        // right hand
             RBRC,6,   7,   8,   9,   0,   EQL,
             FN3, Y,   U,   I,   O,   P,   QUOT,
                  FN18,J,   K,   L,   FN21,FN14,
             FN4, N,   M,   COMM,DOT, SLSH,FN15,
                       LEFT,UP,  DOWN,RGHT,FN4,
        PGUP,DEL,
        PGDN,
        FN11,FN12,FN13
    ),

    KEYMAP(  // layout: layer 1: F-keys instead of numbers
        // left hand
        TRNS,F1,  F2,  F3,  F4,  F5,  F6,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             F7,  F8,  F9,  F10, F11, F12, TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    KEYMAP(  // layout: layer 2: mouse + numpad
        // left hand
        TRNS,NO,  NO,  NO,  NO,  PAUS,PSCR,
        TRNS,WH_L,WH_U,WH_D,WH_R,BTN2,TRNS,
        TRNS,MS_L,MS_U,MS_D,MS_R,BTN1,
        TRNS,NO,  NO,  NO,  TRNS,BTN3,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             SLCK,NLCK,PSLS,PAST,PAST,PMNS,BSPC,
             TRNS,NO,  P7,  P8,  P9,  PMNS,BSPC,
                  TRNS,P4,  P5,  P6,  PPLS,PENT,
             TRNS,NO,  P1,  P2,  P3,  PPLS,PENT,
                       P0,  PDOT,SLSH,PENT,PENT,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    KEYMAP(  // layout: layer 3: F-keys only
        // left hand
        TRNS,NO,  NO,  NO,  NO,  NO,  NO,
        TRNS,F13, F14, F15, F16, NO,  TRNS,
        TRNS,F17, F18, F19, F20, NO,
        TRNS,F21, F22, F23, F24, NO,  TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             NO,  NO,  NO,  NO,  NO,  NO,  TRNS,
             TRNS,NO,  F1,  F2,  F3,  F4,  TRNS,
                  NO,  F5,  F6,  F7,  F8,  TRNS,
             TRNS,NO,  F9,  F10, F11, F12, TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    KEYMAP(  // layout: layer 4: F-keys + cursor
        // left hand
        TRNS,F1,  F2,  F3,  F4,  F5,  F6,
        FN7, NO,  PGUP,UP,  PGDN,PGUP,TRNS,
        TRNS,NO,  LEFT,DOWN,RGHT,PGDN,
        TRNS,NO,  NO,  END, HOME,NO,  TRNS,
        FN5, TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             F7,  F8,  F9,  F10, F11, F12, MINS,
             TRNS,PGUP,PGUP,UP,  PGDN,NO,  FN7,
                  PGDN,LEFT,DOWN,RGHT,NO,  TRNS,
             TRNS,NO,  HOME,END, NO,  NO,  TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    KEYMAP(  // layout: layer 5: Workman layout
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,Q,   D,   R,   W,   B,   TRNS,
        TRNS,A,   S,   H,   T,   G,
        TRNS,Z,   X,   M,   C,   V,   TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,J,   F,   U,   P,   4,   TRNS,
                  Y,   N,   E,   O,   I,   TRNS,
             TRNS,K,   L,   TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    KEYMAP(  // layout: layer 6: F-keys on home+1 row
        // left hand
        TRNS,NO,  NO,  NO,  NO,  NO,  NO,
        TRNS,F1,  F2,  F3,  F4,  F5,  F11,
        TRNS,TRNS,NO,  NO,  NO,  NO,
        TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
        TRNS,TRNS,TRNS,LALT,LGUI,
                                      TRNS,TRNS,
                                           TRNS,
                                 LCTL,LSFT,TRNS,
        // right hand
             NO,  NO,  NO,  NO,  NO,  NO,  TRNS,
             F12, F6,  F7,  F8,  F9,  F10, PGUP,
                  NO,  NO,  NO,  NO,  TRNS,PGDN,
             TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
                       RGUI,RALT,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,RSFT,RCTL
    ),

/*
    // templates to copy from

    KEYMAP(  // layout: layer N: transparent on edges, all others are empty
        // left hand
        TRNS,NO,  NO,  NO,  NO,  NO,  NO,
        TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
        TRNS,NO,  NO,  NO,  NO,  NO,
        TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
        TRNS,TRNS,TRNS,LALT,LGUI,
                                      TRNS,TRNS,
                                           TRNS,
                                 LCTL,LSFT,TRNS,
        // right hand
             NO,  NO,  NO,  NO,  NO,  NO,  TRNS,
             TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
                  NO,  NO,  NO,  NO,  NO,  TRNS,
             TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
                       RGUI,RALT,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,RSFT,RCTL
    ),
    KEYMAP(  // layout: layer N: fully transparent
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),
*/

};

/* id for user defined functions */
enum function_id {
    TEENSY_KEY,
};

/*
 * Fn action definition
 */
static const uint16_t PROGMEM fn_actions[] = {
    ACTION_LAYER_SET(0, ON_BOTH),                   // FN0 - switch to Layer0
    ACTION_LAYER_MOMENTARY(1),                      // FN1 - push Layer1
    ACTION_LAYER_SET(2, ON_BOTH),                   // FN2 - switch to Layer2
    ACTION_LAYER_MOMENTARY(3),                      // FN3 - push Layer3
    ACTION_LAYER_MOMENTARY(4),                      // FN4 - push Layer4
    ACTION_LAYER_SET(5, ON_BOTH),                   // FN5 - switch to Layer5
    ACTION_LAYER_MOMENTARY(2),                      // FN6 - push Layer2
    ACTION_FUNCTION(TEENSY_KEY),                    // FN7 - Teensy key

    ACTION_MODS_TAP_KEY(MOD_LCTL, KC_BSPC),         // FN8  = LShift with tap BackSpace
    ACTION_MODS_TAP_KEY(MOD_LSFT, KC_ESC),          // FN9  = LCtrl with tap Escape
    ACTION_MODS_TAP_KEY(MOD_LALT, KC_SPC),          // FN10 = LAlt with tap Space
    ACTION_MODS_TAP_KEY(MOD_RALT, KC_INS),          // FN11 = RAlt with tap Ins
    ACTION_MODS_TAP_KEY(MOD_RSFT, KC_ENT),          // FN12 = RShift with tap Enter
    ACTION_MODS_TAP_KEY(MOD_RCTL, KC_SPC),          // FN13 = RCtrl with tap Space
    ACTION_MODS_TAP_KEY(MOD_RSFT, KC_MINS),         // FN14 = RShift with tap Enter
    ACTION_MODS_TAP_KEY(MOD_RCTL, KC_BSLS),         // FN15 = RCtrl with tap Space
    ACTION_MODS_TAP_KEY(MOD_LSFT, KC_TAB),          // FN16 = LShift with tap Tab
    ACTION_MODS_TAP_KEY(MOD_LGUI, KC_ESC),          // FN17 = LShift with tap Tab

    ACTION_LAYER_TAP_KEY(2, KC_H),                  // FN18 = L2 symbols on J key, to use with Mouse keys
    ACTION_LAYER_TAP_KEY(2, KC_V),                  // FN19 = L2 symbols on V key, to use with Numpad keys
    ACTION_LAYER_TAP_KEY(6, KC_A),                  // FN20 = L6 symbols on A key, to use with F* keys
    ACTION_LAYER_TAP_KEY(6, KC_SCLN),               // FN21 = L6 symbols on ; key, to use with F* keys
};

void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
    print("action_function called\n");
    print("id  = "); phex(id); print("\n");
    print("opt = "); phex(opt); print("\n");
    if (id == TEENSY_KEY) {
        clear_keyboard();
        print("\n\nJump to bootloader... ");
        _delay_ms(250);
        bootloader_jump(); // should not return
        print("not supported.\n");
    }
}

