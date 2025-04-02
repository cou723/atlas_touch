// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "os_detection.h"

enum {
    DEFAULT_LAYER = 0,
    CONTROL_LAYER,
    MACHINE_CTRL_LAYER,
    GAMING_LAYER,
    TOTAL_LAYERS
};

#define DL DEFAULT_LAYER
#define CL CONTROL_LAYER
#define ML MACHINE_CTRL_LAYER
#define GL GAMING_LAYER

enum { RGBRST = SAFE_RANGE, KC_NWIN, KC_BWIN, KC_WSS, PAREN, EMAIL_1, EMAIL_2, EMAIL_3, UNI_NUM, L_RESET, KC_RNWIN, NAME, BIRTH, P_SHIFT, KC_MCWIN };

const rgblight_segment_t PROGMEM l1[]=RGBLIGHT_LAYER_SEGMENTS({0,1,HSV_AZURE});
const rgblight_segment_t PROGMEM l2[]=RGBLIGHT_LAYER_SEGMENTS({0,1,HSV_BLUE});
const rgblight_segment_t PROGMEM l3[]=RGBLIGHT_LAYER_SEGMENTS({0,1,HSV_CHARTREUSE});
const rgblight_segment_t PROGMEM l4[]=RGBLIGHT_LAYER_SEGMENTS({0,1,HSV_GOLD});

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    l1, l2, l3, l4
);

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0,layer_state_cmp(state,DEFAULT_LAYER));
    rgblight_set_layer_state(1,layer_state_cmp(state,CONTROL_LAYER));
    rgblight_set_layer_state(2,layer_state_cmp(state,MACHINE_CTRL_LAYER));
    rgblight_set_layer_state(3,layer_state_cmp(state,GAMING_LAYER));

    return state;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT_LAYER] = LAYOUT(
        XXXXXXX,XXXXXXX,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,
        XXXXXXX,KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   XXXXXXX,
        KC_ESC, KC_LCTL,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   XXXXXXX,
        XXXXXXX,KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   MO(GL), _______,
                                LALT_T(KC_LNG2),MO(CL), KC_SPC, KC_LWIN,KC_LSFT,

                _______,KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,_______,_______,
                KC_Y,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,_______,
                KC_H,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT,
        KC_MINS,KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_EQL, _______,
        KC_MINS,KC_UNDS,KC_UNDS,MO(ML),RALT_T(KC_LNG1)
    ),
    [CONTROL_LAYER] = LAYOUT(
        XXXXXXX,XXXXXXX,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,
        XXXXXXX,_______,_______,_______,_______,_______,_______,XXXXXXX,
        _______,_______,_______,KC_DEL, KC_DOWN,KC_ENT, _______,XXXXXXX,
        XXXXXXX,_______,_______,_______,_______,_______,_______,XXXXXXX,_______,
                                _______,        _______,_______,_______,_______,

                _______,KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, _______,_______,
                QK_BOOT,KC_PGUP,KC_HOME,KC_UP,  KC_END, KC_GRV, PAREN,  _______,
              C(KC_TAB),KC_PGDN,KC_LEFT,KC_DOWN,KC_RGHT,KC_ENT, KC_EQL, KC_F12,
   KC_MINS,C(S(KC_TAB)),KC_BSPC,KC_DEL, _______,KC_BSLS,KC_APP ,KC_APP, _______,
        KC_UNDS,KC_UNDS,KC_NWIN,MO(ML),RALT_T(KC_LNG1)
    ),
    [MACHINE_CTRL_LAYER] = LAYOUT(
        _______,_______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,
                                        _______,_______,_______,_______,_______,

                _______,_______,_______,_______,_______,_______,_______,_______,
                _______,_______,_______,_______,_______,_______,_______,_______,
                _______,_______,DF(GL), _______,_______,_______,_______,QK_BOOT,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______
    ),
    [GAMING_LAYER] = LAYOUT(
        XXXXXXX,XXXXXXX,KC_0,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,
        XXXXXXX,KC_6,   KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   XXXXXXX,
        KC_9,   KC_ESC, KC_LCTL,KC_A,   KC_S,   KC_D,   KC_F,   XXXXXXX,
        XXXXXXX,KC_7,   KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   XXXXXXX,KC_M,
                                KC_LALT,KC_G,   KC_SPC, KC_T,   KC_B,

                _______,KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,_______,_______,
                KC_Y,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,_______,
                KC_H,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT,
        KC_MINS,KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_EQL, _______,
        KC_MINS,KC_UNDS,KC_UNDS,DF(DL),DF(DL)
    )
};

// clang-format on
// send command ///////////////////////////////////////////////////////////////
void register_code(uint8_t code);
void unregister_code(uint8_t code);

void reset_layer(void) {
    for (int i = 0; i < TOTAL_LAYERS; i++) {
        layer_off(i);
    }
    default_layer_set(0);
}

typedef struct s_send_command {
    int keycode;
    void (*command)(void);
} SEND_COMMAND_PAIR;

/**
 * @param keycode
 * @param record
 * @return is sent command
 */
bool send_command(uint16_t keycode, keyrecord_t *record) {
    SEND_COMMAND_PAIR send_commands[] = {
        {L_RESET, reset_layer},
    };

    for (int i = 0; i < sizeof(send_commands) / sizeof(send_commands[0]); i++) {
        if (keycode != send_commands[i].keycode) continue;

        if (record->event.pressed) send_commands[i].command();
        return true;
    }
    return false;
}

// send command ///////////////////////////////////////////////////////////////

// process_record_user utils //////////////////////////////////////////////////

void tap_code_with_mod(uint16_t keycode, uint16_t mod) {
    register_code(mod);
    tap_code(keycode);
    unregister_code(mod);
}

void open_window_changer(void) {
    register_code(KC_LALT);
    tap_code(KC_TAB);
}

void open_window_changer_remote(void) {
    register_code(KC_LALT);
    tap_code(KC_F15);
}

// process_record_user utils //////////////////////////////////////////////////

typedef enum { NONE, HOLD, HOLD_PULSED_KEY, RELEASE } MOD_STATE;
static MOD_STATE shift_state            = NONE;
static bool      is_open_window_changer = false;

static bool show_alt_tab = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_NWIN:
            if (record->event.pressed) {
                show_alt_tab = true;
                open_window_changer();
            } else {
                show_alt_tab = false;
                unregister_code(KC_LALT);
            }
            break;
        case KC_RNWIN:
            if (record->event.pressed) {
                show_alt_tab = true;
                open_window_changer_remote();
            } else {
                show_alt_tab = false;
                unregister_code(KC_LALT);
            }
            break;
        case KC_MCWIN:
            if (record->event.pressed) {
                register_code(KC_LALT);
                tap_code(KC_TAB);
                is_open_window_changer = true;
            } else {
                unregister_code(KC_LALT);
                is_open_window_changer = false;
            }
            break;
        case PAREN:
            if (record->event.pressed) {
                tap_code(KC_LBRC);
                tap_code(KC_RBRC);
            }
            break;
        case P_SHIFT:
            if (record->event.pressed) {
                shift_state = HOLD;
            } else {
                if (shift_state == HOLD_PULSED_KEY) {
                    shift_state = NONE;
                    return false;
                }
                shift_state = RELEASE;
                tap_code(KC_LSFT);
            }
            return false;
    }

    if (send_command(keycode, record)) return false;

    if ((shift_state == HOLD || shift_state == HOLD_PULSED_KEY) && record->event.pressed) {
        tap_code_with_mod(keycode, KC_LSFT);
        shift_state = HOLD_PULSED_KEY;
        return false;
    }

    if (shift_state == RELEASE && record->event.pressed) {
        tap_code_with_mod(keycode, KC_LSFT);
        shift_state = NONE;
        return false;
    }
    return true;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    // ここでは可読性や拡張性のためにswitch文を使っている
    switch (keycode) {
        case LALT_T(KC_LNG2):
        case RALT_T(KC_LNG1):
            return false;
        default:
            return true;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    // ここでは可読性や拡張性のためにswitch文を使っている
    switch (keycode) {
        case LALT_T(KC_LNG2):
        case RALT_T(KC_LNG1):
            return true;
        default:
            return false;
    }
}

void keyboard_post_init_user(void) {
    // debug_enable = true;
    // debug_matrix = true;

    // wait_ms(500);
    // os_variant_t host = detected_host_os();
    // if (host == OS_MACOS || host == OS_IOS) {
    //     // keymap_config.swap_lctl_lgui = true;
    //     is_apple = true;
    //     default_layer_set(1UL << MAC_DEFAULT_LAYER);
    //     layer_move(MAC_DEFAULT_LAYER);
    // }
    // is_called_keyboard_post_init_user = detected_host_os();
    rgblight_layers=rgb_layers;
}

// #define mac_layer (1 << MAC_DEFAULT_LAYER | 1 << MAC_CTL_LAYER | 1 << MAC_MACHINE_CTL_LAYER)

const key_override_t ctrl_z_to_ctrl_u   = ko_make_basic(MOD_MASK_CTRL, KC_U, C(KC_Z));
const key_override_t maximize           = ko_make_basic(MOD_MASK_GUI, KC_F, G(KC_UP));

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = (const key_override_t *[]){
    &maximize,
    &ctrl_z_to_ctrl_u,         //
    NULL,
};
