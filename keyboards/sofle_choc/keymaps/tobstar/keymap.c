/* Copyright 2023 Brian Low
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

/* This is copied from generated.c, which was generated from tobstar.json via
 * qmk json2c keyboards/sofle_choc/keymaps/tobstar/tobstar.json > keyboards/sofle_choc/keymaps/tobstar/generated.c
 * tobstar.json was generated in the online configurator https://config.qmk.fm/#/sofle_choc/LAYOUT
 * see also: https://mechanische-tastaturen.net/qmk-und-via-guide/qmk-via-keycodes-fuer-deutsche-zeichen/
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(KC_CAPS, KC_GRV, KC_NUHS, RALT(KC_8), RALT(KC_9), LSFT(KC_8), LSFT(KC_9), RALT(KC_7), RALT(KC_0), KC_RBRC, KC_MINS, KC_PSCR, KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE, KC_MPLY, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LGUI, KC_LALT, KC_LCTL, MO(1), KC_ENT, KC_SPC, KC_BSPC, KC_RCTL, KC_RALT, KC_APP),
	[1] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_ESC, LSFT(KC_2), KC_HOME, KC_UP, KC_END, KC_PGUP, RALT(KC_Q), KC_7, KC_8, KC_9, KC_PMNS, KC_EQL, KC_TAB, LSFT(KC_NUHS), KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NUBS, KC_4, KC_5, KC_6, KC_PPLS, KC_NO, KC_LSFT, KC_NUBS, LSFT(KC_NUBS), LSFT(KC_7), RALT(KC_MINS), KC_INS, RGB_TOG, KC_CALC, KC_0, KC_1, KC_2, KC_3, RALT(KC_NUBS), KC_RSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_TRNS, KC_ENT, KC_SPC, KC_DEL, KC_RCTL, KC_RALT, KC_APP)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),   ENCODER_CCW_CW(KC_MPRV, KC_MNXT)  },
    [1] =  { ENCODER_CCW_CW(RGB_MODE_REVERSE, RGB_MODE_FORWARD),   ENCODER_CCW_CW(RGB_VAD, RGB_VAI)  },
    // [2] =  { ENCODER_CCW_CW(RGB_VAD, RGB_VAI),   ENCODER_CCW_CW(RGB_SPD, RGB_SPI)  },
    // [3] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD),  ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },
};
#endif

// TODO: program oled
#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

void write_int_ln(const char* prefix, uint8_t value) {
    oled_write_P(prefix, false);
    oled_write(get_u8_str(value, ' '), false);
}

static void print_status_narrow(void) {
    oled_write_ln_P(PSTR("SofleChoc _____"), false);

/*
    if (get_highest_layer(layer_state) == _ADJUST) {
        uint8_t mode  = rgb_matrix_get_mode();
        HSV     hsv   = rgb_matrix_get_hsv();
        uint8_t speed = rgb_matrix_get_speed();

        if (keymap_config.swap_lctl_lgui) {
            oled_write_ln_P(PSTR("MAC\n"), false);
        } else {
            oled_write_ln_P(PSTR("WIN\n"), false);
        }

        oled_write_ln("RGB", false);
        write_int_ln(PSTR("Mo"), mode);
        write_int_ln(PSTR("H "), hsv.h);
        write_int_ln(PSTR("S "), hsv.s);
        write_int_ln(PSTR("V "), hsv.v);
        write_int_ln(PSTR("Sp"), speed);
        oled_write_P(PSTR("\n\n\n"), false);
    } else {
        oled_write_P(PSTR("\n\n\n\n\n\n\n\n\n"), false);
        led_t led_usb_state = host_keyboard_led_state();
        if (led_usb_state.caps_lock) {
            oled_write_ln_P(PSTR(" CAP "), true);
        } else {
            oled_write_ln_P(PSTR("     "), false);
        }
    }
*/

    // Print current layer
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("- 0 -"), false);
            break;
        case 1:
            oled_write_P(PSTR("- 1 -"), false);
            break;
        default:
            oled_write_P(PSTR("- ? -"), false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }

    return false;
}

#endif
