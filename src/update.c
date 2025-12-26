#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_state.h"
#include "input.h"

bool compare_pos(vector_t a, vector_t b) {
  if (a.x == b.x && a.y == b.y) {
    return true;
  }
  return false;
};

void draw(game_state_t *state) {
  system("clear");

  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      for (int j = 1; j < state->body_length; j++) {
        if (x == state->body[j].pos.x && y == state->body[j].pos.y) {
          putchar('x');
        }
      }
      if (x == state->body[0].pos.x && y == state->body[0].pos.y)
        putchar('O');
      else if (x == state->food.x && y == state->food.y)
        putchar('@');
      else
        putchar('.');
    }
    putchar('\n');
  }
}

void update(game_state_t *state) {

  for (int i = 0; i <= 200; i++) {

    if (state->body[i].pos.x == -1)
      return;

    // Set Directions points

    if (kbhit()) {
      char c = getchar();
      if (c == 'w') {
        state->dir[state->dir_count + 1].pos = state->body[0].pos;
        state->dir[state->dir_count + 1].dir = DIR_TOP;
      }
      if (c == 's') {
        state->dir[state->dir_count + 1].pos = state->body[0].pos;
        state->dir[state->dir_count + 1].dir = DIR_BOTTOM;
      }
      if (c == 'a') {
        state->dir[state->dir_count + 1].pos = state->body[0].pos;
        state->dir[state->dir_count + 1].dir = DIR_LEFT;
      }
      if (c == 'd') {
        state->dir[state->dir_count + 1].pos = state->body[0].pos;
        state->dir[state->dir_count + 1].dir = DIR_RIGHT;
      }
    }

    // food
    if (compare_pos(state->body[0].pos, state->food)) {
      state->health++;
      state->food.x = rand() % 20;
      state->food.y = rand() % 20;
    }

    // If into self -> lost
    for (int j = 0; j <= state->body_length; j++) {
      if (compare_pos(state->body[i].pos, state->body[j].pos)) {
        state->lost = true;
      }
    }

    // Wrap-around

    if (state->body[i].pos.x < 0)
      state->body[i].pos.x = W - 1;
    if (state->body[i].pos.y < 0)
      state->body[i].pos.y = H - 1;

    // Reset if all good

    if (state->body[i].pos.x >= W)
      state->body[i].pos.x = 0;
    if (state->body[i].pos.y >= H)
      state->body[i].pos.y = 0;

    // Change Dir if one a field

    for (int j = 0; j < state->dir_count; j++) {
      if (compare_pos(state->body[i].pos, state->dir[j].pos)) {
        state->body[i].dir = state->dir[j].dir;
        if(i == state->body_length) {
          state->dir[j].pos.x = -1;
        } 
      }
    }

    // Move based on dir

    switch (state->body[i].dir) {
    case DIR_TOP:
      state->body[i].pos.y++;
      break;
    case DIR_BOTTOM:
      state->body[i].pos.y--;
      break;
    case DIR_LEFT:
      state->body[i].pos.x--;
      break;
    case DIR_RIGHT:
      state->body[i].pos.x++;
      break;
    }
  }
}
