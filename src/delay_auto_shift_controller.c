#include "delay_auto_shift_controller.h"

void das_update(das_t * das) {
  das->movement_allowed = false;
  if (das->delay_auto_shift_enabled == false) {
    das->delay_auto_shift_counter++;
    if (das->delay_auto_shift_counter == DAS_INITIAL_THRESHOLD) {
      das->delay_auto_shift_enabled = true;
      das->delay_auto_shift_counter = 0;
    }
  } else {
    if (das->delay_auto_shift_counter == 0) {
      das->movement_allowed = true;
    } else {
      das->delay_auto_shift_counter++;
      if (das->delay_auto_shift_counter == DAS_REPEAT_THRESHOLD) {
        das->delay_auto_shift_counter = 0;
      }
    }
  }
}

void das_reset_das(das_t * das) {
  das->delay_auto_shift_counter = 0;
  das->delay_auto_shift_enabled = false;
  das->movement_allowed = false;
}