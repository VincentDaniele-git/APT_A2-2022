
#include "Board.h"

#define BOARD_DIM 15

Board::Board() {

    // Initializing a single row
    //     std::vector<Tile*> row(BOARD_DIM, new Tile(' ', 0));
 
    // // Initializing the 2-D vector
    //     std::vector<std::vector<Tile*> > vectorname(BOARD_DIM, row);

    std::vector<std::vector<Tile*> > vectorName(BOARD_DIM, std::vector<Tile*>(BOARD_DIM));
    for (int i=0; i<BOARD_DIM; ++i){
        for (int j=0; j<BOARD_DIM; ++j) {
            vectorName[i][j] = new Tile(' ', 0);
        }
    }
        this->board = vectorName;
}


void Board::addToBoard(Tile* letter, int row, int col) {
        this->board[row][col] = letter;
}

bool Board::checkFreeTile(int row, int col) {
    if (this->board[row][col]->getLetter() == ' ') {
        return true;
    }
    else {
        std::cout << "Invalid Input" << std::endl;
        return false;
    }
}

void Board::printBoard() {

    char grid_letter = 'A';

    std::cout << "    0   1   2   3   4   5   6   7   8   9   10  11  12  13  14" << std::endl;
    std::cout << "  -------------------------------------------------------------" << std::endl;
       
    for (int row = 0; row < BOARD_DIM; row++) {
        
        std::cout << grid_letter;
        std::cout << " | ";

        grid_letter += 1;
        for (int col = 0; col < BOARD_DIM; col++) {
            std::cout << this->board[row][col]->getLetter();
            std::cout << " | ";
        }
        std::cout << "\n";
    }
}

void Board::printBoardToFile(std::ostream& os) {

    char grid_letter = 'A';

    os << "    0   1   2   3   4   5   6   7   8   9   10  11  12  13  14" << std::endl;
    os << "  -------------------------------------------------------------" << std::endl;
       
    for (int row = 0; row < BOARD_DIM; row++) {
        
        os << grid_letter;
        os << " | ";

        grid_letter += 1;
        for (int col = 0; col < BOARD_DIM; col++) {
            os << this->board[row][col]->getLetter();
            os << " | ";
        }
        os << "\n";
    }
}
Board::~Board() {
    for (int row = 0; row < BOARD_DIM; row++) {
        for (int col = 0; col < BOARD_DIM; col++) {
            if (this->board[row][col] != nullptr){
                delete this->board[row][col];
            }
        }
    }
}

