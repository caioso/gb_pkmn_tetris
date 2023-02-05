#pragma once

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>
#include <stdbool.h>

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

typedef struct block_t {
  uint8_t type;
} block_t;

typedef struct board_t {
  block_t blocks[BOARD_HEIGHT][BOARD_WIDTH];
  bool dirty;
} board_t;

/* Public Functions*/
/* @brief initialize board with empty blocks
 * @param[in, out] board reference to board object.
 * @param[in] template initialization template.
*/
void gbm_initialize_board(board_t * board, const block_type_t template[BOARD_HEIGHT][BOARD_WIDTH]);

/* @brief update board tiles if needed
 * @param[in] board reference to board object.
*/
void gbm_render_board_if_needed(board_t * board);
