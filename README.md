# Kakuro_Solver
C++ Kakuro Solver, not for any class, just because I love Kakuro!

## Input
1 Command Line argument for input file encoding a single board (up to 10x10) as follows: 
``` 
  1 line with N: integer value containing number of initial blank spaces  
  N lines each containing: x and y coordinates of an initial blank space  
    (coordinates start with 1,1 in the top left corner of the board)  
  1 line with M: integer value of number of RULES (# of columns + # of rows)  
  M lines each containing a RULE as follows:  
    'v' or 'h' to designate vertical rule or horizontal rule    
    SPACE  
    Sum of that row or column  
    SPACE   
    Coordinates of START point of rule (top most OR left most blank square)   
    SPACE   
    Length of row or column   
    EXAMPLE RULE: 'h 42 2 2 8' encodes a horizontal rule that states   
      'The row beginning at 2,2 of length 8 sums to 42'   
```
## To Run
Simply download source and compile with C++ compiler of your choice (recommend GCC),  
then run from cmd line with single argument (name of input file containing init board state)

## Example Output
![Output](https://github.com/One2Remember/Kakuro_Solver/blob/master/Example_Output.PNG)

## New to Kakuro?
* [Link to Kakuro Wiki](https://en.wikipedia.org/wiki/Kakuro)
* [Link to Free Web Kakuro Game](https://www.kakuroconquest.com/)
