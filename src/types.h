#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>


/* useful types */
typedef struct point_2d_t {
  uint8_t y;
  uint8_t x;
} point_2d_t;

/* Board-related types */
/* Common board constants */
#define BOARD_WIDTH             (10)
#define BOARD_HEIGHT            (20)
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
  point_2d_t shine_position[4];
  bool shine_requested;
  uint8_t current_block_type;
  bool dirty;
  uint8_t rows_removed_this_frame;
  uint16_t total_removed_lines;
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
#define TETRAMINO_TYPE_NULL (0x07)

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
   int16_t x;
   int16_t y;
   uint8_t x_offset;
   uint8_t y_offset;
   uint8_t ghost_y;
   uint8_t ghost_x_offset;
   uint8_t ghost_y_offset;
   tetramino_type_t type;
   uint8_t first_sprite;
   rotation_type_t rotation;
   uint16_t gravity;
   uint16_t gravity_counter;
   uint8_t lock_delay;
   uint8_t lock_counter;
   bool hard_drop_request;
   bool should_update_ghost;
   bool soft_drop_enabled;
   tetramino_type_t held;
   bool held_request;
   bool held_swapped_allowed;
   bool just_spawned;
} tetramino_t;

/* DAS types */
typedef struct das_t {
  bool movement_allowed;
  bool delay_auto_shift_enabled;
  uint8_t delay_auto_shift_counter;
} das_t;

typedef struct randomizer_t {
  tetramino_type_t bag[7];
  uint8_t length;
} randomizer_t;

typedef uint8_t screen_rumble_direction_t;
#define SCREEN_RUMBLE_DIRECTION_RIGHT (0x00)
#define SCREEN_RUMBLE_DIRECTION_LEFT (0x01)
#define SCREEN_RUMBLE_DIRECTION_DOWN (0x02)
#define SCREEN_RUMBLE_DIRECTION_UP (0x03)

/* Catch controller */
typedef struct catch_controller_t {
  uint8_t catch_target;
  uint8_t catch_progress;
  uint8_t num_bars_to_fill;
  bool progress_dirty;
} catch_controller_t;

/* Pokemon Portrait */
typedef struct pokemon_portrait_t {
  uint8_t noise_level;
  uint8_t initial_tile_index;
  uint8_t tile_w;
  uint8_t tile_h;
  uint8_t origin_x;
  uint8_t origin_y;
  uint8_t * tile_bytes;
  uint8_t * attribute_bytes;
  palette_color_t * palette_bytes;
  bool dirty;
} pokemon_portrait_t;