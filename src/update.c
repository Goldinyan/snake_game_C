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

void draw(game_state_t *state) {
  if (state->blinking_i == 0)
    state->blinking_i = (rand() % 40) == 0 ? 8 : 0;

  system("clear");

  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {

      const char *c = "";
      const char *c_1 = ".";
      const char *c_2 = ".";
      bool is_wall = false;

      bool is_not_blocked = (x != 4 && x != 5);

      // WALLS
      if (x == 0 || x == W - 1 || y == 0 || y == H - 1) {

        is_wall = true;

        if (y == 0 && x == 0) {
          c = "┌";
          printf("%s", c);
        } else if (y == 0 && x == 4) {
          printf("%4d", state->time / 10);
        } else if (y == 0 && x == W - 1) {
          c = "┐";
          printf("%s", c);
        } else if (y == H - 1 && x == 0) {
          c = "└";
          printf("%s", c);
        } else if (y == H - 1 && x == W - 1) {
          c = "┘";
          printf("%s", c);
        } else if ((y == 0 || y == H - 1) && is_not_blocked) {
          c = "─";
          printf("%s%s", c, c);
        } else if (x == 0 || x == W - 1) {
          c = "│";
          printf("%s", c);
        }
      }

      // food
      if (x == state->food.x && y == state->food.y) {
        c_1 = "@";
        c_2 = "@";
      }

      // body
      for (int j = 1; j < state->body_length; j++) {
        if (x == state->body[j].x && y == state->body[j].y) {
          c_1 = "(";
          c_2 = ")";
          break;
        }
      }

      // head
      if (x == state->body[0].x && y == state->body[0].y) {
        if (state->blinking_i > 0) {
          c_1 = "0";
          c_2 = "0";
          state->blinking_i--;
        } else {
          c_1 = "O";
          c_2 = "O";
        }
      }

      if (!is_wall) {
        printf("%s%s", c_1, c_2);
      }

    }
    putchar('\n');
  }
}

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
