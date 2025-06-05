#include "../include/terminal_input.h"
#include <iostream>
#include <termios.h>
#include <unistd.h>

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
  std::cout << "Press arrow keys or wasd to move(q to quit):\n";

  // char c;
}

int update_input() {
  //
  char c = getchar();
  if (c == '/') { // signal exit
    return 0;
  }

  std::cout << c << " pressed\n";

  return 69; // base value
}

void close_input() { //
  setRawMode(false);
}
