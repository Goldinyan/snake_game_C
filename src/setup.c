#include <stdbool.h>
#include <stdio.h>

#include "game_state.h"
#include "input.h"

void setup_game(game_state_t *state) {
  state->lost = false;
  state->health = 5;
  state->time = 0;
  state->body_length = 1;

  for (int i = 0; i <= 200; i++)
    state->body[i].pos.x = -1;

  enable_raw_mode();
}

void clear_grid(game_state_t *state) {
  for (int y = 0; y < H; y++)
    for (int x = 0; x < W; x++)
      state->grid[y][x] = ' ';
}
