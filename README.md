# Chess Game – C++ with SFML (OOP Concepts)

## Description
A graphical chess game built in **C++** using **SFML**, showcasing **Object-Oriented Programming (OOP) principles**.  
Each chess piece is a class with movement rules, while the board, game logic, and UI are modularly separated.  
Supports standard chess rules, including **check, checkmate, and stalemate**, with an interactive graphical interface.

## Features
- Drag-and-drop piece movement  
- Standard chess rules implemented  
- Modular OOP design (encapsulation, inheritance, polymorphism)  
- Easy to extend with AI or custom rules  

## Requirements
- **C++17** or later  
- **SFML 2.5+**  
- **VS Code** or any C++ IDE  
- (Optional) **CMake** for building  

## Setup & Run (VS Code)
1. Install SFML and set up the include/lib paths.  
2. Clone the repository:  
   ```bash
   git clone <repo_url>
   cd ChessGame

## Compile the project:
g++ -std=c++17 src/*.cpp -o ChessGame -lsfml-graphics -lsfml-window -lsfml-system

## Run the game:
./ChessGame

## Project Structure
ChessGame/
│── src/          # Source code files
│── include/      # Header files
│── assets/       # Images, fonts, icons
│── .gitignore
│── README.md
