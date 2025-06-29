# 🧩 Sudoku Solver (C++ Backend with Crow)

A fast and simple Sudoku solver backend built with C++ using the lightweight [Crow](https://github.com/ipkn/crow) web framework. This project solves 9x9 Sudoku puzzles and exposes a REST API endpoint for integration with frontends.

---

## 🚀 Features

- Accepts 9x9 Sudoku board via JSON
- Solves puzzles using backtracking algorithm
- Exposes a simple HTTP POST API
- CORS-enabled (perfect for frontend use)

---

## 🔧 Technologies Used

- C++
- [Crow Web Framework](https://github.com/ipkn/crow)
- JSON Handling
- CMake for build management

---
## ⚙️ Build & Run

### 🛠 Prerequisites

- [CMake](https://cmake.org/)
- C++ Compiler (MSVC / g++)
- Git
- Live Server extension (for VSCode or browser)

---

### 🧱 Build (Backend)

```bash
mkdir build
cd build
cmake ..
cmake --build .

./Debug/sudoku.exe
```
## 📦 API Usage

### POST `/solve`

**Request Body:**
```json
[
  ["5", "3", ".", ".", "7", ".", ".", ".", "."],
  ...
]
```
**Response:**
```json
[
  ["5", "3", "4", "6", "7", "8", "9", "1", "2"],
  ...
]
```

## 📁 Folder Structure

```
Sudoku_Solver/
│
├── backend/
│   ├── main.cpp              # Crow-based C++ server
│   ├── sudoku_solver.cpp     # Core solving logic
│   ├── crow/                 # Crow framework source
│   ├── asio/                 # ASIO dependency (required by Crow)
│   ├── CMakeLists.txt        # Build configuration
│   └── build/                # Build output directory
│
├── frontend/
│   ├── index.html            # Web UI
│   ├── style.css             # Styles
│   └── script.js             # Handles frontend logic & API calls
│
└── README.md                 # You're reading it!
```

---



