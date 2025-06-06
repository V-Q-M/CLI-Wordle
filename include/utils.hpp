#ifndef UTILS_H
#define UTILS_H

#include <string>

// Constant ANSI color codes
extern const std::string WHITE;
extern const std::string GREY;
extern const std::string RED;
extern const std::string BLUE;
extern const std::string GREEN;
extern const std::string YELLOW;
extern const std::string RESET;

// Mutable color selection
extern std::string color;

std::string paint(const std::string &input, const std::string &color);
void remove_colors(std::string input_array[], int size);

void clear_screen();

std::string array_to_representation(const std::string input[], int size);

void resize_window();
extern std::string top_margin;
extern std::string left_margin;

#endif
