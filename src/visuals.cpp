#include "../include/visuals.hpp"
#include "../include/game.hpp"
#include "../include/utils.hpp"
#include "../include/word_machine.hpp"
#include <ios>
#include <iostream>

const std::string vertical = "│";
const std::string horizontal = "─";

/*
const std::string corner_tl = "┌";
const std::string corner_tr = "┐";
const std::string corner_bl = "└";
const std::string corner_br = "┘";
                                */
const std::string corner_tl = "╭"; // top-left
const std::string corner_tr = "╮";
const std::string corner_bl = "╰";
const std::string corner_br = "╯";
const std::string cross_top = "┬";
const std::string cross_mid = "┼";
const std::string cross_bot = "┴";
const std::string vertical_sep = "│";
const std::string horizontal_sep = "├";
const std::string horizontal_end = "┤";

int show_invalid_word_msg_for = 0;
int show_invalid_length_msg_for = 0;

std::vector<std::string> keys = {"Q", "W", "E", "R", "T", "Y", "U", "I", "O",
                                 "P", "A", "S", "D", "F", "G", "H", "J", "K",
                                 "L", "Z", "X", "C", "V", "B", "N", "M"};
std::string clean_keys = "QWERTYUIOPASDFGHJKLZXCVBNM";

void paint_keys(std::string letter, std::string color) {
  for (int i = 0; i < 26; i++) {
    if (std::string(1, clean_keys[i]) == letter) {
      keys[i] = paint(std::string(1, clean_keys[i]), color);
    }
  }
}

void print_keyboard() {
  std::cout << word_size_offset << left_margin + ' '
            << corner_tl + "─────────────────────" + corner_tr;
  std::cout << '\n' << word_size_offset << left_margin + ' ' << vertical + " ";
  for (int i = 0; i < 26; i++) {
    if (i == 10) {
      std::cout << vertical << "\n";
      std::cout << word_size_offset << left_margin + ' ' << vertical + "  ";

    } else if (i == 19) {
      std::cout << " " + vertical << "\n";
      std::cout << word_size_offset << left_margin + ' ' << vertical + "    ";
    }
    std::cout << keys[i] << ' ';
  }
  std::cout << "   " + vertical << '\n';
  std::cout << word_size_offset << left_margin + ' '
            << corner_bl + "─────────────────────" + corner_br << '\n';
}

void top_part(int i) {
  for (int j = 0; j < WORD_LENGTH; j++) {
    switch (letter_color[i][j]) {
    case 1:
      std::cout << paint(corner_tl + "───" + corner_tr, GREEN);
      break;
    case 2:
      std::cout << paint(corner_tl + "───" + corner_tr, YELLOW);
      break;
    case 3:
      std::cout << paint(corner_tl + "───" + corner_tr, GREY);
      break;
    default:
      std::cout << corner_tl + "───" + corner_tr;
    }
  }
  std::cout << '\n';
  std::cout << left_margin;
}

void middle_part(std::vector<std::vector<std::string>> entered_words, int i) {

  for (int j = 0; j < WORD_LENGTH; j++) {
    std::string cell = entered_words[i][j];
    switch (letter_color[i][j]) {
    case 1:
      std::cout << paint("│ " + (cell.empty() ? " " : cell) + " │", GREEN);
      paint_keys(cell, GREEN);
      break;
    case 2:
      std::cout << paint("│ " + (cell.empty() ? " " : cell) + " │", YELLOW);
      paint_keys(cell, YELLOW);
      break;
    case 3:
      std::cout << paint("│ " + (cell.empty() ? " " : cell) + " │", GREY);
      paint_keys(cell, GREY);
      break;
    default:
      std::cout << "│ " + (cell.empty() ? " " : cell) + " │";
    }
  }
  std::cout << '\n';
  std::cout << left_margin;
}

void bottom_part(int i) {

  for (int j = 0; j < WORD_LENGTH; j++) {
    switch (letter_color[i][j]) {
    case 1:
      std::cout << paint(corner_bl + "───" + corner_br, GREEN);
      break;
    case 2:
      std::cout << paint(corner_bl + "───" + corner_br, YELLOW);
      break;
    case 3:
      std::cout << paint(corner_bl + "───" + corner_br, GREY);
      break;
    default:
      std::cout << corner_bl + "───" + corner_br;
    }
  }
  std::cout << '\n';
}

void print_menu() {
  std::cout << "\n\n\n\n";
  std::cout << left_margin
            << corner_tl + "────────────────────────────────" + corner_tr
            << '\n';
  std::cout << left_margin
            << vertical + "            OPTIONS             " + vertical << '\n';
  std::cout << left_margin
            << vertical + " Press 1. Start 5 letter Wordle " + vertical << '\n';
  std::cout << left_margin
            << vertical + " Press 2. Start 6 letter Wordle " + vertical << '\n';
  std::cout << left_margin
            << vertical + " Press 3. Start 7 letter Wordle " + vertical << '\n';

  std::cout << left_margin
            << corner_bl + "────────────────────────────────" + corner_br
            << '\n';
}

void print_board(std::vector<std::vector<std::string>> entered_words,
                 int game_state_code) {
  resize_window();
  // top margin
  std::cout << top_margin;

  if (game_state_code == 1) {
    std::cout << left_margin << word_size_offset << "         You won!" << '\n';
  } else if (game_state_code == 2) {
    std::cout << left_margin << word_size_offset
              << "   The word was: " << get_solution() << '\n';
  } else if (invalid_word_msg) {
    std::cout << left_margin << word_size_offset
              << " Invalid word. Try again.\n";
    if (show_invalid_word_msg_for == 1) {
      invalid_word_msg = false;
      show_invalid_word_msg_for = 0;
    } else {
      show_invalid_word_msg_for++;
    }
  } else if (invalid_length_msg) {
    std::cout << left_margin << word_size_offset << "    Attempt to short."
              << '\n';
    if (show_invalid_length_msg_for == 1) {
      invalid_length_msg = false;
      show_invalid_length_msg_for = 0;
    } else {
      show_invalid_length_msg_for++;
    }
  } else if (show_menu) {
    print_menu();
  } else {
    std::cout << '\n'; // To block weird shifts when text is actually shown
  }
  if (!show_menu) {
    for (int i = 0; i < AMOUNT_OF_WORDS; i++) {
      std::cout << left_margin;
      // top part
      top_part(i);
      // middle part
      middle_part(entered_words, i);
      // bottom part
      bottom_part(i);
    }

    print_keyboard();
  }
}
