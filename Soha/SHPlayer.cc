/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

#include <iostream>
#include <cstring>
#include <cassert>
#include "AnsiPrint.h"
#include "Card.h"
#include "CardPattern.h"
#include "SHPlayer.h"


using namespace std;

const char* HandTypeName[9] = {
	"Straight flush",
	"Four of a kind",
	"Full house",
	"Flush",
	"Straight",
	"Three of a kind",
	"Two pair",
	"One pair",
	"Other"
};

// constructor
SHPlayer::SHPlayer(const char* playerName)
{

}

// initialize the number of cards to 0
void
SHPlayer::start()
{
	numberofcard=0;	
}

// add a new card to the current hand
// need to protect the array from overflowing
void SHPlayer::addCard(Card newCard)
{
	cards[numberofcard]=newCard;
	numberofcard++;
}
// open the first card so it faces up
void
SHPlayer::closeFirstCard()
{
	close=13;	
}

// print the current hand to the screen graphically
void
SHPlayer::showCards() const
{
	char pokercard[12]={'\0'};
	char suit;
	for(int i=0;i<11;i++){
		for(int k=0;k<5;k++){
			if(cards[k].getSuit()==0){
				suit='S';
			}	
			else if(cards[k].getSuit()==1){
				suit='H';
			}
			else if(cards[k].getSuit()==2){
				suit='D';
			}
			else{
				suit='C';
			}
			for(int j=0;j<11;j++){
				if(k==0 && close==13){
					pokercard[j]=card[close][i][j];
				}
				else{ 
					if(card[cards[k].getPip()][i][j]=='x'){
						pokercard[j]=suit;
					}
					else{
						pokercard[j]=card[cards[k].getPip()][i][j];
					}
				}
			}
			if(suit=='S' || suit=='C'){
				AnsiPrint(pokercard,black,white,false,false);
			}
			else {
				AnsiPrint(pokercard,red,white,false,false);
			}
			cout<<" ";
		}
		cout<<endl;
	}	
}

// get the total points of the current hand
int
SHPlayer::totalPips() const
{
	int sum=0;
	for(int i=0;i<5;i++){
		sum=sum+cards[i].getPip()+1;
	}
	return sum;
}

// judge what kind of hand type you own
// you need to have 5 cards
HandType
SHPlayer::getHandPattern() 
{
	sortCards();
	if (isStraightFlush()){
		return STRAIGHT_FLUSH;
	}	
	if (isFourOfAKind()){
		return FOUR_OF_A_KIND;
	}	
	if(isFullHouse()){
		return FULL_HOUSE;
	}
	if(isFlush()){
		return FLUSH;
	}
	if(isStraight()){
		return STRAIGHT;
	}
	if(isThreeOfAKind()){
		return THREE_OF_A_KIND;
	}
	if(isTwoPair()){
		return TWO_PAIR;
	}
	if(isOnePair()){
		return ONE_PAIR;
	}
	else{
		return OTHER;
	}
}

// return the number of cards at hand
int
SHPlayer::getNumCards() const
{

}

void
SHPlayer::sortCards() 
{
	for(int i=0;i<4;i++){
		for(int j=0;j<4-i;j++){
			if(cards[j].getPip()>cards[j+1].getPip()){
				Card tempd=cards[j];
				cards[j]=cards[j+1];
				cards[j+1]=tempd;
			}
		}
	}

	for(int k=0;k<5;k++){
		sortedCards[k]=cards[k];
	}
}

// any five card sequence of same suit
bool 
SHPlayer::isStraightFlush() const
{
	return isStraight() && isFlush();	
}

// four cards of the same pip
bool 
SHPlayer::isFourOfAKind() const
{
	// O O O O X
	if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
			sortedCards[2].getPip() == sortedCards[3].getPip() &&
			sortedCards[0].getPip() == sortedCards[2].getPip() )
		return true;
	// X O O O O
	if( sortedCards[1].getPip() == sortedCards[2].getPip() &&
			sortedCards[3].getPip() == sortedCards[4].getPip() &&
			sortedCards[1].getPip() == sortedCards[3].getPip() )
		return true;

	return false;
}

// three of a kind combined with a pair
bool 
SHPlayer::isFullHouse() const
{
	// O O O X X
	if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
			sortedCards[1].getPip() == sortedCards[2].getPip() &&
			sortedCards[3].getPip() == sortedCards[4].getPip() )
		return true;
	// X X X O O
	if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
			sortedCards[2].getPip() == sortedCards[3].getPip() &&
			sortedCards[3].getPip() == sortedCards[4].getPip() )
		return true;

	return false;
}

// five cards of the same suit
bool
SHPlayer::isFlush() const
{
	for( int i = 0; i < kMaxCards - 1; i++ )
		if( sortedCards[i].getSuit() != sortedCards[i+1].getSuit() )
			return false;

	return true;
}

// five cards in sequence
bool 
SHPlayer::isStraight() const
{
	for( int i = 0; i < kMaxCards - 1; i++ )
		if( sortedCards[i].getPip() + 1 != sortedCards[i+1].getPip() )
			return false;

	return true;
}

// three cards of the same pip
bool 
SHPlayer::isThreeOfAKind() const
{
	for( int i = 0; i < kMaxCards - 2; i++ )
		if( sortedCards[i].getPip() == sortedCards[i+1].getPip() &&
				sortedCards[i].getPip() == sortedCards[i+2].getPip() )
			return true;

	return false;
}

// two cards of one pip, two cards of another pip
bool 
SHPlayer::isTwoPair() const
{
	// O O @ @ X
	if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
			sortedCards[2].getPip() == sortedCards[3].getPip() )
		return true;
	// O O X @ @
	if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
			sortedCards[3].getPip() == sortedCards[4].getPip() )
		return true;
	// X O O @ @
	if( sortedCards[1].getPip() == sortedCards[2].getPip() &&
			sortedCards[3].getPip() == sortedCards[4].getPip() )
		return true;

	return false;
}

// two cards of one pip
bool 
SHPlayer::isOnePair() const
{
	for( int i = 0; i < kMaxCards - 1; i++ )
		if( sortedCards[i].getPip() == sortedCards[i+1].getPip() )
			return true;

	return false;
}


