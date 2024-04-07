#include "Scrabble.h"

#include <iostream>



Scrabble::Scrabble() {

}

Scrabble::~Scrabble() {
   delete this->TileBag;
   delete this->board;
}


Scrabble::Scrabble(Board* board, LinkedList* TileBag, std::shared_ptr<Player> currentPlayer, std::shared_ptr<Player> player1, std::shared_ptr<Player> player2) {
    this->board = board;
    this->TileBag = TileBag;
    this->currentPlayer = currentPlayer;
    this->player1 = player1;
    this->player2 = player2;
}

void Scrabble::setPlayer1(std::shared_ptr<Player> player1) {
   this->player1 = player1;
}

void Scrabble::setPlayer2(std::shared_ptr<Player> player2) {
   this->player2 = player2;
}

void Scrabble::setBoard(Board* board) {
   this->board = board;
}

void Scrabble::setCurrentPlayer(std::shared_ptr<Player> currentPlayer) {
   this->currentPlayer = currentPlayer;
}

void Scrabble::setTileBag(LinkedList* TileBag) {   
   this->TileBag = TileBag;
}

void Scrabble::GameOver(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2) {

   std::cout << "Game over" << std::endl;
   std::cout << "Score for " << player1->getPlayerName() << ": " << player1->getPlayerScore() << std::endl;
   std::cout << "Score for " << player2->getPlayerName() << ": " << player2->getPlayerScore() << std::endl;

   if (player1->getPlayerScore() > player2->getPlayerScore()) {
      std::cout << "Player " << player1->getPlayerName() << " " << "won!" << std::endl;
   }
   else if (player1->getPlayerScore() == player2->getPlayerScore()) {
      std::cout << "Players " << player1->getPlayerName() << " " << player1->getPlayerName() << " tie!" << std::endl;
   }
   else if (player1->getPlayerScore() < player2->getPlayerScore()) {
      std::cout << "Player " << player2->getPlayerName() << " " << "won!" << std::endl;
   }

   std::cout << std::endl;

}


void Scrabble::playGame() {
   std::cin.get() ;
//Initial hand for Player 1
   player1->pickUpTiles(TileBag);
   player2->pickUpTiles(TileBag);

   bool player1Turn;
   if (currentPlayer == player1) {
      player1Turn = true;
   }
   else {
      player1Turn = false;
   }

   bool gameRunning = true;
   std::vector<std::string> commandVec;

   
   while (gameRunning) {

      //Player 1 Turn
      if (player1Turn) {
         std::cout << std::endl;
         std::cout << player1->getPlayerName() << ", it's your turn!" << std::endl;
         std::cout << "Score for " << player1->getPlayerName() << ": " << player1->getPlayerScore() << std::endl;
         std::cout << "Score for " << player2->getPlayerName() << ": " << player2->getPlayerScore() << std::endl;
         board->printBoard();
         player1->displayPlayerHand();
         commandVec = player1->getPlayerCommand();
         int p1_pass_counter = player1->getPlayerPassCount_TileBagEmpty();
         gameRunning = playerTurn(commandVec, board, TileBag, player1, player1, player2, gameRunning, p1_pass_counter);

         if ((TileBag->size() == 0) && (player1->getPlayerPassCount_TileBagEmpty() == 2)) {
            GameOver(player1, player2);
            gameRunning = false;
         }
         if ((TileBag->size() == 0) && (player1->getPlayerHand()->size() == 0)) {
            GameOver(player1, player2);
            gameRunning = false;
         }
         player1->pickUpTiles(TileBag);
      }

      //Player 2 Turn
      else {
         std::cout << std::endl;
         std::cout << player2->getPlayerName() << ", it's your turn!" << std::endl;
         std::cout << "Score for " << player1->getPlayerName() << ": " << player1->getPlayerScore() << std::endl;
         std::cout << "Score for " << player2->getPlayerName() << ": " << player2->getPlayerScore() << std::endl;
         board->printBoard();
         player2->displayPlayerHand();
         commandVec = player2->getPlayerCommand();
         int p2_pass_counter = player2->getPlayerPassCount_TileBagEmpty();
         gameRunning = playerTurn(commandVec, board, TileBag, player2, player1, player2, gameRunning, p2_pass_counter);

         if ((TileBag->size() == 0) && (player2->getPlayerPassCount_TileBagEmpty() == 2)) {
            GameOver(player1, player2);
            gameRunning = false;
         }

         if ((TileBag->size() == 0) && (player2->getPlayerHand()->size() == 0)) {
            GameOver(player1, player2);
            gameRunning = false;
         }

         player2->pickUpTiles(TileBag);
      }
      player1Turn = !player1Turn;
   }
}


bool Scrabble::playerTurn(std::vector<std::string> commandVec, Board* board, LinkedList* TileBag, std::shared_ptr<Player> currentPlayer, std::shared_ptr<Player> player1, std::shared_ptr<Player> player2, bool gameRunning, int pass_counter) {
  
   while (commandVec[0] != "quit") {
      while (commandVec[0] != "save") {
         if (commandVec[0] == "place" && commandVec[1] != "\0") {
            // std::cout << "test1" << std::endl;
            if (commandVec[2] == "\0" || commandVec[3] == "\0") {
               std::cout << "Invalid Input" << std::endl;
               commandVec.clear();
               commandVec = currentPlayer->getPlayerCommand();
            }
            //Initialise how many tiles placed during this turn
            int num_tile_placed_counter = 0;
            while (commandVec[2] != "\0" && commandVec[3] != "\0") {
               // std::cout << "test2" << std::endl;
               while (commandVec[1] != "Done" && commandVec[0] != "quit") {
                     int positionLetter = commandVec[3][0] - 'A'; 
                     int positionNumber = (int)(commandVec[3][1]) - 48; 
                     if (commandVec[3][2] != '\0') {
                        char c1 = commandVec[3][1];
                        char c2 = commandVec[3][2];
                        std::string s;
                        s += c1;
                        s += c2;
                        positionNumber = stoi(s);
                     }
                     
                     if (positionNumber < 0 || positionNumber > 14) {
                           std::cout << "Invalid Input" << std::endl;
                     }
                     else {
                           if (currentPlayer->hasTile(commandVec[1][0])) {               
                              if (board->checkFreeTile(positionLetter, positionNumber)) {
                              Tile* tileToAdd = currentPlayer->getPlayerHand()->getTile(commandVec[1][0]);
                              board->addToBoard(tileToAdd, positionLetter, positionNumber);
                              currentPlayer->updatePlayerScore(tileToAdd->getValue());
                              num_tile_placed_counter += 1;
                              }
                              if ((currentPlayer->getPlayerHand()->size() == 0) && (num_tile_placed_counter == 7)) {
                                 std::cout << std::endl;
                                 std::cout << "BINGO!!!" << std::endl;
                                 std::cout << std::endl;
                                 currentPlayer->updatePlayerScore(50) ;
                                 return true;
                              }
                           }
                           else {
                              std::cout << "Invalid Input Dont have letter" << std::endl;
                           }
                     }
                     if (currentPlayer->getPlayerHand()->size() == 0) {
                        return false;
                     }
                     commandVec.clear();
                     commandVec = currentPlayer->getPlayerCommand();
                     
                  }
                  if (commandVec[1] == "Done") {
                  //TO IMPLEMENT CheckIfLegalMove()
                  return true;
               }
            }
            if (commandVec[0] == "quit") {
               return false;
            }
            if (commandVec[1] == "Done") {
                  //TO IMPLEMENT CheckIfLegalMove()
                  return true;
               }
         }

         else if (commandVec[0] == "replace") {
            char letterToReplace = commandVec[1][0];
            currentPlayer->replaceTile(letterToReplace, TileBag);
            currentPlayer->displayPlayerHand();
            currentPlayer->pickUpTiles(TileBag);
            return true;
         }
         

         else if (commandVec[0] == "pass") {

            if (TileBag->size() == 0) {
               pass_counter += 1;
               currentPlayer->updatePlayerPassCount(pass_counter);
            }
            return true;
         }

         else {
            std::cout << "Invalid Input. (pass, replace, place, place Done, quit only)" << std::endl; 
            commandVec.clear();
            commandVec = currentPlayer->getPlayerCommand();
            if (commandVec[0] == "quit") {
               return false;
            }
         }
      }

      if (commandVec[0] == "save") {

         std::ofstream saveFile;

         saveFile.open(commandVec[1]);

         //Store Player 1 
         saveFile << player1->getPlayerName() << std::endl;
         saveFile << player1->getPlayerScore() << std::endl;
         player1->getPlayerHand()->printLinkedListToFile(player1->getPlayerHand()->size(), saveFile); // printing out a std::endl

         //Store Player 2
         saveFile << player2->getPlayerName() << std::endl;   
         saveFile << player2->getPlayerScore() << std::endl;
         player2->getPlayerHand()->printLinkedListToFile(player2->getPlayerHand()->size(), saveFile); // printing out a std::endl
         
         //Store Board
         board->printBoardToFile(saveFile);
         
         //Store TileBag
         if (TileBag->size() == 0) {
            saveFile << "EMPTY" << std::endl;
         }
         else {
         TileBag->printLinkedListToFile(TileBag->size(), saveFile); // printing out a std::endl
         }

         //Store Current Player Name:
         saveFile << currentPlayer->getPlayerName() << std::endl;

         //Close File
         saveFile.close();

         std::cout << "Game saved successfully" << std::endl;
         
         // Game continues for the same player; and new command is asked for.
         commandVec.clear();
         commandVec = currentPlayer->getPlayerCommand();
      }
   }  
      return false;
}






