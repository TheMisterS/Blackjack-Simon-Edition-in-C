#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include "con_lib.h"

#define blackjack 21
#define decksize 52
#define starting_balance 500

//COMMENTS AND NOTES

// 1-10 values are normal
// 11 - is J, 12 is Q, 13 is K, 14 is A

// ace can be 11 or 1

//STRUCTS
typedef struct card {
    int valuee;
    char suit;
}Card;

typedef struct deck {
    Card *card;
    int isShuffled;
    int unusedCards;
}Deck;

//PROTOTYPES
void initialiseDeck(Deck *deck);
void shuffle(Deck *deck);
Card getTopCard(Deck *deck, int unusedCards);
void print_card(Card);

int main(){
//variables
Deck play_deck;
char input_char_temp;
//TEST
initialiseDeck(&play_deck);
shuffle(&play_deck);
for(int i = 0; i < 52;++i){
    printf("%d", play_deck.card[i].valuee);
    printf("%c \n", play_deck.card[i].suit);
}
printf("\n\n\n");
Card y = getTopCard(&play_deck, play_deck.unusedCards);
printf("%d", y.valuee);
printf("%c\n", y.suit);

//GAME
char *start_text ="Hello and welcome";
puts(start_text);
//printf("Press any key if you wish to play\n");
//getch();

printf("The dealers cards:\n");
print_card(getTopCard(&play_deck,  play_deck.unusedCards));
printf("XX\n");
printf("Your cards: \n");
print_card(getTopCard(&play_deck,  play_deck.unusedCards));
print_card(getTopCard(&play_deck,  play_deck.unusedCards));
printf("Do you wish to Hit or Stand? Press (H/S)\n");
input_char_temp = getch();
printf("%c",input_char_temp);


return 0;
}










//Functions
void initialiseDeck(Deck *deck){
    int index = 2;
    deck->card = (Card*)calloc(decksize, sizeof(Card));

    for(int i = 0; i < 13;++i){
        deck->card[i].valuee = index;
        deck->card[i].suit = 'S';
        index++;
    }
    index = 2;
    for(int i = 13; i < 26;++i){
        deck->card[i].valuee = index;
        deck->card[i].suit = 'H';
        index++;
    }
    index = 2;
    for(int i = 26; i < 39;++i){
        deck->card[i].valuee = index;
        deck->card[i].suit = 'D';
        index++;
    }
    index = 2;
    for(int i = 39; i < 52;++i){
        deck->card[i].valuee = index;
        deck->card[i].suit = 'C';
        index++;
    }
}

void shuffle(Deck *deck){
    int i, j;
    Card index,index2;
    deck->unusedCards = decksize;
    for (i = decksize - 1; i > 0; i--){
        j = rand() % (i + 1);
        index = deck->card[j];
        deck->card[j] = deck->card[i];
        deck->card[i] = index;
}
}

Card getTopCard(Deck *deck, int unusedCards){
deck->unusedCards = deck->unusedCards - 1;
return deck->card[deck ->unusedCards];
}

void print_card(Card top_card){
    printf("%d%c\n",top_card.valuee, top_card.suit);

}

//Text Samples
/*
printf(" $$$$$$\\  $$\\                                   $$\\\n");
printf("$$  __$$\\ \\__|                                  $  |\n");
printf("$$ /  \\__|$$\\ $$$$$$\\$$$$\\   $$$$$$\\  $$$$$$$\\  \\_/  $$$$$$$\\\n");
printf("\\$$$$$$\\  $$ |$$  _$$  _$$\\ $$  __$$\\ $$  __$$\\     $$  _____|\n");
printf(" \\____$$\\ $$ |$$ / $$ / $$ |$$ /  $$ |$$ |  $$ |    \\$$$$$$\\\n");
printf("$$\\   $$ |$$ |$$ | $$ | $$ |$$ |  $$ |$$ |  $$ |     \\____$$\\\n");
printf("\\$$$$$$  |$$ |$$ | $$ | $$ |\\$$$$$$  |$$ |  $$ |    $$$$$$$  |\n");
printf(" \\______/ \\__|\\__| \\__| \\__| \\______/ \\__|  \\__|    \\_______/\n");
printf("$$$$$$$\\  $$\\                     $$\\          $$$$$\\                     $$\\\n");
printf("$$  __$$\\ $$ |                    $$ |         \\__$$ |                    $$ |\n");
printf("$$ |  $$ |$$ | $$$$$$\\   $$$$$$$\\ $$ |  $$\\       $$ | $$$$$$\\   $$$$$$$\\ $$ |  $$\\\n");
printf("$$$$$$$\\ |$$ | \\____$$\\ $$  _____|$$ | $$  |      $$ | \\____$$\\ $$  _____|$$ | $$  |\n");
printf("$$  __$$\\ $$ | $$$$$$$ |$$ /      $$$$$$  / $$\\   $$ | $$$$$$$ |$$ /      $$$$$$  /\n");
printf("$$ |  $$ |$$ |$$  __$$ |$$ |      $$  _$$<  $$ |  $$ |$$  __$$ |$$ |      $$  _$$<\n");
printf("$$$$$$$  |$$ |\\$$$$$$$ |\\$$$$$$$\\ $$ | \\$$\\ \\$$$$$$  |\\$$$$$$$ |\\$$$$$$$\\ $$ | \$$\\\n");
printf("\\_______/ \\__| \\_______| \\_______|\\__|  \\__| \\______/  \\_______| \\_______|\\__|  \\__|\n");
printf("\n\n");
*/
