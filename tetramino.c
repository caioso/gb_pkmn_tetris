#include "tetramino.h"
#include "constants.h"

void initialize_tetraminos_sprites(tetramino_t * tetramino);
void set_sprites_position_from_type(tetramino_t * tetramino);

/* Format: [TYPE][SPRITE][X/Y] */
const uint8_t tetramino_sprite_position_offset[6][4][2] = {
    /* TETRAMINO_TYPE_Z */
    {{0, 0}, {BLOCK_SIDE_IN_PIXELS, 0}, {BLOCK_SIDE_IN_PIXELS, BLOCK_SIDE_IN_PIXELS}, {2 * BLOCK_SIDE_IN_PIXELS, BLOCK_SIDE_IN_PIXELS}},
    /* TETRAMINO_TYPE_O */
    {{0, 0}, {BLOCK_SIDE_IN_PIXELS, 0}, {0, BLOCK_SIDE_IN_PIXELS}, {BLOCK_SIDE_IN_PIXELS, BLOCK_SIDE_IN_PIXELS}},
    /* TETRAMINO_TYPE_L */
    {{0, 0}, {0, BLOCK_SIDE_IN_PIXELS}, {0, 2 * BLOCK_SIDE_IN_PIXELS}, {BLOCK_SIDE_IN_PIXELS, 2 * BLOCK_SIDE_IN_PIXELS}},
    /* TETRAMINO_TYPE_S */
    {{BLOCK_SIDE_IN_PIXELS, 0}, {2 * BLOCK_SIDE_IN_PIXELS, 0}, {0, BLOCK_SIDE_IN_PIXELS}, {BLOCK_SIDE_IN_PIXELS, BLOCK_SIDE_IN_PIXELS}},
    /* TETRAMINO_TYPE_T */
    {{0, 0}, {BLOCK_SIDE_IN_PIXELS, 0}, {2 * BLOCK_SIDE_IN_PIXELS, 0}, {BLOCK_SIDE_IN_PIXELS, BLOCK_SIDE_IN_PIXELS}},
    /* TETRAMINO_TYPE_J */
    {{BLOCK_SIDE_IN_PIXELS, 0}, {BLOCK_SIDE_IN_PIXELS, BLOCK_SIDE_IN_PIXELS}, {BLOCK_SIDE_IN_PIXELS, 2 * BLOCK_SIDE_IN_PIXELS}, {0, 2 * BLOCK_SIDE_IN_PIXELS}},
};

void t_initialize_tetramino(tetramino_t * tetramino,
                            uint8_t type,
                            uint8_t first_sprite) {
  tetramino->y = 40;
  tetramino->x = BLOCK_SIDE_IN_PIXELS * 5;
  tetramino->type = type;
  tetramino->first_sprite = first_sprite;

  initialize_tetraminos_sprites(tetramino);
  set_sprites_position_from_type(tetramino);
}

void t_update_tetramino(tetramino_t * tetramino) {
  (void)tetramino;
}

/* private functions */
void initialize_tetraminos_sprites(tetramino_t * tetramino) {
  /* Initialize palette and sprite */
  /* TODO: values here are temporary. */
  set_sprite_tile(tetramino->first_sprite, 1);
  set_sprite_prop(tetramino->first_sprite, 6);
  set_sprite_tile(tetramino->first_sprite + 1, 1);
  set_sprite_prop(tetramino->first_sprite + 1, 6);
  set_sprite_tile(tetramino->first_sprite + 2, 1);
  set_sprite_prop(tetramino->first_sprite + 2, 6);
  set_sprite_tile(tetramino->first_sprite + 3, 1);
  set_sprite_prop(tetramino->first_sprite + 3, 6);

}

void set_sprites_position_from_type(tetramino_t * tetramino) {
  uint8_t i = 0;
  for (i = 0; i < 4; i++) {
    move_sprite(tetramino->first_sprite + i,
                tetramino->x + tetramino_sprite_position_offset[tetramino->type][i][0],
                tetramino->y + tetramino_sprite_position_offset[tetramino->type][i][1]);
  }
}
