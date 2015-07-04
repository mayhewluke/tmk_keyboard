/*
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "keycode.h"
#include "action.h"
#include "action_util.h"
#include "action_code.h"
#include "action_macro.h"
#include "action_layer.h"
#include "bootloader.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"
#include "ergodox.h"

#define SHIFT(key) ACTION(ACT_MODS, (MOD_LSFT << 8) | (key))
#define CTRL(key) ACTION(ACT_MODS, (MOD_LCTL << 8) | (key))
#define ALT(key) ACTION(ACT_MODS, (MOD_LALT << 8) | (key))
#define GUI(key) ACTION(ACT_MODS, (MOD_LGUI << 8) | (key))

extern const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
extern const uint16_t fn_actions[];

/* ErgoDox keymap definition macro */
#define KEYMAP(                                                 \
                                                                \
    /* left hand, spatial positions */                          \
    k00,k01,k02,k03,k04,k05,k06,                                \
    k10,k11,k12,k13,k14,k15,k16,                                \
    k20,k21,k22,k23,k24,k25,                                    \
    k30,k31,k32,k33,k34,k35,k36,                                \
    k40,k41,k42,k43,k44,                                        \
                            k55,k56,                            \
                                k54,                            \
                        k53,k52,k51,                            \
                                                                \
    /* right hand, spatial positions */                         \
        k07,k08,k09,k0A,k0B,k0C,k0D,                            \
        k17,k18,k19,k1A,k1B,k1C,k1D,                            \
            k28,k29,k2A,k2B,k2C,k2D,                            \
        k37,k38,k39,k3A,k3B,k3C,k3D,                            \
                k49,k4A,k4B,k4C,k4D,                            \
    k57,k58,                                                    \
    k59,                                                        \
    k5C,k5B,k5A )                                               \
                                                                \
   /* matrix positions */                                       \
   {                                                            \
    { k00,k10,k20,k30,k40,KC_NO   },   \
    { k01,k11,k21,k31,k41,k51},   \
    { k02,k12,k22,k32,k42,k52},   \
    { k03,k13,k23,k33,k43,k53},   \
    { k04,k14,k24,k34,k44,k54},   \
    { k05,k15,k25,k35,KC_NO,   k55},   \
    { k06,k16,KC_NO,   k36,KC_NO,   k56},   \
                                                                \
    { k07,k17,KC_NO,   k37,KC_NO,   k57},   \
    { k08,k18,k28,k38,KC_NO,   k58},   \
    { k09,k19,k29,k39,k49,k59},   \
    { k0A,k1A,k2A,k3A,k4A,k5A},   \
    { k0B,k1B,k2B,k3B,k4B,k5B},   \
    { k0C,k1C,k2C,k3C,k4C,k5C},   \
    { k0D,k1D,k2D,k3D,k4D,KC_NO   }    \
   }

/* id for user defined functions & macros */
enum function_id {
    TEENSY_KEY,
};

/*
enum macro_id {
};
*/

/* translates key to keycode */
uint16_t actionmap_key_to_action(uint8_t layer, keypos_t key)
{
  return pgm_read_word(&keymaps[(layer)][(key.row)][(key.col)]);
}

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
  return (action_t){ .code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]) };
}

/*
 * NOTES:
 * ACTION_MODS_TAP_KEY(MOD_RCTL, KC_ENT)
 * Works as a modifier key while holding, but registers a key on tap(press and release quickly)
 *
 * ACTION_LAYER_MOMENTARY(layernumber)
 * it activates when key is pressed and deactivate when released
 * From the docs it seems like the destination layer button must be the same or transparent.
 *
 * ACTION_LAYER_TOGGLE(layer)
 * Turns on layer with first type(press and release) and turns off with next.
 *
 * ACTION_LAYER_TAP_KEY(layer, key)
 * Turns on layer momentary while holding, but registers key on tap(press and release quickly).
 *
 * ACTION_LAYER_SET(layer, on)
 * Turn on layer only. layer_state = (1<<layer) [layer: 0-31]
 *
 * MACRO()
 *
 * ACTION_FUNCTION(id, opt)
 * Not sure how it's different from ACTION_FUNCTION_TAP
 *
 */
const uint16_t PROGMEM fn_actions[] = {
  [0] = ACTION_FUNCTION(TEENSY_KEY),
  [1] = ACTION_LAYER_MOMENTARY(1),  // Activates Layer 1 while held
  [2] = ACTION_LAYER_MOMENTARY(2), // Activates Layer 2 while held
  [3] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC) // Escape when tapped, Ctrl when held
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  if (id == TEENSY_KEY) {
    clear_keyboard();
    print("\n\nJump to bootloader... ");
    _delay_ms(50);
    // Does not work --> bootloader_jump(); // should not return
    // Workaround: (https://github.com/tmk/tmk_keyboard/issues/179)
    cli();
    UDCON = 1;
    USBCON = (1<<FRZCLK);  // disable USB
    UCSR1B = 0;
    _delay_ms(5);
    EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
    TIMSK0 = 0; TIMSK1 = 0; TIMSK3 = 0; TIMSK4 = 0; UCSR1B = 0; TWCR = 0;
    DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0; TWCR = 0;
    PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
    asm volatile("jmp 0x7E00");

    print("not supported.\n");
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0:
     * ,-----------------------------------------------.           ,---------------------------------------------------.
     * |         |     |     |     |      |     |      |           |      |       |       |      |     |      |        |
     * |---------+-----+-----+-----+------+------------|           |------+-------+-------+------+-----+------+--------|
     * |   LAlt  |  Q  |  W  |  E  |  R   |  T  |      |           |      |   Y   |   U   |   I  |  O  |   P  |  LGUI  |
     * |---------+-----+-----+-----+------+-----|      |           |      |-------+-------+------+-----+------+--------|
     * |    -_   |  A  |  S  |  D  |  F   |  G  |------|           |------|   H   |   J   |   K  |  L  |  '"  |  Enter |
     * |---------+-----+-----+-----+------+-----|      |           |      |-------+-------+------+-----+------+--------|
     * |    =+   |  Z  |  X  |  C  |  V   |  B  |      |           |      |   N   |   M   |  ,<  | .>  |  /?  |  FN7   |
     * `---------+-----+-----+-----+------+------------'           `--------------+-------+------+-----+------+--------'
     *  |        |     |     |     |  L1  |                                       |  Tab  | FN5  |     | FN6  |       |
     *  `---------------------------------'                                       `-----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 | FN3: |      |      |       |      |      |      |
     *                                 | Esc/ |LShift|------|       |------| Bspc |Space |
     *                                 | Ctrl |      |  L2  |       | FN4  |      |      |
     *                                 `--------------------'       `--------------------'
     *
     * Layer 1:
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |  TRNS  | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |           | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |  TRNS  |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |  TRNS  |  %   |  $   |  [   |  ]   |  #   | TRNS |           | TRNS |  |   |  7   |  8   |  9   |  ^   |  TRNS  |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |  FN8   |  ~   |  `   |  (   |  )   |  !   |------|           |------|  \   |  4   |  5   |  6   |  ;   |  TRNS  |
     * |--------+------+------+------+------+------| TRNS |           | TRNS |------+------+------+------+------+--------|
     * |  FN9   |  *   |  @   |  {   |  }   |  &   |      |           |      |  :   |  1   |  2   |  3   | FN13 |  FN14  |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | TRNS | TRNS | TRNS | TRNS | TRNS |                                       |  0   | TRNS |  .   | TRNS | TRNS |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |Teensy|       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 | TRNS | FN10 |------|       |------|      | TRNS |
     *                                 |      |      | FN11 |       | FN12 |      |      |
     *                                 `--------------------'       `--------------------'
     *
     * Layer 2:
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |  TRNS  | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |           | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |  TRNS  |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |  TRNS  | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |           | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |  TRNS  |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |  TRNS  | TRNS | TRNS | TRNS | TRNS | TRNS |------|           |------| LEFT | DOWN |  UP  | RIGHT| TRNS |  TRNS  |
     * |--------+------+------+------+------+------| TRNS |           | TRNS |------+------+------+------+------+--------|
     * |  TRNS  | TRNS | TRNS | TRNS | TRNS | TRNS |      |           |      | TRNS | TRNS | TRNS | TRNS | TRNS |  TRNS  |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | TRNS | TRNS | TRNS | TRNS | TRNS |                                       | TRNS | TRNS | TRNS | TRNS | TRNS |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      | TRNS |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 | TRNS | TRNS |------|       |------| TRNS | TRNS |
     *                                 |      |      | TRNS |       | TRNS |      |      |
     *                                 `--------------------'       `--------------------'
     */

    KEYMAP(  // Layer0, Left hand.
         KC_NO,   KC_NO,    KC_NO,    KC_NO,     KC_NO,  KC_NO,    KC_NO,
       KC_LALT,    KC_Q,     KC_W,     KC_E,      KC_R,   KC_T,    KC_NO,
       KC_MINS,    KC_A,     KC_S,     KC_D,      KC_F,   KC_G,
        KC_EQL,    KC_Z,     KC_X,     KC_C,      KC_V,   KC_B,    KC_NO,
         KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_FN1,

                                           KC_NO,  KC_NO,
                                                   KC_NO,
                               KC_FN3, KC_LSHIFT, KC_FN2,

            // Right hand.
              KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,    KC_NO,   KC_NO,
              KC_NO,    KC_Y,    KC_U,     KC_I,    KC_O,     KC_P, KC_LGUI,
                        KC_H,    KC_J,     KC_K,    KC_L,  KC_QUOT,  KC_ENT,
              KC_NO,    KC_N,    KC_M,  KC_COMM,  KC_DOT,  KC_SLSH,  KC_FN7,
                      KC_TAB,  KC_FN5,    KC_NO,  KC_FN6,    KC_NO,

          KC_NO,      KC_NO,
          KC_NO,
          KC_FN4,   KC_BSPC, KC_SPC
    ),

    KEYMAP(  // Layer1, left hand
        KC_TRNS,         KC_TRNS,     KC_TRNS,        KC_TRNS,        KC_TRNS,     KC_TRNS, KC_TRNS,
        KC_TRNS,     SHIFT(KC_5), SHIFT(KC_4),        KC_LBRC,        KC_RBRC, SHIFT(KC_3), KC_TRNS,
         KC_FN8, SHIFT(KC_GRAVE),    KC_GRAVE,    SHIFT(KC_9),    SHIFT(KC_0), SHIFT(KC_1),
         KC_FN9,     SHIFT(KC_8), SHIFT(KC_2), SHIFT(KC_LBRC), SHIFT(KC_RBRC), SHIFT(KC_7), KC_TRNS,
        KC_TRNS,         KC_TRNS,     KC_TRNS,        KC_TRNS,        KC_TRNS,

                                          KC_TRNS,   KC_FN0,
                                                    KC_TRNS,
                                KC_TRNS,  KC_FN10,  KC_FN11,

        // right hand
             KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,
             KC_TRNS,   SHIFT(KC_BSLS),    KC_7,    KC_8,    KC_9, SHIFT(KC_6), KC_TRNS,
                               KC_BSLS,    KC_4,    KC_5,    KC_6,   KC_SCOLON, KC_TRNS,
             KC_TRNS, SHIFT(KC_SCOLON),    KC_1,    KC_2,    KC_3,     KC_FN13, KC_FN14,
                                           KC_0, KC_TRNS,  KC_DOT,     KC_TRNS, KC_TRNS,

         KC_NO, KC_TRNS,
         KC_NO,
       KC_FN12,   KC_NO, KC_TRNS
    ),

    KEYMAP(  // Layer2, left hand
        KC_TRNS,         KC_TRNS,     KC_TRNS,        KC_TRNS,        KC_TRNS,     KC_TRNS, KC_TRNS,
        KC_TRNS,         KC_TRNS,     KC_TRNS,        KC_TRNS,        KC_TRNS,     KC_TRNS, KC_TRNS,
        KC_TRNS,         KC_TRNS,     KC_TRNS,        KC_TRNS,        KC_TRNS,     KC_TRNS,
        KC_TRNS,         KC_TRNS,     KC_TRNS,        KC_TRNS,        KC_TRNS,     KC_TRNS, KC_TRNS,
        KC_TRNS,         KC_TRNS,     KC_TRNS,        KC_TRNS,        KC_TRNS,

                                          KC_TRNS,  KC_TRNS,
                                                    KC_TRNS,
                                KC_TRNS,  KC_TRNS,  KC_TRNS,

        // right hand
             KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,     KC_TRNS, KC_TRNS,
             KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,     KC_TRNS, KC_TRNS,
                               KC_LEFT, KC_DOWN,   KC_UP, KC_RIGHT,     KC_TRNS, KC_TRNS,
             KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,     KC_TRNS, KC_TRNS,
                                        KC_TRNS, KC_TRNS,  KC_TRNS,     KC_TRNS, KC_TRNS,

       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
    )
};
