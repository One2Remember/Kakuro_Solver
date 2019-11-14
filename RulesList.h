# ifndef RULESLIST_H_INCLUDED
# define RULESLIST_H_INCLUDED
#include <iostream>
using std::ostream;
using std::endl;

struct Rule
{
    char orientation;
    int sum,
        startY,
        startX,
        length;
    Rule * next;
    friend ostream & operator <<( ostream &, Rule & );
};

class RulesList
{
private:
    int numRules;
    Rule * head;
    void addRule( Rule * );
public:
    RulesList();
    ~RulesList();
    void addRule( char, int, int, int, int );
    void init();
    void printRules( ostream & );
    Rule & findRule( char, int, int );
};

# endif // RULESLIST_H_INCLUDED


