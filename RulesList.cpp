#include "RulesList.h"

RulesList::RulesList()
{
    head = nullptr;
    numRules = 0;
}
RulesList::~RulesList()
{
    init();
}
void RulesList::addRule( char orient,
    int sum, int startY, int startX, int len )
{
    Rule * r = new Rule{orient, sum, startY, startX, len, nullptr};
    addRule( r );
}
void RulesList::addRule( Rule * r )
{
    if( head )
    {
        r->next = head;
    }
    head = r;
    numRules++;
}
void RulesList::init()
{
    Rule * p = head, * q = nullptr;
    while( p )
    {
        q = p;
        p = p->next;
        delete q;
    }
    numRules = 0;
}
void RulesList::printRules( ostream & out )
{
    Rule * r = head;
    while( r )
    {
        out << r->orientation << ' ' << r->sum << ' '
            << r->startY << ' ' << r->startX
            << ' ' << r->length << endl;
        r = r->next;
    }
}
Rule & RulesList::findRule( char orient, int y, int x)
{
    Rule * p = head;
    if( orient == 'h' )
    {
        while( p && ! ( p->orientation == orient && x >= p->startX
                       && x < p->startX + p->length && y == p->startY ) )
        {
            p = p->next;
        }
    }
    else if( orient == 'v' )
    {
        while( p && ! ( p->orientation == orient && y >= p->startY
                       && y < p->startY + p->length && x == p->startX ) )
        {
            p = p->next;
        }
    }
    return *p;
}
ostream & operator <<( ostream & out, Rule & r )
{
    out << "Sum: " << r.sum << "\nOrient: " << r.orientation
        << "\nStartY: " << r.startY << "\nStartX: " << r.startX << endl;
}
