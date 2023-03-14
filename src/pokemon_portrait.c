#include "pokemon_portrait.h"
#include "constants.h"
#include <rand.h>

static uint8_t noisy_tiles_pixels[NUMBER_OF_BYTES_PER_TILE_2BPP * TOTAL_POKEMON_PORTRAIT_TILES];
static uint8_t noisy_pixel_row_backup_msb[POKEMON_PORTRAIT_COLS];
static uint8_t noisy_pixel_row_backup_lsb[POKEMON_PORTRAIT_COLS];
static uint8_t current_pixel_row = 0;
static uint8_t current_tile_row = 0;
static uint8_t noise_bar_animation_delay = 0;
void pp_initialize(pokemon_portrait_t * portrait, uint8_t initial_tile_index,
                   uint8_t * tile_bytes, uint8_t * attribute_bytes,
                   uint8_t * palette_bytes,
                   uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
  portrait->noise_level = 0;
  portrait->initial_tile_index = initial_tile_index;
  portrait->tile_w = w;
  portrait->tile_h = h;
  portrait->origin_x = x;
  portrait->origin_y = y;
  portrait->dirty = true;
  portrait->tile_bytes = tile_bytes;
  portrait->attribute_bytes = attribute_bytes;
  portrait->palette_bytes = palette_bytes;

  /* Load Palettes */
  set_bkg_palette(BKGF_CGB_PAL0, 1, &portrait->palette_bytes[0]);
  set_bkg_palette(BKGF_CGB_PAL1, 1, &portrait->palette_bytes[4]);

  /* Load Tiles */
  for (uint8_t i = 0; i < 35; i++) {
    set_bkg_data(POKEMON_PORTRAIT_STARTING_TILE + i, 1,
                 &portrait->tile_bytes[2 * NUMBER_OF_BYTES_PER_TILE_2BPP]);
  }

  VBK_REG = VBK_TILES;
  uint8_t portrait_tiles[TOTAL_POKEMON_PORTRAIT_TILES];
  uint8_t tile_counter = 0;
  for (uint8_t i = 0; i < portrait->tile_h; i++) {
    for (uint8_t j = 0; j < portrait->tile_w; j++) {
      portrait_tiles[i*portrait->tile_w + j] =
        POKEMON_PORTRAIT_STARTING_TILE + tile_counter; /* Should be updated to the actual pokemon tiles. */
      tile_counter++;
    }
  }
  set_bkg_tiles(portrait->origin_x, portrait->origin_y,
                POKEMON_PORTRAIT_COLS, POKEMON_PORTRAIT_ROWS, portrait_tiles);

  VBK_REG = VBK_ATTRIBUTES;
  tile_counter = 0;
  for (uint8_t i = 0; i < portrait->tile_h; i++) {
    for (uint8_t j = 0; j < portrait->tile_w; j++) {
      portrait_tiles[i*portrait->tile_w + j] = portrait->attribute_bytes[tile_counter]; /* Should be updated to the actual pokemon tiles. */
      tile_counter++;
    }
  }
  set_bkg_tiles(portrait->origin_x, portrait->origin_y,
                POKEMON_PORTRAIT_COLS, POKEMON_PORTRAIT_ROWS, portrait_tiles);
}

void pp_set_noise(pokemon_portrait_t * portrait, uint8_t noise_level) {
  VBK_REG = VBK_TILES;
  current_tile_row = 0;
  current_pixel_row = 0;
  portrait->noise_level = noise_level;

  uint8_t backup_counter = 0;
  uint16_t counter = 0;
  for (uint8_t i = 0; i < TOTAL_POKEMON_PORTRAIT_TILES; i++) {

    uint8_t tile = 0;
    for (uint8_t j = 0; j < NUMBER_OF_BYTES_PER_TILE_2BPP; j += 2) {
      uint8_t pixel_msb = portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j] = \
        (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j]);
      uint8_t pixel_lsb = portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j + 1] = \
        (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j + 1]);

      uint8_t value = (((uint8_t)rand()));
      if (value % (uint8_t)MAX_NOISE_LEVEL >= (portrait->noise_level)) {
          pixel_msb = portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j] & value;
          pixel_lsb = portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j + 1] & value;

        if ((i >= 1 && i <= 5) || (i >= 29 && i <= 33)) {
          if (j == 0 || j == 14) {
            pixel_msb = (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j]);
            pixel_lsb = (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j + 1]);
          }
        } else if (i == 7 || i == 14 || i == 21) {
          pixel_msb = (0x80 & (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j])) | (0x7F & value);
          pixel_lsb = (0x80 & (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j + 1])) | (0x7F & value);
        } else if (i == 13 || i == 20 || i == 27) {
          pixel_msb = (0x01 & (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j])) | (0xFE & value);
          pixel_lsb = (0x01 & (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j + 1]))| (0xFE & value);
        } else if (i == 0) {
          if (j >= 2) {
            pixel_msb = (0x80 & (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j])) | (0x7F & value);
            pixel_lsb = (0x80 & (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j + 1])) | (0x7F & value);
          } else {
            pixel_msb = (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j]);
            pixel_lsb = (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j + 1]);
          }
        }  else if (i == 6) {
          if (j >= 2) {
            pixel_msb = (0x01 & (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j])) | (0xFE & value);
            pixel_lsb = (0x01 & (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j + 1])) | (0xFE & value);
          } else {
            pixel_msb = (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j]);
            pixel_lsb = (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j + 1]);
          }
        } else if (i == 28) {
          if (j < 14) {
            pixel_msb = (0x80 & (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j])) | (0x7F & value);
            pixel_lsb = (0x80 & (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j + 1])) | (0x7F & value);
          } else {
            pixel_msb = (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j]);
            pixel_lsb = (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j + 1]);
          }
        } else if (i == 34) {
          if (j < 14) {
            pixel_msb = (0x01 & (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j])) | (0xFE & value);
            pixel_lsb = (0x01 & (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j + 1])) | (0xFE & value);
          } else {
            pixel_msb = (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j]);
            pixel_lsb = (portrait->tile_bytes[i*NUMBER_OF_BYTES_PER_TILE_2BPP + j + 1]);
          }
        }
      }

      noisy_tiles_pixels[counter] = pixel_msb;
      noisy_tiles_pixels[counter + 1] = pixel_lsb;

      if (i >= POKEMON_PORTRAIT_LAST_ROW_FIRST_TILE_INDEX && j == 14){
        noisy_pixel_row_backup_msb[backup_counter] = pixel_msb;
        noisy_pixel_row_backup_lsb[backup_counter] = pixel_lsb;
        backup_counter++;
      }

      counter += 2;
    }
  }

  set_bkg_data(POKEMON_PORTRAIT_STARTING_TILE,
               TOTAL_POKEMON_PORTRAIT_TILES, noisy_tiles_pixels);
}

void pp_update(pokemon_portrait_t * portrait) {
  (void)(portrait);
  VBK_REG = VBK_TILES;
  if (noise_bar_animation_delay == 0) {
    /* Per tile column, corrupt the restore the previouspixel row*/
    for (uint8_t i = 0; i < POKEMON_PORTRAIT_COLS; i++) {
      uint16_t backup_tile_row = 0;
      uint16_t backup_pixel_row = 0;
      if (current_pixel_row == 0) { /* previous tile */
        backup_tile_row = current_tile_row == 0? POKEMON_PORTRAIT_LAST_ROW : current_tile_row - 1;
        backup_pixel_row = (backup_tile_row * POKEMON_PORTRAIT_COLS + i) *
                              NUMBER_OF_BYTES_PER_TILE_2BPP + 14;
      } else { /* previous pixel row*/
        backup_tile_row = (current_tile_row * POKEMON_PORTRAIT_COLS + i) *
                              NUMBER_OF_BYTES_PER_TILE_2BPP;
        backup_pixel_row = backup_tile_row + (current_pixel_row - 1) * 2;
      }

      /* Update Tiles */
      noisy_tiles_pixels[backup_pixel_row] = noisy_pixel_row_backup_msb[i];
      noisy_tiles_pixels[backup_pixel_row + 1] = noisy_pixel_row_backup_lsb[i];
    }
  } else if (noise_bar_animation_delay == 2) {
    /* Per tile column, corrupt the current pixel row*/
    for (uint8_t i = 0; i < POKEMON_PORTRAIT_COLS; i++) {
      uint16_t tile_base_address = (current_tile_row * POKEMON_PORTRAIT_COLS + i) *
                                      NUMBER_OF_BYTES_PER_TILE_2BPP;
      uint16_t pixel_row_base_address = tile_base_address + current_pixel_row * 2;

      /* back currentpixel rowup. */
      noisy_pixel_row_backup_msb[i] = noisy_tiles_pixels[pixel_row_base_address];
      noisy_pixel_row_backup_lsb[i] = noisy_tiles_pixels[pixel_row_base_address + 1];

      /* Update Tiles */
      noisy_tiles_pixels[pixel_row_base_address] = (((uint8_t)rand()));
      noisy_tiles_pixels[pixel_row_base_address + 1] = (((uint8_t)rand()));
    }
  } else if (noise_bar_animation_delay == POKEMON_PORTRAIT_LAST_ROW) {
      /* Update Tiles in VRAM (point to first pixel in the current tile row)*/
      uint16_t tile_base_address = (current_tile_row * POKEMON_PORTRAIT_COLS) *
                                      NUMBER_OF_BYTES_PER_TILE_2BPP;
      uint16_t tile_index = POKEMON_PORTRAIT_STARTING_TILE + (current_tile_row * POKEMON_PORTRAIT_COLS);
      set_bkg_data(tile_index, 7, &noisy_tiles_pixels[tile_base_address]);

      if (current_pixel_row == 0) { /* previous tile */
        uint16_t target_tile_row = (current_tile_row == 0? POKEMON_PORTRAIT_LAST_ROW : current_tile_row - 1);
        tile_base_address = (target_tile_row * POKEMON_PORTRAIT_COLS) * NUMBER_OF_BYTES_PER_TILE_2BPP;
        tile_index = POKEMON_PORTRAIT_STARTING_TILE + (target_tile_row * POKEMON_PORTRAIT_COLS);
        set_bkg_data(tile_index, POKEMON_PORTRAIT_COLS, &noisy_tiles_pixels[tile_base_address]);
      }

      /* Update row counters*/
      current_pixel_row++;
      if (current_pixel_row == PIXELS_ROWS_IN_TILE) {
        current_pixel_row = 0;
        current_tile_row++;
      }

      if (current_tile_row == POKEMON_PORTRAIT_ROWS) {
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