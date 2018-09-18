#include "card.h"
#include "math.h"

//constructor "Card" type
Card::Card(unsigned short const val, const QString suit) : value(val), suit(suit) {
    this->name = names[val];
    this->facepic = QPixmap(":/cards/cards/" + name + suit + ".bmp");
    this->faceup = false;
}

//It's need for changing "standard Card" (JOCKERJOCKER) to any
void Card::init (unsigned short const val, unsigned short const suit) {
    if (val < 14 && suit < 5) { //So protected. Such secure...
        this->value = val;
        this->suit = suits[suit];
        this->name = names[val];
        this->facepic = QPixmap(":/cards/cards/" + this->name + this->suit + ".bmp");
        this->faceup = false;
    }
}

//copy constructor, destructor and = operator
Card::Card ( Card const & a ) : facepic(a.facepic), value(a.value), name(a.name), faceup(a.faceup), suit(a.suit) {}
Card::~Card() {};
Card & Card::operator =(Card const & a ) {
    if ( this != & a ) {
        facepic = a.facepic ;
        value = a.value;
        name = a.name;
        faceup = a.faceup;
        suit = a.suit;
    }
    return * this ;
}

//Coloda constructor
Coloda::Coloda(unsigned short const col) : Card(), colvo(col), cards(new Card[col]) {
    if (int(col/4) < 14) {
            unsigned short k = 0;
            for (unsigned short i = 0; i<(col/4); ++i) {
                for (unsigned short j = 0; j<4; ++j) {
                    cards[i+j+k].init(i, j);
                    if (j == 3) {k+=3;}
                }
            }
        }
}

//Coloda destructor
Coloda::~Coloda() {delete [] cards;}

//It's for: "Coloda A = B.share(5 cards to A);"
const Coloda Coloda::share(unsigned short const col){
        Coloda t(col);
        unsigned short tc = this->colvo;
        Coloda tt(tc-col);
        for (int i = 0; i < col; ++i) { //reading for A
            t.cards[i] = this->cards[tc - col + i];
        }
        for (int i = 0; i < (tc-col); ++i) { //reading for B
           tt.cards[i] = this->cards[i];
        }
        *this = tt;//writing
        return t;
}

//shuffle some Cards at Coloda
void Coloda::shuffle() {
        if (this->colvo > 1)
        {
            int i;
            srand(time(NULL));
            for (i = 0; i < this->colvo - 1; i++)
            {
              int j = i + rand() / (RAND_MAX / (this->colvo - i) + 1);
              Card t = this->cards[j];
              this->cards[j] = this->cards[i];
              this->cards[i] = t;
            }
        }
}

//Copy constructor for Coloda
Coloda::Coloda (Coloda const & a): Card(), colvo (a.colvo), cards (new Card [colvo]) {
    for (size_t i = 0; i != colvo ; ++i) {
        cards[i] = a.cards[i];
    }
}

//= operator for Coloda
Coloda & Coloda::operator =( Coloda const & a ) {
    if ( this != & a ) {
        delete [] cards ;
        colvo = a . colvo ;
        cards = new Card [ colvo ];
        for ( size_t i = 0; i != colvo ; ++ i )
        cards [ i ] = a . cards [ i ];
    }
    return * this ;
}

//It's for reading private cards
const Card& Coloda::getcard(unsigned short const i) const {return this->cards[i];}
unsigned short Coloda::getcolvo(){return colvo;}

//It's for reading private card values
unsigned short Card::getvalue () const {return value;};
const QPixmap Card::getpic() const {return facepic;}

