#include <iostream>
#include <sstream>
#include <vector>

#include "Player.h"

Player::Player(std::string playerName) {
    this->playerName = playerName;
    this->playerScore = 0;
    this->playerHand = new LinkedList();
    this->playerPassCount_TileBagEmpty = 0;
}

Player::~Player() {
    delete playerHand;
}

std::string Player::getPlayerName() {
    return this->playerName;
}

int Player::getPlayerPassCount_TileBagEmpty() {
    return this->playerPassCount_TileBagEmpty;
}

void Player::updatePlayerPassCount(int pass_count) {
    this->playerPassCount_TileBagEmpty = pass_count;
}


int Player::getPlayerScore() {
    return this->playerScore;
}

LinkedList* Player::getPlayerHand() {
    return this->playerHand;
}

void Player::setPlayerHand(LinkedList* playerHand) {
    this->playerHand = playerHand;
}

void Player::updatePlayerScore(int scoreToAdd) {
    this->playerScore += scoreToAdd;
}

void Player::pickUpTiles(LinkedList* TileBag) {
    while ((playerHand->size() < 7) && (TileBag->size() > 0)) {       
        Tile* currentTile = TileBag->pickFromFront();
        Tile* tile = new Tile(currentTile->getLetter(), currentTile->getValue());
        Node* node = new Node(tile, nullptr);
        playerHand->add_back(node);
    }
}

void Player::displayPlayerHand() {
    std::cout << "Your hand is " << std::endl;
    playerHand->printLinkedList(playerHand->size());
}


void Player::replaceTile(char letterToReplace, LinkedList* TileBag) {
    if (playerHand->lookForTile(letterToReplace)) {
        Tile* replaceTile = playerHand->getTile(letterToReplace);
        Node* node = new Node(replaceTile, nullptr);
        TileBag->add_back(node);
    }
    else {
        std::cout << "Invalid Input" << std::endl;
    }
}

std::vector<std::string> Player::getPlayerCommand() {
    std::string word;
    std::string command;
    std::cout << "> ";
    std::getline(std::cin, command); 
    std::vector<std::string> commandVec;

    if (!std::cin.eof()) {
        std::stringstream ss(command);
        while (ss >> word) {
            commandVec.push_back(word);
        }
        return commandVec;
    }
    
    std::cout << "Goodbye" << std::endl;
    return commandVec;

}


bool Player::hasTile(char letter) {
    if (playerHand->lookForTile(letter)) {
        return true;
    }
    return false;
}   