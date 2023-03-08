#pragma once

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>
#include <stdbool.h>

#include "types.h"

/* @brief Catch Controller Object Initialized.
 * @param[in, out] catch_controller Catch controller object. */
void cc_catch_controller_init(catch_controller_t * catch_controller);

/* @brief Catch Controller Object Initialized.
 * @param[in, out] catch_controller Catch controller object.
 * @param[in] progress current progress (from 0 to 64). */
void cc_catch_controller_set_progress(catch_controller_t * catch_controller,
                                      int8_t progress);

/* @brief Catch Controller Update.
 * @param[in, out] catch_controller Catch controller object */
void cc_catch_controller_update(catch_controller_t * catch_controller);