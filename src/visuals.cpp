#include "../include/visuals.hpp"
#include <iostream>
const std::string vertical = "│";
const std::string horizontal = "─";

const std::string corner_tl = "┌";
const std::string corner_tr = "┐";
const std::string corner_bl = "└";
const std::string corner_br = "┘";
/*
const std::string corner_tl = "╭"; // top-left
const std::string corner_tr = "╮"; // top-right
const std::string corner_bl = "╰"; // bottom-left
const std::string corner_br = "╯"; // bottom-right
                                */
const std::string cross_top = "┬";
const std::string cross_mid = "┼";
const std::string cross_bot = "┴";
const std::string vertical_sep = "│";
const std::string horizontal_sep = "├";
const std::string horizontal_end = "┤";

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

void print_keyboard() {
  std::cout << "  " << corner_tl + "─────────────────────" + corner_tr;
  //  std::cout << corner_tl << horizontal << corner_tr << "\n";
  std::cout << '\n' << "  " << vertical + " ";
  for (int i = 0; i < 26; i++) {
    if (i == 10) {
      std::cout << "" << vertical << "\n  " + vertical + "  ";
      //     std::cout << corner_bl << horizontal << corner_br << "\n";
    } else if (i == 19) {
      std::cout << " " + vertical << "\n  " + vertical + "    ";
    }
    // std::cout << vertical << " " << keys[i] << " " << vertical << ' ';
    std::cout << keys[i] << ' ';
  }
  std::cout << "   " + vertical << '\n';
  std::cout << "  " << corner_bl + "─────────────────────" + corner_br << '\n';
}

void print_board(std::string entered_words[6][5]) {
  // top border
  std::cout << " ";
  for (int i = 0; i < 5; i++)
    std::cout << corner_tl << "───" << corner_tr;
  std::cout << "\n ";

  // rows
  for (int i = 0; i < 6; i++) {
    // std::cout << vertical;
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
  print_keyboard();
}
