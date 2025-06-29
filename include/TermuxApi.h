#ifndef TERMUX_API_H
#define TERMUX_API_H

#include <string>

class TermuxApi {
public:
    TermuxApi();
    std::string getTelephonyInfo();
};

#endif // TERMUX_API_H
