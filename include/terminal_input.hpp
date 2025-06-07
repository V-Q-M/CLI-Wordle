#ifndef INPUT_H
#define INPUT_H

void setup_input();
int update_input();
void close_input();

extern char current_key;
extern bool enter_pressed;
extern bool backspace_pressed;
extern bool tab_pressed;

#endif
