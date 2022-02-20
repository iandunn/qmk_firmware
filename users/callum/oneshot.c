#include "oneshot.h"

#include <print.h>

void update_oneshot(
    oneshot_state *state,
    uint16_t mod,       // eg, KC_LALT
    uint16_t trigger,   // eg, OS_ALT
    uint16_t keycode,   // the key that was actually pressed on the board which triggered procrecuser
    keyrecord_t *record
) {
//    dprintf("trigger: %s", trigger); // this breaks everything. maybe it's an unprintable code or something?
//    dprintf("keycode: %s %d", keycode, keycode); // lets try something simpler
    // that prints initialy then whole board breaks again. wtf

    if (keycode == trigger) {
        printf("i pressed {trigger}");

        if (record->event.pressed) {
            printf("print state before and after?");
            // Trigger keydown
            if (*state == os_up_unqueued) {
                register_code(mod);
            }
            *state = os_down_unused;
        } else {
            printf("print state before and after?");
            // Trigger keyup
            switch (*state) {
            case os_down_unused:
                // If we didn't use the mod while trigger was held, queue it.
                *state = os_up_queued;
                break;
            case os_down_used:
                // If we did use the mod while trigger was held, unregister it.
                *state = os_up_unqueued;
                unregister_code(mod);
                break;
            default:
                break;
            }
        }
    } else {
        printf("i pressed some other key");

        if (record->event.pressed) {
            printf("print state before and after?");
            if (is_oneshot_cancel_key(keycode) && *state != os_up_unqueued) {
                // Cancel oneshot on designated cancel keydown.
                *state = os_up_unqueued;
                unregister_code(mod);
            }
        } else {
          printf("print state before and after?");
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                case os_down_unused:
                    *state = os_down_used;
                    break;
                case os_up_queued:
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    break;
                default:
                    break;
                }
            }
        }
    }
}
