#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <windows.h>
#include <execution>
#include <conio.h>


std::mutex mtx;


int velocityY = 1;
int velocityX = 1;
size_t positionY = 5;
size_t positionX = 15;
size_t minX = 0;
size_t maxX = 30;
size_t minY = 0;
size_t maxY = 29;


void printState() {
    while (true) {
        mtx.lock();
        system("cls");
        for (size_t i = minX; i < 10; ++i) {
            for (size_t j = minY; j < maxY; ++j) {
                if (i == positionY && j == positionX) {
                    std::cout << "0";
                }
                else {
                    std::cout << "#";
                }
            }
            std::cout << std::endl;
        }
        positionY += velocityY;
        positionY = (std::min)(positionY, maxY);
        positionY = (std::max)(positionY, minY);
        positionX += velocityX;
        positionX = (std::min)(positionX, maxX);
        positionX = (std::max)(positionX, minX);
        mtx.unlock();
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1000ms);

    }
}



void getState() {
    while (true) {
        mtx.lock();
        if (positionY==9) {
            velocityY = -1;
        }
        else if (positionY==0) {
            velocityY = 1;
        }
        if (positionX==28) {
            velocityX = -1;
        }
        else if (positionX==0){
            velocityX = 1;
        }
        mtx.unlock();
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1000ms);
    }
}

int main() {
    std::thread th1(getState);
    std::thread th2(printState);
    th1.join();
    th2.join();
    return 0;
}