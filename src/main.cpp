#include "TermuxApi.h"
#include "Display.h"
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <ncurses.h>

int main(int argc, char* argv[]) {
    bool refresh_mode = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--json") {
            TermuxApi api;
            std::string info = api.getTelephonyInfo();
            std::cout << info;
            return 0;
        } else if (arg == "-r") {
            refresh_mode = true;
        }
    }

    TermuxApi api;
    Display display;

    if (refresh_mode) {
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
    } else {
        std::string info = api.getTelephonyInfo();
        display.update(info);
        // Wait for a key press before exiting in one-shot mode
        getch();
    }

    return 0;
}
