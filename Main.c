#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "con_lib.h"


#define blackjack 21
#define decksize 52

//Structs
typedef struct deck {
    int *value;
    char *suit;
    int  IsShuffled;
}Deck;

typedef struct player {
    int balance;
    int currentBet;
    int count;
}Player;

typedef struct dealer {
    int count;

}Dealer;

//Prototypes
void initialiseDeck(Deck *deck);
void initialisePlayer(Player *players_hand);
void initialiseDealer(Dealer *dealers_hand);
void shuffle(Deck *deck);

int main(){
char *start_text ="Hello and welcome";
puts(start_text);

//variables
Player players_hand;
Dealer dealers_hand;
Deck play_deck;

initialiseDeck(&play_deck);
shuffle(&play_deck);
for(int i = 0; i < 52;++i){

    printf("%d", *(play_deck.value + i));
    printf("%c \n", *(play_deck.suit + i));
}

return 0;
}

//Functions
void initialiseDeck(Deck *deck){
    int index = 1;
    deck->suit = (char*)calloc(decksize, sizeof(char));
    deck->value = (int*)calloc(decksize, sizeof(int));

    for(int i = 0; i < 13;++i){
        *(deck->value + i) = index;
        *(deck->suit + i) = 'S';
        index++;
    }
    index = 1;
    for(int i = 13; i < 26;++i){
        *(deck->value + i) = index;
        *(deck->suit + i) = 'H';
        index++;
    }
    index = 1;
    for(int i = 26; i < 39;++i){
        *(deck->value + i) = index;
        *(deck->suit + i) = 'D';
        index++;
    }
    index = 1;
    for(int i = 39; i < 52;++i){
        *(deck->value + i) = index;
        *(deck->suit + i) = 'C';
        index++;
    }
}
void initialisePlayer(Player *players_hand){



}

void initialiseDealer(Dealer *dealers_hand){



}

void shuffle(Deck *deck){
    int i, j, index,index2;
    for (i = decksize - 1; i > 0; i--){
        j = rand() % (i + 1);
        index = *(deck->value +j);
        *(deck->value + j) = *(deck->value + i);
        *(deck->value + i) = index;
        index2 = *(deck->suit +j);
        *(deck->suit + j) = *(deck->suit + i);
        *(deck->suit + i) = index2;
}
}
//Text Samples
