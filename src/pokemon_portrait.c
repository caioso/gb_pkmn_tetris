#include "pokemon_portrait.h"
#include "constants.h"
#include "minos.h"

#include <rand.h>

static uint8_t current_tile[16 * 35];
static uint8_t backup_msb[7];
static uint8_t backup_lsb[7];
static uint8_t current_pixel_row = 0;
static uint8_t current_tile_row = 0;
static uint8_t noise_bar_animation_delay = 0;
void pp_initialize(pokemon_portrait_t * portrait, uint8_t initial_tile_index,
                   uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
  portrait->noise_level = 0;
  portrait->initial_tile_index = initial_tile_index;
  portrait->tile_w = w;
  portrait->tile_h = h;
  portrait->origin_x = x;
  portrait->origin_y = y;
  portrait->dirty = true;

  VBK_REG = VBK_TILES;
  uint8_t portrait_tiles[7 * 5];
  uint8_t tile_counter = 0;
  for (uint8_t i = 0; i < portrait->tile_h; i++) {
    for (uint8_t j = 0; j < portrait->tile_w; j++) {
      portrait_tiles[i*portrait->tile_w + j] = POKEMON_PORTRAIT_STARTING_TILE + tile_counter; /* Should be updated to the actual pokemon tiles. */
      tile_counter++;
    }
  }
  set_bkg_tiles(portrait->origin_x, portrait->origin_y, 7, 5, portrait_tiles);
}

void pp_set_noise(pokemon_portrait_t * portrait, uint8_t noise_level) {
  VBK_REG = VBK_TILES;
  current_tile_row = 0;
  current_pixel_row = 0;
  portrait->noise_level = noise_level;
  uint16_t counter = 0;
  for (uint8_t i = 0; i < 35; i++) {

    uint8_t tile = 0;
    for (uint8_t j = 0; j < NUMBER_OF_BYTES_PER_TILE_2BPP; j+=2) {
      uint8_t pixel_msb = \
        (minos[3 * NUMBER_OF_BYTES_PER_TILE_2BPP + j]);
      uint8_t pixel_lsb = \
        (minos[3 * NUMBER_OF_BYTES_PER_TILE_2BPP + j + 1]);

      uint8_t value = (((uint8_t)rand()));
      if (value % (uint8_t)MAX_NOISE_LEVEL >= (portrait->noise_level)) {
          pixel_msb &= value;
          pixel_lsb &= value;
      }

      current_tile[counter] = pixel_msb;
      current_tile[counter + 1] = pixel_lsb;

      if (i < 7 && j == 0){
        backup_msb[i] = pixel_msb;
        backup_lsb[i] = pixel_lsb;
      }

      counter += 2;
    }
  }

  set_bkg_data(POKEMON_PORTRAIT_STARTING_TILE, 35, current_tile);
}

void pp_update(pokemon_portrait_t * portrait) {
  (void)(portrait);
  VBK_REG = VBK_TILES;
  //else
  {
    if (noise_bar_animation_delay == 9) {
      for (uint8_t i = 0; i < 7; i++) {
        uint16_t tile_index_base = (i + current_tile_row * 7) * NUMBER_OF_BYTES_PER_TILE_2BPP;

        if (current_pixel_row > 0) {
          if (current_pixel_row == 0 && current_tile_row > 0) {
            /* restore previous row (last row, previous tile row) */
            uint16_t previous_tile_base = (i + (current_tile_row - 1) * 7) *
            NUMBER_OF_BYTES_PER_TILE_2BPP;
            current_tile[previous_tile_base + 2*(7)] = backup_msb[i];
            current_tile[previous_tile_base + 2*(7) + 1] = backup_lsb[i];
          } else {
            current_tile[tile_index_base + 2*(current_pixel_row - 1)] = backup_msb[i];
            current_tile[tile_index_base + 2*(current_pixel_row - 1) + 1] = backup_lsb[i];
          }
          backup_msb[i] = current_tile[tile_index_base + 2*current_pixel_row];
          backup_lsb[i] = current_tile[tile_index_base + 2*current_pixel_row + 1];
        }

        current_tile[tile_index_base + 2*current_pixel_row] = (((uint8_t)rand()));
        current_tile[tile_index_base + 2*current_pixel_row + 1] = (((uint8_t)rand()));
      }

      current_pixel_row++;
      if (current_pixel_row == 8) {
        current_tile_row++;
        current_pixel_row = 0;
      }
      if (current_tile_row == 5) {
        current_tile_row = 0;
      }
      if (current_pixel_row == 0 && current_tile_row > 0) {
        set_bkg_data(POKEMON_PORTRAIT_STARTING_TILE + (((current_tile_row - 1) * 7)), 7,
      &current_tile[((current_tile_row - 1) * 7) * NUMBER_OF_BYTES_PER_TILE_2BPP]);
      }
      set_bkg_data(POKEMON_PORTRAIT_STARTING_TILE + ((current_tile_row * 7)), 7,
      &current_tile[(current_tile_row * 7) * NUMBER_OF_BYTES_PER_TILE_2BPP]);
      noise_bar_animation_delay = 0;
    } else {
      noise_bar_animation_delay++;
    }
  }
}