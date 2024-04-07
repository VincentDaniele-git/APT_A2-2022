
#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include <iostream>
#include "Tile.h"
#include <vector>
#include <ostream>

class Board {
public:

    Board();
    ~Board();

    void printBoard();
    void printBoardToFile(std::ostream& os);
    void addToBoard(Tile* letter, int row, int col);
    bool checkFreeTile(int row, int col);


private:

  std::vector<std::vector<Tile*> > board;
  
  // std::vector<std::vector<std::string>> board;
  // char grid_letter = 'A';

};



#endif // ASSIGN2_BOARD_H