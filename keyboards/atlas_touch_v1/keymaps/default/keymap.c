// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_ESC, KC_ESC, KC_1,   KC_2,   KC_9,   KC_4,   KC_5,   KC_6,
        KC_TAB, KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,
        KC_LCTL,KC_LCTL,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,
        KC_LSFT,KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_ENT,
                                        KC_LGUI,KC_SPC, KC_SPC, KC_ENT, KC_ENT,
                KC_7,   KC_7,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL,
                KC_Y,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,
                KC_H,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT,
        KC_N,   KC_N,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_BSLS,KC_PGUP,
        KC_LEFT,KC_DOWN,KC_RGHT,KC_PGDN,KC_DEL
    )
};
