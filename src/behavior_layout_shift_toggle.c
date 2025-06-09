#define DT_DRV_COMPAT zmk_behavior_layout_shift_toggle

#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <string.h>
#include <drivers/behavior.h>
#include <zmk/behavior.h>
#include <zmk/event_manager.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

enum toggle_mode {
    TOGGLE_MODE_ON,
    TOGGLE_MODE_OFF,
    TOGGLE_MODE_FLIP
};

struct behavior_layout_shift_toggle_config {
    enum toggle_mode toggle_mode;
};

struct behavior_layout_shift_toggle_data {};

// Global layout shift state
static bool layout_shift_active = false;

// Function to get current layout shift state
bool zmk_layout_shift_is_active(void) {
    return layout_shift_active;
}

// Function to set layout shift state
void zmk_layout_shift_set_active(bool active) {
    if (layout_shift_active != active) {
        layout_shift_active = active;
        LOG_INF("Layout shift %s", active ? "activated" : "deactivated");
    }
}

// Function to toggle layout shift state
void zmk_layout_shift_toggle(void) {
    zmk_layout_shift_set_active(!layout_shift_active);
}

static int on_layout_shift_toggle_binding_pressed(struct zmk_behavior_binding *binding,
                                                 struct zmk_behavior_binding_event event) {
    const struct device *dev = zmk_behavior_get_binding(binding->behavior_dev);
    const struct behavior_layout_shift_toggle_config *config = dev->config;

    switch (config->toggle_mode) {
        case TOGGLE_MODE_ON:
            zmk_layout_shift_set_active(true);
            break;
        case TOGGLE_MODE_OFF:
            zmk_layout_shift_set_active(false);
            break;
        case TOGGLE_MODE_FLIP:
            zmk_layout_shift_toggle();
            break;
    }

    return ZMK_BEHAVIOR_OPAQUE;
}

static int on_layout_shift_toggle_binding_released(struct zmk_behavior_binding *binding,
                                                  struct zmk_behavior_binding_event event) {
    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api behavior_layout_shift_toggle_driver_api = {
    .binding_pressed = on_layout_shift_toggle_binding_pressed,
    .binding_released = on_layout_shift_toggle_binding_released,
    .locality = BEHAVIOR_LOCALITY_GLOBAL,
#if IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)
    .get_parameter_metadata = zmk_behavior_get_empty_param_metadata,
#endif
};

static int layout_shift_toggle_init(const struct device *dev) {
    layout_shift_active = false;
    LOG_INF("Layout Shift Toggle Behavior Initialized!");
    return 0;
}

#define TOGGLE_MODE_FROM_STR(str) \
    (strcmp(str, "on") == 0 ? TOGGLE_MODE_ON : \
     strcmp(str, "off") == 0 ? TOGGLE_MODE_OFF : \
     TOGGLE_MODE_FLIP)

#define LAYOUT_SHIFT_TOGGLE_INST(n) \
    static struct behavior_layout_shift_toggle_data behavior_layout_shift_toggle_data_##n = {}; \
    static const struct behavior_layout_shift_toggle_config behavior_layout_shift_toggle_config_##n = { \
        .toggle_mode = TOGGLE_MODE_FROM_STR(DT_INST_PROP_OR(n, toggle_mode, "flip")), \
    }; \
    BEHAVIOR_DT_INST_DEFINE(n, layout_shift_toggle_init, NULL, \
                            &behavior_layout_shift_toggle_data_##n, \
                            &behavior_layout_shift_toggle_config_##n, \
                            POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, \
                            &behavior_layout_shift_toggle_driver_api);

DT_INST_FOREACH_STATUS_OKAY(LAYOUT_SHIFT_TOGGLE_INST)