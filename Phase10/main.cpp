#include <iostream>
#include <vector>
#include <algorithm>
#include "Deck.h"
#include <stack>
#include "Card.h"

void printDeck(PhaseDeck deck);//prints deck
void deal(std::vector<PhaseCard>& hand, PhaseDeck& deck);//deaks 10 cards to the hand
void printHand(std::vector<PhaseCard> hand);// Shows hand
std::vector<PhaseCard> draw(std:: vector<PhaseCard> hand, PhaseDeck deck);//draws card from the deck
void discard(std::vector<PhaseCard> hand,int location,std::stack<PhaseCard> discard);//adds a card to the discard pile
std::vector<PhaseCard> drawFromDiscard(std::vector<PhaseCard> hand, std::stack<PhaseCard>);//draws from discard pile
bool checkPhase(int phase, std::vector<PhaseCard> hand);//checks to see if you meet the requirements for your current phase
std::vector<PhaseCard> setWild(int location, int color, int number, std::vector<PhaseCard> player);
std::vector<PhaseCard> sort(std::vector<PhaseCard> hand);
int getPoints(std::vector<PhaseCard> hand);

using namespace std;

int main()
{
    int player1Phase= 1;
    int player2Phase= 1;
    int playerInput;
    int player1Points = 0;
    int player2Points = 0;
    int currentPlayer = 1;
    cout << "========================================================================================================================" << endl;
    cout << "PPPPPP    H     H     AAA       SSSSSS    EEEEEEEEE               1        0000000" << endl;
    cout << "P     P   H     H    A   A     S      S   E                      11       0     0 0" << endl;
    cout << "P     P   H     H   A     A    S          E                     1 1       0    0  0" << endl;
    cout << "PPPPPP    HHHHHHH   A     A     SSSSS     EEEEEE                  1       0   0   0" << endl;
    cout << "P         H     H   AAAAAAA          S    E                       1       0  0    0" << endl;
    cout << "P         H     H   A     A    S     S    E                       1       0 0     0" << endl;
    cout << "P         H     H   A     A     SSSSS     EEEEEEEEE            11111111    0000000" << endl;
    cout << "========================================================================================================================" << endl;
    cout<< "" << endl;
    cout<< "" << endl;
    cout<< "" << endl;
    cout<< "" << endl;

    cout << "Enter 1 to play" << endl;
    cout << "Enter 0 to quit" << endl;
    cin >> playerInput;
    if (playerInput == 1){
        int player1Phase = 1;
        int player2Phase = 1;
        while(playerInput != 0){
            while(currentPlayer != 0){
                PhaseDeck deck;
                deck.shuffle();

                stack<PhaseCard> discardPile;
                discardPile.push(deck.deal());

                vector<PhaseCard> player1;
                vector<PhaseCard> player2;
                deal(player1, deck);
                deal(player2, deck);

                if(currentPlayer == 1){
                    cout << "Player one would you like to draw from the discard pile or the deck" << endl;
                    cout << discardPile.top().toString() << " Is on top of the discard pile" << endl;
                    cout << "1: deck and 2: discard pile" << endl;
                    printHand(player1);
                    cin >> playerInput;

                    if (playerInput == 1){
                        player1 = draw(player1, deck);
                    }

                    else if(playerInput == 2){
                        player1 = drawFromDiscard(player1,discardPile);
                    }

                    printHand(player1);
                    cout << "Do you think you have your phase?" << endl;
                    cout << "1: Yes, 2: No" << endl;
                    cin >> playerInput;
                    if(playerInput == 1){
                        cout << "do you have any wilds?"<< endl;
                        cout << "1:yes 2:no" << endl;
                        cin >> playerInput;

                        if(playerInput == 1){
                            //first it has them  set their wilds to the cards they need for their phases

                            int color;
                            int number;
                            cout << "What is the location in your hand" << endl;
                            cout << "Enter a number between 0 and 10." << endl;
                            cin >> playerInput;

                            cout << "Enter a color." << endl;
                            cout << "1:Blue 2:Red 3:Green 4:Yellow" << endl;
                            cin >> color;

                            cout << "Enter a number between 1 and 12" << endl;
                            cin >> number;
                            player1 = setWild(playerInput, color, number, player1);

                        }
                        //then it checks to see if they have their current Phase

                        bool result = checkPhase(player1Phase, player1);
                        if(result == true){
                            cout << "You have you're Phase!" << endl;
                            cout << "Type the positions of the cards in your phase to remove them one at a time 0 is the first position and 10 is the last one. and press 11 when done." << endl;
                            while(playerInput != 11){
                                if(playerInput == 11){
                                    break;
                                }
                                cin >> playerInput;
                                player1.erase(player1.begin()+playerInput);
                            }

                            player1Phase++;
                            player1Points = player1Points + getPoints(player1);
                            player2Points = player2Points + getPoints(player2);
                            break;

                        }//if they have their phase it ends the round and tally's the points in their hand
                        else {
                            cout << "You do not have your Phase." << endl;
                        }

                    }
                    cout << "Which card would you like to discard?" << endl;
                    cout << "enter a number between 0 and 10" << endl;
                    cin >> playerInput;

                    //this piece of code is how I am handing the discarding phase of a turn
                    PhaseCard temp = player1.at(playerInput);
                    player1.erase(player1.begin()+playerInput);
                    discardPile.push(temp);

                    cout << discardPile.top().toString() << " Is now on top" << endl;
                    printHand(player1);
                    if(discardPile.top().rankNum() == 13){
                        currentPlayer--;//used to impliment the skip
                    }
                    currentPlayer++;//this is used to transition to the next players turn

                }
                else if(currentPlayer == 2){
                    cout << "Player two would you like to draw from the discard pile or the deck" << endl;
                    cout << discardPile.top().toString() << " Is on top of the discard pile" << endl;
                    cout << "1: deck and 2: discard pile" << endl;
                    printHand(player2);
                    cin >> playerInput;

                    if (playerInput == 1){
                        player2 = draw(player2, deck);
                    }

                    else if(playerInput == 2){
                        player2 = drawFromDiscard(player2,discardPile);
                    }

                    printHand(player2);
                    cout << "Do you think you have your phase?" << endl;
                    cout << "1: Yes, 2: No" << endl;
                    cin >> playerInput;
                    if(playerInput == 1){
                        cout << "do you have any wilds?"<< endl;
                        cout << "1:yes 2:no" << endl;
                        cin >> playerInput;

                        if(playerInput == 1){

                            int color;
                            int number;
                            cout << "What is the location in your hand" << endl;
                            cout << "Enter a number between 0 and 10." << endl;
                            cin >> playerInput;

                            cout << "Enter a color." << endl;
                            cout << "1:Blue 2:Red 3:Green 4:Yellow" << endl;
                            cin >> color;

                            cout << "Enter a number between 1 and 12" << endl;
                            cin >> number;
                            player2 = setWild(playerInput, color, number, player1);

                        }

                        bool result = checkPhase(player1Phase, player1);
                        if(result == true){
                            cout << "You have you're Phase!" << endl;
                            cout << "Type the positions of the cards in your phase to remove them one at a time 0 is the first position and 10 is the last one. and press 11 when done." << endl;
                            while(playerInput != 11){
                                if(playerInput == 11){
                                    break;
                                }
                                cin >> playerInput;
                                player2.erase(player2.begin()+playerInput);
                            }

                            player2Phase++;
                            player1Points = player1Points + getPoints(player1);
                            player2Points = player2Points + getPoints(player2);
                            break;

                        }
                        else{
                            cout << "You don't have you're Phase" << endl;
                        }

                    }
                    cout << "Which card would you like to discard?" << endl;
                    cout << "enter a number between 0 and 10" << endl;
                    cin >> playerInput;

                    //this piece of code is how I am handing the discarding phase of a turn
                    PhaseCard temp = player2.at(playerInput);
                    player2.erase(player2.begin()+playerInput);
                    discardPile.push(temp);

                    cout << discardPile.top().toString() << " Is now on top" << endl;
                    printHand(player1);
                    if(discardPile.top().rankNum() == 13){
                        currentPlayer++;//used to impliment the skip
                    }
                    currentPlayer--;//this is used to transition to the next players turn

                }

            }
        }
    }
    


    return 0;
}
void printDeck(PhaseDeck deck){
    cout << "current hand" << endl;
    cout << "======================================================" << endl;
    for(int i = 0; i < deck.getSize(); i++){
        cout << deck.getCardAt(i).toString() << endl;
    }
    cout << "======================================================" << endl;
}
    void deal(vector<PhaseCard> &hand, PhaseDeck &deck){
        for(int i = 0; i < 10; i++){
            hand.push_back(deck.deal());
        }
    }
    void printHand(vector<PhaseCard> hand){
        cout << "current hand" << endl;
        cout << "======================================================" << endl;
        for(int i= 0; i < hand.size(); i++){
            cout << hand.at(i).toString() << endl;
        }
        cout << "======================================================" << endl;
    }
    vector<PhaseCard> draw(vector<PhaseCard> hand, PhaseDeck deck){
        hand.push_back(deck.deal());
        return hand;
    }
    vector<PhaseCard> drawFromDiscard(vector<PhaseCard> hand, stack<PhaseCard> discardPile){
        PhaseCard temp = discardPile.top();
        hand.push_back(temp);
        discardPile.pop();
        return hand;
    }
    void discard(vector<PhaseCard> hand, int location, stack<PhaseCard> discardPile){
        PhaseCard temp = hand.at(location);
        hand.erase(hand.begin()+location);
        discardPile.push(temp);
    }//this discards a card from the hand

    vector<PhaseCard> setWild(int location, int color, int number, vector<PhaseCard> player){
        if(player.at(location).rankNum() != 0){
            cout << " ERROR! card at this location is not wild" << endl;
        }

        else {
            PhaseCard temp(color, number);
            player.erase(player.begin()+location);
            player.push_back(temp);
            return player;
        }
    }//this changes the wild into a useable card

    vector<PhaseCard> sort(vector<PhaseCard> hand){
        vector<PhaseCard> temp = hand;
        vector<PhaseCard> temp2;
        PhaseCard smallest;
        int smallestPos;
        for(int i = 0; i < hand.size(); i++){
            smallest = temp.at(i);
            for(int j = 0; j < temp.size(); j++){
                if(temp.at(j).rankNum() < smallest.rankNum()){
                    smallest = temp.at(j);
                    smallestPos = j;
                }
            }
            temp2.push_back(smallest);
            temp.erase(temp.begin()+smallestPos);
        }
    }

    int getPoints(vector<PhaseCard> hand){// used to tally the points of the hand
        int points = 0;
        for(int i = 0; i < hand.size(); i++){
            if(hand.at(i).rankNum()>= 1 and hand.at(i).rankNum() <= 9){
                points = points+10;
            }
            else if(hand.at(i).rankNum()>= 10 and hand.at(i).rankNum() <= 12){
                points = points+15;
            }
            else if(hand.at(i).rankNum() == 13){
                points = points + 20;
            }
            else if (hand.at(i).rankNum() == 0){
                points = points + 25;
            }
        }
    }

    bool checkPhase(int phase, vector<PhaseCard> hand){//checks to see if the player acheived the phase
        int runCount;
        int setCount;
        int cardCount;
        int colorCount;
        if(phase == 1){
            setCount = 0;//counts the number of sets
            for(int i = 0; i < hand.size() ; i++){
                int cardCount = 0;//counts the number of cards with the same number
                for(int j = 0; j < hand.size(); j++ ){
                    if (hand.at(i).rankNum() == hand.at(j).rankNum()){
                        cardCount++;
                        if(cardCount > 3){
                            setCount++;
                        }
                    }
                }
            }
            if(setCount >= 2){

                return true;
        }
            else {
                return false;
            }
        }
            else if(phase == 2){
                 setCount = 0;//counts the number of sets
                 runCount = 0;
                for(int i = 0; i < hand.size() ; i++){
                    cardCount = 0;//counts the number of cards with the same number
                    for(int j = 0; j < hand.size(); j++ ){
                        if(hand.at(j).rankNum() == hand.at(i).rankNum() + 1){
                                runCount++;
                            }

                        if (hand.at(i).rankNum() == hand.at(j).rankNum()){
                            cardCount++;
                            if(cardCount > 3){
                                setCount++;
                            }
                        }
                    }
                }
                if(setCount >= 1 and runCount > 4){

                    return true;
            }
            else{
                return false;
            }
    }
            else if(phase == 3){
                 setCount = 0;//counts the number of sets
                 runCount = 0;
                for(int i = 0; i < hand.size() ; i++){
                    int cardcount = 0;//counts the number of cards with the same number
                    for(int j = 0; j < hand.size(); j++ ){

                       if(hand.at(j).rankNum() == hand.at(i).rankNum() + 1){
                                runCount++;
                            }

                        if (hand.at(i).rankNum() == hand.at(j).rankNum()){
                            cardCount++;
                            if(cardCount > 4){
                                setCount++;
                            }
                        }
                    }
                }
                if(setCount >= 1  and runCount > 4){

                    return true;
            }
            else{
                return false;
            }
    }
            else if(phase == 4){
                 runCount = 0;
                for(int i = 0; i < hand.size() ; i++){
                    for(int j = 0; j < hand.size(); j++ ){

                       if(hand.at(j).rankNum() == hand.at(i).rankNum() + 1){
                                runCount++;
                            }

                    }
                }
                if( runCount >= 7){

                    return true;
            }
            else{
                return false;
            }
    }
            else if(phase == 5){
                 runCount = 0;
                for(int i = 0; i < hand.size() ; i++){
                    for(int j = 0; j < hand.size(); j++ ){

                       if(hand.at(j).rankNum() == hand.at(i).rankNum() + 1){
                                runCount++;
                            }

                    }
                }
                if( runCount >= 8){

                    return true;
            }
            else{
                return false;
            }
    }
            else if(phase == 6){
                 runCount = 0;
                for(int i = 0; i < hand.size() ; i++){
                    for(int j = 0; j < hand.size(); j++ ){

                       if(hand.at(j).rankNum() == hand.at(i).rankNum() + 1){
                                runCount++;
                            }

                    }
                }
                if( runCount >= 9){

                    return true;
            }
            else{
                return false;
            }
    }
        if(phase == 7){
            setCount = 0;//counts the number of sets
            for(int i = 0; i < hand.size() ; i++){
                int cardCount = 0;//counts the number of cards with the same number
                for(int j = 0; j < hand.size(); j++ ){
                    if (hand.at(i).rankNum() == hand.at(j).rankNum()){
                        cardCount++;
                        if(cardCount >= 4){
                            setCount++;
                        }
                    }
                }
            }
            if(setCount >= 2){

                return true;
        }
            else {
                return false;
            }
        }
        if(phase == 8){
            colorCount = 0;
            for(int i = 0; i < hand.size(); i++){
                for(int j = 0; j < hand.size(); j++){

                    if(hand.at(i).colorNum() == hand.at(j).colorNum()){
                        colorCount++;
                        if(colorCount == 7){
                            return true;
                        }
                    }
                }
            }
            return false;
        }
        if(phase == 9){
            colorCount = 0;
            for(int i = 0; i < hand.size(); i++){
                for(int j = 0; j < hand.size(); j++){

                    if(hand.at(i).colorNum() == hand.at(j).colorNum()){
                        colorCount++;
                        if(colorCount == 8){
                            return true;
                        }
                    }
                }
            }
            return false;
        }
        if(phase == 10){
            colorCount = 0;
            for(int i = 0; i < hand.size(); i++){
                for(int j = 0; j < hand.size(); j++){

                    if(hand.at(i).colorNum() == hand.at(j).colorNum()){
                        colorCount++;
                        if(colorCount == 9){
                            return true;
                        }
                    }
                }
            }
            return false;
        }
    }




