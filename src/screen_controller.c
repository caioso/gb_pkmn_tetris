#include "screen_controller.h"

bool screen_shake_requested = false;
bool screen_rumble_requested = false;
int8_t screen_shake_counter = 0;
int8_t screen_rumble_counter = 0;
int8_t rumble_direction;
screen_rumble_direction_t last_direction = SCREEN_RUMBLE_DIRECTION_RIGHT;
const int8_t shake_offset[5] = {-6, +3, +2, +1, 0};
const int8_t rumble_offset[4] = {2, -1, -1, 0};

/* Public functions */
void sc_shake_screen(tetramino_t * tetramino) {
  if (screen_shake_requested == true && screen_shake_counter > 0 && screen_shake_counter < 5) {
    /* Clear vertical scroll register (more efficient)*/
    (*(uint8_t*)(0xFF42)) = 0;
    tetramino->y_offset = 0;
    tetramino->ghost_y_offset = 0;
  }

  screen_shake_requested = true;
  screen_shake_counter = -1;
}

void sc_rumble_screen(tetramino_t * tetramino, screen_rumble_direction_t direction) {
  (void) tetramino;
  if (screen_rumble_counter == true && screen_rumble_counter > 0 && screen_rumble_counter < 4) {
    /* Clear horizontal scroll register (more efficient)*/
    (*(uint8_t*)(0xFF43)) = 0;
    tetramino->x_offset = 0;
    tetramino->ghost_x_offset = 0;
  }

  rumble_direction = direction == SCREEN_RUMBLE_DIRECTION_RIGHT ? 1 : -1;
  screen_rumble_requested = true;
  screen_rumble_counter = 0;
  last_direction = direction;
}

bool sc_is_screen_shaking(void) {
  return true;
}

void sc_update_screen_controller(tetramino_t * tetramino) {
  if (screen_shake_requested == true) {
    if (screen_shake_counter < 0) {
      /* nop */
    } else {
      scroll_bkg(0, shake_offset[screen_shake_counter]);
      tetramino->y_offset = shake_offset[screen_shake_counter];
      /* Red mode only */
      tetramino->ghost_y_offset = shake_offset[screen_shake_counter];
    }

    if (screen_shake_counter == 4) {
      screen_shake_requested = false;
    }
    screen_shake_counter++;
  }

  if (screen_rumble_requested == true) {
    scroll_bkg(rumble_direction * rumble_offset[screen_rumble_counter], 0);
    tetramino->x_offset = rumble_direction * rumble_offset[screen_rumble_counter];
    /* Red mode only */
    tetramino->ghost_x_offset = rumble_direction * rumble_offset[screen_rumble_counter];

    if (screen_rumble_counter == 3) {
      screen_rumble_requested = false;
    }
    screen_rumble_counter++;
  }
}