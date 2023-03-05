#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>
#include <stdio.h>
#include <rand.h>

/* extern dependencies */
#include "../extern/include/hUGEDriver.h"

/* game includes */
#include "board_initialization_templates.h"
#include "collision_detector.h"
#include "constants.h"
#include "delay_auto_shift_controller.h"
#include "general_board_manager.h"
#include "piece_randomizer.h"
#include "screen_controller.h"
#include "tetramino.h"

/* Game Assets */
#include "minos.h"

/* Bank of tiles. */
#define bar_cBank 0

/* Super Gameboy palette 0 */
#define bar_cSGBPal0c0 0
#define bar_cSGBPal0c1 0
#define bar_cSGBPal0c2 0
#define bar_cSGBPal0c3 0

/* Super Gameboy palette 1 */
#define bar_cSGBPal1c0 25368
#define bar_cSGBPal1c1 0
#define bar_cSGBPal1c2 4104
#define bar_cSGBPal1c3 6

/* Super Gameboy palette 2 */
#define bar_cSGBPal2c0 0
#define bar_cSGBPal2c1 0
#define bar_cSGBPal2c2 4104
#define bar_cSGBPal2c3 6

/* Super Gameboy palette 3 */
#define bar_cSGBPal3c0 0
#define bar_cSGBPal3c1 0
#define bar_cSGBPal3c2 4104
#define bar_cSGBPal3c3 6

/* Gameboy Color palette 0 */
#define bar_cCGBPal0c0 32767
#define bar_cCGBPal0c1 25368
#define bar_cCGBPal0c2 19026
#define bar_cCGBPal0c3 0

/* Gameboy Color palette 1 */
#define bar_cCGBPal1c0 18
#define bar_cCGBPal1c1 24
#define bar_cCGBPal1c2 31
#define bar_cCGBPal1c3 12

/* Gameboy Color palette 2 */
#define bar_cCGBPal2c0 384
#define bar_cCGBPal2c1 576
#define bar_cCGBPal2c2 768
#define bar_cCGBPal2c3 992

/* Gameboy Color palette 3 */
#define bar_cCGBPal3c0 12288
#define bar_cCGBPal3c1 18432
#define bar_cCGBPal3c2 24576
#define bar_cCGBPal3c3 31744

/* Gameboy Color palette 4 */
#define bar_cCGBPal4c0 792
#define bar_cCGBPal4c1 1023
#define bar_cCGBPal4c2 396
#define bar_cCGBPal4c3 594

/* Gameboy Color palette 5 */
#define bar_cCGBPal5c0 24600
#define bar_cCGBPal5c1 31775
#define bar_cCGBPal5c2 12300
#define bar_cCGBPal5c3 18450

/* Gameboy Color palette 6 */
#define bar_cCGBPal6c0 19008
#define bar_cCGBPal6c1 25344
#define bar_cCGBPal6c2 32736
#define bar_cCGBPal6c3 12672

/* Gameboy Color palette 7 */
#define bar_cCGBPal7c0 31663
#define bar_cCGBPal7c1 25368
#define bar_cCGBPal7c2 19026
#define bar_cCGBPal7c3 12684
/* CGBpalette entries. */
extern const unsigned char bar_cCGB[];
/* Start of tile array. */
extern const unsigned char bar_c[];

/* End of BAR_C.H */

/* Sound test */
extern const hUGESong_t sample_song;

unsigned char background_data[] = {
    0x00, 0x01, 0x00, 0x01};

const uint16_t bar_p[] =
    {
        bar_cCGBPal0c0, bar_cCGBPal0c1, bar_cCGBPal0c2, bar_cCGBPal0c3,
        bar_cCGBPal1c0, bar_cCGBPal1c1, bar_cCGBPal1c2, bar_cCGBPal1c3,
        bar_cCGBPal2c0, bar_cCGBPal2c1, bar_cCGBPal2c2, bar_cCGBPal2c3,
        bar_cCGBPal3c0, bar_cCGBPal3c1, bar_cCGBPal3c2, bar_cCGBPal3c3,
        bar_cCGBPal4c0, bar_cCGBPal4c1, bar_cCGBPal4c2, bar_cCGBPal4c3,
        bar_cCGBPal5c0, bar_cCGBPal5c1, bar_cCGBPal5c2, bar_cCGBPal5c3,
        bar_cCGBPal6c0, bar_cCGBPal6c1, bar_cCGBPal6c2, bar_cCGBPal6c3,
        bar_cCGBPal7c0, bar_cCGBPal7c1, bar_cCGBPal7c2, bar_cCGBPal7c3};

/* Move this to a central game control object */
uint16_t random_seed = 0;

void main(void)
{
  NR52_REG = 0x80;
  NR51_REG = 0xFF;
  NR50_REG = 0x77;

  /* Init audio */
  __critical {
    hUGE_init(&sample_song);
    //add_VBL(hUGE_dosound);
  }

  /* bag randomizer */
  randomizer_t randomizer;
  pr_initialize_piece_randomizer(&randomizer);

  /* Initialize randomizer */
  waitpad(J_START);
  random_seed = LY_REG;
  random_seed |= (uint16_t)DIV_REG << 8;
  initrand(random_seed);

  /* Game settings */
  uint16_t game_level = 1;

  /* Temporary: Initialize general board */
  board_t general_board;

  /* Initialize board */
  gbm_initialize_board(&general_board,
                       board_initialization_template,
                       BLOCK_TYPE_CYAN);

  /* Temporary: Initialize tetramino */
  tetramino_t player_tetramino;

  /* Initialize tetramino */
  t_initialize_tetramino(&player_tetramino,
                         pr_get_next_piece(&randomizer),
                         MAIN_TETRAMINO_SPRITE_INDEX);
  t_spawn_tetramino(&player_tetramino, &general_board);

  /* Background setup */
  set_bkg_palette(BKGF_CGB_PAL7, 1, &bar_p[0]);
  set_bkg_palette(BKGF_CGB_PAL6, 1, &bar_p[4]);
  set_bkg_palette(BKGF_CGB_PAL5, 1, &bar_p[8]);
  set_bkg_palette(BKGF_CGB_PAL4, 1, &bar_p[12]);
  set_bkg_palette(BKGF_CGB_PAL3, 1, &bar_p[16]);
  set_bkg_palette(BKGF_CGB_PAL2, 1, &bar_p[20]);
  set_bkg_palette(BKGF_CGB_PAL1, 1, &bar_p[24]);
  set_bkg_palette(BKGF_CGB_PAL0, 1, &bar_p[28]);

  /* Background tiles code transfer */
  set_bkg_data(1, 9, minos);

  /* Sprite setup */
  set_sprite_palette(BKGF_CGB_PAL7, 1, &bar_p[0]);
  set_sprite_palette(BKGF_CGB_PAL6, 1, &bar_p[4]);
  set_sprite_palette(BKGF_CGB_PAL5, 1, &bar_p[8]);
  set_sprite_palette(BKGF_CGB_PAL4, 1, &bar_p[12]);
  set_sprite_palette(BKGF_CGB_PAL3, 1, &bar_p[16]);
  set_sprite_palette(BKGF_CGB_PAL2, 1, &bar_p[20]);
  set_sprite_palette(BKGF_CGB_PAL1, 1, &bar_p[24]);
  set_sprite_palette(BKGF_CGB_PAL0, 1, &bar_p[28]);

  /* Sprite tiles code transfer */
  set_sprite_data(1, 9, minos);

  /* show background */
  SHOW_BKG;
  SHOW_SPRITES;

  uint8_t key = 0;
  bool strat_pressed = false;
  bool select_pressed = false;
  bool A_pressed = false;
  bool B_pressed = false;
  bool right_pressed = false;
  bool left_pressed = false;
  bool up_pressed = false;
  bool down_pressed = false;
  das_t right_das;
  das_t left_das;
  das_reset_das(&right_das);
  das_reset_das(&left_das);
  bool game_over = false;
  bool rumble_requested = false;
  int16_t x_before_moving = 0;
  int16_t previous_frame_y = 0;
  bool das_rumble_requested = false;

  set_bkg_tile_xy(0, 0, 8);
  set_bkg_tile_xy(0, 1, 9);

  while (1) {
    if (game_over == true) {
      set_bkg_tile_xy(0, 0, 4);
      continue;
    }

    key = joypad();

    /* Board update */
    gbm_update_board_if_needed(&general_board);

    int8_t offset_x = 0;
    int8_t offset_y = 0;

    if ((key & J_RIGHT) && right_pressed == false) {
      right_pressed = true;
      x_before_moving = player_tetramino.x;
      t_move_tetramino_horizontally(&player_tetramino, &general_board, 1);

      if (x_before_moving == player_tetramino.x) {
        sc_rumble_screen(&player_tetramino, SCREEN_RUMBLE_DIRECTION_RIGHT);
      }

    } else if ((key & J_RIGHT) && right_pressed == true) {
      /* Process delay auto-shift (DAS) [RIGHT] */
      das_update(&right_das);
      if (right_das.movement_allowed) {
        x_before_moving = player_tetramino.x;
        t_move_tetramino_horizontally(&player_tetramino, &general_board, 1);

          if (das_rumble_requested == false && x_before_moving == player_tetramino.x) {
          sc_rumble_screen(&player_tetramino, SCREEN_RUMBLE_DIRECTION_RIGHT);
          das_rumble_requested = true;
        }
      }
    } else if ((key & J_LEFT) && left_pressed == false) {
      left_pressed = true;
      x_before_moving = player_tetramino.x;
      t_move_tetramino_horizontally(&player_tetramino, &general_board, -1);

      if (x_before_moving == player_tetramino.x) {
        sc_rumble_screen(&player_tetramino, SCREEN_RUMBLE_DIRECTION_LEFT);
      }
    } else if ((key & J_LEFT) && left_pressed == true) {
      /* Process delay auto-shift (DAS) [LEFT] */
      das_update(&left_das);
      if (left_das.movement_allowed) {
        x_before_moving = player_tetramino.x;
        t_move_tetramino_horizontally(&player_tetramino, &general_board, -1);

          if (das_rumble_requested == false && x_before_moving == player_tetramino.x) {
          sc_rumble_screen(&player_tetramino, SCREEN_RUMBLE_DIRECTION_LEFT);
          das_rumble_requested = true;
        }
      }
    }

    if (!(key & J_RIGHT) && right_pressed == true) {
      right_pressed = false;
      das_rumble_requested = false;
      das_reset_das(&right_das);
    }

    if (!(key & J_LEFT) && left_pressed == true) {
      left_pressed = false;
      das_rumble_requested = false;
      das_reset_das(&left_das);
    }

    if ((key & J_UP) && up_pressed == false) {
      up_pressed = true;
      if (cd_detect_collision(&general_board, &player_tetramino, 0, 1) == false) {
        t_request_hard_drop(&player_tetramino);
        sc_shake_screen(&player_tetramino);
      }
    }

    if (!(key & J_UP) && up_pressed == true) {
      up_pressed = false;
    }

    if ((key & J_DOWN) && down_pressed == false) {
      down_pressed = true;

      t_request_soft_drop(&player_tetramino, true);
      if (das_rumble_requested == false &&
          player_tetramino.soft_drop_enabled == true &&
          cd_detect_collision(&general_board, &player_tetramino, 0, 1) == true) {
          sc_rumble_screen(&player_tetramino, SCREEN_RUMBLE_DIRECTION_DOWN);
          das_rumble_requested = true;
      }
    } else if ((key & J_DOWN) && down_pressed == true) {
      if (das_rumble_requested == false &&
          player_tetramino.soft_drop_enabled == true &&
          cd_detect_collision(&general_board, &player_tetramino, 0, 1) == true) {
          sc_rumble_screen(&player_tetramino, SCREEN_RUMBLE_DIRECTION_DOWN);
          das_rumble_requested = true;
      }
    }

    if (!(key & J_DOWN) && down_pressed == true) {
      down_pressed = false;
      das_rumble_requested = false;
      t_request_soft_drop(&player_tetramino, false);
    }


    if ((key & J_START) && strat_pressed == false)
    {
      strat_pressed = true;
    }

    if (!(key & J_START) && strat_pressed == true)
    {
      strat_pressed = false;
    }

    if ((key & J_A) && A_pressed == false)
    {
      A_pressed = true;
      t_try_to_rotate_tetramino(
          &player_tetramino, &general_board, ROTATION_CLOCKWISE);
    }

    if (!(key & J_A) && A_pressed == true)
    {
      A_pressed = false;
    }

    if ((key & J_B) && B_pressed == false)
    {
      B_pressed = true;
      t_try_to_rotate_tetramino(
          &player_tetramino, &general_board, ROTATION_COUNTER_CLOCKWISE);
    }

    if (!(key & J_B) && B_pressed == true)
    {
      B_pressed = false;
    }

    if ((key & J_SELECT) && select_pressed == false)
    {
      select_pressed = true;
      t_request_hold(&player_tetramino, &general_board, &randomizer);
    }

    if (!(key & J_SELECT) && select_pressed == true)
    {
      select_pressed = false;
    }

    /* Update functions */
    game_over = t_update_tetramino(&player_tetramino, &general_board, &randomizer, game_level);
    sc_update_screen_controller(&player_tetramino);

    // Done processing, yield CPU and wait for start of next frame
    wait_vbl_done();
  }
}
