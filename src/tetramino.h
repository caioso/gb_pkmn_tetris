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
 * @param[in] level current game level. */
void t_update_tetramino(tetramino_t * tetramino,
                        board_t * board,
                        uint16_t level);

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

/* @brief Attempts to reset lock delay
 * @param[in, out] tetramino target tetramino. */
void t_try_to_reset_lock_delay(tetramino_t * tetramino);

/* @brief Posts hard drop request (current frame only)
 * @param[in, out] tetramino target tetramino. */
void t_request_hard_drop(tetramino_t * tetramino);

/* @brief Moves tetramino to left or right
  * @param[in, out] tetramino target tetramino.
  * @param[in] board target board.
  * @offset direction */
void t_move_tetramino_horizontally(tetramino_t * tetramino,
                                   board_t * board,
                                   int8_t offset);

/* @brief Toggle soft drop
 * @param[in, out] tetramino target tetramino.
 * @param[in] state sofr_drop_state. */
void t_request_soft_drop(tetramino_t * tetramino, bool state);