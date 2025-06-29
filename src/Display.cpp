#include "Display.h"
#include <ncurses.h>
#include <json.hpp>

using json = nlohmann::json;

Display::Display() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
}

Display::~Display() {
    endwin();
}

void Display::update(const std::string& data) {
    clear();

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    attron(COLOR_PAIR(1));
    mvprintw(rows / 2 - 5, (cols - 20) / 2, "Cellular Information");
    mvprintw(rows / 2 - 4, (cols - 20) / 2, "====================");
    attroff(COLOR_PAIR(1));

    try {
        json info = json::parse(data);
        mvprintw(rows / 2 - 2, (cols - 30) / 2, "Operator: %s", info["network_operator_name"].get<std::string>().c_str());
        mvprintw(rows / 2 - 1, (cols - 30) / 2, "Network Type: %s", info["network_type"].get<std::string>().c_str());
        mvprintw(rows / 2, (cols - 30) / 2, "Data State: %s", info["data_state"].get<std::string>().c_str());
        mvprintw(rows / 2 + 1, (cols - 30) / 2, "Data Activity: %s", info["data_activity"].get<std::string>().c_str());
    } catch (json::parse_error& e) {
        mvprintw(rows / 2, (cols - 30) / 2, "Error parsing JSON");
    }


    mvprintw(rows - 1, 0, "Press 'q' to quit");

    refresh();
}
