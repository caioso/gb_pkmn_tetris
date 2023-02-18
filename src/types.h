#pragma once

#include <stdbool.h>
#include <stdint.h>

/* Board-related types */
/* Common board constants */
#define BOARD_WIDTH             (10)
#define BOARD_HEIGHT            (18)
#define BOARD_HORIZONTAL_OFFSET (1u)

/* Allowed block types (optimized to fit in 8 bits)*/
typedef uint8_t block_type_t;
#define BLOCK_TYPE_EMPTY   (0x00)
#define BLOCK_TYPE_RED     (0x01)
#define BLOCK_TYPE_BLUE    (0x02)
#define BLOCK_TYPE_CYAN    (0x03)
#define BLOCK_TYPE_ORANGE  (0x04)
#define BLOCK_TYPE_YELLOW  (0x05)
#define BLOCK_TYPE_GREEN   (0x06)
#define BLOCK_TYPE_PURPLE  (0x07)

typedef struct board_t {
  uint8_t blocks[BOARD_HEIGHT][BOARD_WIDTH];
  uint8_t current_block_type;
  bool dirty;
} board_t;

/* Tetramino-related types */
typedef uint8_t tetramino_type_t;
#define TETRAMINO_TYPE_Z (0x00)
#define TETRAMINO_TYPE_O (0x01)
#define TETRAMINO_TYPE_L (0x02)
#define TETRAMINO_TYPE_S (0x03)
#define TETRAMINO_TYPE_T (0x04)
#define TETRAMINO_TYPE_J (0x05)
#define TETRAMINO_TYPE_I (0x06)

typedef uint8_t rotation_type_t;
#define ROTATION_TYPE_T_0 (0x00)
#define ROTATION_TYPE_T_1 (0x01)
#define ROTATION_TYPE_T_2 (0x02)
#define ROTATION_TYPE_T_3 (0x03)
#define ROTATION_TYPE_T_MAX (0x04)

typedef uint8_t rotation_direction_t;
#define ROTATION_CLOCKWISE         (0x00)
#define ROTATION_COUNTER_CLOCKWISE (0x01)

typedef struct tetramino_t {
   uint8_t x;
   uint8_t y;
   tetramino_type_t type;
   uint8_t first_sprite;
   rotation_type_t rotation;
   uint16_t gravity;
   uint16_t gravity_counter;
   uint8_t lock_delay;
   uint8_t lock_counter;
} tetramino_t;
