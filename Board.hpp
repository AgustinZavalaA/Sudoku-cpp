#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "Coordinate.hpp"

class Board {
   private:
    Coordinate c[81];
    int        posX, posY;
    int        difficulty;

   public:
    Board();
    ~Board();
    void display();
    void changePosX(int);
    void changePosY(int);
    void setCoord(int);
    bool checkRow();
    bool checkColumn();
    bool checkBox();
    void randomFill();
};

Board::Board() {
    posX       = 0;
    posY       = 0;
    difficulty = 10;
}

Board::~Board() {}

void Board::display() {
    std::cout << "\033[;34m    1 2 3   4 5 6   7 8 9\n\033[;37m\n";
    for (int i = 0; i < 9; i++) {
        std::cout << "\033[;34m" << i + 1 << "   \033[;37m";
        for (int j = 0; j < 9; j++) {
            if (posX == j && posY == i) {
                std::cout << "\033[1;31m\u25A0 \033[;37m";
            } else {
                if (c[i + 9 * j].getValid()) {
                    std::cout << c[i + 9 * j].getData() << " ";
                } else {
                    std::cout << "\033[1;31m" << c[i + 9 * j].getData()
                              << " \033[;37m";
                }
            }
            if ((j + 1) % 3 == 0 && j != 8) std::cout << "\033[;35m| \033[;37m";
        }
        std::cout << "  \033[;34m " << i + 1 << "\033[;37m";
        std::cout << "\n";
        if ((i + 1) % 3 == 0 && i != 8)
            std::cout << "\033[;35m    ---------------------\n\033[;37m";
    }

    std::cout << "\n\033[;34m    1 2 3   4 5 6   7 8 9\033[;37m";
}

void Board::changePosX(int x) {
    posX += x;
    if (posX > 8) posX = 0;
    if (posX < 0) posX = 8;
}
void Board::changePosY(int y) {
    posY += y;
    if (posY > 8) posY = 0;
    if (posY < 0) posY = 8;
}

void Board::setCoord(int x) {
    c[posY + posX * 9].setData(x);
    c[posY + posX * 9].setValid(checkBox() && checkRow() && checkColumn());
}

bool Board::checkRow() {
    int rowStart       = int(posX / 9) * 9;
    int repetition[10] = {0};
    for (int i = rowStart; i < rowStart + 9; i++) {
        repetition[c[posY + i * 9].getData()] += 1;
    }
    for (int i = 1; i < 10; i++) {
        if (repetition[i] > 1) return false;
    }
    return true;
}

bool Board::checkColumn() {
    int colStart       = int(posY / 9) * 9;
    int repetition[10] = {0};
    for (int i = colStart; i < colStart + 9; i++) {
        repetition[c[i + posX * 9].getData()] += 1;
    }
    for (int i = 1; i < 10; i++) {
        if (repetition[i] > 1) return false;
    }
    return true;
}

bool Board::checkBox() {
    int posStart       = int(posY / 3) * 27 + int(posX / 3) * 3;
    int repetition[10] = {0};
    for (int i = posStart; i < posStart + 3; i++) {
        repetition[c[i].getData()] += 1;
    }
    for (int i = posStart + 9; i < posStart + 9 + 3; i++) {
        repetition[c[i].getData()] += 1;
    }
    for (int i = posStart + 18; i < posStart + 18 + 3; i++) {
        repetition[c[i].getData()] += 1;
    }
    for (int i = 1; i < 10; i++) {
        if (repetition[i] > 1) return false;
    }
    return true;
}

void Board::randomFill() {
    srand(time(NULL));
    // for (int i = 0; i < 81; i++) {
    //    do {
    //        c[i].setData(rand() % 9 + 1);
    //        c[i].setValid(checkBox() && checkRow() && checkColumn());
    //    } while (!c[i].getValid());
    //}
    // for (posX = 0; posX < 9; posX++) {
    //    for (posY = 0; posY < 9; posY++) {
    //        // std::cout << posX << ":" << posY << " ";
    //        int i = 0;
    //        while (1) {
    //            c[posY + posX * 9].setData(rand() % 9 + 1);
    //            c[posY + posX * 9].setValid(checkBox() && checkRow//() &&
    //                                        checkColumn());
    //            std::cout << c[posY + posX * 9].getValid() << " ";
    //            if (c[posY + posX * 9].getValid()) break;
    //            i++;
    //            if (i > 9) {
    //                i = 0;
    //                // if (posY == 0)
    //                //    posX -= 1;
    //                // else
    //                //    posY -= 1;
    //                break;
    //            }
    //        }
    //    }
    //}
    // posX = 0;
    // posY = 0;
    std::vector<int> Available[81];
    for (int i = 0; i < 81; i++) {
        for (int j = 1; j < 10; j++) Available[i].push_back(j);
    }
    int i = 0;
    while (i < 81) {
        printf("%d\n", Available[i].size());
        if (Available[i].size()) {
            int random = rand() % Available[i].size();
            int numR   = Available[i].at(random);

            posX = int(i / 9);
            posY = i % 9;
            // setCoord(numR);

            c[i].setData(numR);
            c[i].setValid(checkBox() && checkRow() && checkColumn());
            printf("%d:%d %d %d\n", i, Available[i].size(), numR,
                   c[i].getValid());
            display();
            if (c[i].getValid()) {
                i++;
            }
            Available[i].erase(Available[i].begin() + random);

        } else {
            for (int j = 1; j < 10; j++) Available[i].push_back(j);
            // posX = int(i / 9);
            // posY = i % 9;
            // setCoord(0);
            c[i].setData(0);
            c[i].setValid(1);
            i -= 1;
        }
    }
}