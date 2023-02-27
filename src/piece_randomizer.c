#include "piece_randomizer.h"
#include <rand.h>

void shuffle(randomizer_t * randomizer);

/* Public functions */
void pr_initialize_piece_randomizer(randomizer_t * randomizer) {
  randomizer->length = 0;
}

tetramino_type_t pr_get_next_piece(randomizer_t * randomizer) {
  if (randomizer->length == 0) {
    shuffle(randomizer);
  }

  uint8_t index = ((uint8_t)rand()) % (uint8_t)7;;
  while (randomizer->bag[index] == TETRAMINO_TYPE_NULL) {
    index = ((uint8_t)rand()) % (uint8_t)7;
  }

  randomizer->length--;
  tetramino_type_t tetramino = randomizer->bag[index];
  randomizer->bag[index] = TETRAMINO_TYPE_NULL;
  return tetramino;
}

/* private functions */
void shuffle(randomizer_t * randomizer) {
  randomizer->length = 7;
  randomizer->bag[0] = TETRAMINO_TYPE_Z;
  randomizer->bag[1] = TETRAMINO_TYPE_O;
  randomizer->bag[2] = TETRAMINO_TYPE_L;
  randomizer->bag[3] = TETRAMINO_TYPE_S;
  randomizer->bag[4] = TETRAMINO_TYPE_T;
  randomizer->bag[5] = TETRAMINO_TYPE_J;
  randomizer->bag[6] = TETRAMINO_TYPE_I;

  for (uint8_t i = 0; i < 7; i++) {
    uint8_t index_1 = ((uint8_t)rand()) % (uint8_t)7;
    uint8_t index_2 = ((uint8_t)rand()) % (uint8_t)7;

    while (index_1 == index_2) {
      index_2 = ((uint8_t)rand()) % (uint8_t)7;
    }

    tetramino_type_t first = randomizer->bag[index_1];
    randomizer->bag[index_1] = randomizer->bag[index_2];
    randomizer->bag[index_2] = first;
  }
}