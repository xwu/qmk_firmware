#include QMK_KEYBOARD_H

enum ctrl_keycodes {
    U_T_AGCR = SAFE_RANGE, // USB Toggle Automatic GCR Control
    DBG_TOG,               // DEBUG Toggle On / Off
    DBG_MTRX,              // DEBUG Toggle Matrix Prints
    DBG_KBD,               // DEBUG Toggle Keyboard Prints
    DBG_MOU,               // DEBUG Toggle Mouse Prints
    MD_BOOT,               // Restart into bootloader after hold timeout
};

#define TG_NKRO MAGIC_TOGGLE_NKRO // Toggle 6KRO / NKRO mode

// Tap Dance
enum {
    TD_MPLY_MNXT,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Play/Pause, twice for Next Track
    [TD_MPLY_MNXT] = ACTION_TAP_DANCE_DOUBLE(KC_MPLY, KC_MNXT),
};

#define TD_PLNX TD(TD_MPLY_MNXT)

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   TD_PLNX, KC_MUTE, KC_VOLD, KC_VOLU,            KC_PSCR, KC_SLCK, KC_PAUS, \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                              KC_UP, \
        KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                             KC_RGUI, KC_RALT, MO(1),   KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT \
    ),
    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,             _______, _______, RGB_TOG, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   RGB_HUI, RGB_SAI, RGB_VAI, \
        _______, _______, _______, _______, _______, _______, _______, _______, U_T_AGCR,_______, _______, _______, _______, _______,   RGB_HUD, RGB_SAD, RGB_VAD, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, MD_BOOT, TG_NKRO, EEP_RST, _______, _______, _______, _______,                              RGB_SPI, \
        _______, _______, AG_TOGG,                   _______,                            AG_TOGG, _______, _______, _______,            RGB_RMOD,RGB_SPD, RGB_MOD \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                              _______, \
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______ \
    ),
    */
};

enum ctrl_rgb_mode {
    RGB_MODE_ALL,
    RGB_MODE_KEYLIGHT,
    RGB_MODE_UNDERGLOW,
    RGB_MODE_NONE,
};

// EEPROM storage type.
typedef union {
    uint32_t raw;
    struct {
        uint8_t rgb_mode;
    };
} ctrl_config_t;

ctrl_config_t ctrl_config;

void load_ctrl_config(void) {
    ctrl_config.raw = eeconfig_read_user();
    switch (ctrl_config.rgb_mode) {
        case RGB_MODE_ALL:
            rgb_matrix_set_flags(LED_FLAG_ALL);
            rgb_matrix_enable_noeeprom();
            break;
        case RGB_MODE_KEYLIGHT:
            rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
            rgb_matrix_set_color_all(0, 0, 0);
            break;
        case RGB_MODE_UNDERGLOW:
            rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
            rgb_matrix_set_color_all(0, 0, 0);
            break;
        case RGB_MODE_NONE:
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
            break;
    }
}

void save_ctrl_config(void) {
    switch (rgb_matrix_get_flags()) {
        case LED_FLAG_ALL:
            ctrl_config.rgb_mode = RGB_MODE_ALL;
            break;
        case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR:
            ctrl_config.rgb_mode = RGB_MODE_KEYLIGHT;
            break;
        case LED_FLAG_UNDERGLOW:
            ctrl_config.rgb_mode = RGB_MODE_UNDERGLOW;
            break;
        default:
            ctrl_config.rgb_mode = RGB_MODE_NONE;
            break;
    }
    eeconfig_update_user(ctrl_config.raw);
}

void keyboard_post_init_user(void) {
    load_ctrl_config();
}

void eeconfig_init_user(void) {
    save_ctrl_config();
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= BOOTKEY_HOLD_MS) {
                    reset_keyboard();
                }
            }
            return false;
        case EEP_RST:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= BOOTKEY_HOLD_MS) {
                    eeconfig_init();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL:
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                        rgb_matrix_set_color_all(0, 0, 0);
                        break;
                    case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR:
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        rgb_matrix_set_color_all(0, 0, 0);
                        break;
                    case LED_FLAG_UNDERGLOW:
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_disable_noeeprom();
                        break;
                    default:
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable_noeeprom();
                        break;
                }
                save_ctrl_config();
            }
            return false;
        default:
            return true; // Process all other keycodes normally.
    }
}
