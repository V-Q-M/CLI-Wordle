#include "../include/utils.hpp"
#include <cstdlib> // for system()
#include <iostream>
#include <regex> //
//
//
// Define the constants
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";
const std::string GREY = "\033[90m";
const std::string RESET = "\033[0m";

// Mutable color state
std::string color = WHITE;
void clear_screen() {

#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

std::string paint(const std::string &input, const std::string &color) {
  return color + input + RESET;
}

void remove_colors(std::string input_array[], int size) {
  std::regex ansi_regex(R"(\x1B\[[0-9;]*m)");

  for (int i = 0; i < size; i++) {
    input_array[i] = std::regex_replace(input_array[i], ansi_regex, "");
  }
}

std::string array_to_representation(const std::string input[], int size) {
  std::string result;

  // TOP SIDE
  result.append("┌───");
  for (int i = 0; i < size - 1; i++) {
    result.append("┬───");
  }
  result.append("┐");
  result.append("\n");

  // MAIN ARRAY
  result.append("│ ");
  for (int i = 0; i < size; i++) {
    result.append(input[i]);
    result.append(" │ ");
  }
  result.append("\n");

  // BOTTOM SIDE
  result.append("└───");

  for (int i = 0; i < size - 1; i++) {
    result.append("┴───");
  }
  result.append("┘");

  return result;
}

//
// RESIZE WINDOW
//
//
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

std::string top_margin;
std::string left_margin;

void resize_window() {
  int rows = 24; // default fallback
  int cols = 80;

#ifdef _WIN32
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
    cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
  } else {
    std::cerr << "Failed to get terminal size on Windows.\n";
  }
#else
  struct winsize w;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
    std::cerr << "Failed to get terminal size on Unix.\n";
  } else {
    rows = w.ws_row;
    cols = w.ws_col;
  }
#endif

  top_margin = "";
  for (int i = 0; i < rows / 4; i++) {
    top_margin += '\n';
  }

  left_margin = "";
  for (int i = 0; i < cols / 2 - 12; i++) {
    left_margin += ' ';
  }
}
