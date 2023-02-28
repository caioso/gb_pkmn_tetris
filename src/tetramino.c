#include "tetramino.h"
#include "collision_detector.h"
#include "piece_randomizer.h"

/* Format: [TYPE][ROTATION][TEMPLATE_ROW][TEMPLATE_COL] */
const uint8_t tetramino_sprite_position_template[7][4][4][4] = {
  /* TETRAMINO_TYPE_Z */
  {
    /* ROTATION 0 */
    {
      {1, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}
    },
    /* ROTATION 1 */
    {
      {0, 0, 1, 0},
      {0, 1, 1, 0},
      {0, 1, 0, 0},
      {0, 0, 0, 0}
    },
    /* ROTATION 2 */
    {
      {0, 0, 0, 0},
      {1, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0}
    },
    /* ROTATION 3 */
    {
      {0, 1, 0, 0},
      {1, 1, 0, 0},
      {1, 0, 0, 0},
      {0, 0, 0, 0}
    },
  },
  /* TETRAMINO_TYPE_O */
  {
    /* ROTATION 0 */
    {
      {0, 1, 1, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}
    },
    /* ROTATION 1 */
    {
      {0, 1, 1, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}
    },
    /* ROTATION 2 */
    {
      {0, 1, 1, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}
    },
    /* ROTATION 3 */
    {
      {0, 1, 1, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}
    },
  },
  /* TETRAMINO_TYPE_L */
  {
    /* ROTATION 0 */
    {
      {0, 0, 1, 0},
      {1, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}
    },
    /* ROTATION 1 */
    {
      {0, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0}
    },
    /* ROTATION 2 */
    {
      {0, 0, 0, 0},
      {1, 1, 1, 0},
      {1, 0, 0, 0},
      {0, 0, 0, 0}
    },
    /* ROTATION 3 */
    {
      {1, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 0, 0}
    },
  },
  /* TETRAMINO_TYPE_S */
  {
    /* ROTATION 0 */
    {
      {0, 1, 1, 0},
      {1, 1, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}
    },
    /* ROTATION 1 */
    {
      {0, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 0}
    },
    /* ROTATION 2 */
    {
      {0, 0, 0, 0},
      {0, 1, 1, 0},
      {1, 1, 0, 0},
      {0, 0, 0, 0}
    },
    /* ROTATION 3 */
    {
      {1, 0, 0, 0},
      {1, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 0, 0}
    },
  },
  /* TETRAMINO_TYPE_T */
  {
    /* ROTATION 0 */
    {
      {0, 1, 0, 0},
      {1, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}
    },
    /* ROTATION 1 */
    {
      {0, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 1, 0, 0},
      {0, 0, 0, 0}
    },
    /* ROTATION 2 */
    {
      {0, 0, 0, 0},
      {1, 1, 1, 0},
      {0, 1, 0, 0},
      {0, 0, 0, 0}
    },
    /* ROTATION 3 */
    {
      {0, 1, 0, 0},
      {1, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 0, 0}
    },
  },
/* TETRAMINO_TYPE_J */
  {
    /* ROTATION 0 */
    {
      {1, 0, 0, 0},
      {1, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}
    },
    /* ROTATION 1 */
    {
      {0, 1, 1, 0},
      {0, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 0, 0}
    },
    /* ROTATION 2 */
    {
      {0, 0, 0, 0},
      {1, 1, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 0}
    },
    /* ROTATION 3 */
    {
      {0, 1, 0, 0},
      {0, 1, 0, 0},
      {1, 1, 0, 0},
      {0, 0, 0, 0}
    },
  },
/* TETRAMINO_TYPE_I */
  {
    /* ROTATION 0 */
    {
      {0, 0, 0, 0},
      {1, 1, 1, 1},
      {0, 0, 0, 0},
      {0, 0, 0, 0}
    },
    /* ROTATION 1 */
    {
      {0, 0, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 1, 0}
    },
    /* ROTATION 2 */
    {
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {1, 1, 1, 1},
      {0, 0, 0, 0}
    },
    /* ROTATION 3 */
    {
      {0, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 0, 0}
    },
  }
};

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

/* Format: [TYPE][ROTATION_TRANSITION][TEST][X/Y] */
const int8_t rotation_test_offset[2][8][5][2] = {
  /* J, L, T, S, Z */
  {
    {
      {0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}
    },
    /* 0 -> 1 */
    {
      {0, 0}, {1, 0}, {-1, 1}, {0, -2}, {1, -2}
    },
    /* 1 -> 2 */
    {
      {0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}
    },
    /* 2 -> 1 */
    {
      {0, 0}, {1, 0}, {1, -1}, {0, 2}, {-1, 2}
    },
    /* 2 -> 3 */
    {
      {0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}
    },
    /* 3 -> 2 */
    {
      {0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}
    },
    /* 3 -> 0 */
    {
      {0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}
    },
    /* 0 -> 3 */
    {
      {0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}
    },
  },
  /* I */
  {
    {
      {0, 0}, {-2, 0}, {1, 0}, {-2, 1}, {1, -2}
    },
    /* 0 -> 1 */
    {
      {0, 0}, {2, 0}, {-1, 0}, {2, -1}, {-1, 2}
    },
    /* 1 -> 2 */
    {
      {0, 0}, {-1, 0}, {2, 0}, {-1, -2}, {2, 1}
    },
    /* 2 -> 1 */
    {
      {0, 0}, {1, 0}, {-2, 0}, {1, 2}, {-2, -1}
    },
    /* 2 -> 3 */
    {
      {0, 0}, {2, 0}, {-1, 0}, {2, -1}, {-1, 2}
    },
    /* 3 -> 2 */
    {
      {0, 0}, {-2, 0}, {1, 0}, {-2, 1}, {1, -2}
    },
    /* 3 -> 0 */
    {
      {0, 0}, {1, 0}, {-2, 0}, {1, 2}, {-2, -1}
    },
    /* 0 -> 3 */
    {
      {0, 0}, {-1, 0}, {2, 0}, {-1, -2}, {2, 1}
    },
  }
};

const uint8_t gravity_table[15] = {
  48 /* level 00 */,
  43 /* level 01 */,
  38 /* level 02 */,
  33 /* level 03 */,
  28 /* level 04 */,
  23 /* level 05 */,
  18 /* level 06 */,
  13 /* level 07 */,
  8 /* level 08 */,
  6 /* level 09 */,
  5 /* level 10-12 */,
  4 /* level 13-15 */,
  3 /* level 16-19 */,
  2 /* level 19-28 */,
  1 /* level 29+ */
};

void initialize_tetraminos_sprites(tetramino_t * tetramino);
void apply_gravity(tetramino_t * tetramino, uint16_t level);
void set_real_sprites_position_from_type(tetramino_t * tetramino);
void set_ghost_sprites_position_from_type(tetramino_t * tetramino);
void set_held_sprites_position_from_type(tetramino_t * tetramino);
void reset_lock_delay(tetramino_t * tetramino);
bool can_reset_lock_delay(tetramino_t * tetramino);
uint8_t get_rotation_transition_index(rotation_type_t current, rotation_type_t next);
rotation_type_t get_next_rotation(tetramino_t * tetramino, rotation_direction_t direction);
int8_t is_rotation_allowed(tetramino_t * tetramino, board_t * board, rotation_direction_t direction);
uint8_t get_test_by_type(tetramino_t * tetramino);
void process_red_mode(tetramino_t * tetramino, board_t * board, randomizer_t * randomizer, uint16_t level);
uint8_t get_gravity_by_level(uint16_t level);
uint8_t find_drop_position(tetramino_t * tetramino, board_t * board);

void t_initialize_tetramino(tetramino_t * tetramino,
                            uint8_t type,
                            uint8_t first_sprite) {
  tetramino->y = PLAYFIELD_OFFSET_X; /* initial Y */
  tetramino->x = PLAYFIELD_OFFSET_Y;
  tetramino->type = type;
  tetramino->first_sprite = first_sprite;
  tetramino->rotation = ROTATION_TYPE_T_0;
  tetramino->gravity = 0;
  tetramino->lock_delay = 0;
  tetramino->lock_counter = 0;
  tetramino->hard_drop_request = false;
  tetramino->should_update_ghost = false;
  tetramino->soft_drop_enabled = false;
  tetramino->held = TETRAMINO_TYPE_NULL;
  tetramino->held_request = true;
  tetramino->held_swapped_allowed = true;

  initialize_tetraminos_sprites(tetramino);
  set_real_sprites_position_from_type(tetramino);
  set_ghost_sprites_position_from_type(tetramino);
}

void t_setup_tetramino(tetramino_t * tetramino,
                       uint8_t type) {
  tetramino->y = PLAYFIELD_OFFSET_X; /* initial Y */
  tetramino->x = PLAYFIELD_OFFSET_Y;
  tetramino->type = type;
  tetramino->rotation = ROTATION_TYPE_T_0;
  tetramino->gravity = 0;
  tetramino->lock_delay = 0;
  tetramino->lock_counter = 0;
  tetramino->hard_drop_request = false;
  tetramino->should_update_ghost = false;
  tetramino->soft_drop_enabled = false;
  tetramino->held_request = false;
  tetramino->held_swapped_allowed = true;

  initialize_tetraminos_sprites(tetramino);
  set_real_sprites_position_from_type(tetramino);
  set_ghost_sprites_position_from_type(tetramino);
}

void t_update_tetramino(tetramino_t * tetramino, board_t * board, randomizer_t * randomizer, uint16_t level) {
  /* Red Mode */
  process_red_mode(tetramino, board, randomizer, level);
}

void t_spawn_tetramino(tetramino_t * tetramino) {
  tetramino->lock_delay = 0;
  tetramino->lock_counter = 0;
  tetramino->gravity_counter = 0;
  tetramino->x = tetramino_spawn_position[tetramino->type][0] * BLOCK_SIDE_IN_PIXELS + PLAYFIELD_OFFSET_X;
  tetramino->y = tetramino_spawn_position[tetramino->type][1] * BLOCK_SIDE_IN_PIXELS + PLAYFIELD_OFFSET_Y;
  tetramino->ghost_y = tetramino->y;
  tetramino->should_update_ghost = true;

  set_real_sprites_position_from_type(tetramino);
}

void t_try_to_rotate_tetramino(tetramino_t * tetramino, board_t * board, rotation_direction_t direction) {
  if (tetramino->type == TETRAMINO_TYPE_O) {
    return;
  }

  int8_t rotation_allowed = is_rotation_allowed(tetramino, board, direction);

  if (rotation_allowed != -1) {
    uint8_t test_type = get_test_by_type(tetramino);
    uint8_t next_rotation = get_next_rotation(tetramino, direction);
    uint8_t transition_index = get_rotation_transition_index(tetramino->rotation, next_rotation);

    tetramino->rotation = next_rotation;
    tetramino->x += (rotation_test_offset[test_type][transition_index][rotation_allowed][0] << 3);
    tetramino->y += (rotation_test_offset[test_type][transition_index][rotation_allowed][1] << 3);

    if (can_reset_lock_delay(tetramino)) {
      reset_lock_delay(tetramino);
    }

    tetramino->should_update_ghost = true;
    set_real_sprites_position_from_type(tetramino);
  }
}

void t_try_to_reset_lock_delay(tetramino_t * tetramino) {
  if (can_reset_lock_delay(tetramino)) {
    reset_lock_delay(tetramino);
  }
}

void t_request_hard_drop(tetramino_t * tetramino) {
  tetramino->hard_drop_request = true;
  tetramino->lock_counter = MAX_LOCK_COUNTER - 1;
  tetramino->lock_delay = MAX_LOCK_DELAY;
}

void t_request_soft_drop(tetramino_t * tetramino, bool state) {
  tetramino->soft_drop_enabled = state;

  if (state == true) {
    tetramino->gravity_counter = 0xFFFF;
  } else {
    tetramino->gravity_counter = 0x0000;
  }
}

void t_request_hold(tetramino_t * tetramino, randomizer_t * randomizer) {
  if (tetramino->held_swapped_allowed == true) {
    tetramino_type_t held = tetramino->held;

    if (held == TETRAMINO_TYPE_NULL) {
      held = pr_get_next_piece(randomizer);
    } else {
      held = tetramino->held;
    }

    tetramino->held_swapped_allowed = false;
    tetramino->held = tetramino->type;
    tetramino->type = held;

    t_spawn_tetramino(tetramino);
    set_ghost_sprites_position_from_type(tetramino);
    set_held_sprites_position_from_type(tetramino);
  }
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

  /* Ghost Piece */
  set_sprite_tile(tetramino->first_sprite + 4, 1);
  set_sprite_prop(tetramino->first_sprite + 4, 6);
  set_sprite_tile(tetramino->first_sprite + 4 + 1, 1);
  set_sprite_prop(tetramino->first_sprite + 4 + 1, 6);
  set_sprite_tile(tetramino->first_sprite + 4 + 2, 1);
  set_sprite_prop(tetramino->first_sprite + 4 + 2, 6);
  set_sprite_tile(tetramino->first_sprite + 4 + 3, 1);
  set_sprite_prop(tetramino->first_sprite + 4 + 3, 6);

  /* Held Piece */
  set_sprite_tile(tetramino->first_sprite + 8, 1);
  set_sprite_prop(tetramino->first_sprite + 8, 6);
  set_sprite_tile(tetramino->first_sprite + 8 + 1, 1);
  set_sprite_prop(tetramino->first_sprite + 8 + 1, 6);
  set_sprite_tile(tetramino->first_sprite + 8 + 2, 1);
  set_sprite_prop(tetramino->first_sprite + 8 + 2, 6);
  set_sprite_tile(tetramino->first_sprite + 8 + 3, 1);
  set_sprite_prop(tetramino->first_sprite + 8 + 3, 6);
}

void set_real_sprites_position_from_type(tetramino_t * tetramino) {
  uint8_t sprite = 0;
  for (uint8_t i = 0; i < 4; i++) {
    for (uint8_t j = 0; j < 4; j++) {
      if (tetramino_sprite_position_template[tetramino->type][tetramino->rotation][i][j] == 1) {
        move_sprite(tetramino->first_sprite + sprite,
                tetramino->x + j * BLOCK_SIDE_IN_PIXELS,
                tetramino->y + i * BLOCK_SIDE_IN_PIXELS);
        sprite++;
        if (sprite == 4) {
          return;
        }
      }
    }
  }
}

void set_ghost_sprites_position_from_type(tetramino_t * tetramino) {
  uint8_t sprite = 0;
  for (uint8_t i = 0; i < 4; i++) {
    for (uint8_t j = 0; j < 4; j++) {
      if (tetramino_sprite_position_template[tetramino->type][tetramino->rotation][i][j] == 1) {
        move_sprite(tetramino->first_sprite + sprite + 4,
                tetramino->x + j * BLOCK_SIDE_IN_PIXELS,
                tetramino->ghost_y + i * BLOCK_SIDE_IN_PIXELS);
        sprite++;
        if (sprite == 4) {
          return;
        }
      }
    }
  }
}

void set_held_sprites_position_from_type(tetramino_t * tetramino) {
  uint8_t sprite = 0;
  for (uint8_t i = 0; i < 4; i++) {
    for (uint8_t j = 0; j < 4; j++) {
      if (tetramino_sprite_position_template[tetramino->held][0][i][j] == 1) {
        move_sprite(tetramino->first_sprite + sprite + 8,
                PLAYFIELD_OFFSET_X + 12 * BLOCK_SIDE_IN_PIXELS + j * BLOCK_SIDE_IN_PIXELS,
                PLAYFIELD_OFFSET_Y + BLOCK_SIDE_IN_PIXELS + i * BLOCK_SIDE_IN_PIXELS);
        sprite++;
        if (sprite == 4) {
          return;
        }
      }
    }
  }
}

rotation_type_t get_next_rotation(tetramino_t * tetramino, rotation_direction_t direction) {
  rotation_type_t rotation = ROTATION_TYPE_T_0;
  if (direction == ROTATION_CLOCKWISE) {
    rotation = (tetramino->rotation + 1) % ROTATION_TYPE_T_MAX;
  } else if (direction == ROTATION_COUNTER_CLOCKWISE) {
    if (tetramino->rotation == ROTATION_TYPE_T_0) {
      rotation = ROTATION_TYPE_T_3;
    } else {
      rotation = (tetramino->rotation - 1);
    }
  }

  return rotation;
}

int8_t is_rotation_allowed(tetramino_t * tetramino, board_t * board, rotation_direction_t direction) {
  rotation_type_t next_rotation = get_next_rotation(tetramino, direction);
  uint8_t transition_index = get_rotation_transition_index(tetramino->rotation, next_rotation);
  uint8_t test_type = get_test_by_type(tetramino);
  uint8_t test = 0;
  uint8_t sprite = 0;
  int8_t result_index = -1;

  for (test = 0; test < 5; test++) {
    bool passed = true;
    for (sprite = 0; sprite < 4; sprite++) {
      int8_t col = (tetramino->x + tetramino_sprite_position_offset[tetramino->type][next_rotation][sprite][0] - PLAYFIELD_OFFSET_X) >> 3;
      int8_t row = (tetramino->y + tetramino_sprite_position_offset[tetramino->type][next_rotation][sprite][1] - PLAYFIELD_OFFSET_Y) >> 3;

      col += rotation_test_offset[test_type][transition_index][test][0];
      row += rotation_test_offset[test_type][transition_index][test][1];

      if (col < 0 || row < 0 ||
          col >= BOARD_WIDTH || row >= BOARD_HEIGHT ||
          board->blocks[row][col] == 1) {
        passed = false;
        break;
      }
    }
    if (passed == true) {
      result_index = test;
      break;
    }
  }

  return result_index;
}

uint8_t get_rotation_transition_index(rotation_type_t current, rotation_type_t next) {
  if (current == ROTATION_TYPE_T_0 && next == ROTATION_TYPE_T_1) {
    return 0;
  } else if (current == ROTATION_TYPE_T_1 && next == ROTATION_TYPE_T_0) {
    return 1;
  } else if (current == ROTATION_TYPE_T_1 && next == ROTATION_TYPE_T_2) {
    return 2;
  } else if (current == ROTATION_TYPE_T_2 && next == ROTATION_TYPE_T_1) {
    return 3;
  } else if (current == ROTATION_TYPE_T_2 && next == ROTATION_TYPE_T_3) {
    return 4;
  } else if (current == ROTATION_TYPE_T_3 && next == ROTATION_TYPE_T_2) {
    return 5;
  } else if (current == ROTATION_TYPE_T_3 && next == ROTATION_TYPE_T_0) {
    return 6;
  } else /* current == ROTATION_TYPE_T_0 && next == ROTATION_TYPE_T_3 */ {
    return 7;
  }
}

uint8_t get_test_by_type(tetramino_t * tetramino) {
  if (tetramino->type == TETRAMINO_TYPE_Z ||
      tetramino->type == TETRAMINO_TYPE_O ||
      tetramino->type == TETRAMINO_TYPE_L ||
      tetramino->type == TETRAMINO_TYPE_S ||
      tetramino->type == TETRAMINO_TYPE_T ||
      tetramino->type == TETRAMINO_TYPE_J) {
    return 0;
  } else {
    return 1;
  }
}

uint8_t get_gravity_by_level(uint16_t level) {
  uint8_t index = level;
  if (level >= 10) {
    if (level <= 12) {
      return gravity_table[10];
    } else if (level >= 13 && level <= 15) {
      return gravity_table[11];
    } else if (level >= 16 && level <= 18) {
      return gravity_table[12];
    } else if (level >= 19 && level <= 28) {
      return gravity_table[13];
    } else {
      return gravity_table[14];
    }
  } else {
    return gravity_table[index];
  }
}

void apply_gravity(tetramino_t * tetramino, uint16_t level) {
  if (tetramino->soft_drop_enabled == false &&
      tetramino->gravity_counter >= get_gravity_by_level(level)) {
    tetramino->gravity_counter = 0;
    tetramino->y += BLOCK_SIDE_IN_PIXELS;
  } else if (tetramino->soft_drop_enabled == true &&
             tetramino->gravity_counter >= get_gravity_by_level(10)) {
    tetramino->gravity_counter = 0;
    tetramino->y += BLOCK_SIDE_IN_PIXELS;
  } else {
    tetramino->gravity_counter++;
  }
}

bool can_reset_lock_delay(tetramino_t * tetramino) {
  return tetramino->lock_delay != 0 && tetramino->lock_counter < MAX_LOCK_COUNTER;
}

void reset_lock_delay(tetramino_t * tetramino) {
  tetramino->lock_delay = 0;
  tetramino->lock_counter++;
}
void process_red_mode(tetramino_t * tetramino, board_t * board, randomizer_t * randomizer, uint16_t level) {
  /* Update ghost if needed. */
  if (tetramino->should_update_ghost == true) {
    tetramino->ghost_y = find_drop_position(tetramino, board);
    tetramino->should_update_ghost = false;
  }

  /* If tetramino can drop down. */
  if (tetramino->hard_drop_request == true) {
    tetramino->hard_drop_request = false;
    tetramino->y = tetramino->ghost_y;
  } else {
    if (cd_detect_collision(board, tetramino, 0, 1) == false) {
      /* No Hard-drop requested*/
      if (tetramino->hard_drop_request == false) {
        if (can_reset_lock_delay(tetramino)) {
          reset_lock_delay(tetramino);
        }
        apply_gravity(tetramino, level);
      }
    } else {   /* If it collided with something. */
      tetramino->lock_delay++;

      if (tetramino->lock_delay >= MAX_LOCK_DELAY) {
        gbm_write_tetramino_to_board(board, tetramino);
        gmb_remove_full_lines(board);
        t_setup_tetramino(tetramino,
                          pr_get_next_piece(randomizer));
        t_spawn_tetramino(tetramino);
      }
    }
  }

  /* Update sprites */
  set_real_sprites_position_from_type(tetramino);
  set_ghost_sprites_position_from_type(tetramino);
}

uint8_t find_drop_position(tetramino_t * tetramino, board_t * board) {
  uint8_t old_y = tetramino->y;
  uint8_t final_y = 0;
  /* Improve performance */
  while(cd_detect_collision(board, tetramino, 0, 1) == false) {
    tetramino->y += BLOCK_SIDE_IN_PIXELS;
  }

  final_y = tetramino->y;
  tetramino->y = old_y;
  return final_y;
}

void t_move_tetramino_horizontally(tetramino_t * tetramino, board_t * board, int8_t offset) {
  if (cd_detect_collision(board, tetramino, offset, 0) == false) {
    tetramino->x += BLOCK_SIDE_IN_PIXELS * offset;
    tetramino->should_update_ghost = true;
    t_try_to_reset_lock_delay(tetramino);
  }
}