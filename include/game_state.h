#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdbool.h>

#define W 80
#define H 20
#define MAX_BODY 200
#define MAX_DIR 200

typedef enum { DIR_TOP, DIR_BOTTOM, DIR_LEFT, DIR_RIGHT } direction_t;

typedef struct Vector {
  int x;
  int y;
 } vector_t;

typedef struct {
  vector_t pos; 
  direction_t dir;
} entity_t;

typedef struct GameState {

  entity_t body[MAX_BODY];
  vector_t food;
  entity_t dir[MAX_DIR];
  direction_t head_direction;
  int body_length;
  int dir_count;
  int health;
  int time;
  char grid[H][W];
  bool lost;

} game_state_t;

#endif
