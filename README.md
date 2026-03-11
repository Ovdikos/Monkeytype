# Monkeytype Clone (C++)

A performance-oriented typing trainer built from scratch in C++. This project focuses on efficient string processing, real-time input handling, and high-fps graphical feedback.

## Tech Stack
- **Language:** Modern C++ (C++20 standards)
- **Framework:** SFML (Simple and Fast Multimedia Library) for windowing, rendering, and fonts.
- **Build System:** CMake
- **Data Management:** File-based dictionary system for dynamic word generation.

## Key Features
- **Real-time Logic:** Low-latency input processing for an accurate typing experience.
- **Menu System:** Modular UI with separate views for Records, Settings, and the Main Game loop.
- **Record Tracking:** Persistent high-score system implemented via file I/O operations.
- **Dynamic Word Generation:** Algorithmic selection of words from local data files to ensure varied gameplay.

## Architecture & Practices
- **Modular Design:** Divided into specialized managers (`WordManager`, `HUD`, `WindowFunction`) to maintain the **Single Responsibility Principle**.
- **Game Loop Optimization:** Implementation of a consistent game loop for smooth rendering and event processing.
- **Pointer & Memory Safety:** Use of modern C++ features to ensure efficient memory utilization and avoid leaks.
- **UX/UI Polish:** Integration of custom fonts (`.ttf`) and textures to provide a professional visual style.
