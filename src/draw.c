#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_state.h"

typedef enum {
  WALL_NONE,
  WALL_CORNER_TL,
  WALL_CORNER_TR,
  WALL_CORNER_BL,
  WALL_CORNER_BR,
  WALL_H,
  WALL_V
} wall_t;

wall_t get_wall_type(int x, int y) {
  if (y == 0 && x == 0)
    return WALL_CORNER_TL;
  if (y == 0 && x == W - 1)
    return WALL_CORNER_TR;
  if (y == H - 1 && x == 0)
    return WALL_CORNER_BL;
  if (y == H - 1 && x == W - 1)
    return WALL_CORNER_BR;

  if ((y == 0 || y == H - 1))
    return WALL_H;
  if (x == 0 || x == W - 1)
    return WALL_V;

  return WALL_NONE;
}

const char *wall_char(wall_t w) {
  switch (w) {
  case WALL_CORNER_TL:
    return "┌";
  case WALL_CORNER_TR:
    return "┐";
  case WALL_CORNER_BL:
    return "└";
  case WALL_CORNER_BR:
    return "┘";
  case WALL_H:
    return "─";
  case WALL_V:
    return "│";
  default:
    return NULL;
  }
}

bool is_time_slot(int x, int y) { return (y == 0 && x == 4); }
bool is_blocked(int x, int y) { return ((y == 0) && (x == 5 || x == 5)); }

void draw(game_state_t *state) {
  if (state->blinking_i == 0)
    state->blinking_i = (rand() % 40) == 0 ? 8 : 0;

  system("clear");

  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {

      wall_t w = get_wall_type(x, y);

      if (!is_blocked(x, y)) {

        if (is_time_slot(x, y)) {
          printf("%4d", state->time / 10);
        } else if (w != WALL_NONE) {

          const char *wc = wall_char(w);

          if (w == WALL_H)
            printf("%s%s", wc, wc); // hord 2x
          else
            printf("%s", wc); // vert 1x

        } else {
          const char *c_1 = ".";
          const char *c_2 = ".";

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
          printf("%s%s", c_1, c_2);
        }
      }
    }
    putchar('\n');
  }
}
