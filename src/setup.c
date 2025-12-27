#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_state.h"
#include "input.h"

void setup_game(game_state_t *state) {
  state->body[0].x = W / 2;
  state->body[0].y = H / 2;
  state->body_length = 1;
  state->blinking_i = 0;
  state->head_direction = DIR_TOP;

  // Other
  state->food.y = rand() % (H - 1) + 1;
  state->food.x = rand() % (W - 1) + 1;
  state->lost = false;
  state->health = 5;
  state->time = 0;

  for (int i = 1; i < MAX_BODY; i++) {
    // hatte i <= MAX_BODY -> gab es nicht hat anderes -1 gemacht
    // in dem Fall food.x, da next in memory, ist das krank
    state->body[i].x = -1;
  }

  enable_raw_mode();
}

void clear_grid(game_state_t *state) {
  for (int y = 0; y < H; y++)
    for (int x = 0; x < W; x++)
      state->grid[y][x] = ' ';
}
