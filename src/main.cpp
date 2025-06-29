#include "TermuxApi.h"
#include "Display.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <ncurses.h>

int main() {
    TermuxApi api;
    Display display;

    while (true) {
        std::string info = api.getTelephonyInfo();
        display.update(info);

        // Non-blocking getch
        timeout(1000); // 1 second timeout
        int ch = getch();

        if (ch == 'q') {
            break;
        }
    }

    return 0;
}
