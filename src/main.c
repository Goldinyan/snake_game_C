#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "setup.h"
#include "game_state.h"
#include "update.h"

int main(void) {
  game_state_t state;

  clear_grid(&state);
  setup_game(&state);


  
  while (!state.lost) {
        draw(&state);
        update(&state);
        usleep(100000); // 100 ms
  }

  return 0;
}

