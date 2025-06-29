#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

class Display {
public:
    Display();
    ~Display();
    void update(const std::string& data);
};

#endif // DISPLAY_H
