# Notepad
# Text Editor using 2D Doubly Linked List

## 📌 Description

This project is a console-based **text editor** built using a **2D Doubly Linked List**. Each character in the editor is represented as a node that maintains four directional pointers — `up`, `down`, `left`, and `right`. These pointers link the characters together to form a 2D grid, which enables navigation similar to real text editors.

This project is a demonstration of applying **data structure concepts** such as:

* 2D doubly linked list creation and management
* Dynamic memory allocation and deallocation
* Cursor movement (up, down, left, right)
* Real-time text insertion and deletion (including `Backspace` and `Delete`)
* File operations (saving to and loading from a file)

It showcases how complex behaviors can be implemented from scratch without the use of built-in string handling or containers — reinforcing low-level programming principles.

## 🛠 Features

* Character-by-character input via keyboard
* Arrow-key based navigation of cursor
* Support for new lines (Enter key)
* `Backspace` and `Delete` key functionality
* Save (`Ctrl+S`) and Load (`Ctrl+L`) from a file

## 🧠 Data Structure Logic

The editor maintains a `cursor` pointer that traverses the 2D doubly linked list:

* On insertion, new nodes are created and properly linked to neighbors.
* On Enter, the line is split and connections are updated.
* On Delete/Backspace, the corresponding node is removed and links are re-wired.
* The up/down connections between lines are maintained using helper functions that mirror the layout of text lines.

This structure mimics a basic line editor with full manual control over character data.

## 🏁 How to Run

1. Open the code in a C++-compatible IDE (e.g., Visual Studio).
2. Ensure the console has permission to read/write `file.txt`.
3. Compile and run the project.
4. Use the keyboard to type and navigate:

   * Arrow Keys: Move cursor
   * Enter: New line
   * Backspace/Delete: Remove character
   * Ctrl+S: Save to file
   * Ctrl+L: Load from file

> ⚠ Note: This application uses Windows-specific headers (`conio.h`, `windows.h`) and may not work on Linux/macOS without modification.

## ✅ Requirements

* Windows OS
* C++ Compiler (MSVC recommended)
