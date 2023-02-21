#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>
#include <stdio.h>

/* game includes */
#include "board_initialization_templates.h"
#include "collision_detector.h"
#include "constants.h"
#include "general_board_manager.h"
#include "screen_controller.h"
#include "tetramino.h"

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

// lots of comments
unsigned char smile[] =
    {
        0x0F, 0x0F, 0x30, 0x30, 0x40, 0x40, 0x40, 0x40,
        0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84,
        0x84, 0x84, 0x84, 0x84, 0x80, 0x80, 0x80, 0x80,
        0x44, 0x44, 0x43, 0x43, 0x30, 0x30, 0x0F, 0x0F,
        0xF0, 0xF0, 0x0C, 0x0C, 0x02, 0x02, 0x02, 0x02,
        0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
        0x21, 0x21, 0x21, 0x21, 0x01, 0x01, 0x01, 0x01,
        0x22, 0x22, 0xC2, 0xC2, 0x0C, 0x0C, 0xF0, 0xF0,
        0x0F, 0x0F, 0x30, 0x30, 0x40, 0x40, 0x40, 0x40,
        0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84,
        0x84, 0x84, 0x84, 0x84, 0x80, 0x80, 0x80, 0x80,
        0x44, 0x44, 0x43, 0x43, 0x30, 0x30, 0x0F, 0x0F,
        0xF0, 0xF0, 0x0C, 0x0C, 0x02, 0x02, 0x02, 0x02,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xF9, 0xF9,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x22, 0x22, 0xC2, 0xC2, 0x0C, 0x0C, 0xF0, 0xF0};
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

void main(void)
{
  /* Game settings */
  uint16_t game_level = 0;

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
                         TETRAMINO_TYPE_Z,
                         MAIN_TETRAMINO_SPRITE_INDEX);
  t_spawn_tetramino(&player_tetramino);

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
  set_bkg_data(1, 8, smile);

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
  set_sprite_data(1, 8, smile);

  /* show background */
  SHOW_BKG;
  SHOW_SPRITES;

  /* test: set some tiles to see the change */
  general_board.blocks[5][5] = BLOCK_TYPE_BLUE;
  general_board.blocks[6][5] = BLOCK_TYPE_BLUE;
  general_board.blocks[7][5] = BLOCK_TYPE_BLUE;
  general_board.blocks[7][6] = BLOCK_TYPE_BLUE;
  general_board.dirty = true;

  uint8_t key = 0;
  bool strat_pressed = false;
  bool select_pressed = false;
  bool A_pressed = false;
  bool B_pressed = false;
  bool right_pressed = false;
  bool left_pressed = false;
  bool up_pressed = false;

  while (1) {
    key = joypad();

    /* Board update */
    gbm_update_board_if_needed(&general_board);

    int8_t offset_x = 0;
    int8_t offset_y = 0;

    if ((key & J_RIGHT) && right_pressed == false) {
      right_pressed = true;
      if (cd_detect_collision(&general_board, &player_tetramino, 1, 0) == false) {
        player_tetramino.x = player_tetramino.x + BLOCK_SIDE_IN_PIXELS;
        player_tetramino.should_update_ghost = true;
        t_try_to_reset_lock_delay(&player_tetramino);
      }
    }
    else if ((key & J_LEFT) && left_pressed == false) {
      left_pressed = true;
      if (cd_detect_collision(&general_board, &player_tetramino, -1, 0) == false) {
        player_tetramino.x = player_tetramino.x - BLOCK_SIDE_IN_PIXELS;
        player_tetramino.should_update_ghost = true;
        t_try_to_reset_lock_delay(&player_tetramino);
      }
    }

    if (!(key & J_RIGHT) && right_pressed == true) {
      right_pressed = false;
    }

    if (!(key & J_LEFT) && left_pressed == true)
    {
      left_pressed = false;
    }

    if ((key & J_UP) && up_pressed == false) {
      up_pressed = true;
      if (cd_detect_collision(&general_board, &player_tetramino, 0, 1) == false) {
        t_request_hard_drop(&player_tetramino);
        sc_shake_screen();
      }
    }

    if (!(key & J_UP) && up_pressed == true) {
      up_pressed = false;
    }

    if ((key & J_START) && strat_pressed == false)
    {
      strat_pressed = true;
      game_level = 10;
    }

    if (!(key & J_START) && strat_pressed == true)
    {
      strat_pressed = false;
      game_level = 0;
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
    }

    if (!(key & J_SELECT) && select_pressed == true)
    {
      select_pressed = false;
    }

    /* Update functions */
    t_update_tetramino(&player_tetramino, &general_board, game_level);
    sc_update_screen_controller(&player_tetramino);

    // Done processing, yield CPU and wait for start of next frame
    wait_vbl_done();
  }
}
