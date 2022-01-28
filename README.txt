G2

GROUP MEMBERS:
- Carolina Mendes Catarino Cerveira de Albuquerque
- Maria Eduarda Loureiro Caldeira
- Mariana de Sousa Gandra

ADDITIONAL SPECIFICATIONS:
- In order to give the user a more dynamic experience, 3 different configuration files were created for different game durations (1: short; 2: intermediate; 3: long). 
These files were named "CONFIG_NUM.txt" (1 <= NUM <= 3) and present as follows:

	WINNER POINTS: numPts
	NUMBER OF ROWS: numRows
	NUMBER OF COLUMNS: numCols
	SIZE OF THE RACK: rackSize
	VALID WORDS: wordFile
	LETTERS:
	let1 occ1
	let2 occ2
	...
	letn occn

where numPts specifies the amount of points required to win the game, numRows and numCols specify the number of rows an columns of the board, respectively, rackSize specifies the size 
of the rack, wordFile is the name of the text file that stores the list of valid words (this text file should be saved in the same directory as the program), leti is a letter and occi 
specifies the amount of times that leti appears on the game. 
Using these files, the user can try different versions of the game and play with non-square boards. There is also the possibility of playing with the originaly provided configurations 
(file "CONFIG_0.txt"). The user should have all the provided text files saved in the same directory as the program (a warning is shown if the file corresponding to the selected game mode 
isn't properly saved in the user's computer).

- If a player inserts a word that isn't part of the given list of valid words, a warning is shown and the player has the opportunity to try another word. If the player inserts 3 
consecutive non valid words, they lose their turn.

- When a player gives up, their score is removed from the board. The letters they had on the board keep the players' color until they are stollen.

PROGRAM'S STATE OF DEVELOPMENT:
- The developed program achieves all of the proposed goals.
- Improvements: 
	* If a player doesn't insert their name, they are given a name by default (PlayerX, being X the number of the player).
	* As stated above, the user has the opportunity to choose between different playing modes (some of these modes include the possibility of using non-square boards).
	* As stated above, if a player inserts 3 consecutive non valid words, they lose their turn. Besides, it is considered that the player passed their turn, to prevent the game from 
	being endless if a player refuses to pass.
	* The usage of "object oriented programming" improved the organization of the code.
	* The usage of STL containers and functions improved the efficiency of the program. As an example, using a set to save the list of words considered valid made the search for the 
	played words on that list much quicker than the previously implemented method. In fact, with this improvment we were able to overcome one of the difficulties we pointed in the 
	previous assignement (quoting: "It would be convenient to find a more efficient way to search for the word in the list of valid words (because the list is being searched from top 
	to bottom until a correspondence is found, which is particularly costful if the searched word starts by "Z").")

MAIN DIFFICULTIES:
- Verification of the validity of all the new words formed perpendicularly to a new word placed on the board (when a new word is placed side by side with an old one, the program confirms
that the adjacent letters of the old word form complete words with the letters of the new word).