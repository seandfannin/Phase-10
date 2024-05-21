#ifndef CARD_H
#define CARD_H

#include <string>
#include <stdexcept>

class PhaseCard{
private:
    int color; // 0 is wild, 1 is blue, 2 is red, 3 is green, 4 is yellow
    int rank; // 0-9 is the numbers, 10 is skip, 11 is reverse, 12 is +2, 13 is wild color change, 14 is +4

    void setColor(int color){
        if(color < 0 or color > 4){
            throw std::invalid_argument("Invalid Color");
        }
        this->color = color;

    }

    void setRank(int rank){
        if(rank < 0 or rank > 14){
            throw std::invalid_argument("Invalid color");
        }
        this->rank = rank;
    }
public:
    PhaseCard(){

    }
    PhaseCard(int color, int rank){
        setColor(color);
        setRank(rank);
    }

    int colorNum(){
        return color;
    }

    std::string ColorName(){
        switch(color){
        case 0: return "Wild";
        case 1: return "Blue";
        case 2: return "Red";
        case 3: return "Green";
        case 4: return "Yellow";
        default: return "Error";
        }
    }

    int rankNum(){
        return rank;
    }

    std::string rankName(){//gives cards their number
        switch(rank){
        case 0: return "0";
        case 1: return "1";
        case 2: return "2";
        case 3: return "3";
        case 4: return "4";
        case 5: return "5";
        case 6: return "6";
        case 7: return "7";
        case 8: return "8";
        case 9: return "9";
        case 10: return "10";
        case 11: return "11";
        case 12: return "12";
        case 13: return "Skip";
        default: return "Error";
        }
    }

    std::string toString(){
        if(color == 0){
            return "Wild";
        }
        else{
            return rankName() + " " + ColorName();
        }
    }
};

#endif // CARD_H
