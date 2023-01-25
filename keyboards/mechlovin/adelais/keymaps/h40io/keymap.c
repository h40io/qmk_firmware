/* Copyright 2020 Team Mechlovin
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

enum my_keycodes {
  BL_TOG = USER00,
  BL_EFFECT = USER01,
  BL_ISPD = USER02,
  BL_DSPD = USER03,
  BL_IHUE = USER04,
  BL_DHUE = USER05,
  BL_ISAT = USER06,
  BL_DSAT = USER07,
  BL_IVAL = USER08,
  BL_DVAL = USER09
};

bool is_alt_gui_active = false;
bool is_alt_tab_active = false;
uint16_t alt_gui_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        KC_KB_MUTE, QK_GESC,  KC_1, KC_2,    KC_3, KC_4,   KC_5, KC_6,            KC_7, KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
     KC_PGUP, KC_TAB,  KC_Q, KC_W,    KC_E, KC_R,   KC_T,                  KC_Y, KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
     KC_PGDN, KC_LCTL, KC_A, KC_S,    KC_D, KC_F,   KC_G,                  KC_H, KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
             KC_LSFT,       KC_Z,    KC_X, KC_C,   KC_V, KC_B,            KC_B, KC_N,   KC_M,    KC_COMM, KC_DOT,  MO(1), KC_RSFT, KC_SLSH,
             KC_LCTL,       KC_LGUI,       KC_SPC,       KC_LALT,                 KC_SPC,          KC_RALT,                            KC_RCTL ),
    [1] = LAYOUT_all(
     KC_CAPS, KC_GRV, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_F6,         KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_NUM_LOCK, KC_TRNS, RGB_TOG,   KC_P7,   KC_P8,   KC_P9, KC_PSLS,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     KC_SCROLL_LOCK, KC_TRNS, KC_TRNS,   KC_P4,   KC_P5,   KC_P6, KC_PAST,                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS,
              KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_TRNS, KC_RIGHT, KC_DOWN,
              KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,                  KC_TRNS,          TO(2),                            KC_TRNS ),
    [2] = LAYOUT_all(
        KC_KB_MUTE, QK_GESC,  KC_1, KC_2,    KC_3, KC_4,   KC_5, KC_6,            KC_7, KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_PGUP, KC_TAB,  KC_Q, KC_W,    KC_E, KC_R,   KC_T,                  KC_Y, KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_PGDN, KC_LCTL, KC_A, KC_S,    KC_D, KC_F,   KC_G,                  KC_H, KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT,       KC_Z,    KC_X, KC_C,   KC_V, KC_B,            KC_B, KC_N,   KC_M,    KC_COMM, KC_DOT,  MO(3), KC_RSFT, KC_SLSH,
        KC_LCTL,       KC_LALT,       KC_SPC,       KC_LGUI,                 KC_SPC,          KC_RALT,                            KC_RCTL ),
    [3] = LAYOUT_all(
        KC_CAPS, KC_GRV, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_F6,         KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_NUM_LOCK, KC_TRNS, KC_TRNS,   KC_P7,   KC_P8,   KC_P9, KC_PSLS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_SCROLL_LOCK, KC_TRNS, KC_TRNS,   KC_P4,   KC_P5,   KC_P6, KC_PAST,                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS,
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_TRNS, KC_RIGHT, KC_DOWN,
              KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,                  KC_TRNS,          TO(0),                            KC_TRNS ),

};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Top rotary for Control + Tab (tab switching)
        if (clockwise) {
            tap_code16(C(KC_TAB));
        } else {
            tap_code16(S(C(KC_TAB)));
        }
    } else if (index == 1) {
        // Middle rotary for Alt + Tab (Windows window switching)
        if (clockwise) {
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(KC_LALT);
            }
            alt_gui_timer = timer_read();
            tap_code16(KC_TAB);
        } else {
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(KC_LALT);
            }
            alt_gui_timer = timer_read();
            tap_code16(S(LALT(KC_TAB)));
        }
    } else if (index == 2) {
        // Bottom rotary for Cmd + Tab (OSX window switching)
        if (clockwise) {
            if (!is_alt_gui_active) {
                is_alt_gui_active = true;
                register_code(KC_LGUI);
            }
            alt_gui_timer = timer_read();
            tap_code16(KC_TAB);
        } else {
            if (!is_alt_gui_active) {
                is_alt_gui_active = true;
                register_code(KC_LGUI);
            }
            alt_gui_timer = timer_read();
            tap_code16(S(LGUI(KC_TAB)));
        }
    }
    return true;
}
#endif
																						
void matrix_scan_user(void) {
  if (is_alt_gui_active) {
    if (timer_elapsed(alt_gui_timer) > 750) {
      unregister_code(KC_LGUI);
      is_alt_gui_active = false;
    }
  } else if (is_alt_tab_active) {
    if (timer_elapsed(alt_gui_timer) > 750) {
    unregister_code(KC_LALT);
    is_alt_tab_active = false;
  }
}
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
#ifdef RGB_MATRIX_ENABLE
    case RGB_TOG: // toggle rgb matrix
      rgb_matrix_toggle();
      return false;
#endif
    default:
      break;
    }
  }
  return true;
}
