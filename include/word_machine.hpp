#ifndef WORD_MACHINE_H
#define WORD_MACHINE_H
#include <string>
#include <unordered_set>
#include <vector>

extern std::unordered_set<std::string> acceptableWords5;
extern std::vector<std::string> possibleAnswers5;
extern std::unordered_set<std::string> acceptableWords6;
extern std::vector<std::string> possibleAnswers6;
extern std::unordered_set<std::string> acceptableWords7;
extern std::vector<std::string> possibleAnswers7;

std::string random_word();

extern std::string word_size_offset;
#endif
