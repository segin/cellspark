#ifndef TERMUX_API_H
#define TERMUX_API_H

#include <string>

/**
 * @class TermuxApi
 * @brief A wrapper for the Termux API.
 */
class TermuxApi {
public:
    /**
     * @brief Construct a new TermuxApi object.
     */
    TermuxApi();

    /**
     * @brief Gets telephony information from the Termux API.
     *
     * @return A JSON string containing the telephony information.
     */
    std::string getTelephonyInfo();
};

#endif // TERMUX_API_H
