#include "tetramino.h"

/* Format: [TYPE][ROTATION][SPRITE][X/Y] */
const uint8_t tetramino_sprite_position_offset[7][4][4][2] = {
    /* TETRAMINO_TYPE_Z */
    {
      /* ROTATION 0 */
      {{TEMPLATE_00, TEMPLATE_00}, {TEMPLATE_1P, TEMPLATE_00}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_2P, TEMPLATE_1P}},
      /* ROTATION 1 */
      {{TEMPLATE_2P, TEMPLATE_00}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_2P, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_2P}},
      /* ROTATION 2 */
      {{TEMPLATE_00, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_2P}, {TEMPLATE_2P, TEMPLATE_2P}},
      /* ROTATION 3 */
      {{TEMPLATE_1P, TEMPLATE_00}, {TEMPLATE_00, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_00, TEMPLATE_2P}},
    },
    /* TETRAMINO_TYPE_O */
    {
      /* ROTATION 0 */
      {{TEMPLATE_1P, TEMPLATE_00}, {TEMPLATE_2P, TEMPLATE_00}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_2P, TEMPLATE_1P}},
      /* ROTATION 1 */
      {{TEMPLATE_1P, TEMPLATE_00}, {TEMPLATE_2P, TEMPLATE_00}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_2P, TEMPLATE_1P}},
      /* ROTATION 2 */
      {{TEMPLATE_1P, TEMPLATE_00}, {TEMPLATE_2P, TEMPLATE_00}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_2P, TEMPLATE_1P}},
      /* ROTATION 3 */
      {{TEMPLATE_1P, TEMPLATE_00}, {TEMPLATE_2P, TEMPLATE_00}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_2P, TEMPLATE_1P}},
    },
    /* TETRAMINO_TYPE_L */
    {
      /* ROTATION 0 */
      {{TEMPLATE_2P, TEMPLATE_00}, {TEMPLATE_00, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_2P, TEMPLATE_1P}},
      /* ROTATION 1 */
      {{TEMPLATE_1P, TEMPLATE_00}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_2P}, {TEMPLATE_2P, TEMPLATE_2P}},
      /* ROTATION 2 */
      {{TEMPLATE_00, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_2P, TEMPLATE_1P}, {TEMPLATE_00, TEMPLATE_2P}},
      /* ROTATION 3 */
      {{TEMPLATE_00, TEMPLATE_00}, {TEMPLATE_1P, TEMPLATE_00}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_2P}},
    },
    /* TETRAMINO_TYPE_S */
    {
      /* ROTATION 0 */
      {{TEMPLATE_1P, TEMPLATE_00}, {TEMPLATE_2P, TEMPLATE_00}, {TEMPLATE_00, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_1P}},
      /* ROTATION 1 */
      {{TEMPLATE_1P, TEMPLATE_00}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_2P, TEMPLATE_1P}, {TEMPLATE_2P, TEMPLATE_2P}},
      /* ROTATION 2 */
      {{TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_2P, TEMPLATE_1P}, {TEMPLATE_00, TEMPLATE_2P}, {TEMPLATE_1P, TEMPLATE_2P}},
      /* ROTATION 3 */
      {{TEMPLATE_00, TEMPLATE_00}, {TEMPLATE_00, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_2P}},
    },
    /* TETRAMINO_TYPE_T */
    {
      /* ROTATION 0 */
      {{TEMPLATE_1P, TEMPLATE_00}, {TEMPLATE_00, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_2P, TEMPLATE_1P}},
      /* ROTATION 1 */
      {{TEMPLATE_1P, TEMPLATE_00}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_2P, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_2P}},
      /* ROTATION 2 */
      {{TEMPLATE_00, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_2P, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_2P}},
      /* ROTATION 3 */
      {{TEMPLATE_1P, TEMPLATE_00}, {TEMPLATE_00, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_2P}},
    },
    /* TETRAMINO_TYPE_J */
    {
      /* ROTATION 0 */
      {{TEMPLATE_00, TEMPLATE_00}, {TEMPLATE_00, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_2P, TEMPLATE_1P}},
      /* ROTATION 1 */
      {{TEMPLATE_1P, TEMPLATE_00}, {TEMPLATE_2P, TEMPLATE_00}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_2P}},
      /* ROTATION 2 */
      {{TEMPLATE_00, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_2P, TEMPLATE_1P}, {TEMPLATE_2P, TEMPLATE_2P}},
      /* ROTATION 3 */
      {{TEMPLATE_1P, TEMPLATE_00}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_00, TEMPLATE_2P}, {TEMPLATE_1P, TEMPLATE_2P}},
    },
    /* TETRAMINO_TYPE_I */
    {
      /* ROTATION 0 */
      {{TEMPLATE_00, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_2P, TEMPLATE_1P}, {TEMPLATE_3P, TEMPLATE_1P}},
      /* ROTATION 1 */
      {{TEMPLATE_2P, TEMPLATE_00}, {TEMPLATE_2P, TEMPLATE_1P}, {TEMPLATE_2P, TEMPLATE_2P}, {TEMPLATE_2P, TEMPLATE_3P}},
      /* ROTATION 2 */
      {{TEMPLATE_00, TEMPLATE_2P}, {TEMPLATE_1P, TEMPLATE_2P}, {TEMPLATE_2P, TEMPLATE_2P}, {TEMPLATE_3P, TEMPLATE_2P}},
      /* ROTATION 3 */
      {{TEMPLATE_1P, TEMPLATE_00}, {TEMPLATE_1P, TEMPLATE_1P}, {TEMPLATE_1P, TEMPLATE_2P}, {TEMPLATE_1P, TEMPLATE_3P}},
    },
};

/* Format: [TYPE][X/Y] */
const uint8_t tetramino_spawn_position[7][2] = {
  /* TETRAMINO_TYPE_Z */
  {3, 0},
  /* TETRAMINO_TYPE_O */
  {4, 0},
  /* TETRAMINO_TYPE_L */
  {3, 0},
  /* TETRAMINO_TYPE_S */
  {3, 0},
  /* TETRAMINO_TYPE_T */
  {3, 0},
  /* TETRAMINO_TYPE_J */
  {3, 0},
  /* TETRAMINO_TYPE_I */
  {3, 0},
};

void initialize_tetraminos_sprites(tetramino_t * tetramino);
void set_sprites_position_from_type(tetramino_t * tetramino);
void update_rotation(tetramino_t * tetramino, rotation_direction_t direction);

void t_initialize_tetramino(tetramino_t * tetramino,
                            uint8_t type,
                            uint8_t first_sprite) {
  tetramino->y = PLAYFIELD_OFFSET_X; /* initial Y */
  tetramino->x = PLAYFIELD_OFFSET_Y;
  tetramino->type = type;
  tetramino->first_sprite = first_sprite;
  tetramino->rotation = ROTATION_TYPE_T_0;

  initialize_tetraminos_sprites(tetramino);
  set_sprites_position_from_type(tetramino);
}

void t_update_tetramino(tetramino_t * tetramino) {
  set_sprites_position_from_type(tetramino);
}

void t_spawn_tetramino(tetramino_t * tetramino) {
  tetramino->x = tetramino_spawn_position[tetramino->type][0] * BLOCK_SIDE_IN_PIXELS + PLAYFIELD_OFFSET_X;
  tetramino->y = tetramino_spawn_position[tetramino->type][1] * BLOCK_SIDE_IN_PIXELS + PLAYFIELD_OFFSET_Y;
  set_sprites_position_from_type(tetramino);
}

void t_try_to_rotate_tetramino(tetramino_t * tetramino, board_t * board, rotation_direction_t direction) {
  (void) board;
  update_rotation(tetramino, direction);
  set_sprites_position_from_type(tetramino);
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
                tetramino->x + tetramino_sprite_position_offset[tetramino->type][tetramino->rotation][i][0],
                tetramino->y + tetramino_sprite_position_offset[tetramino->type][tetramino->rotation][i][1]);
  }
}

void update_rotation(tetramino_t * tetramino, rotation_direction_t direction) {
  if (direction == ROTATION_CLOCKWISE) {
    tetramino->rotation = (tetramino->rotation + 1) % ROTATION_TYPE_T_MAX;
  } else if (direction == ROTATION_COUNTER_CLOCKWISE) {
    if (tetramino->rotation == ROTATION_TYPE_T_0) {
      tetramino->rotation = ROTATION_TYPE_T_3;
    } else {
      tetramino->rotation = (tetramino->rotation - 1);
    }
  }
}