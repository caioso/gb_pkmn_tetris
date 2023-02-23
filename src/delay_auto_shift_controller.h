#pragma once

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>
#include <stdbool.h>

#include "constants.h"
#include "data_tables.h"
#include "types.h"

/* @brief Update DAS controller by incrementing one.
 * @param[in, out] das DAS object. */
void das_update(das_t * das);

/* @brief reset DAS
 * @param[in] das DAS object. */
void das_reset_das(das_t * das);