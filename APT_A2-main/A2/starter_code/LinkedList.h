
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <ostream>

class LinkedList {
public:

   LinkedList();
   LinkedList(LinkedList& other);
   ~LinkedList();

   void add_back(Node* node);
   void remove(int index);
   void clear();
   void remove_front();

   void printLinkedList(int size);
   void printLinkedListToFile(int size, std::ostream& os);
   Tile* getTile(char letter);

   Tile* pickFromFront();
   bool lookForTile(char letter);

   void buildFromString(std::string playerHandStr);

   int size();

private:
   Node* head;
};

#endif // ASSIGN2_LINKEDLIST_H
