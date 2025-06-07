#include "../include/game.hpp"
#include "../include/terminal_input.hpp"
#include "../include/utils.hpp"
#include "../include/visuals.hpp"
#include "../include/word_machine.hpp"
#include <cctype>
#include <iostream>
#include <string>
#include <unistd.h> // For usleep
#include <vector>
// WORDLE

int WORD_LENGTH = 5;
int AMOUNT_OF_WORDS = 6;

char cursor_char = '_';

int word_position = 0;
bool won = false;
bool lost = false;

std::string solution;
// Stores the letters which get visualized
// std::string enteredWords[6][5];

std::vector<std::vector<std::string>> enteredWords;

// Array needed for colorization
// int letter_color[6][5];
std::vector<std::vector<int>> letter_color;

std::string attempt = "";

// Dictates the current row
int attempt_counter = 0;

constexpr int GREEN_ID = 1;
constexpr int YELLOW_ID = 2;
constexpr int GREY_ID = 3;

bool invalid_word_msg = false;
bool invalid_length_msg = false;

void try_guess() {
  //
  for (int i = 0; i < WORD_LENGTH; i++) {
    if (!enteredWords[attempt_counter][i].empty()) {
      attempt += std::tolower(enteredWords[attempt_counter][i][0]);
    } else {
      attempt += cursor_char; // or some sentinel char
    }
  }
  if (WORD_LENGTH == 5) {

    if (acceptableWords5.count(attempt) == 0) {
      invalid_word_msg = true;
      attempt = "";
      return;
    }

  } else if (WORD_LENGTH == 6) {

    if (acceptableWords6.count(attempt) == 0) {
      invalid_word_msg = true;
      attempt = "";
      return;
    }
  } else if (WORD_LENGTH == 7) {

    if (acceptableWords7.count(attempt) == 0) {
      invalid_word_msg = true;
      attempt = "";
      return;
    }
  }
  if (attempt == solution) {
    won = true;
  }
  // Track matched positions
  std::vector<bool> matchedSolution = {false};
  std::vector<bool> matchedAttempt = {false};
  matchedSolution.resize(WORD_LENGTH);
  matchedAttempt.resize(WORD_LENGTH);

  // First pass: Green letters
  for (int i = 0; i < WORD_LENGTH; i++) {
    if (attempt[i] == solution[i]) {
      letter_color[attempt_counter][i] = GREEN_ID;
      matchedSolution[i] = true;
      matchedAttempt[i] = true;
    }
  }

  // Second pass: Yellow letters
  for (int i = 0; i < WORD_LENGTH; i++) {
    if (matchedAttempt[i])
      continue; // already green

    bool found_yellow = false;
    for (int j = 0; j < WORD_LENGTH; j++) {
      if (!matchedSolution[j] && attempt[i] == solution[j]) {
        letter_color[attempt_counter][i] = YELLOW_ID;
        matchedSolution[j] = true;
        found_yellow = true;
        break;
      }
    }
    if (!found_yellow) {
      letter_color[attempt_counter][i] = GREY_ID;
    }
  }
  attempt = "";
  word_position = 0;
  if (attempt_counter + 1 == AMOUNT_OF_WORDS) {
    lost = true;
    return;
  }
  attempt_counter++;
  enteredWords[attempt_counter][word_position] = "_";
}

void handle_input() {
  // Display player input
  if (current_key >= 'a' && current_key <= 'z' && word_position < WORD_LENGTH) {
    enteredWords[attempt_counter][word_position] =
        std::string(1, current_key - 32);
    current_key = 0; // reset key to not trigger spam
    word_position++;
    if (word_position < WORD_LENGTH) {
      enteredWords[attempt_counter][word_position] = '_';
    }
  }

  if (backspace_pressed) {
    backspace_pressed = false; // reset immediately
    if (word_position > 0) {
      if (word_position < WORD_LENGTH) {
        enteredWords[attempt_counter][word_position] = "";
      }
      word_position--;
      enteredWords[attempt_counter][word_position] = '_';
    }
  }

  if (enter_pressed) {
    enter_pressed = false;
    if (word_position == WORD_LENGTH) {
      try_guess();
    } else {
      invalid_length_msg = true;
    }
  }
}

std::string get_solution() { return solution; }

void setup_game() {
  solution = random_word();

  enteredWords.resize(AMOUNT_OF_WORDS);

  for (std::vector<std::string> &row : enteredWords) {
    row.resize(WORD_LENGTH);
  }

  letter_color.resize(AMOUNT_OF_WORDS);
  for (std::vector<int> &row : letter_color) {
    row.resize(WORD_LENGTH);
  }

  // intialize the board with one space
  for (int i = 0; i < AMOUNT_OF_WORDS; i++) {
    for (int j = 0; j < WORD_LENGTH; j++) {
      enteredWords[i][j] = " ";
    }
  }
}

int won_code = 1;
int lost_code = 2;

int check_game_over() {
  if (won) {
    clear_screen();
    print_board(enteredWords, won_code);
    std::cout << "You won!\n";
    return 0;
  } else if (lost) {
    clear_screen();
    print_board(enteredWords, lost_code);
    std::cout << "You lost! The answer was: " << solution << "\n";
    return 0;
  }
  return 69;
}

int update_game() {
  clear_screen();
  print_board(enteredWords, 0);
  handle_input();
  clear_screen();
  print_board(enteredWords, 0);

  return check_game_over();
}
