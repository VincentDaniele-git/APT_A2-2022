
#include "LinkedList.h"
#include "Player.h"
#include "Board.h"
#include "Scrabble.h"


#include <iostream>
#include <sstream>
#include <string>
#include <ostream>
#include <fstream>
#include <memory>
#include <random>
#include <cctype>
#include <algorithm>
#include <vector>
#include <chrono>

#define EXIT_SUCCESS 0


bool displayMenu();
bool containsOnlyUpperLetters(std::string &playerName);


bool containsOnlyUpperLetters(std::string &playerName) {
   return playerName.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos;
}

void startNewGame() {
   std::cout << std::endl;
   std::cout << "Starting a New Game" << std::endl;
   std::cout << std::endl;

   std::string playerName; 

   std::cout << "Enter a name for player 1 (uppercase characters only)" << std::endl;
   std::cout << "> ";
   

   std::cin >> playerName; 

   if (!std::cin.eof()) {

      //check playerName is only uppercase letters.
      while (!containsOnlyUpperLetters(playerName) && !std::cin.eof()) {
         std::cout << "Invalid Input" << std::endl;
         std::cout << "> ";
         std::cin >> playerName;
      }

      std::shared_ptr<Player> player1 = std::make_shared<Player>(playerName);


      std::cout << "Enter a name for player 2 (uppercase characters only)" << std::endl;
      std::cout << "> ";
      std::cin >> playerName;

      if (!std::cin.eof()) {

      //check playerName is only uppercase letters.
         while (!containsOnlyUpperLetters(playerName) && !std::cin.eof()) {
            std::cout << "Invalid Input" << std::endl;
            std::cout << "> ";
            std::cin >> playerName;
         }
         std::shared_ptr<Player> player2 = std::make_shared<Player>(playerName);



         std::cout << std::endl;
         std::cout << "Let's Play!" << std::endl;
         std::cout << std::endl;

         Board* board = new Board();

         
         LinkedList* TileBag = new LinkedList();

         std::ifstream infile("ScrabbleTiles.txt");

         char letter;
         int value;
         int count = 0;

         Tile *randomArray[98];
         unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
         std::default_random_engine e(seed);
         while (infile >> letter >> value) {
            Tile* tile = new Tile(letter, value);
            randomArray[count] = tile;
            count++;
         }
         std::shuffle(std::begin(randomArray), std::end(randomArray), e);
         for (int i = 0; i < 98; ++i) {
            Node* node = new Node(randomArray[i], nullptr);
            TileBag->add_back(node);
         }


         while (infile >> letter >> value) {
            Tile* tile = new Tile(letter, value);
            Node* node = new Node(tile, nullptr);
            TileBag->add_back(node);
         }


         Scrabble* scrabbleGame = new Scrabble(board, TileBag, player1, player1, player2);
         scrabbleGame->playGame();

         delete scrabbleGame;
      }
   }

   std::cout << "Goodbye" << std::endl;

}

void showCredits() {
   std::cout << "----------------------------------" << std::endl;

   std::string studentName;
   std::string studentID;

   studentName = "Vincent Daniele";
   studentID = "s3780417";
   std::cout << "Name: " << studentName << std::endl;
   std::cout << "Student ID: " << studentID << std::endl;
   std::cout << "Email: " << studentID << "@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;

   studentName = "Angeline Zhang";
   studentID = "s3905135";
   std::cout << "Name: " << studentName << std::endl;
   std::cout << "Student ID: " << studentID << std::endl;
   std::cout << "Email: " << studentID << "@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;

   studentName = "Bryan Hong";
   studentID = "s3679989";
   std::cout << "Name: " << studentName << std::endl;
   std::cout << "Student ID: " << studentID << std::endl;
   std::cout << "Email: " << studentID << "@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;

   std::cout << "----------------------------------" << std::endl;

   
   displayMenu();
}


void loadGame() {
   
      std::string savedGame;

      std::cout << std::endl;
      std::cout << "Enter the file name from which to load a game" << std::endl;
      std::cout << "> ";

      std::cin >> savedGame;

      if (!std::cin.eof()) {

         std::ifstream loadFile;

         loadFile.open(savedGame, std::ios::in);
         while (!loadFile) {
            std::cout << "Invalid Input" << std::endl;
            std::cout << "> ";
            std::cin >> savedGame;
            loadFile.open(savedGame, std::ios::in);
         }
         std::string player1NameStr;
         std::string player1ScoreStr;
         std::string player1HandStr;
         
         std::string player2NameStr;
         std::string player2ScoreStr;
         std::string player2HandStr;

         

         if (loadFile.is_open()) {
            std::getline(loadFile, player1NameStr);
            std::getline(loadFile, player1ScoreStr);
            std::getline(loadFile, player1HandStr);
            std::getline(loadFile, player2NameStr);
            std::getline(loadFile, player2ScoreStr);
            std::getline(loadFile, player2HandStr);

         }
         std::shared_ptr<Player> player1 = std::make_shared<Player>(player1NameStr);
         int player1Score = stoi(player1ScoreStr);
         player1->updatePlayerScore(player1Score);
         LinkedList* player1Hand = new LinkedList();
         player1Hand->buildFromString(player1HandStr); 
         player1->setPlayerHand(player1Hand);


         std::shared_ptr<Player> player2 = std::make_shared<Player>(player2NameStr);
         int player2Score = stoi(player2ScoreStr);
         player2->updatePlayerScore(player2Score);
         LinkedList* player2Hand = new LinkedList();
         player2Hand->buildFromString(player2HandStr); 
         player2->setPlayerHand(player2Hand);  

         Board* loadBoard = new Board();
         std::string s;
         std::getline(loadFile, s);
         std::getline(loadFile, s);


         for (int i=0; i<15; ++i) {
               std::getline(loadFile, s); 
               s.erase(0, 1);
               std::string delimiter = " | ";

               size_t pos = 0;
               std::string token;
               int column = -1;
               while ((pos = s.find(delimiter)) != std::string::npos) {
                  token = s.substr(0, pos);
                  Tile* tile = new Tile(s[0], 0);
                  loadBoard->addToBoard(tile, i, column);
                  s.erase(0, pos + delimiter.length());
                  column++;
            }
         }


         std::string loadTileBagStr;
         std::getline(loadFile, loadTileBagStr);

         LinkedList* loadTileBag = new LinkedList();
         loadTileBag->buildFromString(loadTileBagStr); 
   
         std::string currentPlayerStr;
         std::getline(loadFile, currentPlayerStr);
         
         std::shared_ptr<Player> currentPlayer;
         if (currentPlayerStr == player1NameStr) {
            currentPlayer = player1;
         }
         else {
            currentPlayer = player2;
         }

         Scrabble* loadScrabble = new Scrabble(loadBoard, loadTileBag, currentPlayer, player1, player2);

         std::cout << std::endl;
         std::cout << "Scrabble game successfully loaded" << std::endl;

         loadScrabble->playGame();

         delete loadScrabble;
      }
      
      std::cout << "Goodbye" << std::endl;

   }




int getIntValueFrom1to4() {
    int  input;
    bool notDone = true;
    while(notDone && (!std::cin.eof())) {
        std::string line;
        std::getline(std::cin, line);

        std::istringstream is(line);

        char empty = '\0';

         //if (Not an Integer || is whitespace or is null) || or is less than 1 || or is more than 4) 
         if (!std::cin.eof()) {
            if ( !(is >> input) ||  (is >> std::ws && is.get(empty)) ||  (input < 1) || (input > 4)) {
               std::cout << "Invalid Input. Integer (1-4) Only. \n";
               std::cout << "> ";   
            }
            else
               notDone = false ;
         }
         else {
            std::cout << "Goodbye" << std::endl;
         }
    }
    
    return input;
}



bool displayMenu() {
   
   std::cout << "Menu" << std::endl;
   std::cout << "----" << std::endl;

   std::cout << "1. New Game" << std::endl;
   std::cout << "2. Load Game" << std::endl;
   std::cout << "3. Credits (Show student information)" << std::endl;
   std::cout << "4. Quit" << std::endl;

   std::cout << "> ";   
   
   // Only accepts integers from 1 to 4;
   int input = getIntValueFrom1to4();

   if (input == 1) {
      startNewGame();
      return false;         
   }
   else if (input == 2) {
      loadGame();  
      return false;      
   }
   else if (input == 3) {
      showCredits();
      return true; 
   }
   else if (input == 4) {
      std::cout << "Goodbye" << std::endl; 
      return false;
   }
   else {
      return false;
   }
}



int main(void) {

   //Start Game
   std::cout<<std::endl;
   std::cout << "Welcome to Scrabble!" << std::endl;
   std::cout << "-------------------" << std::endl;

   //Display Menu
   
   displayMenu();

   return EXIT_SUCCESS;
}
