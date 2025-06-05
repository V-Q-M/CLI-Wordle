#ifndef WORD_MACHINE_H
#define WORD_MACHINE_H
#include <string>
#include <unordered_set>
#include <vector>

extern std::unordered_set<std::string> acceptableWords;
extern std::vector<std::string> possibleAnswers;

std::string random_word();

#endif
