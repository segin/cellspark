#include "TermuxApi.h"
#include "Display.h"
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <ncurses.h>

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--json") {
        TermuxApi api;
        std::string info = api.getTelephonyInfo();
        std::cout << info;
        return 0;
    }

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
