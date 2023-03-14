#pragma once

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>
#include <stdbool.h>

#include "types.h"

/* @brief Initialize Pokmeon Portrait Data Struvture.
 * @param[in, out] portrait Pokemon Portrait.
 * @param[in] initial_tile_index initial tile index.
 * @param[in] tile_bytes Tile Bytes reference
 * @param[in] attribute_bytes Attribute Bytes Reference
 * @param[in] palette_bytes Palette Bytes Reference
 * @param[in] x initial x (tile) position
 * @param[in] y initial y (tile) position
 * @param[in] w portrait width (tile)
 * @param[in] h portrait height (tile) */
void pp_initialize(pokemon_portrait_t * portrait, uint8_t initial_tile_index,
                   uint8_t * tile_bytes, uint8_t * attribute_bytes,
                   uint8_t * palette_bytes,
                   uint8_t x, uint8_t y, uint8_t w, uint8_t h);

/* @brief Set target noise level.
 * @param[in, out] portrait Pokemon Portrait.
 * @param[in] h noise_level target noise level. */
void pp_set_noise(pokemon_portrait_t * portrait, uint8_t noise_level);

/* @brief Update current portrait level.
 * @param[in, out] portrait Pokemon Portrait. */
void pp_update(pokemon_portrait_t * portrait);