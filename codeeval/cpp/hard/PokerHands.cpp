//
// Challenge name: Poker Hands
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/86/
// Compile       : g++ -Wall -g -o PokerHands PokerHands.cpp
//

#include <stdio.h>
#define HAND_SIZE 5

enum Ranks {
    HighCard = 0,
    OnePair,
    TwoPairs,
    ThreeOfaKind,
    Straight,
    Flush,
    FullHouse,
    FourOfaKind,
    StraightFlush,
    RoyalFlush
};

enum CardValue {
    Two = 0,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
    NumCards
};

enum CardType {
    Club = 0,
    Diamond,
    Heart,
    Spade
};

struct Card {
    Card():val(Two),type(Club) {}
    ~Card() {}

    void readCard(char v, char t) {
        switch(v) {
        case '2': val = Two; break;
        case '3': val = Three; break;
        case '4': val = Four; break;
        case '5': val = Five; break;
        case '6': val = Six; break;
        case '7': val = Seven; break;
        case '8': val = Eight; break;
        case '9': val = Nine; break;
        case 'T': val = Ten; break;
        case 'J': val = Jack; break;
        case 'Q': val = Queen; break;
        case 'K': val = King; break;
        case 'A': val = Ace; break;
        };
        switch(t) {
        case 'C': type = Club; break;
        case 'D': type = Diamond; break;
        case 'H': type = Heart; break;
        case 'S': type = Spade; break;
        }
    }

    bool operator==(const Card& c) const {
        return (val == c.val);
    }

    bool operator>(const Card& c) const {
        return (val > c.val);
    }

    bool operator>=(const Card& c) const {
        return (val >= c.val);
    }

    bool operator<(const Card& c) const {
        return (val < c.val);
    }

    bool operator<=(const Card& c) const {
        return (val <= c.val);
    }

    CardValue val;
    CardType type;
};


struct Hand {
    Hand() {}
    ~Hand() {}

    bool readHand(FILE* fp) {
        for(int i=0;i<NumCards;++i) {
            hist[i] = 0;
        }
        for(int i=0;i<HAND_SIZE;++i) {
            char data[4];
            if(fscanf(fp,"%s",data) != 1) {
                return false;
            }
            cards[i].readCard(data[0], data[1]);
            int val = (int)cards[i].val;
            hist[val] += 1;
        }
        for(int i=0;i<HAND_SIZE;++i) {
            for(int j=i+1;j<HAND_SIZE;++j) {
                if(cards[i] < cards[j]) { // descending order
                    Card t = cards[i];
                    cards[i] = cards[j];
                    cards[j] = t;
                }
            }
        }
        getRank();
        return true;
    }

    int compareHand(const Hand& h) const {
        if(rank > h.rank) {
            return 1;
        }
        if(rank < h.rank) {
            return -1;
        }
        return compareValues(h);
    }

    int compareValues(const Hand& h) const {
        for(int i=0;i<HAND_SIZE;++i) {
            if(cards[i] > h.cards[i]) {
                return 1;
            }
            if(cards[i] < h.cards[i]) {
                return -1;
            }
        }
        return 0;
    }

    void getRank() {
        if(isRoyalFlush()) {
            rank = RoyalFlush;
        }
        else if(isStraightFlush()) {
            rank = StraightFlush;
        }
        else if(fourKindPair()) {
            rank = FourOfaKind;
        }
        else if(isFullHouse()) {
            rank = FullHouse;
        }
        else if(sameSuit()) {
            rank = Flush;
        }
        else if(consecutive()) {
            rank = Straight;
        }
        else if(threeKindPair()) {
            rank = ThreeOfaKind;
        }
        else if(twoKindTwoPairs()) {
            rank = TwoPairs;
        }
        else if(twoKindOnePair()) {
            rank = OnePair;
        }
        else {
            rank = HighCard;
        }
    }

    bool isRoyalFlush() const {
        return (sameSuit() && consecutive((int)Ten));
    }

    bool isStraightFlush() const {
        return (sameSuit() && consecutive());
    }

    bool isFullHouse() const {
        return (threeKindPair() && twoKindOnePair());
    }

    bool sameSuit() const {
        for(int i=1;i<HAND_SIZE;++i) {
            if(cards[i-1].type != cards[i].type) {
                return false;
            }
        }
        return true;
    }

    bool consecutive(int start=-1) const {
        int v = start;
        if(v < 0) {
            v = (int) cards[0].val;
        }
        for(int i=0;i<HAND_SIZE;++i,++v) {
            if(v != (int)cards[i].val) {
                return false;
            }
        }
        return true;
    }

    bool twoKindOnePair() const {
        int num = 0;
        for(int i=0;i<NumCards;++i) {
            if(hist[i] == 2) {
                ++num;
            }
        }
        return (num == 1);
    }

    bool twoKindTwoPairs() const {
        int num = 0;
        for(int i=0;i<NumCards;++i) {
            if(hist[i] == 2) {
                ++num;
            }
        }
        return (num == 2);
    }

    bool threeKindPair() const {
        for(int i=0;i<NumCards;++i) {
            if(hist[i] == 3) {
                return true;
            }
        }
        return false;
    }

    bool fourKindPair() const {
        for(int i=0;i<NumCards;++i) {
            if(hist[i] == 4) {
                return true;
            }
        }
        return false;
    }

    Card cards[HAND_SIZE];
    int hist[NumCards];
    Ranks rank;
};

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: PokerHands <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        Hand left, right;
        if(!left.readHand(fp) || !right.readHand(fp)) {
            continue;
        }
        int v = left.compareHand(right);
        if(v == 0) {
            printf("none\n");
        }
        else if(v > 0) {
            printf("left\n");
        }
        else {
            printf("right\n");
        }
    }
    fclose(fp);
    return 0;
}
