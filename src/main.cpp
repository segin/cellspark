#include "TermuxApi.h"
#include "Display.h"
#include "Exceptions.h"
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <ncurses.h>
#include <map>
#include <algorithm>

// Helper function to convert color name string to ncurses color constant
int color_name_to_ncurses_color(const std::string& color_name) {
    std::string lower_color_name = color_name;
    std::transform(lower_color_name.begin(), lower_color_name.end(), lower_color_name.begin(), ::tolower);

    if (lower_color_name == "black") return COLOR_BLACK;
    if (lower_color_name == "red") return COLOR_RED;
    if (lower_color_name == "green") return COLOR_GREEN;
    if (lower_color_name == "yellow") return COLOR_YELLOW;
    if (lower_color_name == "blue") return COLOR_BLUE;
    if (lower_color_name == "magenta") return COLOR_MAGENTA;
    if (lower_color_name == "cyan") return COLOR_CYAN;
    if (lower_color_name == "white") return COLOR_WHITE;
    return -1; // Invalid color
}

int main(int argc, char* argv[]) {
    bool refresh_mode = false;
    int refresh_interval_ms = 1000; // Default to 1 second

    // Default colors
    int titleColor = COLOR_CYAN;
    int labelColor = COLOR_WHITE;
    int valueColor = COLOR_YELLOW;
    int errorColor = COLOR_RED;

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
        } else if (arg == "--title-color") {
            if (i + 1 < argc) {
                int color = color_name_to_ncurses_color(argv[++i]);
                if (color != -1) {
                    titleColor = color;
                } else {
                    std::cerr << "Error: Invalid color name for --title-color." << std::endl;
                    return 1;
                }
            } else {
                std::cerr << "Error: --title-color requires an argument (color name)." << std::endl;
                return 1;
            }
        } else if (arg == "--label-color") {
            if (i + 1 < argc) {
                int color = color_name_to_ncurses_color(argv[++i]);
                if (color != -1) {
                    labelColor = color;
                } else {
                    std::cerr << "Error: Invalid color name for --label-color." << std::endl;
                    return 1;
                }
            } else {
                std::cerr << "Error: --label-color requires an argument (color name)." << std::endl;
                return 1;
            }
        } else if (arg == "--value-color") {
            if (i + 1 < argc) {
                int color = color_name_to_ncurses_color(argv[++i]);
                if (color != -1) {
                    valueColor = color;
                } else {
                    std::cerr << "Error: Invalid color name for --value-color." << std::endl;
                    return 1;
                }
            } else {
                std::cerr << "Error: --value-color requires an argument (color name)." << std::endl;
                return 1;
            }
        } else if (arg == "--error-color") {
            if (i + 1 < argc) {
                int color = color_name_to_ncurses_color(argv[++i]);
                if (color != -1) {
                    errorColor = color;
                } else {
                    std::cerr << "Error: Invalid color name for --error-color." << std::endl;
                    return 1;
                }
            } else {
                std::cerr << "Error: --error-color requires an argument (color name)." << std::endl;
                return 1;
            }
        }
    }

    TermuxApi api;
    Display display(titleColor, labelColor, valueColor, errorColor);

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

