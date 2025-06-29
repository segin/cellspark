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
    if (has_colors()) {
        init_pair(1, COLOR_CYAN, COLOR_BLACK); // Title
        init_pair(2, COLOR_WHITE, COLOR_BLACK); // Labels
        init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Values
        init_pair(4, COLOR_RED, COLOR_BLACK); // Error
    }
}

Display::~Display() {
    endwin();
}

void Display::update(const std::string& data) {
    clear();

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    // Calculate box dimensions and position
    int box_width = 40;
    int box_height = 10;
    int box_start_y = (rows - box_height) / 2;
    int box_start_x = (cols - box_width) / 2;

    // Draw box
    attron(COLOR_PAIR(1));
    mvaddch(box_start_y, box_start_x, ACS_ULCORNER);
    mvaddch(box_start_y, box_start_x + box_width, ACS_URCORNER);
    mvaddch(box_start_y + box_height, box_start_x, ACS_LLCORNER);
    mvaddch(box_start_y + box_height, box_start_x + box_width, ACS_LRCORNER);
    mvhline(box_start_y, box_start_x + 1, ACS_HLINE, box_width - 1);
    mvhline(box_start_y + box_height, box_start_x + 1, ACS_HLINE, box_width - 1);
    mvvline(box_start_y + 1, box_start_x, ACS_VLINE, box_height - 1);
    mvvline(box_start_y + 1, box_start_x + box_width, ACS_VLINE, box_height - 1);
    attroff(COLOR_PAIR(1));

    // Title
    attron(COLOR_PAIR(1));
    mvprintw(box_start_y + 1, box_start_x + (box_width - 20) / 2, "Cellular Information");
    attroff(COLOR_PAIR(1));

    try {
        json info = json::parse(data);
        attron(COLOR_PAIR(2));
        mvprintw(box_start_y + 3, box_start_x + 2, "Operator:");
        mvprintw(box_start_y + 4, box_start_x + 2, "Network Type:");
        mvprintw(box_start_y + 5, box_start_x + 2, "Data State:");
        mvprintw(box_start_y + 6, box_start_x + 2, "Data Activity:");
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(3));
        mvprintw(box_start_y + 3, box_start_x + 18, "%s", info["network_operator_name"].get<std::string>().c_str());
        mvprintw(box_start_y + 4, box_start_x + 18, "%s", info["network_type"].get<std::string>().c_str());
        mvprintw(box_start_y + 5, box_start_x + 18, "%s", info["data_state"].get<std::string>().c_str());
        mvprintw(box_start_y + 6, box_start_x + 18, "%s", info["data_activity"].get<std::string>().c_str());
        attroff(COLOR_PAIR(3));
    } catch (json::parse_error& e) {
        attron(COLOR_PAIR(4));
        mvprintw(box_start_y + 3, box_start_x + 2, "Error parsing JSON: %s", e.what());
        attroff(COLOR_PAIR(4));
    }

    mvprintw(rows - 1, 0, "Press 'q' to quit");

    refresh();
}
