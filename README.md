Let's play a game!

This is a 4-players card game called "Straights" written in C++.
1. A player can either be a computer or human.
2. Players take turn playing or discards cards from their hand.
3. Every round, the score is counted from the discards pile of each player.
4. The player with the least score wins.
5. If a player quits, they will be replaced by a computer.

The program tells the player what legal moves they have and prevents any illegal moves.
To play a card, "play <card>".
To discard a card, "discard <card>".
To quit as a player, "ragequit".
To exit the program, "quit".
To see the shuffled deck, "deck" (not used as a player).

Rules:
- The player with the 7 of spades starts.
- These are the only legal moves after the 7 of spades is played:
  1. 7 of any suit.
  2. one rank lower or one rank higher, and with the same symbol as cards already played.
  3. If no move, discard a card.
  
How to run the program:
- Download the code.
- Navigate to the folder on command prompt, or open the folder on VSCode.
- On the terminal, type "make" to create the executable "straights".
- Type "./straights" to run the executable.
