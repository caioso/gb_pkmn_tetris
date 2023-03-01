#pragma once

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "types.h"

/* @brief request screen shake.
 * @param[in, out] tetramino piece datastructure. */
void sc_shake_screen(tetramino_t * tetramino);

/* @brief informs whether the screen is shaking
 * @return screen shake status */
bool sc_is_screen_shaking(void);

/* @brief update screen controller.
 * @param[in, out] tetramino piece datastructure. */
void sc_update_screen_controller(tetramino_t * tetramino);