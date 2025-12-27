#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_state.h"
#include "input.h"

static void handle_input(game_state_t *state);

bool compare_pos(vector_t a, vector_t b) {
  if (a.x == b.x && a.y == b.y) {
    return true;
  }
  return false;
};


void update(game_state_t *state) {
  handle_input(state);
  if(!state->lost) state->time += 1;

  // Kopf moven lol
  switch (state->head_direction) {
  case DIR_TOP:
    state->body[0].y--;
    break;
  case DIR_BOTTOM:
    state->body[0].y++;
    break;
  case DIR_LEFT:
    state->body[0].x--;
    break;
  case DIR_RIGHT:
    state->body[0].x++;
    break;
  }

  // Wrap-around
  if (state->body[0].x < 1)
    state->body[0].x = W - 2;
  if (state->body[0].x >= W - 1)
    state->body[0].x = 1;
  if (state->body[0].y < 1)
    state->body[0].y = H - 2;
  if (state->body[0].y >= H - 1)
    state->body[0].y = 1;

  // Self-collision
  for (int i = 1; i < state->body_length; i++) {
    if (compare_pos(state->body[0], state->body[i])) {
      state->lost = true;
      return;
    }
  }

  // Food
  if (compare_pos(state->body[0], state->food)) {
    state->body_length++;
    state->body[state->body_length - 1] = state->body[state->body_length - 2];
    state->food.x = rand() % (W - 1) + 1;
    state->food.y = rand() % (H - 1) + 1;
  }

  // Körper nachziehen
  for (int i = state->body_length - 1; i > 0; i--) {
    state->body[i] = state->body[i - 1];
  }
}

static void handle_input(game_state_t *state) {
  if (!kbhit())
    return;

  char c = getchar();

  direction_t cur = state->head_direction;

  if (c == 'w' && cur != DIR_BOTTOM) {
    state->head_direction = DIR_TOP;
  } else if (c == 's' && cur != DIR_TOP) {
    state->head_direction = DIR_BOTTOM;
  } else if (c == 'a' && cur != DIR_RIGHT) {
    state->head_direction = DIR_LEFT;
  } else if (c == 'd' && cur != DIR_LEFT) {
    state->head_direction = DIR_RIGHT;
  }
}
