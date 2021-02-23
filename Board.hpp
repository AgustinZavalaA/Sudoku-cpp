#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "Coordinate.hpp"

class Board {
   private:
    Coordinate       c[81];
    int              posX, posY;
    int              difficulty;
    std::vector<int> hide;  //[1,81,5,65]

   public:
    Board();
    ~Board();
    void display();
    void changePosX(int);
    void changePosY(int);
    void changeDiff(int);
    void setCoord(int);
    bool checkRow();
    bool checkColumn();
    bool checkBox();
    bool randomFill(int);
    void hideC();
    void help();
    bool win();
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
                // Imprime el cuadrito
                std::cout << "\033[1;31m\u25A0 \033[;37m";
            } else {
                // Si el numero es valido lo imprime normal
                if (c[i + 9 * j].getValid()) {
                    // Obtiene la visibilidad
                    // 1 es No visible
                    // 2 es
                    switch (c[i + 9 * j].getVisibility()) {
                        case 1:
                            std::cout << "  ";
                            break;
                        case 2:
                            std::cout << "\033[1;93m" << c[i + 9 * j].getData()
                                      << " \033[;37m";
                            break;
                        case 3:
                            std::cout << "\033[1;96m" << c[i + 9 * j].getData()
                                      << " \033[;37m";
                            break;
                        default:
                            std::cout << "\033[1;92m" << c[i + 9 * j].getData()
                                      << " ";
                            break;
                    }
                } else {
                    // de lo contrario lo imprime rojo
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

void Board::changeDiff(int d) { difficulty = (d > 80 || d < 0) ? 10 : d; }

void Board::setCoord(int x) {
    if (x != 0) {
        c[posY + posX * 9].setData(x);
        c[posY + posX * 9].setVisibility(0);
        c[posY + posX * 9].setValid(checkBox() && checkRow() && checkColumn());
    } else {
        c[posY + posX * 9].setData(x);
        c[posY + posX * 9].setVisibility(1);
        c[posY + posX * 9].setValid(checkBox() && checkRow() && checkColumn());
    }
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
    int posStart       = int(posX / 3) * 27 + int(posY / 3) * 3;
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

bool Board::randomFill(int idx) {
    srand((int)time(0));
    // caso base
    if (idx == 81) return true;
    // vector de posibilidades
    std::vector<int> posi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    while (posi.size()) {
        int ran  = rand() % posi.size();
        int nRan = posi.at(ran);

        posX = int(idx / 9);
        posY = idx % 9;

        setCoord(nRan);
        c[idx].setVisibility(2);
        // display();
        if (c[idx].getValid()) {
            if (randomFill(idx + 1)) return true;
        }
        setCoord(0);
        posi.erase(posi.begin() + ran);
    }
    return false;
}

bool existInVector(std::vector<int> h, int r) {
    for (int v : h) {
        if (v == r) return true;
    }
    return false;
}

void Board::hideC() {
    srand((int)time(0));
    // generar una lista con numeros unicos a eliminar
    hide.clear();
    for (int i = 0; i < difficulty; i++) {
        int ran = rand() % 81;
        while (existInVector(hide, ran)) {
            ran = rand() % 81;
        }
        hide.push_back(ran);
    }
    // for (int v : hide) std::cout << v << " ";
    for (int v : hide) {
        c[v].setVisibility(1);
    }
}

void Board::help() {
    srand((int)time(0));
    int ran = rand() % hide.size();
    c[hide.at(ran)].setVisibility(3);
    hide.erase(hide.begin() + ran);
}

bool Board::win() {
    if (hide.size() == 0) return true;
    for (int v : hide)
        if (c[v].getVisibility() == 1 || !c[v].getValid()) return false;
    return true;
}