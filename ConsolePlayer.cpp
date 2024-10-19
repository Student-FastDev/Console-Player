#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <iomanip>
#include <chrono>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif
#include "Songs/despacitoSong.h"
#include "Songs/shapeSong.h"

const int FRAME_DELAY = 28000;  // Opóźnienie ramki w mikrosekundach.
#ifdef _WIN32
    const int FRAME_DELAY_MS = FRAME_DELAY / 1000;  // Milisekundy dla Windowsa.
#else
    const int FRAME_DELAY_MS = FRAME_DELAY;  // Mikrosekundy dla Unix/Linux.
#endif

using namespace std;

atomic<bool> isPaused(false);       // Zmienna atomowa do pauzy/wznawiania.
atomic<bool> exitProgram(false);    // Flaga do zakończenia programu.
atomic<int> currentSong(0);         // 0: Despacito, 1: Shape of You.
mutex frameLock;                    // Synchronizacja zmian ramek.

// Funkcja do czyszczenia ekranu zależna od systemu operacyjnego.
void clearScreen() {
    #ifdef _WIN32
        system("cls");  // Czyść ekran w Windows.
    #else
        system("clear");  // Czyść ekran w Unix/Linux.
    #endif
}

void displayFrames(const char* frames[][22], int numFrames, int height, atomic<int>& currentFrame, const string& songTitle) {
    auto startTime = chrono::steady_clock::now();  // Zapisz czas początkowy.
    int duration = (numFrames * FRAME_DELAY) / 1000000;  // Całkowity czas trwania w sekundach.

    while (!exitProgram) {
        if (!isPaused) {
            frameLock.lock();  // Blokowanie dla zapobiegania zmianom ramek w trakcie pauzy.

            clearScreen();  // Czyść ekran przed wyświetleniem nowej ramki.

            // Wyświetl bieżącą ramkę.
            for (int j = 0; j < height; j++) {
                cout << frames[currentFrame][j] << endl;
            }
            cout.flush();
            frameLock.unlock();

            currentFrame++;  // Przejdź do następnej ramki.
            if (currentFrame >= numFrames) {
                currentFrame = 0;  // Powrót do początku po zakończeniu ramek.
            }

            // Oblicz upływający czas w sekundach.
            auto currentTime = chrono::steady_clock::now();
            int elapsedTime = chrono::duration_cast<chrono::seconds>(currentTime - startTime).count();

            // Zresetuj czas trwania i ramkę, gdy piosenka się zapętla.
            if (elapsedTime >= duration) {
                startTime = chrono::steady_clock::now();  // Resetuj czas początkowy dla zapętlenia.
                elapsedTime = 0;
                currentFrame = 0;  // Zresetuj ramkę do pierwszej.
            }

            // Ustaw kolor tekstu na biały.
            cout << "\033[37m";  // Kod ANSI dla białego tekstu.

            // Wyświetl pasek czasu.
            int currentMinutes = elapsedTime / 60;
            int currentSeconds = elapsedTime % 60;
            int totalMinutes = duration / 60;
            int totalSeconds = duration % 60;

            cout << "           | ";
            int barLength = 30;  // Długość paska czasu.
            int progress = (elapsedTime * barLength) / duration;  // Oblicz postęp na podstawie faktycznego czasu.
            for (int i = 0; i < barLength; ++i) {
                if (i < progress) {
                    cout << "#";  // Wypełniona część.
                } else {
                    cout << "-";  // Pusta część.
                }
            }
            cout << " |  [" << setw(2) << setfill('0') << currentMinutes << ":" 
                 << setw(2) << setfill('0') << currentSeconds << "/"
                 << setw(2) << setfill('0') << totalMinutes << ":" 
                 << setw(2) << setfill('0') << totalSeconds << "]" << endl;

            // Wyświetl tytuł piosenki i artystę w białym kolorze.
            cout << "                        " << songTitle << endl;

            cout << "\033[90m";

            // Wyświetl legendę sterowania w białym kolorze.
            cout << "                p - pauza; s - zmien piosenke; q - wyjdz;" << endl;

            // Resetuj kolor tekstu do domyślnego.
            cout << "\033[90;40m";  // Kod ANSI do resetu koloru tekstu do domyślnego.

            // Uśpij na czas opóźnienia ramki.
            #ifdef _WIN32
                Sleep(FRAME_DELAY_MS);
            #else
                usleep(FRAME_DELAY);
            #endif
        } else {
            // Pauza na 100 milisekund, gdy program jest wstrzymany.
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        // Sprawdź, czy zmieniono piosenkę.
        if (currentSong != (songTitle == "Luis Fonsi - Despacito" ? 0 : 1)) {
            break;  // Przerwij, aby zmienić piosenkę.
        }
    }
}

// Funkcja obsługująca wejście użytkownika (pauza, zmiana piosenek, wyjście).
void userInput() {
    char input;
    while (!exitProgram) {
        cin >> input;
        if (input == 'p') {
            isPaused = !isPaused;  // Przełącz pauzę/wznawianie.
        } else if (input == 's') {
            currentSong = (currentSong + 1) % 2;  // Przełącz między 0 i 1.
        } else if (input == 'q') {
            exitProgram = true;  // Wyjdź z programu.
        }
    }
}

// Funkcja główna.
int main() {
    atomic<int> despacitoFrame(0);  // Bieżąca ramka dla Despacito.
    atomic<int> shapeFrame(0);      // Bieżąca ramka dla ShapeSong.

    thread inputThread(userInput);  // Rozpocznij wątek obsługi wejścia użytkownika.

    // Główna pętla odtwarzająca piosenki.
    while (!exitProgram) {
        if (currentSong == 0) {
            // Odtwarzaj Despacito.
            int numDespacitoFrames = sizeof(despacitoFrames) / sizeof(despacitoFrames[0]); 
            displayFrames(despacitoFrames, numDespacitoFrames, despacitoHeight, despacitoFrame, "Luis Fonsi - Despacito");
        }

        if (currentSong == 1) {
            // Odtwarzaj Shape of You.
            int numShapeFrames = sizeof(shapeFrames) / sizeof(shapeFrames[0]);
            displayFrames(shapeFrames, numShapeFrames, shapeHeight, shapeFrame, "Ed Sheeran - Shape of You");
        }
    }

    inputThread.join();  // Poczekaj na zakończenie wątku wejściowego przed zakończeniem programu.
    return 0;
}
