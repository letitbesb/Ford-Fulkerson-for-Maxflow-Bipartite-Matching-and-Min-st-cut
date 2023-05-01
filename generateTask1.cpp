#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

int main() {
    int N = 30;
    int E = 60;
    std::ofstream f("inputTask1.txt");

    if (f.is_open()) {
        f << N << '\n';
        f << E << '\n';

        std::srand(std::time(0));

        for (int i = 0; i < E; ++i) {
            int u = std::rand() % N;
            int v = std::rand() % N;
            while (u == v) {
                v = std::rand() % N;
            }
            int c = std::rand() % 100 + 1;
            f << u << ' ' << v << ' ' << c << '\n';
        }

        f.close();
    } else {
        std::cerr << "Unable to open file";
    }

    return 0;
}