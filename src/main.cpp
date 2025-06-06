/*
 * main.cpp
 * ----------
 * Entry point for the terminal-based application.
 *
 * This program sets up terminal input, enters a loop to process user input
 * in real-time (e.g., WASD or arrow keys), and exits gracefully when
 * instructed.
 *
 * Dependencies:
 *  - game.h: handles game state and visuals
 *  - terminal_input.h: handles raw terminal mode and key detection
 *  - utils.h: general-purpose utility functions
 */
#include "../include/main.hpp"
#include "../include/game.hpp"
#include "../include/terminal_input.hpp"
// #include "../include/utils.hpp"
#include <iostream>

int main() {
  setup_input();
  setup_game();

  while (true) {
    if (update_game() == 0) {
      break;
    }
    if (update_input() == 0) {
      break;
    }
  }

  std::cout << "Closing application..." << std::endl;
  close_input();
  return 0;
}
