# reverse-2048-game
Write C++ code for a program that reads in an unknown num- ber of “Reverse 2048” games. The program must then use an algorithm to solve each of the solvable puzzles given in the input file.

#Part 1: Background
Reverse 2048 is a variation of the classic 2048 puzzle game, a sliding tile game that is played on
a 4×4 grid. Unlike the original game, where the goal is to merge tiles to reach 2048, in Reverse
2048, the player must divide tiles to reach the smallest possible value, typically tile 2.

The game is played using numerical tiles, each having values that are powers of 2. The main rules
of the game are:

1. Players slide tiles in four possible directions (up, down, left, right).
2. When two tiles of the same value collide, they merge into one tile with half the value.
3. The game ends when there are no more valid moves or when the smallest achievable value
has been reached.

#Problem to be solved
Your task is to develop a C++ program that can solve any given configuration of Reverse 2048
based on specified project requirements and constraints. Since the game requires a different strate-
gic approach than traditional 2048, your implementation must optimize moves to reach the smallest
tile possible (tile with a value of 2) before the board becomes full.

#Game Phases and Rules or a regular reverse 2048 game
##Initial Board Setup
• The board consists of a 4×4 grid initially filled with 2 tiles having a value of 2048
• New tiles appear after each move, following a random pattern. The new tiles have large
numerical values of either 2048 or 1024 (no tile value lower than this should appear on the
grid)

##Movement
• Players can slide all tiles in a chosen direction (left, right, up, down). When two tiles of the
same value collide, they merge into one tile with half the value. For example:
– Two 2048s combine into a 1024
– Two 1024s combine into a 512
– Two 512s combine into a 256
– and so on, all down to two 4s combine into a 2
• A move is valid only if at least one tile can be merged or moved.

##End Condition
• The game is won if a tile of value 2 is reached before the board becomes full.
• The game is lost if there are no valid moves left.

#Project Requirements and Constraints
In this project, you required to:
1. Implement Reverse 2048 that supports tile movement and merging based on division by 2.
2. Develop two different algorithms that will play Reverse 2048 against each other. The selected
algorithms will exclusively be referred to as Alg 1 and Alg 2 (no other names will be
accepted).For example:
(a) Alg 1 could be a random move selection strategy.
(b) Alg 2 could be a heuristic-based AI that chooses the best move to reduce tile values
efficiently.
Please note, since this is a group project, each group member must implement one algorithm.
The final code should successfully run with both algorithms. Failure to meet this condition
will result in a penalty to both group members.
3. The two algorithms will play against each other on separate boards at the same time. The
game will start at the same spot on the both boards. The first algorithm to complete the
game will be considered the winner.
4. Implement three variations of the reverse 2048 game. The first will be the reverse 512, the
second is the reverse 256 and the third is reverse 128. For these variations, the board starts
with respective initial tile values. Please note that the original version of the reverse
2048 (max tile size of 2048) will not be implemented to ensure more games can
be completed within the maximum allowed number of moves.
5. For reverse 512, the new tiles that randomly appear on the board will have values of 256,
128 or 64 (no tile value lower than this should appear on the grid).
6. For reverse 256, the new tiles that randomly appear on the board will have values of 128, 64
or 32 (no tile value lower than this should appear on the grid).
7. For reverse 128, the new tiles that randomly appear on the board will have values of 64, 32
or 16 (no tile value lower than this should appear on the grid).
8. Implement a game that will work with board sizes of 3 × 3, 4 × 4 and 5 × 5. Your code must
automatically adjust to the varying inputs. Any hard coding for these inputs will receive a
penalty.
9. A maximum of 1000 moves per game per algorithm is allowed. If this limit is exceeded, the
game ends as unsolved.
10. Optimize game performance to ensure that the solver does not exceed a maximum of 1000
moves per game.

#Input Data
The file holding the configurations is called reverse 2048.txt. An example of
the input would be as follows:

512 , 3
128 , 4
512 , 5
256 , 4

• The second line reads as, a game of reverse 512 on a board size of 3 × 3.
• The first line reads as, a game of reverse 128 on a board size of 4 × 4.
• The second line reads as, a game of reverse 512 on a board size of 5 × 5.
• The third line reads as, a game of reverse 256 on a board size of 4 × 4.

#Output Data
This output file must be called output.txt. This file should contain information for each puzzle including the puzzle
number, which algorithm won (if it solved the puzzle in less than 1000 moves), the number of
moves made as well as each consecutive move. If the puzzle is not solved and 1000 moves are
made, do not print out all consecutive moves to the output file.
Moves will be recorded using direction, represented by a single character: ’U’ for up, ’D’ for down,
’L’ for left, and ’R’ for right.
An example of an output file for three variations of the reverse 512 games would look as follows:
