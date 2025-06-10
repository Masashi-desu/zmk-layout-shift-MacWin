// Layout index - includes all available layout definitions
// Each layout file contains its own conditional compilation directives

#include "layout_jis.h"
#include "layout_dvorak.h"

// Ensure at least one layout is defined
#ifndef LAYOUT_DEFINED
#error "No target layout selected. Please select a layout in Kconfig."
#endif
