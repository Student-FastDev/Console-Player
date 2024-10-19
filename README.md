![Gigathon Icon](https://i.imgur.com/1mSIKP4.png)

This README was written in two languages:
- **English** [Console Player](#console-player-english)
- **Polski** [Konsolowy Odtwarzacz](#konsolowy-odtwarzacz-polski)

# Console Player (English)

## Table of Contents
1. [Project Overview](#project-overview)
2. [Setup and Compilation](#setup-and-compilation)
3. [Controls and Gameplay](#controls-and-gameplay)
4. [Key Features](#key-features)

---

## Project Overview

**Console Player** is an animation-based program created for the **Gigathon Contest**, which plays two well-known songs by showing ASCII animations in the terminal. The program uses multi-threading to handle user input and plays the songs in an endless loop with options to pause, switch songs, and exit the program. It includes two songs: **Luis Fonsi's Despacito** and **Ed Sheeran's Shape of You**, whose frames are stored in `.h` files inside the `Songs/` folder.

The animation frames were generated using a script located at `Generator/videoToTextCopy.py`, but using this script is not necessary for running the program. For more detailed instructions on using the generator, [view Generator Instructions](GENERATOR.md).

---

## Setup and Compilation

### Prerequisites

To compile and run this program, you need:
- A **C++ compiler** such as `g++` or `clang`.
- A terminal or command line interface.
- On Windows, ensure you have the `g++` compiler or a compatible IDE like Visual Studio.

### Compilation Instructions

1. **Download the repository**: Clone or download the repository to your local machine.
   
2. **Unzip frame files**: Extract the `Songs/compressedSongs.rar` to get the required `.h` files with animation frames.

3. **Open a terminal**: Navigate to the folder where the source code (`ConsolePlayer.cpp`) is located.

4. **Compile the code**:
   
   Run the following command in the terminal (assuming `g++` is installed):
   
   ```
   g++ -o ConsolePlayer ConsolePlayer.cpp -lpthread
   ```

   You can also download already compiled version and skip this process.

5. **Run the program**:

   After compilation, you can run the program using:
   
   ```
   ./ConsolePlayer
   ```

   On Windows, run it as:
   
   ```
   ConsolePlayer.exe
   ```

---

## Controls and Gameplay

### Available Commands

When the program starts, it plays the selected song in a loop. The following controls are available during the animation:

- **p**: Pause/Resume the animation.
- **s**: Switch to the next song.
- **q**: Quit the program.

After each instruction, remember to press `Enter`.

### Animation Display

The song plays with ASCII-based frames, showing:
- The current song's title.
- A progress bar with the elapsed time.
- Control instructions for pause, switch, and quit.

---

## Key Features

1. **Multi-threaded Control**:
   - User inputs are handled in a separate thread to allow real-time interaction with the playback.

2. **Cross-Platform Compatibility**:
   - The program works on both Windows and Linux/Unix systems, with appropriate screen-clearing commands for each platform.

3. **Smooth ASCII Animations**:
   - ASCII frames are displayed in sync with the song, with precise timing using `chrono` for frame delays.

4. **Frame Generation**:
   - The frames were created using `Generator/videoToTextCopy.py`, which converts video frames to ASCII art.

---

# Konsolowy Odtwarzacz (Polski)

## Spis treści
1. [Opis Projektu](#opis-projektu)
2. [Konfiguracja i Kompilacja](#konfiguracja-i-kompilacja)
3. [Sterowanie i Rozgrywka](#sterowanie-i-rozgrywka)
4. [Kluczowe Funkcje](#kluczowe-funkcje)

---

## Opis Projektu

**Konsolowy Odtwarzacz** to program oparty na animacjach ASCII, stworzony na konkurs **Gigathon**, który odtwarza dwie popularne piosenki, wyświetlając animacje w terminalu. Program wykorzystuje wielowątkowość do obsługi wejścia użytkownika i odtwarza piosenki w nieskończonej pętli z możliwością pauzowania, zmiany utworu oraz zakończenia programu. W zestawie znajdują się dwie piosenki: **Despacito** Luisa Fonsi oraz **Shape of You** Eda Sheerana, których klatki są zapisane w plikach `.h` w folderze `Songs/`.

Klatki animacji zostały wygenerowane za pomocą skryptu `Generator/videoToTextCopy.py`, ale użycie tego skryptu nie jest konieczne do uruchomienia programu. By dowiedziec sie jak korzysta z generatora, [zapoznaj sie z Instrukcja do Generatora](GENERATOR.md).

---

## Konfiguracja i Kompilacja

### Wymagania wstępne

Aby skompilować i uruchomić program, potrzebujesz:
- **Kompilatora C++**, np. `g++` lub `clang`.
- Terminala lub interfejsu wiersza poleceń.
- Na systemie Windows potrzebny będzie kompilator `g++` lub zgodne IDE, takie jak Visual Studio.

### Instrukcje kompilacji

1. **Pobierz repozytorium**: Sklonuj lub pobierz repozytorium na swój komputer.
   
2. **Wypakuj pliki ramek**: Rozpakuj `Songs/compressedSongs.rar`, aby uzyskać wymagane pliki `.h` z klatkami animacji.

3. **Otwórz terminal**: Przejdź do folderu, w którym znajduje się plik źródłowy (`ConsolePlayer.cpp`).

4. **Skompiluj kod**:

   Uruchom poniższe polecenie w terminalu (zakładając, że masz zainstalowany `g++`):
   
   ```
   g++ -o ConsolePlayer ConsolePlayer.cpp -lpthread
   ```

   Mozesz takze pobrac wczesniej skompilowany plik, by pominac ten proces,

5. **Uruchom program**:

   Po kompilacji uruchom program za pomocą:
   
   ```
   ./ConsolePlayer
   ```

   Na systemie Windows uruchom jako:
   
   ```
   ConsolePlayer.exe
   ```

---

## Sterowanie i Rozgrywka

### Dostępne Komendy

Po uruchomieniu programu odtwarzana jest wybrana piosenka w pętli. Dostępne są następujące komendy:

- **p**: Pauza/Wznów animację.
- **s**: Zmień piosenkę.
- **q**: Zakończ program.

Pamietaj aby po kazdej instrukcji nacisnac przycink `Enter`.

### Wyświetlanie Animacji

Podczas odtwarzania piosenki w animacji ASCII wyświetlane są:
- Tytuł aktualnej piosenki.
- Pasek postępu z upływem czasu.
- Instrukcje sterowania do pauzy, zmiany utworu i wyjścia.

---

## Kluczowe Funkcje

1. **Wielowątkowa Obsługa**:
   - Wejścia użytkownika są obsługiwane w osobnym wątku, co umożliwia interakcję w czasie rzeczywistym z odtwarzaniem.

2. **Kompatybilność z Różnymi Systemami**:
   - Program działa zarówno na systemach Windows, jak i Linux/Unix, z odpowiednimi komendami czyszczenia ekranu dla każdego systemu.

3. **Płynne Animacje ASCII**:
   - Klatki ASCII są wyświetlane w synchronizacji z utworem, z precyzyjnym timingiem za pomocą `chrono`.

4. **Generowanie Klatek**:
   - Klatki zostały stworzone przy użyciu `Generator/videoToTextCopy.py`.


![Preview](https://i.imgur.com/Xv6v8B8.gif)
