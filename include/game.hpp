#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>

void setup_game(int word_mode);
int update_game();

std::string get_solution();

extern int WORD_LENGTH;
extern int AMOUNT_OF_WORDS;

extern std::vector<std::vector<int>> letter_color;
extern bool invalid_word_msg;
extern bool invalid_length_msg;
extern bool show_menu;

#endif
