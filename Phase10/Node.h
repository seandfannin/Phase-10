#ifndef NODE_H
#define NODE_H
#include "Card.h"

class Node{
private:
    PhaseCard info;
    Node* next;
    Node* prev;

public:
    Node(PhaseCard info, Node* prev, Node* next){
        this -> info= info;
        this -> prev = prev;
        this -> next = next;
    }

    void setInfo(PhaseCard info){
        this ->info= info;
    }

    PhaseCard getInfo(){
        return info;
    }

    void setNext(Node* next){
        this ->next = next;
    }
    void setPrev(Node* prev){
        this-> prev = prev;
    }

    Node* getNext(){
        return next;
    }
    Node* getPrev(){
        return prev;
    }
};

#endif // NODE_H
