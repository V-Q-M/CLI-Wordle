#include "../include/terminal_input.hpp"
#include "../include/utils.hpp"
#include "../include/visuals.hpp"
#include "../include/word_machine.hpp"
#include <cctype>
#include <iostream>
#include <string>
#include <unistd.h> // For usleep
// WORDLE

int MAX_LENGTH = 5;
int MAX_WORDS = 6;

const int acceptableWordsLen = 5;
const int possibleAnswersLen = 2;

int word_position = 0;
bool won = false;
std::string solution;

std::string enteredWords[6][5];

std::string attempt;
int attemptCount = 0;

void try_guess() {
  //
  for (int i = 0; i < 5; i++) {
    attempt += std::tolower(enteredWords[attemptCount][i][0]);
  }

  if (acceptableWords.count(attempt) == 0) {
    std::cout << "Invalid word. Try again.\n";
    attempt = "";
    sleep(1);
    return;
  }

  if (attempt == solution) {
    won = true;
  }
  // Track matched positions
  bool matchedSolution[5] = {false};
  bool matchedAttempt[5] = {false};

  // First pass: Green letters
  for (int i = 0; i < 5; i++) {
    if (attempt[i] == solution[i]) {
      enteredWords[attemptCount][i] =
          paint_green(enteredWords[attemptCount][i]);
      matchedSolution[i] = true;
      matchedAttempt[i] = true;
    }
  }

  // Second pass: Yellow letters
  for (int i = 0; i < 5; i++) {
    if (matchedAttempt[i])
      continue; // already green

    bool found_yellow = false;
    for (int j = 0; j < 5; j++) {
      if (!matchedSolution[j] && attempt[i] == solution[j]) {
        enteredWords[attemptCount][i] =
            paint_yellow(enteredWords[attemptCount][i]);
        matchedSolution[j] = true;
        found_yellow = true;
        break;
      }
    }
    if (!found_yellow) {
      enteredWords[attemptCount][i] = paint_grey(enteredWords[attemptCount][i]);
    }
  }
  attempt = "";
  word_position = 0;
  attemptCount++;
}

void handle_input() {
  // Display player input
  if (current_key >= 'a' && current_key <= 'z' && word_position < 5) {
    enteredWords[attemptCount][word_position] = current_key - 32;
    word_position++;
    current_key = 0; // reset key to not trigger spam
    if (word_position != 5) {
      enteredWords[attemptCount][word_position] = '_';
    }
  }

  if (backspace_pressed) {
    backspace_pressed = false; // reset immediately
    if (word_position > 0) {
      enteredWords[attemptCount][word_position] = "";
      word_position--;
      enteredWords[attemptCount][word_position] = '_';
      ; // clear last char
    }
  }

  if (enter_pressed) {
    enter_pressed = false;
    if (word_position == 5) {
      try_guess();
    } else {
      std::cout << "Attempt to short." << std::endl;
      sleep(2);
    }
  }
}

void setup_game() {
  solution = random_word();
  // intialize the board with one space
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 5; j++) {
      enteredWords[i][j] = " ";
    }
  }
}

int check_game_over() {
  if (won) {
    clear_screen();
    print_board(enteredWords);
    std::cout << "You won!\n";
    return 0;
  } else if (attemptCount == 6) {
    clear_screen();
    print_board(enteredWords);
    std::cout << "You lost! The answer was: " << solution << "\n";
    return 0;
  }
  return 69;
}

int update_game() {
  clear_screen();
  print_board(enteredWords);
  handle_input();
  clear_screen();
  print_board(enteredWords);

  return check_game_over();
}
