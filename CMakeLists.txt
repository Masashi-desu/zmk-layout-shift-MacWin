# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.20.5)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(zmk-layout-shift)

if(CONFIG_LAYOUT_SHIFT)
  zephyr_sources(
    ${CMAKE_CURRENT_LIST_DIR}/src/behavior_layout_shift_key_press.c
    ${CMAKE_CURRENT_LIST_DIR}/src/behavior_layout_shift_toggle.c
  )
  zephyr_library_link_libraries(subsys__input)
endif()
