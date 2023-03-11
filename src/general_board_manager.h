#pragma once

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>
#include <stdbool.h>

#include "catch_controller.h"
#include "constants.h"
#include "data_tables.h"
#include "pokemon_portrait.h"
#include "types.h"

/* Public Functions*/
/* @brief initialize board with empty blocks
 * @param[in, out] board reference to board object.
 * @param[in] template initialization template.
 * @param[in] current_block_type board blocks color.
*/
void gbm_initialize_board(board_t * board,
                          const uint8_t template[BOARD_HEIGHT][BOARD_WIDTH],
                          uint8_t current_block_type);

/* @brief update board tiles if needed
 * @param[in] board reference to board object.
*/
void gbm_update_board_if_needed(board_t * board);

/* @brief writes tetramino pieces to board.
 * @param[in, out] board reference to board object.
 * @param[in] tetramino target tetramino to be written to the board. */
void gbm_write_tetramino_to_board(board_t * board, tetramino_t * tetramino);

/* @brief clear any full line in the board
 * @TODO: Move this to RED mode file.
 * @param[in, out] board reference to board object. */
void gmb_remove_full_lines(board_t * board);

/* @brief Shine backround based on position
 * @param[in, out] board reference to board object.
 * @param[in] tetramino target tetramino to be written to the board. */
void gmb_shine_background(board_t * board, tetramino_t * tetramino);

/* @brief Count broken lines and update portrait and progress bat.
 * @param[in, out] board reference to board object.
 * @param[in, out] catch_controller Pokemon catch controller.
 * @param[in, out] portrait Pokemon portait. */
void gmb_count_broken_rows(board_t * board, catch_controller_t * catch_controller,
                           pokemon_portrait_t * portrait);