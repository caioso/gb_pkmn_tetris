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

void gbm_write_tetramino_to_board(board_t * board, tetramino_t * tetramino) {
  uint8_t i = 0;

  for (i = 0; i < 4; i++) {
    uint8_t tetramino_x = tetramino->x + tetramino_sprite_position_offset[tetramino->type][i][0];
    uint8_t tetramino_y = tetramino->y + tetramino_sprite_position_offset[tetramino->type][i][1];
    uint8_t board_col = (tetramino_x - 16) >> 3;
    uint8_t board_row = (tetramino_y - 16) >> 3;
    board->blocks[board_row][board_col] = 1;
  }
  board->dirty = true;
}

void remove_full_lines(board_t * board) {
  uint8_t col = 0;
  int8_t row = 0;

  for (row = 0; row < BOARD_HEIGHT; row++) {
    bool line_full = true;
    for (col = 0; col < BOARD_WIDTH; col++) {
      if (board->blocks[row][col] == 0) {
        line_full = false;
        break;
      }
    }

    if (line_full == true) {
      /* Mark line to be cleared */
      board->blocks[row][0] = 2;
      board->dirty = true;
    }
  }

  /* Clear lines */
  for (row = BOARD_HEIGHT - 1; row >= 0; row--) {
    if (board->blocks[row][0] == 2) {
      for (int8_t collapse_row = row - 1; collapse_row >= 0; collapse_row--) {
        for (col = 0; col < BOARD_WIDTH; col++) {
          board->blocks[collapse_row + 1][col] = board->blocks[collapse_row][col];
        }
      }
      row++;
    }
  }
}