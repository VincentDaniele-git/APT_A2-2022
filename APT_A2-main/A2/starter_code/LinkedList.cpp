
#include "LinkedList.h"
#include <stdexcept>
#include <iostream>
#include <ostream>

LinkedList::LinkedList() {
   head = nullptr;
}

LinkedList::LinkedList(LinkedList& other) {

}

LinkedList::~LinkedList() {
    clear();
}

int LinkedList::size(){
    
    int length = 0;

    Node* current = head;
    while(current != nullptr){
        ++length;
        current = current->next;
    }
    return length;
}

void LinkedList::add_back(Node* node){

    node->next = nullptr;

    if(head == nullptr){
        head = node;
    } 
    else {
        Node* current = head;

        while(current->next != nullptr){
            current = current->next;
        }
        current->next = node;
    }
}

void LinkedList::buildFromString(std::string playerHandStr) {
    std::string s = playerHandStr;
    std::string delimiter = ", ";

    size_t pos = 0;
    std::string token;

    int valueNumber_onedigit;
    int valueNumber_twodigits;

    std::string temp_s_onedigit;
    std::string temp_s_twodigits;

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);

        if (token.length() == 4 ) {
            char c1 = s[2];
            char c2 = s[3];

            temp_s_twodigits += c1;
            temp_s_twodigits += c2;
            valueNumber_twodigits = stoi(temp_s_twodigits);
            temp_s_twodigits = ""; //resetting the temp string for the next double digit

            Tile* tile = new Tile(s[0], valueNumber_twodigits);
            Node* node = new Node(tile, nullptr);
            add_back(node);
            s.erase(0, pos + delimiter.length());

            
        }
        else if (token.length() == 3) {
            char c3 = s[2];
            
            temp_s_onedigit += c3;

            valueNumber_onedigit = stoi(temp_s_onedigit);

            temp_s_onedigit = ""; //resetting the temp string for the next single digit

            Tile* tile = new Tile(s[0], valueNumber_onedigit);
            Node* node = new Node(tile, nullptr);
            add_back(node);
            s.erase(0, pos + delimiter.length());
            
        }
    }
    //Add the Final Tile leftover after while loop;

    token = s.substr(0, pos);

    if (token.length() == 4) {
        char c1 = s[2];
        char c2 = s[3];

        temp_s_twodigits += c1;
        temp_s_twodigits += c2;
        valueNumber_twodigits = stoi(temp_s_twodigits);
        temp_s_twodigits = ""; //resetting the temp string for the next double digit

        Tile* tile = new Tile(s[0], valueNumber_twodigits);
        Node* node = new Node(tile, nullptr);
        add_back(node);        
    }

    else if (token.length() == 3) {
        char c3 = s[2];
        
        temp_s_onedigit += c3;

        valueNumber_onedigit = stoi(temp_s_onedigit);
        temp_s_onedigit = ""; //resetting the temp string for the next single digit

        Tile* tile = new Tile(s[0], valueNumber_onedigit);
        Node* node = new Node(tile, nullptr);
        add_back(node);        
    }
}

void LinkedList::remove(int index){
    if(index >= 0 && index < size()){
        if(head != nullptr){
            int counter = 0;
            Node* current = head;
            //prev should point to node before current;
            Node* prev = nullptr;

            while(counter != index){
                ++counter;
                prev = current;
                current = current->next;
            }

            if(prev == nullptr){
                head = current->next;
            }else{
                prev->next = current->next;
            }

            delete current->tile;
            delete current;
        }
    }
}

void LinkedList::printLinkedList(int size) {
    Node* temp = head;
    int count = 0;
    if (temp != NULL) {
        while(temp != NULL) {
            if (count != size-1) {
                std::cout << temp->tile->getLetter() << "-";
                std::cout << temp->tile->getValue() << ", ";
            }
            else {
                std::cout << temp->tile->getLetter() << "-";
                std::cout << temp->tile->getValue() << std::endl; 
            }
            temp = temp->next;
            count++;
    }
        std::cout << std::endl;
    }
}

void LinkedList::printLinkedListToFile(int size, std::ostream& os) {
    Node* temp = head;
    int count = 0;
    if (temp != NULL) {
        while(temp != NULL) {
            if (count != size-1) {
                os << temp->tile->getLetter() << "-";
                os << temp->tile->getValue() << ", ";
            }
            else {
                os << temp->tile->getLetter() << "-";
                os << temp->tile->getValue() << std::endl; 
            }
            temp = temp->next;
            count++;
        }
    }
}




Tile* LinkedList::pickFromFront() {

    Tile* tilecopy = nullptr;

    if(head != nullptr){
        Tile* tile = head->tile;
        tilecopy = new Tile(*tile);

        Node* toDelete = head;
        head = head->next;
        delete toDelete->tile;
        delete toDelete;
    } 
   
    else {
       throw std::runtime_error("Nothing to remove");
    }
       
    return tilecopy;
}



// This method is to be able to just look at a tile without deleting and then moving to the next node.
bool LinkedList::lookForTile(char letter) {
    Node* current = head;
    while(current != NULL) {
        if (current->tile->getLetter() == letter) {
            return true;
        }
        current = current->next;
    }
    return false;
}

Tile* LinkedList::getTile(char letter) {
    Node* current = head;
    Node* prev = NULL;

    if (current != NULL && current->tile->getLetter() == letter) {
        head = current->next;
        return current->tile;
    }
    else {
        while(current != NULL && current->tile->getLetter() != letter) {
            prev = current;
            current = current->next;
        }
        prev->next = current->next;
        return current->tile;
    }
}

void LinkedList::remove_front(){
    if(head != nullptr){
        Node* toDelete = head;
        head = head->next;

        delete toDelete->tile;
        delete toDelete;
    } else{
        throw std::runtime_error("Nothing to remove");
    }

}


void LinkedList::clear(){

    while(head != nullptr){
        remove_front();
    }
}


