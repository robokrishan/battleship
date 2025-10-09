# ⚓ Battleship Game (C++)

A modular, object-oriented implementation of the classic **Battleship** strategy game written in **C++**.  
This project demonstrates clean design principles, dynamic memory management, and encapsulated game logic — perfect for learning or showcasing OOP concepts.

---

## 🚀 Features

- 🎮 **Two-player gameplay** (human vs human or manual/auto placement)
- 🧭 **Encapsulated game logic** in dedicated classes:
  - `Battleship` – game controller  
  - `Player` – player data, ships, and grid management  
  - `Grid` – 2D dynamic grid of pointers with ownership tracking  
  - `Ship` – encapsulated ship models and metadata
- 🧩 **Automatic ship placement** using randomized fit checks
- 💣 **Collision-safe placement** via grid validation (`isFit()`)
- 🧱 **Robust memory handling** with ownership-aware destructors
- 🛠️ **Debug mode** (`#define DEBUG`) for verbose console logging

---

## 🗂️ Project Structure

```bash
Battleship/
├── include/                 # Header files (class declarations)
│   ├── Battlelog.h
│   ├── Battleship.h
│   ├── BattleshipUtil.h
│   ├── game_err.h
│   ├── Grid.h
│   ├── Player.h
│   ├── Position.h
│   ├── Ship.h
│   └── ShipType.h 
│
├── src/                     # Source files (class definitions)
│   ├── Battlelog.cpp
│   ├── Battleship.cpp
│   ├── Grid.cpp
│   ├── Player.cpp
│   ├── Ship.cpp
│   └── main.cpp
│
├── Makefile                 # Build configuration
├── README.md                # Project documentation
└── .gitignore               # Ignored build artifacts and binaries


```

---

## 🧩 Class Overview


| Class        | Responsibility |
|---------------|----------------|
| **Battleship** | Manages overall game flow, player initialization, and round control |
| **Player**     | Handles player-specific data (name, grid, ships) and placement logic |
| **Grid**       | 2D array of `char*` pointers representing ocean cells and ship segments |
| **Ship**       | Represents an individual ship, its size, type, and occupied cells |

---

## 🧰 Build Instructions

### 🧱 Prerequisites
- **C++17** or newer
- **make** (optional, for Makefile builds)

### 🧑‍💻 Build via Makefile
```bash
make
```

### ▶️ Run the Game
```bash
./game
```

### To rebuild from scratch:
```bash
make clean && make
```

### 🎮 Gameplay

Run the executable:
```bash
./game
```


1. Enter the number of players (currently 2 supported)

2. Enter each player's name

3. Choose whether to place ships manually or automatically (y/n)

4. Watch the grids populate with ships!

### 🧪 Debugging

You can enable detailed console output by uncommenting the #define DEBUG lines in each .cpp file:

```bash
#define DEBUG
```

This prints constructor/destructor calls, placement logs, and grid state transitions.

### 🧼 Memory Management

All dynamic allocations are paired with safe deallocation:

- Grid destructor frees only 'O' cells (it owns them)

- Ship destructor frees its internal shipMap

- Player destructor deletes each dynamically allocated Ship

- Battleship destructor frees the Player[] array

Run with AddressSanitizer to confirm:

```bash
g++ -Wall -fsanitize=address -g -o game *.cpp
./game
```

### 🧭 Future Enhancements

- 🧍 Single-player mode vs computer AI

- 💻 GUI visual board

- 📊 Scoreboard and replay system

- 🚢 Manual placement of ships

## 🧑‍💻 Author

Harit Krishan

🎓 Postgraduate Student, Monash University

💡 Passionate about Embedded Systems, AI, and Game Design