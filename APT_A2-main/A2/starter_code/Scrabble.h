#ifndef ASSIGN2_SCRABBLE_H
#define ASSIGN2_SCRABBLE_H

#include "LinkedList.h"
#include "Player.h"
#include "Board.h"



#include <iostream>
#include <ostream>
#include <fstream>
#include <memory>
#include <random>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <vector>
#include <chrono>


class Scrabble {

public:
    Scrabble();
    ~Scrabble();
    Scrabble(Board* board, LinkedList* TileBag, std::shared_ptr<Player> currentPlayer, std::shared_ptr<Player> player1, std::shared_ptr<Player> player2);
    void setPlayer1(std::shared_ptr<Player> player1);
    void setPlayer2(std::shared_ptr<Player> player2);
    void setBoard(Board* board);
    void setCurrentPlayer(std::shared_ptr<Player> currentPlayer);
    void setTileBag(LinkedList* TileBag);
    void playGame();
    bool playerTurn(std::vector<std::string> commandVec, Board* board, LinkedList* TileBag, std::shared_ptr<Player> currentPlayer, std::shared_ptr<Player> player1, std::shared_ptr<Player> player2, bool gameRunning, int pass_counter);
    void BINGO(std::shared_ptr<Player> currentPlayer, Board* board);
    void GameOver(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2);

private:
    std::vector<std::string> commandVec;
    Board* board;
    LinkedList* TileBag;
    std::shared_ptr<Player> currentPlayer;
    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;
};

#endif // ASSIGN2_SCRABBLE_H