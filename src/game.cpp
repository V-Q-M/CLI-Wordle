#include "../include/terminal_input.h"
#include "../include/utils.h"
#include "../include/visuals.h"
#include "../include/word_machine.h"
#include <cctype>
#include <iostream>
#include <string>
#include <unistd.h> // For usleep
// WORDLE

const int acceptableWordsLen = 5;
const int possibleAnswersLen = 2;

int word_position = 0;

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
    sleep(2);
    return;
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

    for (int j = 0; j < 5; j++) {
      if (!matchedSolution[j] && attempt[i] == solution[j]) {
        enteredWords[attemptCount][i] =
            paint_yellow(enteredWords[attemptCount][i]);
        matchedSolution[j] = true;
        break;
      }
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
  }

  if (backspace_pressed) {
    backspace_pressed = false; // reset immediately

    if (word_position > 0) {
      word_position--;
      enteredWords[attemptCount][word_position] = ""; // clear last char
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
  if (attempt == solution) {
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
