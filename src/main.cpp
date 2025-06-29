#include "TermuxApi.h"
#include "Display.h"
#include "Exceptions.h"
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
            try {
                std::string info = api.getTelephonyInfo();
                std::cout << info;
            } catch (const TermuxApiException& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return 1;
            } catch (const JsonParseException& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return 1;
            }
            return 0;
        } else if (arg == "-r") {
            refresh_mode = true;
        }
    }

    TermuxApi api;
    Display display;

    if (refresh_mode) {
        while (true) {
            try {
                std::string info = api.getTelephonyInfo();
                display.update(info);
            } catch (const TermuxApiException& e) {
                display.updateError(e.what());
            } catch (const JsonParseException& e) {
                display.updateError(e.what());
            }

            // Non-blocking getch
            timeout(1000); // 1 second timeout
            int ch = getch();

            if (ch == 'q') {
                break;
            }
        }
    } else {
        try {
            std::string info = api.getTelephonyInfo();
            display.update(info);
        } catch (const TermuxApiException& e) {
            display.updateError(e.what());
        } catch (const JsonParseException& e) {
            display.updateError(e.what());
        }
        // Wait for a key press before exiting in one-shot mode
        getch();
    }

    return 0;
}
