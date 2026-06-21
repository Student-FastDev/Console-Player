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

const int FRAME_DELAY = 28000;  
#ifdef _WIN32
    const int FRAME_DELAY_MS = FRAME_DELAY / 1000;  
#else
    const int FRAME_DELAY_MS = FRAME_DELAY;  
#endif

using namespace std;

atomic<bool> isPaused(false);       
atomic<bool> exitProgram(false);    
atomic<int> currentSong(0);         
mutex frameLock;                    

void clearScreen() {
    #ifdef _WIN32
        system("cls");  
    #else
        system("clear");  
    #endif
}

void displayFrames(const char* frames[][22], int numFrames, int height, atomic<int>& currentFrame, const string& songTitle) {
    auto startTime = chrono::steady_clock::now();  
    int duration = (numFrames * FRAME_DELAY) / 1000000;  

    while (!exitProgram) {
        if (!isPaused) {
            frameLock.lock();  

            clearScreen();  
            
            for (int j = 0; j < height; j++) {
                cout << frames[currentFrame][j] << endl;
            }
            cout.flush();
            frameLock.unlock();

            currentFrame++;  
            if (currentFrame >= numFrames) {
                currentFrame = 0;  
            }
            
            auto currentTime = chrono::steady_clock::now();
            int elapsedTime = chrono::duration_cast<chrono::seconds>(currentTime - startTime).count();
            
            if (elapsedTime >= duration) {
                startTime = chrono::steady_clock::now();  
                elapsedTime = 0;
                currentFrame = 0;  
            }

            cout << "\033[37m";  

            int currentMinutes = elapsedTime / 60;
            int currentSeconds = elapsedTime % 60;
            int totalMinutes = duration / 60;
            int totalSeconds = duration % 60;

            cout << "           | ";
            int barLength = 30;  
            int progress = (elapsedTime * barLength) / duration;  
            for (int i = 0; i < barLength; ++i) {
                if (i < progress) {
                    cout << "#";  
                } else {
                    cout << "-";  
                }
            }
            cout << " |  [" << setw(2) << setfill('0') << currentMinutes << ":" 
                 << setw(2) << setfill('0') << currentSeconds << "/"
                 << setw(2) << setfill('0') << totalMinutes << ":" 
                 << setw(2) << setfill('0') << totalSeconds << "]" << endl;

            cout << "                        " << songTitle << endl;
            cout << "\033[90m";
            cout << "                p - pauza; s - zmien piosenke; q - wyjdz;" << endl;

            cout << "\033[90;40m"; 
            
            #ifdef _WIN32
                Sleep(FRAME_DELAY_MS);
            #else
                usleep(FRAME_DELAY);
            #endif
        } else {
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        
        if (currentSong != (songTitle == "Luis Fonsi - Despacito" ? 0 : 1)) {
            break;  
        }
    }
}

void userInput() {
    char input;
    while (!exitProgram) {
        cin >> input;
        if (input == 'p') {
            isPaused = !isPaused;  
        } else if (input == 's') {
            currentSong = (currentSong + 1) % 2;  
        } else if (input == 'q') {
            exitProgram = true;  
        }
    }
}

int main() {
    atomic<int> despacitoFrame(0);  
    atomic<int> shapeFrame(0);      
    thread inputThread(userInput);  

    while (!exitProgram) {
        if (currentSong == 0) {
            int numDespacitoFrames = sizeof(despacitoFrames) / sizeof(despacitoFrames[0]); 
            displayFrames(despacitoFrames, numDespacitoFrames, despacitoHeight, despacitoFrame, "Luis Fonsi - Despacito");
        }

        if (currentSong == 1) {
            int numShapeFrames = sizeof(shapeFrames) / sizeof(shapeFrames[0]);
            displayFrames(shapeFrames, numShapeFrames, shapeHeight, shapeFrame, "Ed Sheeran - Shape of You");
        }
    }

    inputThread.join();  
    return 0;
}
