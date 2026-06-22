# Fruit Ninja Clone (C++ / SplashKit)

A C++ recreation of Fruit Ninja built using the [SplashKit](https://splashkit.io/) library, developed for Monash FIT1045.

## Overview

This project implements core Fruit Ninja mechanics from scratch, including realistic projectile motion, real-time slicing detection, combo scoring, and persistent per-level high scores.

## Features

- **Bézier curve fruit movement** — fruit follow smooth, natural-looking arcs as they're launched and fall
- **Line-circle intersection collision detection** — accurately detects when the knife's swipe path slices through a fruit
- **Circular buffer knife trail rendering** — efficiently renders the fading slice trail behind the cursor
- **Combo system** — tracks consecutive slices, resetting correctly between levels
- **Pomegranate bomb mechanic** — spawns only after a score threshold is reached
- **Per-level high score persistence** — high scores are saved to and loaded from text files, tracked separately per level
- **Session management** - if a user quits while playing, session persists when program is run again + if the user goes to the menu while playing, session for that level persists

## Built With

- C++
- [SplashKit SDK](https://splashkit.io/)

## Getting Started

### Prerequisites

- [SplashKit SDK](https://splashkit.io/guides/getting-started/) installed
- A C++ compiler (e.g. g++ via MinGW on Windows)
- VS Code (recommended) with the SplashKit extension

### Build & Run

```bash
# from the project root
skm run
```

> If your setup doesn't use the SplashKit CLI, compile manually with your SplashKit include/lib paths, e.g.:
> ```bash
> g++ -o fruit_ninja *.cpp -I"<splashkit_include_path>" -L"<splashkit_lib_path>" -lSplashKit
> ```

### Known issues
- Loss of combo state doesn't apply to knife
- If user chooses not to continue from a file-based session, the in-game session will still be retained
