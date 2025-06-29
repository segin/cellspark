# Project Roadmap: C++ Ncurses Cellular Info Display

This document outlines the plan for creating a C++ ncurses-based application to display cellular connection information in Termux.

## Initial Prompt

> I am running Gemini CLI on Termux on an Android phone. Please generate a ncurses-based display that shows my current cellular connection info in Termux console? Q to quit. Updates in realtime or regular refresh. You may install missing software with `pkg`. Create the program in C++. Use a Makefile to build it. Put each class in its own .cpp and .h files. Updste in real-time or regularly. Use Google Search to learn how termux-api is implemented, find its source code, download it, study it well. Make anfull program project roadmap and save it to disk. Put this prompt in the roadmap document. Always update the roadmap. Use Git religiously. Query the roadmap before proceeding on each step.

## Project Plan

1.  **Initialize Git Repository:** Create a new Git repository for the project. (Done)
2.  **Create Project Roadmap:** Create this `ROADMAP.md` file. (Done)
3.  **Research `termux-api`:**
    *   Use Google Search to find the source code for `termux-api`.
    *   Analyze the source code to understand how to call `termux-telephony-deviceinfo` from a C++ program.
    *   Identify the mechanism for inter-process communication (IPC) used by `termux-api`.
4.  **Set up Project Structure:**
    *   Create `src`, `include`, and `build` directories.
5.  **Create Makefile:**
    *   Create a `Makefile` to compile the C++ source code.
6.  **Implement C++ Application:**
    *   **`TermuxApi` Class:**
        *   Create `TermuxApi.h` and `TermuxApi.cpp`.
        *   Implement a method to execute the `termux-telephony-deviceinfo` command and capture its JSON output.
        *   Integrate a C++ JSON parsing library.
    *   **`Display` Class:**
        *   Create `Display.h` and `Display.cpp`.
        *   Implement an ncurses-based display to show the cellular information.
    *   **Improve UI:**
        *   Enhance the `Display` class to use colors and box-drawing characters for a more polished look.
    *   **`main` function:**
        *   Create `main.cpp`.
        *   Instantiate the `TermuxApi` and `Display` classes.
        *   Implement the main loop to refresh the data and handle user input ('q' to quit).
    *   **Add One-Shot and Refresh Modes:** (Done)
        *   Modify `main.cpp` to display information once and exit by default.
        *   Add a command-line flag (`-r`) to enable real-time refresh with 'q' to quit.
    *   **Add Non-interactive Mode:**
        *   Modify `main.cpp` to handle a command-line flag (e.g., `--json`).
        *   If the flag is present, the application will:
            *   Fetch the telephony information.
            *   Print the raw JSON to standard output.
            *   Exit immediately without initializing the ncurses display.
7.  **Build and Test:**
    *   Compile the project using the `Makefile`.
    *   Run the application and verify its functionality.
    *   Test the non-interactive JSON output mode.
8.  **Git Commits:**
    *   Commit changes to the Git repository at each significant step.

## Future Enhancements

9.  **Error Handling and Robustness:** (Done)
    *   Implement more comprehensive error handling for `termux-telephony-deviceinfo` command execution (e.g., command not found, permission issues).
    *   Gracefully handle malformed JSON output from `termux-telephony-deviceinfo`.
    *   Add logging capabilities for debugging and error reporting.
    *   Implement signal handling (e.g., SIGINT) for clean application shutdown.
10. **Configuration Options:**
    *   Allow users to configure refresh interval via command-line argument. (Done)
    *   Allow users to configure display colors via command-line arguments or a configuration file.
    *   Implement a configuration file (e.g., `~/.config/cinfo.conf`) for persistent settings.
11. **More Telephony Information:**
    *   Integrate other `termux-telephony-*` commands (e.g., `termux-telephony-callinfo`, `termux-telephony-cellinfo`, `termux-telephony-siminfo`).
    *   Display signal strength (RSSI, RSRP, RSRQ, SINR) if available.
    *   Show current cell ID and location area code.
    *   Display detailed SIM card information (ICCID, IMSI).
    *   Show call state (idle, ringing, off-hook).
12. **User Interface Improvements (Advanced):**
    *   Implement a multi-panel layout using ncurses windows for different information categories.
    *   Add a status bar at the bottom for messages or current time.
    *   Implement interactive elements (e.g., scrollable lists if data becomes extensive).
    *   Support different themes/color schemes.
    *   Add a splash screen on startup.
    *   Implement a help screen accessible via a key press.
    *   Add a "last updated" timestamp on the display.
    *   Animate loading indicators while fetching data.
13. **Cross-Platform Compatibility (Conceptual):**
    *   Investigate possibilities for running on other Linux-like environments (requires alternative to `termux-api`).
14. **Performance Optimizations:**
    *   Optimize JSON parsing for large data sets (if applicable in future).
    *   Minimize system calls for data fetching.
15. **Testing and CI/CD:**
    *   Write unit tests for `TermuxApi` and `Display` classes.
    *   Set up a continuous integration (CI) pipeline (e.g., GitHub Actions) for automated builds and tests.
    *   Implement integration tests for command-line arguments.
16. **Packaging and Distribution:**
    *   Create a Termux package for easy installation.
    *   Provide clear installation instructions in `README.md`.
17. **Code Quality and Maintainability:**
    *   Refactor code for better modularity and readability.
    *   Add Doxygen comments for API documentation.
    *   Enforce coding style guidelines (e.g., using `clang-format`).
    *   Migrate to CMake for build system (more flexible than Makefile for larger projects).
18. **Accessibility:**
    *   Consider options for screen reader compatibility (if ncurses allows).
19. **Security:**
    *   Review `popen` usage for potential security vulnerabilities (e.g., command injection, though less critical for internal tools).
20. **Internationalization (i18n):**
    *   Support multiple languages for UI text.
21. **Battery Usage Optimization:**
    *   Investigate ways to reduce battery consumption, especially in refresh mode.
22. **Background Service (Conceptual):
    *   Explore creating a background service for data collection (more complex, Android-specific).
23. **Notifications:**
    *   Integrate with Termux notifications for critical alerts (e.g., network disconnected).
24. **Historical Data:**
    *   Store historical cellular data and display trends.
25. **Network Speed Test Integration:**
    *   Integrate a simple network speed test.
26. **Bluetooth Information:**
    *   Integrate `termux-bluetooth-deviceinfo` to show Bluetooth status.
27. **Wi-Fi Information:**
    *   Integrate `termux-wifi-connectioninfo` to show Wi-Fi status.
28. **Device Information:**
    *   Integrate `termux-battery-status` and `termux-telephony-deviceinfo` for more general device info.
29. **Interactive Debugging:**
    *   Add a debug mode with verbose output.
30. **User Feedback Mechanism:**
    *   Implement a way for users to submit feedback or bug reports from within the app.