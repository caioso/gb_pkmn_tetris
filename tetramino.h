#pragma once

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdlib.h>
#include <stdint.h>

#include "constants.h"
#include "data_tables.h"
#include "types.h"

/* public functions */
/* @brief initialize tetramino data structure.
 * @param[in, out] tetramino piece datastructure.
 * @paramp[in] target tetramino_type.
 * @paramp[in] fisrt_sprite first sprite (sequentially taking the next four). */
void t_initialize_tetramino(tetramino_t * tetramino,
                            uint8_t type,
                            uint8_t first_sprite);

/* @brief calculate next tetramino state
 * @param[in, out] target tetramino
 * @param[in] board target board.
 */
void t_update_tetramino(tetramino_t * tetramino,
                        board_t * board);

/* @brief spawn tetramino at location described in the official rules.
 * @param[in, out] target tetramino */
void t_spawn_tetramino(tetramino_t * tetramino);

/* @brief Attempt tetramino rotation based on standard rotation and wallkick tests.
 * @param[in, out] tetramino target tetramino.
 * @param[in] board target board.
 * @param[in] rotation tetramino rotation direction. */
void t_try_to_rotate_tetramino(tetramino_t * tetramino,
                               board_t * board,
                               rotation_direction_t direction);