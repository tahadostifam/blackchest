#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <unistd.h> // For usleep()
#include <cstdlib>  // For system("clear")
#include <termios.h> // For non-blocking input

// Function to clear the screen (Linux)
void clearScreen() {
    std::cout << "\033[2J\033[1;1H"; // ANSI escape codes for clear and reset cursor
}

// Function to sleep (Linux)
void sleepMillis(int milliseconds) {
    usleep(milliseconds * 1000);
}

// Function to get non-blocking input (Linux)
int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}


int main() {
    std::vector<std::string> frames = {
        R"(
         _,-._
        / \_/ \
        >-(_)-<
        \_/ \_/
          `-'
    )",
        R"(
         _,-._
        / \_/ \
       >-(_)-<
        \_/ \_/
         `-'
        O
    )",
        R"(
         _,-._
        / \_/ \
       >-(_)-<
        \_/ \_/
          `-'
         O O
    )",
        R"(
         _,-._
        / \_/ \
       >-(_)-<
        \_/ \_/
          `-'
        O   O
    )",
        R"(
         _,-._
        / \_/ \
       >-(_)-<
        \_/ \_/
          `-'
       O     O
    )",
        R"(
         _,-._
        / \_/ \
      >-(_)-<
        \_/ \_/
          `-'
     O       O
    )",
        R"(
         _,-._
        / \_/ \
     >-(_)-<
        \_/ \_/
          `-'
   O         O
    )",
        R"(
         _,-._
        / \_/ \
    >-(_)-<
        \_/ \_/
          `-'
 O           O
    )",
        R"(
         _,-._
        / \_/ \
   >-(_)-<
        \_/ \_/
          `-'
O             O
    )",

    };

    int frameIndex = 0;
    while (true) {
        clearScreen();
        std::cout << frames[frameIndex] << std::endl;

        frameIndex = (frameIndex + 1) % frames.size();
        sleepMillis(100); // Adjust speed here

        if (kbhit()) { // Check for key press
            char c = getchar();
            if (c == 'q') { // Quit on 'q'
                break;
            }
        }
    }

    return 0;
}