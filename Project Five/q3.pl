:- dynamic o/1.
:- dynamic x/1.
:- dynamic(p/3).

numMatrix(1,2,3).
numMatrix(4,5,6).
numMatrix(7,8,9).
numMatrix(1,4,7).
numMatrix(2,5,8).
numMatrix(3,6,9).
numMatrix(1,5,9).
numMatrix(3,5,7).

letterMatrix(A,B,C) :- numMatrix(A,B,C).
letterMatrix(A,B,C) :- numMatrix(A,C,B).
letterMatrix(A,B,C) :- numMatrix(B,A,C).
letterMatrix(A,B,C) :- numMatrix(B,C,A).
letterMatrix(A,B,C) :- numMatrix(C,A,B).
letterMatrix(A,B,C) :- numMatrix(C,B,A).

getA(U,R,C) :- 
    (R is 1, C is 1) -> U = 1;
    (R is 1, C is 2) -> U = 2;
    (R is 1, C is 3) -> U = 3;
    (R is 2, C is 1) -> U = 4;
    (R is 2, C is 2) -> U = 5;
    (R is 2, C is 3) -> U = 6;
    (R is 3, C is 1) -> U = 7;
    (R is 3, C is 2) -> U = 8;
    (R is 3, C is 3) -> U = 9.

getRow(H,R) :- 
    (H is 1 ; H is 2 ; H is 3) -> R = 1;
    (H is 4 ; H is 5 ; H is 6) -> R = 2;
    (H is 7 ; H is 8 ; H is 9) -> R = 3.

getCol(H,C) :- 
    (H is 1 ; H is 4 ; H is 7) -> C = 1;
    (H is 2 ; H is 5 ; H is 8) -> C = 2;
    (H is 3 ; H is 6 ; H is 9) -> C = 3.

p(o,R,C) :- 
    !, getA(U,R,C) -> assert(o(U)).

p(x,R,C) :- 
    !, getA(U,R,C) -> assert(x(U)).

move(x,R,C) :- 
    goodX(A), 
    empty(A),
    printboard.

move(o,R,C) :- 
    goodO(A), 
    empty(A),
    printboard.

full(A) :- o(A).
full(A) :- x(A).

empty(A) :- not(full(A)).

goodX(A) :- winX(A), getRow(A,R), getCol(A,C), format('Move to win!!! \n R = ~w C = ~w \n', [R,C]).
goodX(A) :- block_winX(A), getRow(A,R), getCol(A,C), format('Block the win! \n R = ~w C = ~w \n', [R,C]).
goodX(A) :- splitX(A), getRow(A,R), getCol(A,C), format('Setup! \n R = ~w C = ~w \n', [R,C]).
goodX(A) :- block_splitX(A), getRow(A,R), getCol(A,C), format('Block Opponent! \n R = ~w C = ~w \n', [R,C]).
goodX(A) :- buildX(A), getRow(A,R), getCol(A,C), format('Setup \n R = ~w C = ~w \n', [R,C]).


goodO(A) :- winO(A), getRow(A,R), getCol(A,C), format('Move to win!!! \n R = ~w C = ~w \n', [R,C]).
goodO(A) :- block_winO(A), getRow(A,R), getCol(A,C), format('Block the win! \n R = ~w C = ~w \n', [R,C]).
goodO(A) :- splitO(A), getRow(A,R), getCol(A,C), format('Setup! \n R = ~w C = ~w\n', [R,C]).
goodO(A) :- block_splitO(A), getRow(A,R), getCol(A,C), format('Block Opponent! \n R = ~w C = ~w \n', [R,C]).
goodO(A) :- buildO(A), getRow(A,R), getCol(A,C), format('Setup \n R = ~w C = ~w \n', [R,C]).

good(5).
good(1). good(3). good(7). good(9).
good(2). good(4). good(6). good(8).

winX(A) :- x(B), x(C), \+o(B), \+o(C), letterMatrix(A,B,C).
block_winX(A) :- o(B), o(C), letterMatrix(A,B,C).
splitX(A) :- x(B), x(C), different(B,C), letterMatrix(A,B,D), letterMatrix(A,C,E), empty(D), empty(E).
same(A,A).
different(A,B) :- not(same(A,B)).
block_splitX(A) :- o(B), o(C), different(B,C), letterMatrix(A,B,D), letterMatrix(A,C,E), empty(D), empty(E).
buildX(A) :- x(B), letterMatrix(A,B,C), empty(C).


winO(A) :- o(B), o(C), \+x(B), \+x(C), letterMatrix(A,B,C).
block_winO(A) :- o(B), o(C), letterMatrix(A,B,C).
splitO(A) :- x(B), x(C), different(B,C), letterMatrix(A,B,D), letterMatrix(A,C,E), empty(D), empty(E).

block_splitO(A) :- o(B), o(C), different(B,C), letterMatrix(A,B,D), letterMatrix(A,C,E), empty(D), empty(E).
buildO(A) :- x(B), letterMatrix(A,B,C), empty(C).

all_full :- full(1),full(2),full(3),full(4),full(5),full(6),full(7),full(8),full(9).
done :- numMatrix(A,B,C), x(A), x(B), x(C), write('X won.'),nl.
done :- numMatrix(A,B,C), o(A), o(B), o(C), write('O won.'),nl.
done :- all_full, write('Draw.'), nl.

printsquare(N) :- o(N), format('  o  ').
printsquare(N) :- x(N), format('  x  ').
printsquare(N) :- empty(N), format('  .  ').

printboard :- 
    printsquare(1),printsquare(2),printsquare(3),nl,
    printsquare(4),printsquare(5),printsquare(6),nl,
    printsquare(7),printsquare(8),printsquare(9),nl.

clear :- x(A), retract(x(A)), fail.
clear :- o(A), retract(o(A)), fail.