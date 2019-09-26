/* Copyright 2018 Eucalyn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

enum custom_keycodes {
  RGBRST = SAFE_RANGE,
  M_VI_I,
    M_VI_A,
    M_VI_O,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,    KC_BSPC,  \
    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,  \
    KC_CAPS,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,        KC_ENT,   \
    KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MO(2),   KC_UP,  KC_DEL,   \
    KC_GRV,    KC_LCTL,    KC_LGUI,    KC_LALT,    KC_SPC,        KC_RCTL, TO(1),  KC_RSFT,               KC_LEFT,KC_DOWN,KC_RGHT \
  ),
  [1] = LAYOU( \
    _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,    _______, \
    XXXXXXX,   XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, M_VI_I, M_VI_O, KC_HOME, KC_PGUP, XXXXXXX, XXXXXXX, \
    XXXXXXX,     M_VI_A, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_END, KC_PGDN,        _______, \
    _______,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, _______, \
    XXXXXXX,   _______,    _______,    _______,    _______,       _______, TO(0), _______,                   KC_HOME, KC_PGDN, KC_END \
  ),
  [2] = LAYOUT( \
    _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,    KC_DEL, \
    XXXXXXX,   XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        _______, \
    _______,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_BSPC, \
    XXXXXXX,   _______,    KC_APP,    _______,    _______,       _______, XXXXXXX, _______,                   KC_HOME, KC_PGDN, KC_END \
  ),
};

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case M_VI_I:
        if (record->event.pressed) {
            layer_move(0);
            return false;
        }
      break;
      case M_VI_A:
          if (record->event.pressed) {
              tap_code(KC_RGHT);
              layer_move(0);
              return false;
          }
          break;
      case M_VI_O:
          if (record->event.pressed) {
              tap_code(KC_END);
              tap_code(KC_ENT);
              layer_move(0);
              return false;
          }
          break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
