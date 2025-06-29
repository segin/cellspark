#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

/**
 * @class Display
 * @brief Handles the ncurses display for cellular information.
 */
class Display {
public:
    /**
     * @brief Construct a new Display object.
     *
     * @param titleColor The color for the title text.
     * @param labelColor The color for the label text.
     * @param valueColor The color for the value text.
     * @param errorColor The color for the error text.
     */
    Display(int titleColor, int labelColor, int valueColor, int errorColor);

    /**
     * @brief Destroy the Display object.
     */
    ~Display();

    /**
     * @brief Updates the display with new cellular information.
     *
     * @param data A JSON string containing the cellular information.
     */
    void update(const std::string& data);

    /**
     * @brief Updates the display with an error message.
     *
     * @param errorMessage The error message to display.
     */
    void updateError(const std::string& errorMessage);
};

#endif // DISPLAY_H
