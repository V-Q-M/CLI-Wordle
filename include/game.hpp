#ifndef GAME_H
#define GAME_H
#include <string>

void setup_game();
int update_game();

std::string get_solution();

extern int letter_color[6][5];
extern bool invalid_word_msg;
extern bool invalid_length_msg;

#endif
