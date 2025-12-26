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
    system("clear");

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {

            char c = '.'; // default

            // food
            if (x == state->food.x && y == state->food.y) {
                c = '@';
            }

            // head
            if (x == state->body[0].pos.x && y == state->body[0].pos.y) {
                c = 'O';
            }

            // body
            for (int j = 1; j < state->body_length; j++) {
                if (x == state->body[j].pos.x && y == state->body[j].pos.y) {
                    c = 'x';
                    break;
                }
            }

            // print twice for square appearance
            putchar(c);
            putchar(c);
        }
        putchar('\n');
    }
}




void update(game_state_t *state) {
    handle_input(state);

    // Kopf moven lol
    switch (state->body[0].dir) {
        case DIR_TOP:    state->body[0].pos.y--; break;
        case DIR_BOTTOM: state->body[0].pos.y++; break;
        case DIR_LEFT:   state->body[0].pos.x--; break;
        case DIR_RIGHT:  state->body[0].pos.x++; break;
    }

    // Wrap-around
    if (state->body[0].pos.x < 0)     state->body[0].pos.x = W - 1;
    if (state->body[0].pos.x >= W)    state->body[0].pos.x = 0;
    if (state->body[0].pos.y < 0)     state->body[0].pos.y = H - 1;
    if (state->body[0].pos.y >= H)    state->body[0].pos.y = 0;

    // Self-collision
    for (int i = 1; i < state->body_length; i++) {
        if (compare_pos(state->body[0].pos, state->body[i].pos)) {
            state->lost = true;
            return;
        }
    }

    // Food
    if (compare_pos(state->body[0].pos, state->food)) {
        state->body_length++;
        state->body[state->body_length - 1].pos = state->body[state->body_length - 2].pos;
        state->food.x = rand() % W;
        state->food.y = rand() % H;
    }

    // Körper nachziehen
    for (int i = state->body_length - 1; i > 0; i--) {
        state->body[i].pos = state->body[i - 1].pos;
    }
}


static void handle_input(game_state_t *state) {
    if (!kbhit()) return;

    char c = getchar();

    direction_t cur = state->body[0].dir;

    if (c == 'w' && cur != DIR_BOTTOM) {
        state->body[0].dir = DIR_TOP;
    } else if (c == 's' && cur != DIR_TOP) {
        state->body[0].dir = DIR_BOTTOM;
    } else if (c == 'a' && cur != DIR_RIGHT) {
        state->body[0].dir = DIR_LEFT;
    } else if (c == 'd' && cur != DIR_LEFT) {
        state->body[0].dir = DIR_RIGHT;
    }
}
