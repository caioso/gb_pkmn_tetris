#include "general_board_manager.h"

void gbm_initialize_board(board_t * board,
                          const uint8_t template[BOARD_HEIGHT][BOARD_WIDTH],
                          uint8_t current_block_type) {
  uint8_t col = 0;
  uint8_t row = 0;

  for (row = 0; row < BOARD_HEIGHT; row++) {
    for (col = 0; col < BOARD_WIDTH; col++) {
      board->blocks[row][col] = template[row][col];
    }
  }
  board->current_block_type = current_block_type;
  board->dirty = false;
}

void gbm_update_board_if_needed(board_t * board) {
  uint8_t col = 0;
  uint8_t row = 0;
  uint8_t current_type = board->current_block_type;

  if (board->dirty == true) {
    for (row = 0; row < BOARD_HEIGHT; row++) {
      for (col = 0; col < BOARD_WIDTH; col++) {
        /* Temporary: set tile and pallette depending on the type. */

        /* The palette indexes will change. */
        if (board->blocks[row][col] == 1) {
          VBK_REG = VBK_TILES;
          set_bkg_tile_xy(col + BOARD_HORIZONTAL_OFFSET, row, 1);

          VBK_REG = VBK_ATTRIBUTES;
          set_bkg_tile_xy(col + BOARD_HORIZONTAL_OFFSET, row, 6);
        } else  {
          VBK_REG = VBK_TILES;
          set_bkg_tile_xy(col + BOARD_HORIZONTAL_OFFSET, row, 0);

          VBK_REG = VBK_ATTRIBUTES;
          set_bkg_tile_xy(col + BOARD_HORIZONTAL_OFFSET, row, 0);
        }
      }
    }

    board->dirty = false;
  }
}