# Soha
Topic: Poker game player simulation

Description: I use C++ classes to simulate player in a poker (Soha) game. Many functions need to be implemented in order to simulate a complete poker game. However, in this assignment I ONLY simulate the player part of the game.

There is more than one way to play a poker game but the basic rules for counting points for a hand of cards are the same. Each user is given a set of 5 cards, called a hand. The face values (pips) and patterns of the five cards determine the order of a hand of cards. For example, a pattern consisting of two cards of the same pip is called a pair. A pattern of cards with five consecutive pips is called a straight.

I have two classes to implement in this simulation: Card and SHPlayer. The Card class encapsulates what a regular card has in a poker game: pip and suit (or a unique ID number for a combination of pip and suit). A user of the Card class calls its member functions to query and set card ID's or other attributes. The SHPlayer class encapsulates what a poker player needs to have. For example, a player needs to keep track of a hand of 5 cards given one by one. I also  check for overflows on array indices.



