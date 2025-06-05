#include "../include/visuals.h"
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

std::vector<std::string> keys = {"q", "w", "e", "r", "t", "y", "u", "i", "o",
                                 "p", "a", "s", "d", "f", "g", "h", "j", "k",
                                 "l", "z", "x", "c", "v", "b", "n", "m"};
std::string clean_keys = {"qwertyuiopasdfghjklzxcvbnm"};

std::string paint_yellow(char letter) {
  for (int i = 0; i < 26; i++) {
    if (keys[i] == std::string(1, letter)) {
      keys[i] = "\033[33m" + keys[i] + "\033[0m";
    }
  }
  return "\033[33m" + std::string(1, letter) + "\033[0m"; // Yellow
}

std::string paint_green(char letter) {
  for (int i = 0; i < 26; i++) {
    if (keys[i] == std::string(1, letter) || keys[i] == paint_yellow(letter)) {
      keys[i] = "\033[32m" + std::string(1, clean_keys[i]) + "\033[0m";
    }
  }

  return "\033[32m" + std::string(1, letter) + "\033[0m"; // Green
}

void greyify(char letter) {
  for (int i = 0; i < 26; i++) {
    if (keys[i] == std::string(1, letter)) {
      keys[i] = "\033[72m" + keys[i] + "\033[0m";
    }
  }

  // return "\033[72m" + std::string(1, letter) + "\033[0m"; // Green
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
