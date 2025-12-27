#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdbool.h>

#define W 40
#define H 16
#define MAX_BODY 200
#define MAX_DIR 200

typedef enum { DIR_TOP, DIR_BOTTOM, DIR_LEFT, DIR_RIGHT } direction_t;

typedef struct Vector {
  int x;
  int y;
 } vector_t;


typedef struct GameState {

  vector_t body[MAX_BODY];
  vector_t food;
  direction_t head_direction;
  int body_length;
  int health;
  int time;
  int blinking_i;
  char grid[H][W];
  bool lost;

} game_state_t;

#endif
