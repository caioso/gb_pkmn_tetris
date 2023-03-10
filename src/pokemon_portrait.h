#pragma once

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>
#include <stdbool.h>

#include "types.h"

void pp_initialize(pokemon_portrait_t * portrait, uint8_t initial_tile_index,
                   uint8_t x, uint8_t y, uint8_t w, uint8_t h);

void pp_set_noise(pokemon_portrait_t * portrait, uint8_t noise_level);

void pp_update(pokemon_portrait_t * portrait);