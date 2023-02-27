#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "types.h"

/* @brief initialize randomizer object
 * @param[in] randomizer piece tetramino randomizer control object. */
void pr_initialize_piece_randomizer(randomizer_t * randomizer);

/* @brief returns next tetramino using the 7-bag system.
 * @param[in] randomizer piece tetramino randomizer control object. */
tetramino_type_t pr_get_next_piece(randomizer_t * randomizer);