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
    int refresh_interval_ms = 1000; // Default to 1 second

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
        } else if (arg == "-i") {
            if (i + 1 < argc) { // Make sure there is a next argument
                try {
                    refresh_interval_ms = std::stoi(argv[++i]);
                    if (refresh_interval_ms < 100) { // Minimum interval to prevent excessive polling
                        refresh_interval_ms = 100;
                    }
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error: Invalid argument for -i. Must be an integer." << std::endl;
                    return 1;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Error: Refresh interval out of range." << std::endl;
                    return 1;
                }
            } else {
                std::cerr << "Error: -i requires an argument (refresh interval in ms)." << std::endl;
                return 1;
            }
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
            timeout(refresh_interval_ms);
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
