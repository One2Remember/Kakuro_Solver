# ifndef RULESLIST_H_INCLUDED
# define RULESLIST_H_INCLUDED
#include <iostream>
using std::ostream;
using std::endl;

// contains all data to hold a rule
struct Rule
{
    char orientation;   // 'v' or 'h' for vertical or horizontal
    int sum,    // sum of row
        startY, // starting y coordinate
        startX, // starting x coordinate
        length; // length of row
    Rule * next;    // for use in list
    friend ostream & operator <<( ostream &, Rule & );  // for printing row
};

// contains a linked list of rules for solving a board
class RulesList
{
private:
    int numRules;
    Rule * head;
    void addRule( Rule * ); // adds rule to list
public:
    RulesList();
    ~RulesList();
    void addRule( char, int, int, int, int );   // takes rule from client
    void init();    // clears rules list
    void printRules( ostream & );   // prints all rules
    Rule & findRule( char, int, int );  // takes orientation and start coord's
};

# endif // RULESLIST_H_INCLUDED


