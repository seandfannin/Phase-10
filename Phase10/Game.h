#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include <algorithm>
#include "Deck.h"
#include <stack>
#include "Card.h"
using namespace std;

class Game{
private:
    PhaseDeck newDeck;
    vector<PhaseCard> player1;
    vector<PhaseCard> player2;
    int points1;
    int points2;
    stack<PhaseCard> discardPile;
    int player1Phase;
    int player2Phase;

public:
        Game(int phase1, int phase2){
      discardPile.push(newDeck.deal());
      points1= 0;
      points2= 0;
      player1Phase = phase1;
      player2Phase = phase2;
    }
    void printDeck(PhaseDeck deck){
        for(int i = 0; i < deck.getSize(); i++){
            cout << deck.getCardAt(i).toString() << endl;
        }
    }
    void deal(vector<PhaseCard>& hand,PhaseDeck& deck){
        for(int i = 0; i < 10; i++){
            hand.push_back(deck.deal());
        }
    }
    vector<PhaseCard> getHand1(){
            return player1;
        }//returns the hand of player 1
    vector<PhaseCard> getHand2(){
            return player2;
    }//gets the hand of player 2
    void draw1(){
        player1.push_back(newDeck.deal());
    }//player 1 draws from the deck

    void draw2(){
        player2.push_back(newDeck.deal());
    }//player 2 draws from the deck
  /*  void drawFromDiscard1(){
        PhaseCard tempcard = discardPile.pop();
        player1.push_back(tempcard);
    }*/

    void player1Discard(int location){
       PhaseCard temp = player1.at(location);
       player1.erase(player1.begin()+location -1);
       discardPile.push(temp);//the discard pile
    }

    void player2Discard(int location){
       PhaseCard temp = player2.at(location);
       player2.erase(player2.begin()+location -1);
       discardPile.push(temp);//the discard pile
    }

    PhaseCard getDiscardPile(){
        return discardPile.top();
    }


};
#endif // GAME_H
