#include "general_board_manager.h"

void gbm_initialize_board(board_t * board, const block_type_t template[BOARD_HEIGHT][BOARD_WIDTH]) {
  uint8_t col = 0;
  uint8_t row = 0;

  for (row = 0; row < BOARD_HEIGHT; row++) {
    for (col = 0; col < BOARD_WIDTH; col++) {
      board->blocks[row][col].type = template[row][col];
    }
  }

  board->dirty = false;
}

void gbm_render_board_if_needed(board_t * board) {
  uint8_t col = 0;
  uint8_t row = 0;

  if (board->dirty == true) {
    for (row = 0; row < BOARD_HEIGHT; row++) {
      for (col = 0; col < BOARD_WIDTH; col++) {
        block_type_t current_type = board->blocks[row][col].type;
        if (current_type != BLOCK_TYPE_EMPTY) {
          /* Temporary: set tile and pallette depending on the type. */
          VBK_REG = VBK_TILES;
          set_bkg_tile_xy(col + BOARD_HORIZONTAL_OFFSET, row, 1);

          VBK_REG = VBK_ATTRIBUTES;
          /* The palette indexes will change. */
          if (current_type == BLOCK_TYPE_RED) {
            set_bkg_tile_xy(col + BOARD_HORIZONTAL_OFFSET, row, 6);
          } else if (current_type == BLOCK_TYPE_BLUE) {
            set_bkg_tile_xy(col + BOARD_HORIZONTAL_OFFSET, row, 4);
          } else if (current_type == BLOCK_TYPE_CYAN) {
            set_bkg_tile_xy(col + BOARD_HORIZONTAL_OFFSET, row, 1);
          } else if (current_type == BLOCK_TYPE_ORANGE) {
            set_bkg_tile_xy(col + BOARD_HORIZONTAL_OFFSET, row, 7);
          } else if (current_type == BLOCK_TYPE_YELLOW) {
            set_bkg_tile_xy(col + BOARD_HORIZONTAL_OFFSET, row, 3);
          } else if (current_type == BLOCK_TYPE_GREEN) {
            set_bkg_tile_xy(col + BOARD_HORIZONTAL_OFFSET, row, 5);
          } else if (current_type == BLOCK_TYPE_PURPLE) {
            set_bkg_tile_xy(col + BOARD_HORIZONTAL_OFFSET, row, 2);
          }
        }
      }
    }

    board->dirty = false;
  }
}