#pragma once

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdlib.h>
#include <stdint.h>

#include "constants.h"

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

/* Format: [TYPE][ROTATION][SPRITE][X/Y] */
extern const uint8_t tetramino_sprite_position_offset[7][4][4][2];

typedef struct tetramino_t {
   uint8_t x;
   uint8_t y;
   tetramino_type_t type;
   uint8_t first_sprite;
   rotation_type_t rotation;
} tetramino_t;

/* public functions */
/* @brief initialize tetramino data structure.
 * @param[in, out] tetramino piece datastructure.
 * @paramp[in] target tetramino_type.
 * @paramp[in] fisrt_sprite first sprite (sequentially taking the next four). */
void t_initialize_tetramino(tetramino_t * tetramino,
                            uint8_t type,
                            uint8_t first_sprite);

/* @brief calculate next tetramino state
 * @param[in, out] target tetramino*/
void t_update_tetramino(tetramino_t * tetramino);

/* @brief spawn tetramino at location described in the official rules.
 * @param[in, out] target tetramino */
void t_spawn_tetramino(tetramino_t * tetramino);

/* @brief rotate tetramino considering wall kick
 * @param[in, out] target tetramino */
void t_rotate_tetramino(tetramino_t * tetramino);