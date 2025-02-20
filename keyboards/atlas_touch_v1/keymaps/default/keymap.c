// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "os_detection.h"

#define DEFAULT_LAYER 0
#define DL DEFAULT_LAYER

#define CONTROL_LAYER 1
#define CL CONTROL_LAYER

#define MACHINE_CTRL_LAYER 2
#define ML MACHINE_CTRL_LAYER

#define REMOTE_DEFAULT_LAYER 3
#define RDL REMOTE_DEFAULT_LAYER

#define REMOTE_CTL_LAYER 4
#define RCL REMOTE_CTL_LAYER

#define REMOTE_MACHINE_CTL_LAYER 5
#define RML REMOTE_MACHINE_CTL_LAYER

#define MAC_DEFAULT_LAYER 6
#define MDL MAC_DEFAULT_LAYER

#define MAC_CTL_LAYER 7
#define MCL MAC_CTL_LAYER

#define MAC_MACHINE_CTL_LAYER 8
#define MML MAC_MACHINE_CTL_LAYER

#define TOTAL_LAYERS 8

static bool is_apple                          = false;
static int  is_called_keyboard_post_init_user = 0;

enum custom_keycodes { RGBRST = SAFE_RANGE, KC_NWIN, KC_BWIN, KC_WSS, PAREN, EMAIL_1, EMAIL_2, EMAIL_3, UNI_NUM, L_RESET, KC_RNWIN, NAME, BIRTH, P_SHIFT, KC_MCWIN };


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT_LAYER] = LAYOUT(
        _______,_______,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,
        _______,KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,
        KC_ESC, KC_LCTL,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,
        _______,KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_LSFT,
                                LALT_T(KC_LNG2),MO(CL), KC_SPC, KC_LWIN,KC_LWIN,
                _______,KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,_______,_______,
                KC_Y,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,_______,
                KC_H,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT,
        KC_MINS,KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_BSLS,_______,
        KC_UNDS,KC_RGUI,KC_UNDS,MO(ML),RALT_T(KC_LNG1)
    ),
    [CONTROL_LAYER] = LAYOUT(
        _______,_______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,
        _______,_______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,KC_DEL, KC_DOWN,KC_ENT, _______,_______,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,
                                _______,        _______,_______,_______,_______,

                _______,KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, _______,_______,
                KC_Y,   KC_Y,   KC_HOME,KC_UP,  KC_END, KC_GRV, PAREN,  _______,
                KC_H,   KC_H,   KC_LEFT,KC_DOWN,KC_RGHT,KC_ENT, KC_EQL, KC_CAPS,
        KC_MINS,KC_B,   KC_BSPC,KC_DEL, KC_PGUP,KC_PGDN,KC_APP ,KC_APP, _______,
        KC_UNDS,KC_UNDS,KC_NWIN,MO(ML),RALT_T(KC_LNG1)
    ),
    [MACHINE_CTRL_LAYER] = LAYOUT(
        _______,_______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,
        _______,_______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,KC_DEL, KC_DOWN,KC_ENT, _______,_______,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,
                                        _______,_______,_______,_______,_______,

                _______,KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, _______,_______,
                KC_Y,   KC_Y,   KC_HOME,KC_UP,  KC_END, KC_GRV, PAREN,  _______,
                KC_H,   KC_H,   KC_LEFT,KC_DOWN,KC_RGHT,KC_ENT, KC_EQL, KC_CAPS,
        KC_MINS,KC_B,   KC_BSPC,KC_DEL, KC_PGUP,KC_PGDN,KC_APP ,KC_APP, _______,
        KC_UNDS,KC_UNDS,KC_NWIN,MO(ML),RALT_T(KC_LNG1)
    ),
};

// clang-format on

// send string ////////////////////////////////////////////////////////////////

typedef struct {
    int   keycode;
    char *str;
} SEND_STRING;

bool send_text(uint16_t keycode, keyrecord_t *record) {
    SEND_STRING send_strings[] = {{EMAIL_1, "mymail"}, {EMAIL_2, "mymail2"}, {EMAIL_3, "mymail3"}, {UNI_NUM, "uni num"}, {BIRTH, "1111 11 11"}};
    for (int i = 0; i < sizeof(send_strings) / sizeof(send_strings[0]); i++) {
        if (keycode != send_strings[i].keycode) continue;

        if (record->event.pressed) send_string(send_strings[i].str);
        return true;
    }
    return false;
}

// send string ////////////////////////////////////////////////////////////////

// send command ///////////////////////////////////////////////////////////////
void register_code(uint8_t code);
void unregister_code(uint8_t code);

void launch_snipping_tool(void) {
    register_code(KC_LCTL);
    register_code(KC_LWIN);
    register_code(KC_S);
    unregister_code(KC_LCTL);
    unregister_code(KC_LWIN);
    unregister_code(KC_S);
}

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
        {KC_WSS, launch_snipping_tool},
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

    if (send_text(keycode, record)) return false;
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
    debug_enable = true;
    debug_matrix = true;

    wait_ms(500);
    os_variant_t host = detected_host_os();
    if (host == OS_MACOS || host == OS_IOS) {
        // keymap_config.swap_lctl_lgui = true;
        is_apple = true;
        default_layer_set(1UL << MAC_DEFAULT_LAYER);
        layer_move(MAC_DEFAULT_LAYER);
    }
    is_called_keyboard_post_init_user = detected_host_os();
}

#define mac_layer (1 << MAC_DEFAULT_LAYER | 1 << MAC_CTL_LAYER | 1 << MAC_MACHINE_CTL_LAYER)

const key_override_t ctrl_z_to_ctrl_u   = ko_make_basic(MOD_MASK_CTRL, KC_U, C(KC_Z));
const key_override_t maximize           = ko_make_basic(MOD_MASK_GUI, KC_F, G(KC_UP));
const key_override_t mac_cmd_z_to_cmd_u = ko_make_with_layers_negmods_and_options(MOD_MASK_CTRL, KC_U, LCTL(KC_Z), mac_layer, 0, ko_option_no_reregister_trigger);

/*
next word				ctrl+right		alt+right
pre word				ctrl+left		alt+left
line start				home			ctrl+a
line end				end				ctrl+e
file start				ctrl+home		ctrl+up
file end				ctrl+end		ctrl+down
delete to word start	ctrl+backspace	alt+backspace
delete to word end		ctrl+delete		alt+delete
move to pre page		alt+left		cmd+left
move to y page			alt+right		cmd+right
*/

// move_word
const key_override_t mac_move_left_word = ko_make_with_layers_negmods_and_options(MOD_MASK_GUI, KC_LEFT, LALT(KC_LEFT), mac_layer, 0, ko_option_no_reregister_trigger);

const key_override_t mac_move_right_word = ko_make_with_layers_negmods_and_options(MOD_MASK_GUI, KC_RIGHT, LALT(KC_RIGHT), mac_layer, 0, ko_option_no_reregister_trigger);

// select_word
const key_override_t mac_select_left_word = ko_make_with_layers_negmods_and_options(MOD_MASK_SG, KC_LEFT, LAG(KC_LEFT), mac_layer, 0, ko_option_no_reregister_trigger);

const key_override_t mac_select_right_word = ko_make_with_layers_negmods_and_options(MOD_MASK_SG, KC_RIGHT, LAG(KC_RIGHT), mac_layer, 0, ko_option_no_reregister_trigger);

// move_line
const key_override_t mac_move_line_start = ko_make_with_layers_negmods_and_options(0, KC_HOME, LCTL(KC_A), mac_layer, 0, ko_option_no_reregister_trigger);

const key_override_t mac_move_line_end = ko_make_with_layers_negmods_and_options(0, KC_END, LCTL(KC_E), mac_layer, 0, ko_option_no_reregister_trigger);

// delete
const key_override_t mac_delete_to_word_start = ko_make_with_layers_negmods_and_options(MOD_MASK_GUI, KC_BACKSPACE, LALT(KC_BACKSPACE), mac_layer, 0, ko_option_no_reregister_trigger);

const key_override_t mac_delete_to_word_end = ko_make_with_layers_negmods_and_options(MOD_MASK_GUI, KC_DELETE, LALT(KC_DELETE), mac_layer, 0, ko_option_no_reregister_trigger);

// to file start/end
const key_override_t mac_move_to_file_start = ko_make_with_layers_negmods_and_options(MOD_MASK_GUI, KC_HOME, LCTL(KC_UP), mac_layer, 0, ko_option_no_reregister_trigger);

const key_override_t mac_move_to_file_end = ko_make_with_layers_negmods_and_options(MOD_MASK_GUI, KC_END, LCTL(KC_DOWN), mac_layer, 0, ko_option_no_reregister_trigger);

// move page
const key_override_t mac_move_pre_page = ko_make_with_layers_negmods_and_options(MOD_MASK_ALT, KC_LEFT, LGUI(KC_LEFT), mac_layer, 0, ko_option_no_reregister_trigger);

const key_override_t mac_move_next_page = ko_make_with_layers_negmods_and_options(MOD_MASK_ALT, KC_RIGHT, LGUI(KC_RIGHT), mac_layer, 0, ko_option_no_reregister_trigger);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &maximize,
    &ctrl_z_to_ctrl_u,         //
    &mac_cmd_z_to_cmd_u,       //
    &mac_move_left_word,       //
    &mac_move_right_word,      //
    &mac_select_left_word,     //
    &mac_select_right_word,    //
    &mac_move_line_start,      //
    &mac_move_line_end,        //
    &mac_delete_to_word_start, //
    &mac_delete_to_word_end,   //
    // &mac_move_to_file_start,   //
    // &mac_move_to_file_end,     //
    &mac_move_pre_page,  //
    &mac_move_next_page, //
    NULL,
};
