#include QMK_KEYBOARD_H

#include "../jonavin/rgb_matrix_map.h"
#include "custom.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    //      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12      Prt           Rotary(Mute)
    //      ^        1        2        3        4        5        6        7        8        9        0        ß        ´        BackSpc           Del
    //      Tab      Q        W        E        R        T        Z        U        I        O        P        Ü        *                          PgUp
    //      Caps     A        S        D        F        G        H        J        K        L        Ö        Ä        #        Enter             PgDn
    //      Sh_L     </>      Y        X        C        V        B        N        M        ,        .        -                 Sh_R     Up       End
    //      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right
    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                   KC_PGUP,
        _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,           KC_PGDN,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FN1),KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN1] = LAYOUT(
        KC_SLEP, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, KC_EJCT, _______,          RGB_TOG,
        RGB_TOG, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_G, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            KC_INS,
        _______, RGB_SAI, RGB_VAI, RGB_HUI, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   KC_HOME,
        KC_CAPS, RGB_SAD, RGB_VAD, RGB_HUD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_END,
        _______, _______, _______, RGB_HUI, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RGB_MOD, KC_MENU,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    )

};
// clang-format on

/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case KC_WINLCK:
            if (record->event.pressed) {
                keymap_config.no_gui = !keymap_config.no_gui; //toggle status
            } else unregister_code16(keycode);
            return false;
    };
    return true;
}
*/

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    switch(biton32(layer_state)){
        case _FN1:
            #ifdef RGB_MATRIX_ENABLE
            if (clockwise) {
                rgblight_increase_val();
            } else {
                rgblight_decrease_val();
            }
            #endif
            break;
        default:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
    }
    return true;
}
#endif


#ifdef RGB_MATRIX_ENABLE

void rgb_matrix_indicators_user() {

    // RED ESCAPE
    rgb_matrix_set_color(LED_ESC, RGB_RED);
    rgb_matrix_set_color(LED_PRT, RGB_SPRINGGREEN);
    //rgb_matrix_set_color(LED_LWIN, RGB_MAGENTA);
    //rgb_matrix_set_color(LED_FN, RGB_BLUE);

    if (IS_LAYER_ON(_FN1)) {
        rgb_matrix_set_color(LED_PRT, RGB_GOLD);
    }

    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(LED_CAPS, RGB_GOLD); //capslock key
    }

     for (int i = 0; i < 8; i++) {
        rgb_matrix_set_color(LED_SIDE_LEFT[i], RGB_WHITE);
        rgb_matrix_set_color(LED_SIDE_RIGHT[i], RGB_WHITE);
    }
}

void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}

void keyboard_pre_init_user(void) {
    rgblight_disable();
    rgb_matrix_sethsv_noeeprom(255, 255, 255);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
}

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR + 3);
    rgb_matrix_sethsv_noeeprom(255, 155, 125);
}

#endif
