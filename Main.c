#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include "con_lib.h"
#include "printables.h"

#define blackjack 21
#define decksize 52
#define starting_balance 500

//STRUCTS;
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
char checkInput(char *error_string, char desired_char_one, char desired_char_two);
int calculate_card_value(int card_value, Player *player);
int calculate_card_value_special(int card_value);
int count_card_sum(int value_first_card, int value_second_card, Player *player);
void save_game(int player_balance,int hands_played, FILE *save);
void load_save(int *player_balance,int *hands_played, FILE *save);



int main(){

//variables
FILE *save;
Player dealer;
Player player;
Deck play_deck;
int player_balance = 500;
int hands_played = 0;
int current_bet = 50;
int game_state = 1;

char *input_char_temp = (char*)calloc(50, sizeof(char));
int *input_int_temp = (int*)calloc(50, sizeof(int));
char input_index;

char hit_stand[] = "Do you wish to Hit or Stand? Press (H/S)";
char continue_playing[] = "Do you wish to continue playing? Press (Y/N)";
char save_option[] = "Do you wish to save the game before exiting? (Y/N)!";

//TEST
srand(time(NULL));
initialise_player(&dealer);
initialise_player(&player);
initialiseDeck(&play_deck);

//GAME
print_intro_logo();
fgets(input_char_temp,50,stdin);
while((*input_char_temp != 'R') && (*input_char_temp != 'r') && (*input_char_temp != 'S') && (*input_char_temp != 's') && (*input_char_temp != 'p') &&(*input_char_temp != 'P') ){
        printf("You have entered an incorrect value, please try again! \n");
        fgets(input_char_temp,50,stdin);
    }
if(*input_char_temp == 'r' || *input_char_temp == 'R'){
    printf("Rules xoxo \n");
    con_sleep(2);
    con_clear();
}else if(*input_char_temp == 's' || *input_char_temp == 'S'){
    load_save(&player_balance,&hands_played ,save);
    printf("Save succesfully loaded! \n");
    con_sleep(1.5);
    con_clear();
   // printf("Couldn't open/find save file \n"); //possible case!!!
}else if(*input_char_temp == 'p' || *input_char_temp == 'P'){
    con_clear();
}


//from here the game loops till the player does not want to play anymore.
while(game_state == 1){
    shuffle(&play_deck);


    printf("Hands played: %d\n",hands_played); //Players played hand count,balance and current bet are displayed.
    printf("YOUR CURRENT BALANCE IS: %d\n", player_balance);
    printf("YOUR BET:%d\n", current_bet);
    //INSERT INT VALIDATION!!!!!!!!!!!!!!!! AND CUSTOM BET = current_bet!!!!!!!!!!!!!!!!!!!!!!

    printf("The dealer's cards:\n"); //Dealer's first two cards are printed in this section, one face down(unknown to the player)
    dealer.dealers_cards[0] = getTopCard(&play_deck,  play_deck.unusedCards);
    dealer.dealers_cards[1] = getTopCard(&play_deck,  play_deck.unusedCards);
    dealer.hand_value = count_card_sum(calculate_card_value(dealer.dealers_cards[0].valuee, &dealer), calculate_card_value(dealer.dealers_cards[1].valuee, &dealer), &dealer);
    print_card(dealer.dealers_cards[0]);
    printf("XX\n");

    printf("Dealers hand value is: %d + X\n\n", calculate_card_value_special(dealer.dealers_cards[0].valuee)); //Dealer's hand value is calculated and shown.
    dealer.played_cards = 2;


    printf("Your cards: \n"); //Player's first two cards are pulled and displayed + the sum of their value;
    player.dealers_cards[0] = getTopCard(&play_deck,  play_deck.unusedCards);
    print_card(player.dealers_cards[0]);
    player.dealers_cards[1] = getTopCard(&play_deck,  play_deck.unusedCards);
    player.hand_value = count_card_sum(calculate_card_value(player.dealers_cards[0].valuee, &player),calculate_card_value(player.dealers_cards[1].valuee, &player), &player);
    print_card(player.dealers_cards[1]);
    printf("Players hand value is: %d\n", player.hand_value);
    player.played_cards = 2;



    if(player.hand_value == 21){  //If players gets a BJ the option to hit is skipped
        game_state = 0;
        con_sleep(1);
    }


    while(game_state > 0){
        input_index = checkInput(hit_stand, 'h', 's'); //player is presented with the option to remain or to get another card
        if(input_index == 'h' || input_index == 'H'){
            printf("The card you pulled is: \n");
            player.dealers_cards[player.played_cards] = getTopCard(&play_deck,  play_deck.unusedCards);
            print_card(player.dealers_cards[player.played_cards]);
            player.hand_value = count_card_sum(player.hand_value, calculate_card_value(player.dealers_cards[player.played_cards].valuee, &player), &player);
            player.played_cards++;
            printf("Players hand value is: %d\n\n", player.hand_value);
            if(player.hand_value  == 21){
                game_state = 0; //player blackjack state
            }else if(player.hand_value > 21){
                game_state = -1;//player lost state
            }
        }else{
           game_state = -2; //player stayed state
        }
    }

    while(game_state == 0 || game_state == -2){  // if the player didnt lose the dealer decides if he wants to hit.
        while(dealer.hand_value < 17 && (game_state == 0 ||game_state == -2)){
            printf("Dealer hits and pulls a: \n");
            dealer.dealers_cards[dealer.played_cards] = getTopCard(&play_deck,  play_deck.unusedCards);
            print_card(dealer.dealers_cards[dealer.played_cards]);
            dealer.hand_value = count_card_sum(dealer.hand_value,calculate_card_value(dealer.dealers_cards[dealer.played_cards].valuee, &dealer),&player);
            if (dealer.hand_value > 21){
                game_state = 2; //dealer overstepped = insta win for player
                printf("Dealers hand value was: %d\n", dealer.hand_value);
            }else if(dealer.hand_value == 21){
                game_state = 3; // dealer blackjack = insta lose for player
            }else if(dealer.hand_value > 17){
                printf("Dealer decided to STAY!\n");
            }
        }
        printf("Dealers hand value is: %d\n", dealer.hand_value); //after dealer stops hitting his hand value is displayed and the winner decided
        if(game_state != 2 && game_state != 3){
            if(dealer.hand_value >= player.hand_value){
                game_state = 4; //dealer wins bcus higher
            }else if(dealer.hand_value < player.hand_value)
                game_state = 5;
        }


    }

    switch(game_state){ // possible game outcomes
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
            printf("Dealer Wins because his hand value is higher or equal to yours!\n");
            break;
        case 5:
            printf("You WON!!!!!!!!\n");
            break;

    }
    //
    if(game_state == 2 || game_state == 5){  //if players wins he gets the bet added
        player_balance = player_balance + current_bet;

    }else if(game_state == -1 || game_state == 3 || game_state == 4){ // if players loses he gets the bet removed
        player_balance = player_balance - current_bet;
    }


    input_index = checkInput(continue_playing, 'y', 'n'); // player is presented with the option to cotinue or not to continue the game
    printf("Your NEW balance is: %d\n", player_balance);
    if(input_index == 'y' || input_index == 'Y'){
        game_state = 1;
        con_clear();
    }else if(input_index == 'n' || 'N'){   // if player doesnt continue he may save the game
        game_state = -10;
        input_index = checkInput(save_option, 'y', 'n');
        if(input_index == 'y' || input_index == 'Y'){
            save_game(player_balance,hands_played,save);
        }
    }

    hands_played++;   //
    }



return 0;
}
//****************************************************************************************************************************************************************************************************

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

char checkInput(char *error_string, char desired_char_one, char desired_char_two){
    char *input_char_temp = (char*)calloc(50, sizeof(char));
    char capitalised_One = toupper(desired_char_one);
    char capitalised_Two = toupper(desired_char_two);
    char tested_char;
    printf("%s\n", error_string);
    fgets(input_char_temp,50,stdin);
    while((*input_char_temp != desired_char_one) && (*input_char_temp != capitalised_One) && (*input_char_temp != desired_char_two) && (*input_char_temp != capitalised_Two)){
        printf("You have entered an incorrect value, please try again! \n");
        printf("%s\n", error_string);
        fgets(input_char_temp,50,stdin);
    }
    tested_char = *input_char_temp;
    free(input_char_temp);
    return tested_char;
}

void save_game(int player_balance,int hands_played, FILE *save){
    save = fopen("save.bin","wb");
    fwrite(&player_balance,sizeof(int) ,1,save);
    fwrite(&hands_played,sizeof(int),1,save);
    fclose(save);
}

void load_save(int *player_balance,int *hands_played, FILE *save){
    save = fopen("save.bin","rb");
    fseek(save, 0, SEEK_SET);
    fread(player_balance ,sizeof(int),1,save);
    fread(hands_played ,sizeof(int),1,save);
    fclose(save);
}
