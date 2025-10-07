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

