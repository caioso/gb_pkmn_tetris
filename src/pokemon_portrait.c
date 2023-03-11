#include "pokemon_portrait.h"
#include "constants.h"
#include "minos.h"

#include <rand.h>

static uint8_t noisy_tiles_pixels[16 * 35];
static uint8_t noisy_pixel_row_backup_msb[7];
static uint8_t noisy_pixel_row_backup_lsb[7];
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
  uint8_t backup_counter = 0;
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

      noisy_tiles_pixels[counter] = pixel_msb;
      noisy_tiles_pixels[counter + 1] = pixel_lsb;

      if (i >= 28 && j == 14){
        noisy_pixel_row_backup_msb[backup_counter] = pixel_msb;
        noisy_pixel_row_backup_lsb[backup_counter] = pixel_lsb;
        backup_counter++;
      }

      counter += 2;
    }
  }

  set_bkg_data(POKEMON_PORTRAIT_STARTING_TILE, 35, noisy_tiles_pixels);
}

void pp_update(pokemon_portrait_t * portrait) {
  (void)(portrait);
  VBK_REG = VBK_TILES;
  if (noise_bar_animation_delay == 0) {
    /* Per tile column, corrupt the restore the previouspixel row*/
    for (uint8_t i = 0; i < 7; i++) {
      uint16_t backup_tile_row = 0;
      uint16_t backup_pixel_row = 0;
      if (current_pixel_row == 0) { /* previous tile */
        backup_tile_row = current_tile_row == 0? 4 : current_tile_row - 1;
        backup_pixel_row = (backup_tile_row * 7 + i) * NUMBER_OF_BYTES_PER_TILE_2BPP + 14;
      } else { /* previouspixel row*/
        backup_tile_row = (current_tile_row * 7 + i) * NUMBER_OF_BYTES_PER_TILE_2BPP;
        backup_pixel_row = backup_tile_row + (current_pixel_row - 1) * 2;
      }

      /* Update Tiles */
      noisy_tiles_pixels[backup_pixel_row] = noisy_pixel_row_backup_msb[i];
      noisy_tiles_pixels[backup_pixel_row + 1] = noisy_pixel_row_backup_lsb[i];
    }
  } else if (noise_bar_animation_delay == 2) {
    /* Per tile column, corrupt the current pixel row*/
    for (uint8_t i = 0; i < 7; i++) {
      uint16_t tile_base_address = (current_tile_row * 7 + i) * NUMBER_OF_BYTES_PER_TILE_2BPP;
      uint16_t pixel_row_base_address = tile_base_address + current_pixel_row * 2;

      /* back currentpixel rowup. */
      noisy_pixel_row_backup_msb[i] = noisy_tiles_pixels[pixel_row_base_address];
      noisy_pixel_row_backup_lsb[i] = noisy_tiles_pixels[pixel_row_base_address + 1];

      /* Update Tiles */
      noisy_tiles_pixels[pixel_row_base_address] = (((uint8_t)rand()));
      noisy_tiles_pixels[pixel_row_base_address + 1] = (((uint8_t)rand()));
    }
  } else if (noise_bar_animation_delay == 4) {
      /* Update Tiles in VRAM (point to first pixel in the current tile row)*/
      uint16_t tile_base_address = (current_tile_row * 7) * NUMBER_OF_BYTES_PER_TILE_2BPP;
      uint16_t tile_index = POKEMON_PORTRAIT_STARTING_TILE + (current_tile_row * 7);
      set_bkg_data(tile_index, 7, &noisy_tiles_pixels[tile_base_address]);

      if (current_pixel_row == 0) { /* previous tile */
        uint16_t target_tile_row = (current_tile_row == 0? 4 : current_tile_row - 1);
        tile_base_address = (target_tile_row * 7) * NUMBER_OF_BYTES_PER_TILE_2BPP;
        tile_index = POKEMON_PORTRAIT_STARTING_TILE + (target_tile_row * 7);
        set_bkg_data(tile_index, 7, &noisy_tiles_pixels[tile_base_address]);
      }

      /* Update row counters*/
      current_pixel_row++;
      if (current_pixel_row == 8) {
        current_pixel_row = 0;
        current_tile_row++;
      }

      if (current_tile_row == 5) {
        current_tile_row = 0;
      }
  }

  /* Update delay counter */
  if (noise_bar_animation_delay == 4) {
    noise_bar_animation_delay = 0 ;
  } else {
    noise_bar_animation_delay++;
  }
}