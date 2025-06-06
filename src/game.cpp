#include "../include/game.hpp"
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

char cursor_char = '_';

int word_position = 0;
bool won = false;
bool lost = false;
std::string solution;

std::string enteredWords[6][5];

int letter_color[6][5];

std::string attempt = "";
int attemptCount = 0;

void try_guess() {
  //
  for (int i = 0; i < 5; i++) {
    if (!enteredWords[attemptCount][i].empty()) {
      attempt += std::tolower(enteredWords[attemptCount][i][0]);
    } else {
      attempt += cursor_char; // or some sentinel char
    }
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
      //      enteredWords[attemptCount][i] =
      // paint_green(enteredWords[attemptCount][i]);
      letter_color[attemptCount][i] = 1;
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
        //        enteredWords[attemptCount][i] =
        // paint_yellow(enteredWords[attemptCount][i]);
        letter_color[attemptCount][i] = 2;
        matchedSolution[j] = true;
        found_yellow = true;
        break;
      }
    }
    if (!found_yellow) {
      // enteredWords[attemptCount][i] =
      // paint_grey(enteredWords[attemptCount][i]);
      letter_color[attemptCount][i] = 3;
    }
  }
  attempt = "";
  word_position = 0;
  if (attemptCount + 1 == MAX_WORDS) {
    lost = true;
    return;
  }
  attemptCount++;
  enteredWords[attemptCount][word_position] = "_";
}

void handle_input() {
  // Display player input
  if (current_key >= 'a' && current_key <= 'z' && word_position < MAX_LENGTH) {
    enteredWords[attemptCount][word_position] =
        std::string(1, current_key - 32);
    current_key = 0; // reset key to not trigger spam
    word_position++;
    if (word_position < MAX_LENGTH) {
      enteredWords[attemptCount][word_position] = '_';
    }
  }

  if (backspace_pressed) {
    backspace_pressed = false; // reset immediately
    if (word_position > 0) {
      if (word_position < MAX_LENGTH) {
        enteredWords[attemptCount][word_position] = "";
      }
      word_position--;
      enteredWords[attemptCount][word_position] = '_';
    }
  }

  if (enter_pressed) {
    enter_pressed = false;
    if (word_position == MAX_LENGTH) {
      try_guess();
    } else {
      std::cout << "Attempt to short." << std::endl;
      sleep(2);
    }
  }
}

std::string get_solution() { return solution; }

void setup_game() {
  solution = random_word();
  // intialize the board with one space
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 5; j++) {
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
