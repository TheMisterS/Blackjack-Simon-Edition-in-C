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

typedef struct player {
Card *dealers_cards;
int ace_count;
int hand_value;
int played_cards;
}Player;

//PROTOTYPES
void initialiseDeck(Deck *deck);
void initialise_player(Player *player);
void shuffle(Deck *deck);
Card getTopCard(Deck *deck, int unusedCards);
void print_card(Card);
int calculate_card_value(int card_value, Player *player);
int calculate_card_value_special(int card_value);
int count_card_sum(int value_first_card, int value_second_card, Player *player);



int main(){
//variables
Player dealer;
Player player;
int game_state = 1;

Deck play_deck;
char *input_char_temp = (char*)calloc(50, sizeof(char));

//TEST
srand(time(NULL));
initialise_player(&dealer);
initialise_player(&player);

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
con_clear();









printf("The dealer's cards:\n");
dealer.dealers_cards[0] = getTopCard(&play_deck,  play_deck.unusedCards);
dealer.dealers_cards[1] = getTopCard(&play_deck,  play_deck.unusedCards);
dealer.hand_value = count_card_sum(calculate_card_value(dealer.dealers_cards[0].valuee, &dealer), calculate_card_value(dealer.dealers_cards[1].valuee, &dealer), &dealer);
print_card(dealer.dealers_cards[0]);
printf("XX\n");

printf("Dealers hand value is: %d + X\n", calculate_card_value_special(dealer.dealers_cards[0].valuee));
dealer.played_cards = 2;


printf("Your cards: \n");
player.dealers_cards[0] = getTopCard(&play_deck,  play_deck.unusedCards);
print_card(player.dealers_cards[0]);
player.dealers_cards[1] = getTopCard(&play_deck,  play_deck.unusedCards);
player.hand_value = count_card_sum(calculate_card_value(player.dealers_cards[0].valuee, &player),calculate_card_value(player.dealers_cards[1].valuee, &player), &player);
print_card(player.dealers_cards[1]);
printf("Players hand value is: %d\n", player.hand_value);
player.played_cards = 2;
// zaidimo flagas ar toliau zaist laikinas











if(player.hand_value == 21){
    game_state = 0;
}


while(game_state > 0){
    printf("Do you wish to Hit or Stand? Press (H/S)\n");
    fgets(input_char_temp,50,stdin);

    while((*input_char_temp != 'h') && (*input_char_temp != 's') && (*input_char_temp != 'S') && (*input_char_temp != 'H')){
        printf("You have entered an incorrect value, please try again! \n");
        printf("Do you wish to Hit or Stand? Press (H/S)\n");
        fgets(input_char_temp,50,stdin);
    }

    if(*input_char_temp == 'h' || *input_char_temp == 'H'){
        printf("The card you pulled is: \n");
        player.dealers_cards[player.played_cards] = getTopCard(&play_deck,  play_deck.unusedCards);
        print_card(player.dealers_cards[player.played_cards]);
        player.hand_value = count_card_sum(player.hand_value, calculate_card_value(player.dealers_cards[player.played_cards].valuee, &player), &player);
        player.played_cards++;
        printf("Players hand value is: %d\n", player.hand_value);
        if(player.hand_value  == 21){
            game_state = 0; //player blackjack state
        }else if(player.hand_value > 21){
            game_state = -1;//player lost state
        }
    }else{
       game_state = -2; //player stayed state
    }
}

while(game_state == 0 || game_state == -2){
    while(dealer.hand_value < 17 && (game_state == 0 ||game_state == -2)){
    dealer.dealers_cards[dealer.played_cards] = getTopCard(&play_deck,  play_deck.unusedCards);
    print_card(dealer.dealers_cards[dealer.played_cards]);
    dealer.hand_value = count_card_sum(dealer.hand_value,calculate_card_value(dealer.dealers_cards[dealer.played_cards].valuee, &dealer),&player);
        if (dealer.hand_value > 21){
           game_state = 2; //dealer overstepped = insta win for player
        }else if(dealer.hand_value == 21){
            game_state = 3; // dealer blackjack = insta lose for player
        }
    }
    if(game_state != 2 && game_state != 3){
        if(dealer.hand_value >= player.hand_value){
            game_state = 4; //dealer wins bcus higher
        }else if(dealer.hand_value < player.hand_value)
            game_state = 5;
    }


}

switch(game_state){
    case -1:
        printf("You LOST because you overstepped 21!\n");
        break;
    case 2:
        printf("You WON because dealer overstepped 21!\n");
        break;
    case 3:
        printf("Dealer WON because he got a BLACKJACK!\n");
        break;
    case 4:
        printf("Dealer Wins because his hand value or equal to yours!\n");
        break;
    case 5:
        printf("You WON!!!!!!!!\n");
        break;





}
printf(" state is :%d", game_state);
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
    if(top_card.valuee == 11){
        printf("J%c\n",top_card.suit);
    }else if(top_card.valuee == 12){
        printf("Q%c\n",top_card.suit);
    }else if(top_card.valuee == 13){
        printf("K%c\n",top_card.suit);
    }else if(top_card.valuee == 14){
        printf("A%c\n",top_card.suit);
    }else{
        printf("%d%c\n",top_card.valuee, top_card.suit);
    }

}
int calculate_card_value(int card_value, Player *player){
int value;
if(card_value <= 10){
    return card_value;
}else if(card_value > 10 && card_value < 14){
    value = 10;
    return value;
}else if(card_value == 14){
player->ace_count += 1;
return 11;
}
return 0;
}

int calculate_card_value_special(int card_value){
int value;
if(card_value <= 10){
    return card_value;
}else if(card_value > 10 && card_value < 14){
    value = 10;
    return value;
}else if(card_value == 14){
return 11;
}
return 0;
}



int count_card_sum(int value_first_card, int value_second_card, Player *player){
int sum;
sum = value_first_card + value_second_card;
while(sum > 21 && player->ace_count > 0){
    sum = sum - 10;
    player->ace_count = player->ace_count - 1;
}
return sum;
}

void initialise_player(Player *player){
player->ace_count = 0;
player->hand_value = 0;
player->played_cards = 0;
player->dealers_cards = (Card*)calloc(decksize, sizeof(Card));
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
