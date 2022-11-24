# College-projects
A collection of all my college projects that i've worked on along the years, at the Universidad de Buenos Aires.

All files are written in spanish as it was needed for the projects themselves, under here you can find an explanation of each project.

TP 1/2:
  A rather simple game that starts with 5 trivia questions about disney/pixar movies or series, answering all 5 correctly will have an impact on the second part of the game, three of the questions are multiple choice, another one is answering a question with an specific number and another is answered by inputting 5 numbers, which all must be primes.
  The second part of the game consists of a 2D grid in which you are able to move, the goal is to move your character to the next character, doing so swaps characters and so on until you reach the last character, then you must move on to the exit to win the game (character order: E -> V -> D -> I, exit is S). While playing you must dodge robots (R), lasers (L, which rotate around the robot they are attached to) and claws (P, which teleport you next to a robot), touching robots and lasers kills you, lasers have a longitude of 5, which is reduced to 3 if all questions of the first part were answered correctly. Every character has a different quantity of moves, which if they run out the game ends, all characters can also pick up powerups (T) which can be activated with "C" and every character has a different power.
  This project tested validation (as in everything must be generated with nothing overlapping or the inputs must be W/A/S/D/C), random numbers (everything must be generated randomly within certain limits), matrix usage (2D grid), program flow (different game states) and overall good practices.



TP 3: 
  This project was about file handling (.csv files), writing in files (while mantaining the order they are in), eliminating specific lines from them or altering them.
