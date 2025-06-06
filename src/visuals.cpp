#include "../include/visuals.hpp"
#include <iostream>
const std::string vertical = "│";
const std::string horizontal = "─";
const std::string corner_tl = "┌";
const std::string corner_tr = "┐";
const std::string corner_bl = "└";
const std::string corner_br = "┘";
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
      keys[i] = "\033[72m" + keys[i] + "\033[0m";
    }
  }

  return "\033[72m" + letter + "\033[0m"; // Gray
}

void print_keyboard() {
  std::cout << corner_tl + "─────────────────────" + corner_tr;
  std::cout << '\n' << vertical + " ";
  for (int i = 0; i < 26; i++) {
    if (i == 10) {
      std::cout << vertical << '\n' + vertical + "  ";
    } else if (i == 19) {
      std::cout << " " + vertical << '\n' + vertical + "    ";
    }
    std::cout << keys[i] << ' ';
  }
  std::cout << "   " + vertical << '\n';
  std::cout << corner_bl + "─────────────────────" + corner_br << '\n';
}

void print_board(std::string entered_words[6][5]) {
  // top border
  std::cout << ' ' + corner_tl;
  for (int i = 0; i < 4; i++)
    std::cout << "───" << cross_top;
  std::cout << "───" << corner_tr << "\n ";

  // rows
  for (int i = 0; i < 6; i++) {
    std::cout << vertical;
    for (int j = 0; j < 5; j++) {
      std::string cell = entered_words[i][j];
      std::cout << " " << (cell.empty() ? " " : cell) << " " << vertical;
    }
    std::cout << "\n ";

    if (i < 5) {
      std::cout << horizontal_sep;
      for (int j = 0; j < 4; j++)
        std::cout << "───" << cross_mid;
      std::cout << "───" << horizontal_end << "\n ";
    }
  }

  // bottom border
  std::cout << corner_bl;
  for (int i = 0; i < 4; i++)
    std::cout << "───" << cross_bot;
  std::cout << "───" << corner_br << "\n";

  print_keyboard();
}
