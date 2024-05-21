#ifndef PHASE10LIST_H
#define PHASE10LIST_H

#include "Node.h"
#include <stdexcept>

/*
Modify all of this to include prev
and take advantage of it where possible
to make things more efficient.
*/

class myList{
private:
    Node* head;
    Node* tail;
    Node* current;
    int length;

public:
    myList(){
        head = nullptr;
        tail = nullptr;
        current = nullptr;
        length = 0;
    }

    void prepend(int item){
        if(head == nullptr){
            head = new Node(item, nullptr, nullptr);
            tail = head;
        }
        else{
            Node* temp = new Node(item, nullptr, head);
            head->setPrev(temp);
            head = temp;
        }
        length++;
    }

    void append(int item){
        if(head == nullptr){
            head = new Node(item, nullptr, nullptr);
            tail = head;
        }
        else{
            if(tail == nullptr){
                throw std::runtime_error("Tail is null!");
            }
            else{
                tail->setNext(new Node(item, tail, nullptr));
                tail = tail->getNext();
            }
        }
        length++;
    }

    void start(){
        current = head;
    }

    void end(){
        current = tail;
    }

    void next(){
        if(current == nullptr){
            throw std::runtime_error("Current is null!");
        }
        else{
            current = current->getNext();
        }
    }

    void previous(){
        if(current == nullptr){
            throw std::runtime_error("Current is null!");
        }
        else{
            current = current->getPrev();
        }
    }


    void insertAfter(int item){
        if(current == nullptr){
            throw std::runtime_error("Current is null!");
        }
        else{
            Node* toInsert = new Node(item, current->getPrev(), current->getNext());
            current->setNext(toInsert);

            if(current == tail){
                tail = current->getNext();
            }
        }
    }

    int removeCurrent(){
        if(current == nullptr){
            throw std::runtime_error("Current is null");
        }
        else{
            Node* toDelete = current;
            Node* toDeleteNext = current->getNext();
            int returnValue = current->getInfo();

            if(current == head){
                head = toDeleteNext;
                current = head;
            }
            else{
                previous();
                current->setNext(toDeleteNext);
            }

            if(toDelete == tail){
                tail = current;
            }

            delete toDelete;
            toDelete = nullptr;

            length--;
            return returnValue;
        }
    }

    int getLength(){
        return length;
    }

    int getCurrentValue(){
        if(current == nullptr){
            throw std::runtime_error("Current is null");
        }
        else{
            return current->getInfo();
        }
    }

    void setValueAt(int position, int value){
        if(head == nullptr){
            throw std::runtime_error("Head is null");
        }
        else{
            Node* temp = head;
            int count = 0;
            while(temp != nullptr and count < position){
                temp = temp->getNext();
                count++;
            }
            if(temp == nullptr){
                throw std::runtime_error("No such position in list");
            }
            else{
                temp->setInfo(value);
            }
        }
    }

    void reverse(){
        Node* Previous = nullptr;
        Node* Current = head;
        Node* next = nullptr;
        tail = head;
        while(Current != nullptr){
            next = Current->getNext();
            Current->setNext(Previous);
            Current->setPrev(next);
            Previous = Current;
            Current = next;
        }
        head = Previous;
    }

    ~myList(){
        Node* temp;
        while(head != nullptr){
            temp = head;
            head = head->getNext();

            delete temp;
        }
        current = nullptr;
        tail = nullptr;
    }
};

#endif // PHASE10LIST_H
