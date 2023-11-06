#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <windows.h>
#include <ctime>

std::mutex mtx;

int randomNumber(int min, int max) {
    srand(time(NULL));
    return min + rand() % (max - min);
}

int velocityX = 1;
int velocityY = 1;
size_t Ball_positionX = 16;
size_t Ball_positionY = 6;
size_t maxX = 30;
size_t minX = 0;
size_t maxY = 9;
size_t minY = 0;
size_t Racket0_positionX = 0;
size_t Racket0_positionY = 5;

int FirstPlayerScore = 0;
int SecondPlayerScore = 0;

void printState() {
    while (true) {
        mtx.lock();
        system("cls");
        for (size_t i = 0; i < 10; ++i) {
            for (size_t j = 0; j < 31; ++j) {
                if (i == Ball_positionY && j == Ball_positionX) {
                    std::cout << "0";
                }
                else if (i == Racket0_positionY && j == Racket0_positionX) {
                    std::cout << "|";
                }
                else {
                    std::cout << "#";
                }
                
            }
            std::cout << std::endl;
        }
        std::cout << std::endl<<"-------------Score------------";
        std::cout << std::endl<<"       Player     Computer";
        std::cout << std::endl << "         " << FirstPlayerScore<<"            "<<SecondPlayerScore;
        Ball_positionY += velocityY;
        Ball_positionY = (std::min)(Ball_positionY, maxY);
        Ball_positionY = (std::max)(Ball_positionY, minY);
        Ball_positionX += velocityX;
        Ball_positionX = (std::min)(Ball_positionX, maxX);
        Ball_positionX = (std::max)(Ball_positionX, minX);
        mtx.unlock();
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(500ms);

    }
}



void getState() {
    while (true) {
        mtx.lock();
        if (Ball_positionY == Racket0_positionY && Ball_positionX - 1 == 0) {
            velocityX = 1;
        }
        if (Ball_positionY == 9) {
            velocityY = -1;
        }
        else if (Ball_positionY == 0) {
            velocityY = 1;
        }
        if (Ball_positionX == 30) {
            velocityX = -1;
            FirstPlayerScore++;
        }
        else if (Ball_positionX == 0) {
            velocityX = 1;
            SecondPlayerScore++;
        }
        if (GetAsyncKeyState(VK_UP) && Racket0_positionY!= 0) {
            Racket0_positionY--;
        }
        else if (GetAsyncKeyState(VK_DOWN) && Racket0_positionY != 9) {
            Racket0_positionY++;
        }
        mtx.unlock();
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(500ms);
    }
}

int main() {
    std::thread th1(getState);
    std::thread th2(printState);
    th1.join();
    th2.join();
    return 0;
}