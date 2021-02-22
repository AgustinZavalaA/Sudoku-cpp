#include "Board.hpp"

class Sudoku {
   private:
    Board b;

   public:
    Sudoku();
    ~Sudoku();
    void play();
};

Sudoku::Sudoku() {}

Sudoku::~Sudoku() {}

void Sudoku::play() {
    char opt;
    b.randomFill();
    while (1) {
        // std::cout << "\033[2J";
        b.display();
        std::cout << "\n[Q] Quit [R] Restart [H,J,K,L] Move [X] Delete\n";
        std::cin >> opt;
        opt = std::toupper(opt);
        if (opt == 'Q') break;
        if (std::isdigit(opt)) {
            b.setCoord(opt - '0');
        } else {
            switch (opt) {
                case 'R':
                    // Restart
                    break;
                case 'X':
                    // set data to 0
                    break;
                case 'H':
                    b.changePosX(-1);
                    break;
                case 'J':
                    b.changePosY(1);
                    break;
                case 'K':
                    b.changePosY(-1);
                    break;
                case 'L':
                    b.changePosX(1);
                    break;

                default:
                    // Debug
                    // printf(b.checkRow() ? "R1" : "R0");
                    // printf(b.checkColumn() ? "C1" : "C0");
                    // printf(b.checkBox() ? "B1" : "B0");
                    // int basura;
                    // scanf("%d", &basura);
                    break;
            }
        }
    }
}