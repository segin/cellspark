#include "TermuxApi.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include "Exceptions.h"
#include <string>
#include <array>

TermuxApi::TermuxApi() {}

std::string TermuxApi::getTelephonyInfo() {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("termux-telephony-deviceinfo", "r"), pclose);
    if (!pipe) {
        throw TermuxApiException("Failed to execute termux-telephony-deviceinfo: popen() failed.");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    int status = pclose(pipe.release());
    if (status == -1) {
        throw TermuxApiException("Failed to execute termux-telephony-deviceinfo: pclose() failed.");
    } else if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
        throw TermuxApiException("termux-telephony-deviceinfo exited with status " + std::to_string(WEXITSTATUS(status)));
    } else if (WIFSIGNALED(status)) {
        throw TermuxApiException("termux-telephony-deviceinfo terminated by signal " + std::to_string(WTERMSIG(status)));
    }

    return result;
}
