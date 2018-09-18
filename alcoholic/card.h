#ifndef CARD_H
#define CARD_H

#include "QList"
#include "QPixmap"

static QList<QString> const names = {"ACE","SIX","SEVEN","EIGHT","NINE","TEN","JACK","QUEEN","KING", "TWO","THREE","FOUR","FIVE", "JOCKER"};
static QList<QString> const suits = {"CLUBS","DIAMONDS","HEARTS","SPADES","JOCKER"};

class Card {
public:
    explicit Card(const unsigned short val = 13, const QString suit = suits[4]);
    void init(const unsigned short val, const unsigned short suit);
    unsigned short getvalue() const;
    const QPixmap getpic() const;
    Card ( Card const & a );
    Card & operator =(Card const & a );
    ~Card();
private:
    QPixmap facepic; //Picture of card
    unsigned short value; //0-13
    QString name; //from "names"; I don't use it, but I feel safe while it is here
    bool faceup; //is it face (1) or back (0); I don't need it now, but maybe in a far future...
    QString suit; //from "suit"; same as "names"
};

class Coloda : Card {
public:
    explicit Coloda(unsigned short const col = 36);
    inline short getvalue (const unsigned short i);
    const Coloda share(const unsigned short col);
    ~Coloda();
    void shuffle();
    const Card& getcard(const unsigned short i) const;
    unsigned short getcolvo();
    Coloda & operator =(Coloda const & a );
    Coloda ( Coloda const & a );
private:
    unsigned short colvo;
    Card * cards;
};

#endif // CARD_H
