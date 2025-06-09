#define DT_DRV_COMPAT zmk_behavior_layout_shift

#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <drivers/behavior.h>
#include <zmk/behavior.h>
#include <zmk/event_manager.h>
#include <zmk/events/keycode_state_changed.h>
#include <zmk/hid.h>
#include <zmk/keys.h>
#include <dt-bindings/zmk/hid_usage.h>
#include <dt-bindings/zmk/hid_usage_pages.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

struct behavior_layout_shift_data {
    // No data needed for now
};

struct behavior_layout_shift_config {
    // No configuration needed for now
};

// Global state for the behavior
static bool a_key_active = false;

static int behavior_layout_shift_keycode_state_changed_listener(const zmk_event_t *eh) {
    struct zmk_keycode_state_changed *ev = as_zmk_keycode_state_changed(eh);

    if (ev == NULL) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    // Skip if already 'A' to avoid infinite loops
    if (ev->keycode == HID_USAGE_KEY_KEYBOARD_A) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    LOG_ERR("LAYOUT_SHIFT: MODIFYING keycode 0x%02X -> A", ev->keycode);

    // Directly modify the keycode in the existing event
    ev->usage_page = HID_USAGE_KEY;
    ev->keycode = HID_USAGE_KEY_KEYBOARD_A;

    LOG_ERR("LAYOUT_SHIFT: Event modified, bubbling to HID");
    return ZMK_EV_EVENT_BUBBLE;
}

// Behavior driver API
static int on_layout_shift_binding_pressed(struct zmk_behavior_binding *binding,
                                           struct zmk_behavior_binding_event event) {
    // This is a global behavior, not bound to specific keys
    return ZMK_BEHAVIOR_OPAQUE;
}

static int on_layout_shift_binding_released(struct zmk_behavior_binding *binding,
                                            struct zmk_behavior_binding_event event) {
    // This is a global behavior, not bound to specific keys
    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api behavior_layout_shift_driver_api = {
    .binding_pressed = on_layout_shift_binding_pressed,
    .binding_released = on_layout_shift_binding_released,
    .locality = BEHAVIOR_LOCALITY_GLOBAL,
#if IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)
    .get_parameter_metadata = zmk_behavior_get_empty_param_metadata,
#endif
};

// Behavior initialization
static int behavior_layout_shift_init(void) {
    a_key_active = false;
    LOG_INF("Layout Shift Behavior Initialized!");
    return 0;
}

// Register as event listener
ZMK_LISTENER(aaa_early_layout_shift, behavior_layout_shift_keycode_state_changed_listener);
ZMK_SUBSCRIPTION(aaa_early_layout_shift, zmk_keycode_state_changed);

// Define behavior instance without devicetree dependency
static struct behavior_layout_shift_data behavior_layout_shift_data_0 = {};
static const struct behavior_layout_shift_config behavior_layout_shift_config_0 = {};

// Use SYS_INIT instead for simpler initialization
SYS_INIT(behavior_layout_shift_init, POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);