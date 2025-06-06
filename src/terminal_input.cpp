#include "../include/terminal_input.h"
#include <iostream>
#include <termios.h>
#include <unistd.h>

char current_key = 0;
bool enter_pressed = false;
bool backspace_pressed = false;

void setRawMode(bool enable) {
  static struct termios oldt, newt;
  if (enable) {
    tcgetattr(STDIN_FILENO, &oldt); // save old settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // disable buffering and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  } else {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore old settings
  }
}

void setup_input() {

  setRawMode(true);
  std::cout << "Press a key to start\n";

  // char c;
}

int update_input() {
  //
  current_key = getchar();
  if (current_key == '/') { // signal exit
    return 0;
  }

  // Detect Enter key (usually '\n' = 10)
  if (current_key == 10 || current_key == 13) {
    enter_pressed = true;
  }

  // Detect Backspace key (usually 127 or sometimes 8)
  if (current_key == 127 || current_key == 8) {
    backspace_pressed = true;
  }

  std::cout << current_key << " pressed\n";

  return 69; // base value
}

void close_input() { //
  setRawMode(false);
}
