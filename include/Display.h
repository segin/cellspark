#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

class Display {
public:
    Display(int titleColor, int labelColor, int valueColor, int errorColor);
    ~Display();
    void update(const std::string& data);
    void updateError(const std::string& errorMessage);
};

#endif // DISPLAY_H
