#include "../include/visuals.hpp"
#include "../include/game.hpp"
#include <iostream>

#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

const std::string vertical = "│";
const std::string horizontal = "─";

/*
const std::string corner_tl = "┌";
const std::string corner_tr = "┐";
const std::string corner_bl = "└";
const std::string corner_br = "┘";
                                */
const std::string corner_tl = "╭"; // top-left
const std::string corner_tr = "╮"; // top-right
const std::string corner_bl = "╰"; // bottom-left
const std::string corner_br = "╯"; // bottom-right
const std::string cross_top = "┬";
const std::string cross_mid = "┼";
const std::string cross_bot = "┴";
const std::string vertical_sep = "│";
const std::string horizontal_sep = "├";
const std::string horizontal_end = "┤";

std::string top_margin = "\n";
std::string left_margin = "  ";

std::vector<std::string> keys = {"Q", "W", "E", "R", "T", "Y", "U", "I", "O",
                                 "P", "A", "S", "D", "F", "G", "H", "J", "K",
                                 "L", "Z", "X", "C", "V", "B", "N", "M"};
std::string clean_keys = "QWERTYUIOPASDFGHJKLZXCVBNM";

std::string paint_yellow(std::string letter) {
  for (int i = 0; i < 26; i++) {
    if (keys[i] == letter) {
      keys[i] = "\033[33m" + keys[i] + "\033[0m";
    }
  }
  return "\033[33m" + letter + "\033[0m"; // Yellow
}

std::string paint_green(std::string letter) {
  for (int i = 0; i < 26; i++) {
    if (keys[i] == letter || keys[i] == paint_yellow(letter)) {
      keys[i] = "\033[32m" + std::string(1, clean_keys[i]) + "\033[0m";
    }
  }

  return "\033[32m" + letter + "\033[0m"; // Green
}

std::string paint_grey(std::string letter) {
  for (int i = 0; i < 26; i++) {
    if (keys[i] == letter) {
      keys[i] = "\033[90m" + keys[i] + "\033[0m";
    }
  }

  return "\033[90m" + letter + "\033[0m"; // Gray
}

void resize_window() {
  struct winsize w;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
    std::cerr << "Failed to get terminal size.\n";
  }

  //  std::cout << "Terminal width: " << w.ws_col << " columns\n";
  //  std::cout << "Terminal height: " << w.ws_row << " rows\n";

  top_margin = "";
  for (int i = 0; i < w.ws_row / 4; i++) {
    top_margin += '\n';
  }

  left_margin = "";
  for (int i = 0; i < w.ws_col / 2 - 12; i++) {
    left_margin += ' ';
  }
}

void print_keyboard() {
  std::cout << left_margin + ' '
            << corner_tl + "─────────────────────" + corner_tr;
  std::cout << '\n' << left_margin + ' ' << vertical + " ";
  for (int i = 0; i < 26; i++) {
    if (i == 10) {
      std::cout << vertical << "\n";
      std::cout << left_margin + ' ' << vertical + "  ";

    } else if (i == 19) {
      std::cout << " " + vertical << "\n";
      std::cout << left_margin + ' ' << vertical + "    ";
    }
    std::cout << keys[i] << ' ';
  }
  std::cout << "   " + vertical << '\n';
  std::cout << left_margin + ' '
            << corner_bl + "─────────────────────" + corner_br << '\n';
}

void print_board(std::string entered_words[6][5], int game_state_code) {
  resize_window();
  // top margin
  std::cout << top_margin;

  if (game_state_code == 1) {
    std::cout << left_margin << "   You won!" << '\n';
  } else if (game_state_code == 2) {
    std::cout << left_margin << "  The word was: " << get_solution() << '\n';
  }

  /*
  // top border
  std::cout << left_margin;
  for (int i = 0; i < 5; i++)
    std::cout << corner_tl << "───" << corner_tr;
  std::cout << "\n ";

  // rows
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 5; j++) {
      std::string cell = entered_words[i][j];
      std::cout << vertical << " " << (cell.empty() ? " " : cell) << " "
                << vertical;
    }
    std::cout << "\n ";

    if (i < 5) {
      for (int j = 0; j < 5; j++)
        std::cout << corner_bl << "───" << corner_br;
      std::cout << "\n ";
      for (int j = 0; j < 5; j++)
        std::cout << corner_tl << "───" << corner_tr;
      std::cout << "\n ";
    }
  }

  // bottom border
  for (int i = 0; i < 5; i++)
    std::cout << corner_bl << "───" << corner_br;
  std::cout << "\n";
*/
  for (int i = 0; i < 6; i++) {
    std::cout << left_margin;
    for (int w = 0; w < 5; w++)
      // top part
      std::cout << corner_tl << "───" << corner_tr;
    std::cout << '\n';
    std::cout << left_margin;
    // middle part
    for (int j = 0; j < 5; j++) {
      std::string cell = entered_words[i][j];
      std::cout << vertical << " " << (cell.empty() ? " " : cell) << " "
                << vertical;
    }
    std::cout << '\n';
    std::cout << left_margin;

    // bottom part
    for (int k = 0; k < 5; k++)
      std::cout << corner_bl << "───" << corner_br;
    std::cout << '\n';
  }

  print_keyboard();
}
