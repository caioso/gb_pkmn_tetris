#include "screen_controller.h"

bool screen_shake_requested = false;
int8_t screen_shake_counter = 0;
const int8_t shake_offset[5] = { -7, +3, +2, +1, +1};

/* Public functions */
void sc_shake_screen(void) {
  screen_shake_requested = true;
  screen_shake_counter = -1;
}

bool sc_is_screen_shaking(void) {
  return true;
}

void sc_update_screen_controller(tetramino_t * tetramino) {
  if (screen_shake_requested == true) {
    if (screen_shake_counter < 0) {
      /* nop */
    } else {
      scroll_bkg(0 , shake_offset[screen_shake_counter]);
      tetramino->y -= shake_offset[screen_shake_counter];
    }

    if (screen_shake_counter == 4) {
      screen_shake_requested = false;
    }
    screen_shake_counter++;
  }
}