
#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <iostream>
#include "LinkedList.h"
#include <vector>

class Player {
public:

    Player(std::string playerName);
    ~Player();

    std::string getPlayerName();
    int getPlayerScore();

    LinkedList* getPlayerHand();

    void setPlayerHand(LinkedList* playerHand); 

    void displayPlayerHand();

    void pickUpTiles(LinkedList* TileBag);

    bool hasTile(char letter);

    std::vector<std::string> getPlayerCommand(); 

    void updatePlayerScore(int scoreToAdd);

    void replaceTile(char letterToReplace, LinkedList* TileBag);

    int playerScore;

    int playerPassCount_TileBagEmpty;

    int getPlayerPassCount_TileBagEmpty();

    void updatePlayerPassCount(int pass_count);

private:
    std::string playerName;
    
    LinkedList* playerHand;

};



#endif // ASSIGN2_PLAYER_H