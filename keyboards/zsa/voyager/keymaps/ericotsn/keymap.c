// Copyright 2025 Eric Ottosson (@ericotsn) <contact@ericotsn.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "layout.h"

enum layers {
    BASE,
    SYM,
    NAV,
};

enum keycode_aliases {
    OS_LSFT = OSM(MOD_LSFT),
    OS_RSFT = OSM(MOD_RSFT),

    PRV_TAB = LCTL(LSFT(KC_TAB)),
    NXT_TAB = LCTL(KC_TAB),

    GUI_A = LGUI_T(KC_A),
    GUI_O = RGUI_T(KC_O),

    SYM_X = LT(SYM, KC_X),
    SYM_DOT = LT(SYM, KC_DOT),

    CTL_BSP = LCTL_T(KC_BSPC),
    ALT_SPC = LALT_T(KC_SPC),
    NAV_ESC = LT(NAV, KC_ESC),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_LR( // Base layer (Colemak-DH)
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,
        OS_LSFT, GUI_A,   KC_R,    KC_S,    KC_T,    KC_G,
        KC_RCTL, KC_Z,    SYM_X,   KC_C,    KC_D,    KC_V,
                                                     CTL_BSP, NAV_ESC,

                 KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
                 KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, KC_BSLS,
                 KC_M,    KC_N,    KC_E,    KC_I,    GUI_O,   OS_RSFT,
                 KC_K,    KC_H,    KC_COMM, SYM_DOT, KC_SLSH, KC_RCTL,
        KC_ENT,  ALT_SPC
    ),
    [SYM] = LAYOUT_LR( // Symbol layer
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
        _______, KC_GRV,  KC_LABK, KC_RABK, KC_MINS, KC_PIPE,
        _______, KC_EXLM, KC_ASTR, KC_SLSH, KC_EQL,  KC_AMPR,
        _______, KC_TILD, KC_PLUS, KC_LBRC, KC_RBRC, KC_PERC,
                                                     _______, _______,

                 KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
                 KC_CIRC, KC_LCBR, KC_RCBR, KC_DLR,  KC_UNDS, KC_F12,
                 KC_HASH, KC_LPRN, KC_RPRN, KC_SCLN, KC_DQUO, _______,
                 KC_AT,   KC_COLN, KC_COMM, KC_DOT,  KC_QUES, _______,
        _______, _______
    ),
    [NAV] = LAYOUT_LR( // Navigation and extras
        RM_TOGG, QK_KB,   RM_NEXT, RGB_M_P, RM_VALD, RM_VALU,
        _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______,
        _______, KC_MPRV, KC_MNXT, KC_MSTP, KC_MPLY, _______,
        _______, _______, _______, _______, _______, _______,
                                                     _______, _______,

                 _______, _______, _______, _______, _______, QK_BOOT,
                 KC_PGUP, KC_HOME, KC_UP,   KC_END , _______, _______,
                 KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
                 _______, PRV_TAB, NXT_TAB, _______, _______, _______,
        _______, _______
    ),
};

// https://docs.qmk.fm/tap_hold#chordal-hold
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_LR( // Handedness for Chordal Hold
        '*', '*', '*', '*', '*', '*',
        '*', 'L', 'L', 'L', 'L', 'L',
        '*', 'L', 'L', 'L', 'L', 'L',
        '*', 'L', 'L', 'L', 'L', 'L',
                                 '*', '*',

             '*', '*', '*', '*', '*', '*',
             'R', 'R', 'R', 'R', 'R', '*',
             'R', 'R', 'R', 'R', 'R', '*',
             'R', 'R', 'R', 'R', 'R', '*',
        '*', '*'
    );

// https://docs.qmk.fm/tap_hold#hold-on-other-key-press
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTL_BSP:
        case SYM_X:
        case SYM_DOT:
            return true;
        default:
            return false;
    }
}

// https://docs.qmk.fm/tap_hold#flow-tap
bool is_flow_tap_key(uint16_t keycode) {
    if ((get_mods() & (MOD_MASK_CG | MOD_BIT_LALT)) != 0) {
        return false; // Disable Flow Tap on hotkeys
    }
    switch (get_tap_keycode(keycode)) {
        case KC_SPC:
        case KC_A ... KC_W:
        case KC_Y ... KC_Z:
        case KC_COMM:
        case KC_SCLN:
        case KC_SLSH:
            return true;
    }
    return false;
}
