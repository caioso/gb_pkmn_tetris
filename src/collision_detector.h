#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "tetramino.h"
#include "general_board_manager.h"

/* @brief detect whether the tetramino collided with pieces in the board.
 * @param[in] board target board.
 * @param[in] tetramino target tetramino.
 * @param[in] x offset x.
 * @param[in] y offset y.
 * @return collision detected (or not). */
bool cd_detect_collision(board_t * board, tetramino_t * tetramino, int16_t x, int16_t y);

/* @brief detect tetramino and board overlap
 * @param[in] board target board.
 * @param[in] tetramino target tetramino.
 * @return overlap detected (or not). */
bool cd_detect_overlap(board_t * board, tetramino_t * tetramino);