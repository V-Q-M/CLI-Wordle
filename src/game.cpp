#include "../include/utils.h"
#include "../include/visuals.h"
#include "../include/word_machine.h"
#include <iostream>
#include <string>
// WORDLE

const int acceptableWordsLen = 5;
const int possibleAnswersLen = 2;

std::string solution;

std::string enteredWords[6][5];

std::string attempt;
int attemptCount = 0;

void printBoard() {
  // top border
  std::cout << ' ' + corner_tl;
  for (int i = 0; i < 4; i++)
    std::cout << "───" << cross_top;
  std::cout << "───" << corner_tr << "\n ";

  // rows
  for (int i = 0; i < 6; i++) {
    std::cout << vertical;
    for (int j = 0; j < 5; j++) {
      std::string cell = enteredWords[i][j];
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

void processInput() {
  std::cout << "Enter guess: ";
  std::cin >> attempt;

  if (acceptableWords.count(attempt) == 0) {
    std::cout << "Invalid word. Try again.\n";
    attemptCount--;
    return;
  }

  // Copy attempt to board
  for (int i = 0; i < 5; i++) {
    enteredWords[attemptCount][i] = attempt[i];
  }

  // Track matched positions
  bool matchedSolution[5] = {false};
  bool matchedAttempt[5] = {false};

  // First pass: Green letters
  for (int i = 0; i < 5; i++) {
    if (attempt[i] == solution[i]) {
      enteredWords[attemptCount][i] = paint_green(attempt[i]);
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
        enteredWords[attemptCount][i] = paint_yellow(attempt[i]);
        matchedSolution[j] = true;
        break;
      }
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
int update_game() {
  // game loop
  clear_screen();
  printBoard();
  processInput();
  printBoard();
  if (attempt == solution) {
    clear_screen();
    printBoard();
    std::cout << "You won!\n";
    return 0;
  } else if (attemptCount == 6) {
    clear_screen();
    printBoard();
    std::cout << "You lost! The correct word was: " << solution << "\n";
    return 0;
  }
  attemptCount++;
  return 69;
}
