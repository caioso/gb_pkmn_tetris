#include "collision_detector.h"

typedef struct point_t {
    uint8_t x, y;
} point_t;


bool do_overlap(point_t * r1, point_t * r2);

bool cd_detect_collision(board_t *board, tetramino_t *tetramino, int8_t x, int8_t y) {
  bool collision = false;
  uint8_t board_col = (tetramino->x - 16 + x) >> 3;
  uint8_t board_row = (tetramino->y - 16 + y) >> 3;
  point_t tetramino_rectangle = {
    .x = tetramino->x,
    .y = tetramino->y,
  };
  point_t board_rectangle = {
    .x = 0,
    .y = 0,
  };

  if (x > 0) {
    if (board->blocks[board_row][board_col + 1] == 1) {
      board_rectangle.x = (((board_col + 1) << 3) + 16);
      board_rectangle.y = ((board_row << 3) + 16);
      collision |= do_overlap(&tetramino_rectangle, &board_rectangle);
    }
    if (collision == false && board->blocks[board_row + 1][board_col + 1] == 1) {
      board_rectangle.x = (((board_col + 1) << 3) + 16);
      board_rectangle.y = (((board_row + 1) << 3) + 16);
      collision |= do_overlap(&tetramino_rectangle, &board_rectangle);
    }
  } else if (x < 0) {
    if (board->blocks[board_row][board_col] == 1) {
      board_rectangle.x = ((board_col << 3) + 16);
      board_rectangle.y = ((board_row << 3) + 16);
      collision |= do_overlap(&tetramino_rectangle, &board_rectangle);
    }
    if (collision == false && board->blocks[board_row + 1][board_col] == 1) {
      board_rectangle.x = ((board_col << 3) + 16);
      board_rectangle.y = (((board_row + 1) << 3) + 16);
      collision |= do_overlap(&tetramino_rectangle, &board_rectangle);
    }

  }

  if (y > 0) {
    if (board->blocks[board_row + 1][board_col] == 1) {
      board_rectangle.x = ((board_col << 3) + 16);
      board_rectangle.y = (((board_row + 1) << 3) + 16);
      collision |= do_overlap(&tetramino_rectangle, &board_rectangle);
    }
    if (collision == false && board->blocks[board_row + 1][board_col + 1] == 1) {
      board_rectangle.x = (((board_col + 1) << 3) + 16);
      board_rectangle.y = (((board_row + 1) << 3) + 16);
      collision |= do_overlap(&tetramino_rectangle, &board_rectangle);
    }
  } else if (y < 0) {
    if (board->blocks[board_row][board_col] == 1) {
      board_rectangle.x = ((board_col << 3) + 16);
      board_rectangle.y = (((board_row) << 3) + 16);
      collision |= do_overlap(&tetramino_rectangle, &board_rectangle);
    }
    if (collision == false && board->blocks[board_row][board_col + 1] == 1) {
      board_rectangle.x = (((board_col + 1) << 3) + 16);
      board_rectangle.y = (((board_row) << 3) + 16);
      collision |= do_overlap(&tetramino_rectangle, &board_rectangle);
    }
  }

  return collision;
}

bool valueInRange(uint8_t value, uint8_t min, uint8_t max)
{ return (value >= min) && (value <= max); }


bool do_overlap(point_t * r1, point_t * r2) {
  bool xOverlap = valueInRange(r1->x, r2->x, r2->x + 8) ||
                  valueInRange(r2->x, r1->x, r1->x + 8);
  bool yOverlap = valueInRange(r1->y, r2->y, r2->y + 8) ||
                  valueInRange(r2->y, r1->y, r1->y + 8);
  return xOverlap && yOverlap;
}