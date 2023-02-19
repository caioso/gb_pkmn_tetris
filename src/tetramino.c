#include "tetramino.h"
#include "collision_detector.h"

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
void set_sprites_position_from_type(tetramino_t * tetramino);
void reset_lock_delay(tetramino_t * tetramino);
bool can_reset_lock_delay(tetramino_t * tetramino);
uint8_t get_rotation_transition_index(rotation_type_t current, rotation_type_t next);
rotation_type_t get_next_rotation(tetramino_t * tetramino, rotation_direction_t direction);
int8_t is_rotation_allowed(tetramino_t * tetramino, board_t * board, rotation_direction_t direction);
uint8_t get_test_by_type(tetramino_t * tetramino);
void process_red_mode(tetramino_t * tetramino, board_t * board, uint16_t level);
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

  initialize_tetraminos_sprites(tetramino);
  set_sprites_position_from_type(tetramino);
}

void t_update_tetramino(tetramino_t * tetramino, board_t * board, uint16_t level) {
  /* Red Mode */
  process_red_mode(tetramino, board, level);
}

void t_spawn_tetramino(tetramino_t * tetramino) {
  tetramino->lock_delay = 0;
  tetramino->lock_counter = 0;
  tetramino->gravity_counter = 0;
  tetramino->x = tetramino_spawn_position[tetramino->type][0] * BLOCK_SIDE_IN_PIXELS + PLAYFIELD_OFFSET_X;
  tetramino->y = tetramino_spawn_position[tetramino->type][1] * BLOCK_SIDE_IN_PIXELS + PLAYFIELD_OFFSET_Y;
  set_sprites_position_from_type(tetramino);
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

    set_sprites_position_from_type(tetramino);
  }
}

void t_try_to_reset_lock_delay(tetramino_t * tetramino) {
  if (can_reset_lock_delay(tetramino)) {
    reset_lock_delay(tetramino);
  }
}

void t_request_hard_drop(tetramino_t * tetramino) {
  tetramino->hard_drop_request = true;
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
  uint8_t sprite = 0;
  for (sprite = 0; sprite < 4; sprite++) {
    move_sprite(tetramino->first_sprite + sprite,
                tetramino->x + tetramino_sprite_position_offset[tetramino->type][tetramino->rotation][sprite][0],
                tetramino->y + tetramino_sprite_position_offset[tetramino->type][tetramino->rotation][sprite][1]);
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
  if (tetramino->gravity_counter >= get_gravity_by_level(level)) {
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

void process_red_mode(tetramino_t * tetramino, board_t * board, uint16_t level) {
  /* If tetramino can drop down. */
  if (tetramino->hard_drop_request == true) {
      tetramino->hard_drop_request = false;
      tetramino->y = find_drop_position(tetramino, board);
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
        t_initialize_tetramino(tetramino,
                              (tetramino->type + 1) % (7),
                              MAIN_TETRAMINO_SPRITE_INDEX);
        t_spawn_tetramino(tetramino);
      }
    }
    /* Debug */
    if (tetramino->hard_drop_request == true) {
      set_bkg_tile_xy(0, 0, 1);
    } else {
      set_bkg_tile_xy(0, 0, 0);
    }
  }

  /* Update sprites */
  set_sprites_position_from_type(tetramino);
}

uint8_t find_drop_position(tetramino_t * tetramino, board_t * board) {
  volatile uint8_t sprite = 0;
  volatile uint8_t found_row[4] = { BOARD_HEIGHT - 1, BOARD_HEIGHT - 1, BOARD_HEIGHT - 1, BOARD_HEIGHT - 1 };

  for (sprite = 0; sprite < 4; sprite++) {
    int8_t col = (tetramino->x + tetramino_sprite_position_offset[tetramino->type][tetramino->rotation][sprite][0] - PLAYFIELD_OFFSET_X) >> 3;
    int8_t row = (tetramino->y + tetramino_sprite_position_offset[tetramino->type][tetramino->rotation][sprite][1] - PLAYFIELD_OFFSET_Y) >> 3;

    for (uint8_t search_row = row + 1; search_row < BOARD_HEIGHT; search_row++) {
      if (board->blocks[search_row][col] == 1) {
        found_row[sprite] = search_row - 1;
        break;
      }
    }
  }

  /* take any number lower than -1;*/
  volatile uint8_t max_row = 1;
  for (sprite = 0; sprite < 4; sprite++) {
    if (max_row < found_row[sprite]) {
      max_row = found_row[sprite];
    }
  }

  return (max_row << 3) + PLAYFIELD_OFFSET_Y;
}