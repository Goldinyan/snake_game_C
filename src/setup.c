#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_state.h"
#include "input.h"

void setup_game(game_state_t *state) {
  state->body[0].pos.x = W/2;
  state->body[0].pos.y = H/2;
  state->body_length = 1;
  state->head_direction = DIR_TOP;


  // Other
  state->food.y = rand() % H;
  state->food.x = rand() % W;
  state->lost = false;
  state->health = 5;
  state->time = 0;

  for (int i = 1; i <= MAX_BODY; i++)
    state->body[i].pos.x = -1;

  enable_raw_mode();
}

void clear_grid(game_state_t *state) {
  for (int y = 0; y < H; y++)
    for (int x = 0; x < W; x++)
      state->grid[y][x] = ' ';
}
