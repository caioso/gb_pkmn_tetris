#include "catch_controller.h"
#include "utils.h"

/* Constants */
#define PROGRESS_BAR_Y (13)
#define PROGRESS_BAR_ORIGIN_X (12)
#define INITAL_PROGRESS_BAR_TILE (11)

/* Public functions */
void cc_catch_controller_init(catch_controller_t * catch_controller) {
  catch_controller->catch_progress = 0;
  catch_controller->catch_target = 0;
  catch_controller->num_bars_to_fill = 0;
  catch_controller->progress_dirty = true;
}

void cc_catch_controller_set_progress(catch_controller_t * catch_controller,
                                      int8_t progress) {
  catch_controller->catch_target = progress >= 64 ? 63 : (progress < 0? 0 : progress);
  catch_controller->num_bars_to_fill = 0;
  catch_controller->progress_dirty = true;
}

void cc_catch_controller_update(catch_controller_t * catch_controller) {
  VBK_REG = VBK_TILES;
  uint8_t tiles[7];
  if (catch_controller->progress_dirty == true) {

    /* 56 bars, 64 levels */
    /* 56 - 64 NumBars = (56*current) / 64;
     * numBars  - current */
    int8_t increment = \
      ((catch_controller->catch_target - catch_controller->catch_progress) >> 2);
    catch_controller->catch_progress += increment;
    int16_t num_bars = (56 * catch_controller->catch_progress) >> 6;

    if (increment == 0) {
      catch_controller->catch_progress = catch_controller->catch_target;
      catch_controller->progress_dirty = false;
    }

    for (uint8_t i = 0; i < 7; i++) {
      if (num_bars > 8) {
        tiles[i] = INITAL_PROGRESS_BAR_TILE + 8;
        num_bars -= 8;
      } else if (num_bars >= 0) {
        tiles[i] = INITAL_PROGRESS_BAR_TILE + num_bars;
        num_bars -= 8;
      } else {
        tiles[i] = INITAL_PROGRESS_BAR_TILE;
      }
    }

    set_bkg_tiles(PROGRESS_BAR_ORIGIN_X, PROGRESS_BAR_Y, 7, 1, tiles);
  }
}