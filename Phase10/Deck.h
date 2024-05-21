#ifndef DECK_H
#define DECK_H

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include "Card.h"

class PhaseDeck{
private:

private:
    std::vector<PhaseCard> Deck;

public:
    PhaseDeck(){
        Deck.reserve(108);

        Deck.push_back(PhaseCard(0,0));
        Deck.push_back(PhaseCard(0,0));
        Deck.push_back(PhaseCard(0,0));
        Deck.push_back(PhaseCard(0,0));
        Deck.push_back(PhaseCard(0,0));
        Deck.push_back(PhaseCard(0,0));
        Deck.push_back(PhaseCard(0,0));
        Deck.push_back(PhaseCard(0,0));
        Deck.push_back(PhaseCard(1,13));
        Deck.push_back(PhaseCard(2,13));
        Deck.push_back(PhaseCard(3,13));
        Deck.push_back(PhaseCard(4,13));

        for(int c = 1; c <= 2; c++){
            for(int i = 1; i <= 4; i++){
                for(int j = 1; j <= 12; j++){
                    Deck.push_back(PhaseCard(i,j));
                }
            }
        }
    }

    int getSize(){
        return Deck.size();
    }

    PhaseCard getCardAt(int i){
        if(i < 0 or i > Deck.size()){
            throw std::invalid_argument("Invalid position");
        }
        return Deck.at(i);
    }

    PhaseCard deal(){
        PhaseCard temp = Deck.back();
        Deck.pop_back();
        return temp;
    }

    void shuffle(){
        std::mt19937 ran( time ( nullptr ) );

        std::shuffle(Deck.begin(), Deck.end(), ran);
    }
};

#endif // DECK_H
