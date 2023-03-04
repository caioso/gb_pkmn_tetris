#include "screen_controller.h"

bool screen_shake_requested = false;
bool screen_rumble_requested = false;
bool is_vertical_rumble = false;
int8_t screen_shake_counter = 0;
int8_t screen_rumble_counter = 0;
int8_t rumble_direction;
const int8_t shake_offset[4] = {-6, +3, +2, +1};
const int8_t rumble_offset[3] = {2, -1, -1};

void clear_offsets(tetramino_t * tetramino);

/* Public functions */
void sc_shake_screen(tetramino_t * tetramino) {
  if (screen_shake_requested == true && screen_shake_counter >= 0 && screen_shake_counter <= 3) {
    clear_offsets(tetramino);
  }

  screen_shake_requested = true;
  screen_shake_counter = -1;
}

void sc_rumble_screen(tetramino_t * tetramino, screen_rumble_direction_t direction) {
  if (screen_rumble_counter == true && screen_rumble_counter >= 0 && screen_rumble_counter <= 2) {
    clear_offsets(tetramino);
  }

  if (direction == SCREEN_RUMBLE_DIRECTION_RIGHT || direction == SCREEN_RUMBLE_DIRECTION_LEFT) {
    rumble_direction = direction == SCREEN_RUMBLE_DIRECTION_RIGHT ? 1 : -1;
    is_vertical_rumble = false;
  } else {
    rumble_direction = direction == SCREEN_RUMBLE_DIRECTION_UP ? 1 : -1;
    is_vertical_rumble = true;
  }

  screen_rumble_requested = true;
  screen_rumble_counter = -1;
}

bool sc_is_screen_shaking(void) {
  return true;
}

void sc_update_screen_controller(tetramino_t * tetramino) {
  if (screen_shake_requested == true) {
    if (screen_shake_counter >= 0) {
      scroll_bkg(0, shake_offset[screen_shake_counter]);
      tetramino->y_offset = shake_offset[screen_shake_counter];
      tetramino->ghost_y_offset = shake_offset[screen_shake_counter];
    }

    if (screen_shake_counter == 3) {
      screen_shake_requested = false;
      clear_offsets(tetramino);
    } else {
      screen_shake_counter++;
    }
  }

  if (screen_rumble_requested == true) {
    if (screen_shake_counter >= 0) {
      if (is_vertical_rumble == false) {
        scroll_bkg(rumble_direction * rumble_offset[screen_rumble_counter], 0);
        tetramino->x_offset = -rumble_direction * rumble_offset[screen_rumble_counter];
        tetramino->ghost_x_offset = -rumble_direction * rumble_offset[screen_rumble_counter];
      } else {
        scroll_bkg(0, rumble_direction * rumble_offset[screen_rumble_counter]);
        tetramino->y_offset = rumble_direction * rumble_offset[screen_rumble_counter];
        tetramino->ghost_y_offset = rumble_direction * rumble_offset[screen_rumble_counter];
      }
    }

    if (screen_rumble_counter == 2) {
      screen_rumble_requested = false;
      clear_offsets(tetramino);
    } else {
      screen_rumble_counter++;
    }
  }
}

/* Private functions */
void clear_offsets(tetramino_t * tetramino) {
  (*(uint8_t*)(0xFF43)) = 0;
  (*(uint8_t*)(0xFF42)) = 0;
  tetramino->x_offset = 0;
  tetramino->ghost_x_offset = 0;
  tetramino->y_offset = 0;
  tetramino->ghost_y_offset = 0;
}