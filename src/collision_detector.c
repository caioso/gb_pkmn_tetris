#include "collision_detector.h"

typedef struct point_t {
    uint16_t x, y;
} point_t;

bool cd_detect_collision(board_t * board, tetramino_t * tetramino, int16_t x, int16_t y) {
  int16_t i, j, k, l;
  int16_t initial_x = ((tetramino->x - PLAYFIELD_OFFSET_X) >> 3);
  int16_t initial_y = ((tetramino->y - PLAYFIELD_OFFSET_Y) >> 3);

  for (j = 0, k = 0; j < 4; j++, k++) {
    for (i = 0, l = 0; i <  4; i++, l++) {
      uint8_t current_board_value =
        tetramino_sprite_position_template[tetramino->type][tetramino->rotation][k][l];
      if (current_board_value == 1 &&
        ((i + initial_x + x < 0) || (i + initial_x + x >= BOARD_WIDTH) ||
         (j + initial_y + y < 0) || (j + initial_y + y >= BOARD_HEIGHT))) {
        return true;
      }

      if (board->blocks[j + initial_y + y][i + initial_x + x] == 1 && current_board_value == 1) {
        return true;
      }
    }
  }
  return false;
}