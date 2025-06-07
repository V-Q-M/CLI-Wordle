#include "../include/terminal_input.hpp"
#include <iostream>

#ifdef _WIN32
#include <windows.h>

char current_key = 0;
bool enter_pressed = false;
bool backspace_pressed = false;
bool tab_pressed = false;

static HANDLE hStdin = NULL;
static DWORD oldMode = 0;

void setRawMode(bool enable) {
  if (enable) {
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hStdin, &oldMode);
    // Disable line input and echo input
    SetConsoleMode(hStdin, oldMode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));
  } else {
    SetConsoleMode(hStdin, oldMode); // restore mode
  }
}

void setup_input() { setRawMode(true); }

int update_input() {
  INPUT_RECORD record;
  DWORD count;
  while (true) {
    ReadConsoleInput(hStdin, &record, 1, &count);
    if (record.EventType == KEY_EVENT && record.Event.KeyEvent.bKeyDown) {
      WORD vk = record.Event.KeyEvent.wVirtualKeyCode;
      char ch = record.Event.KeyEvent.uChar.AsciiChar;

      if (vk == VK_RETURN) {
        enter_pressed = true;
        current_key = '\n';
      } else if (vk == VK_TAB) {
        tab_pressed = true;
      } else if (vk == VK_BACK) {
        backspace_pressed = true;
        current_key = 8;
      } else if (ch >= 32 && ch <= 126) { // printable ASCII
        current_key = ch;
      } else {
        current_key = 0;
      }

     if (vk == VK_ESCAPE) { // exit signal
        return 0;
      }

      return 69;
    }
  }
}

void close_input() { setRawMode(false); }

#else // POSIX (Linux, macOS, BSD)

#include <termios.h>
#include <unistd.h>

char current_key = 0;
bool enter_pressed = false;
bool backspace_pressed = false;
bool tab_pressed = false;

static struct termios oldt;

void setRawMode(bool enable) {
  static struct termios newt;
  if (enable) {
    tcgetattr(STDIN_FILENO, &oldt); // save old settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // disable buffering and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  } else {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore old settings
  }
}

void setup_input() { setRawMode(true); }

int update_input() {
  current_key = getchar();
  if (current_key == 27) { // signal exit
    return 0;
  } else if (current_key == 9) {
    tab_pressed = true;
  } else if (current_key == 10 || current_key == 13) {
    enter_pressed = true;
  } else if (current_key == 127 || current_key == 8) {
    backspace_pressed = true;
  }
  return 69;
}

void close_input() { setRawMode(false); }

#endif
