#ifndef VISUALS_H
#define VISUALS_H
#include <string>
#include <vector>

std::string paint_yellow(std::string letter);
std::string paint_green(std::string letter);
std::string paint_grey(std::string letter);

extern const std::string vertical;
extern const std::string horizontal;
extern const std::string corner_tl;
extern const std::string corner_tr;
extern const std::string corner_bl;
extern const std::string corner_br;
extern const std::string cross_top;
extern const std::string cross_mid;
extern const std::string cross_bot;
extern const std::string vertical_sep;
extern const std::string horizontal_sep;
extern const std::string horizontal_end;

void print_keyboard();

void print_board(std::string entered_words[6][5]);
#endif
