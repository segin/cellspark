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
