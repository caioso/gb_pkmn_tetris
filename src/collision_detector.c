#include "collision_detector.h"

typedef struct point_t {
    uint16_t x, y;
} point_t;


bool do_overlap(point_t * r1, point_t * r2);

bool cd_detect_collision(board_t * board, tetramino_t * tetramino, int16_t x, int16_t y) {
  uint8_t i = 0;
  bool collision = false;
  for (i = 0; i < 4; i++) {
    uint16_t tetramino_x = tetramino->x + tetramino_sprite_position_offset[tetramino->type][tetramino->rotation][i][0];
    uint16_t tetramino_y = tetramino->y + tetramino_sprite_position_offset[tetramino->type][tetramino->rotation][i][1];
    uint16_t board_col = (tetramino_x - PLAYFIELD_OFFSET_X + x) >> 3;
    uint16_t board_row = (tetramino_y - PLAYFIELD_OFFSET_Y + y) >> 3;
    point_t tetramino_rectangle = {
      .x = tetramino_x,
      .y = tetramino_y,
    };
    point_t board_rectangle = {
      .x = 0,
      .y = 0,
    };

    if (x < 0 && tetramino_x <= PLAYFIELD_OFFSET_X) {
      return true;
    } else if (x > 0 && tetramino_x + BLOCK_SIDE_IN_PIXELS >=
               PLAYFIELD_OFFSET_X + BOARD_WIDTH * BLOCK_SIDE_IN_PIXELS) {
      return true;
    }

    if (y < 0 && tetramino_y <= PLAYFIELD_OFFSET_Y) {
      return true;
    } else if (y > 0 && tetramino_y + BLOCK_SIDE_IN_PIXELS >=
               PLAYFIELD_OFFSET_Y + BOARD_HEIGHT * BLOCK_SIDE_IN_PIXELS) {
      return true;
    }

    if (x > 0) {
      if (board->blocks[board_row][board_col + 1] == 1) {
        board_rectangle.x = (((board_col + 1) << 3) + PLAYFIELD_OFFSET_X);
        board_rectangle.y = ((board_row << 3) + PLAYFIELD_OFFSET_Y);
        collision |= do_overlap(&tetramino_rectangle, &board_rectangle);
      }
      if ((tetramino_y) % BLOCK_SIDE_IN_PIXELS != 0x00 && collision == false &&
          board->blocks[board_row + 1][board_col + 1] == 1) {
        board_rectangle.x = (((board_col + 1) << 3) + PLAYFIELD_OFFSET_X);
        board_rectangle.y = (((board_row + 1) << 3) + PLAYFIELD_OFFSET_Y);
        collision |= do_overlap(&tetramino_rectangle, &board_rectangle);
      }
    } else if (x < 0) {
      if (board->blocks[board_row][board_col] == 1) {
        board_rectangle.x = ((board_col << 3) + PLAYFIELD_OFFSET_X);
        board_rectangle.y = ((board_row << 3) + PLAYFIELD_OFFSET_Y);
        collision |= do_overlap(&tetramino_rectangle, &board_rectangle);
      }
      if ((tetramino_y) % BLOCK_SIDE_IN_PIXELS != 0x00 && collision == false &&
          board->blocks[board_row + 1][board_col] == 1) {
        board_rectangle.x = ((board_col << 3) + PLAYFIELD_OFFSET_X);
        board_rectangle.y = (((board_row + 1) << 3) + PLAYFIELD_OFFSET_Y);
        collision |= do_overlap(&tetramino_rectangle, &board_rectangle);
      }

    }

    if (y > 0) {
      if (board->blocks[board_row + 1][board_col] == 1) {
        board_rectangle.x = ((board_col << 3) + PLAYFIELD_OFFSET_X);
        board_rectangle.y = (((board_row + 1) << 3) + PLAYFIELD_OFFSET_Y);
        collision |= do_overlap(&tetramino_rectangle, &board_rectangle);
      }
      if ((tetramino_x) % BLOCK_SIDE_IN_PIXELS != 0x00 && collision == false &&
          board->blocks[board_row + 1][board_col + 1] == 1) {
        board_rectangle.x = (((board_col + 1) << 3) + PLAYFIELD_OFFSET_X);
        board_rectangle.y = (((board_row + 1) << 3) + PLAYFIELD_OFFSET_Y);
        collision |= do_overlap(&tetramino_rectangle, &board_rectangle);
      }
    } else if (y < 0) {
      if (board->blocks[board_row][board_col] == 1) {
        board_rectangle.x = ((board_col << 3) + PLAYFIELD_OFFSET_X);
        board_rectangle.y = (((board_row) << 3) + PLAYFIELD_OFFSET_Y);
        collision |= do_overlap(&tetramino_rectangle, &board_rectangle);
      }
      if ((tetramino_x) % BLOCK_SIDE_IN_PIXELS != 0x00 && collision == false &&
          board->blocks[board_row][board_col + 1] == 1) {
        board_rectangle.x = (((board_col + 1) << 3) + PLAYFIELD_OFFSET_X);
        board_rectangle.y = (((board_row) << 3) + PLAYFIELD_OFFSET_Y);
        collision |= do_overlap(&tetramino_rectangle, &board_rectangle);
      }
    }

    if (collision == true) {
      break;
    }
  }
  return collision;
}

bool valueInRange(uint16_t value, uint16_t min, uint16_t max)
{ return (value >= min) && (value <= max); }

bool do_overlap(point_t * r1, point_t * r2) {
  bool xOverlap = valueInRange(r1->x, r2->x, r2->x + BLOCK_SIDE_IN_PIXELS) ||
                  valueInRange(r2->x, r1->x, r1->x + BLOCK_SIDE_IN_PIXELS);
  bool yOverlap = valueInRange(r1->y, r2->y, r2->y + BLOCK_SIDE_IN_PIXELS) ||
                  valueInRange(r2->y, r1->y, r1->y + BLOCK_SIDE_IN_PIXELS);
  return xOverlap && yOverlap;
}