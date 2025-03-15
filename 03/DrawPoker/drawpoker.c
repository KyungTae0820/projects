// Draw Poker Game
//  This program implements a Draw Poker game.
//  The user can place a bet ranging from 1 to 5.
//  Five cards are dealt, and the user selects which cards to keep and which to discard.
//  The final set of cards is analyzed, and the user is awarded money based on the hand.
//  The user's current balance is displayed, and they can choose whether to continue playing.
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

#define FALSE 0;
#define TRUE 1;

void printGreeting();
int getBet();
char getSuit(int suit);
char getRank(int rank);
void getFirstHand(int cardRank[], int cardSuit[]);
void getFinalHand(int cardRank[], int cardSuit[], int finalRank[], int finalSuit[],
                  int ranksinHand[], int suitsinHand[]);
int analyzeHand(int ranksinHand[], int suitsinHand[]);

int main()
{
    int bet;
    int bank = 100;
    int i;
    int cardRank[5];
    int cardSuit[5];

    int finalRank[5];
    int finalSuit[5];
    int ranksinHand[13];
    int suitsinHand[4];
    int winnings;
    time_t t;
    char suit, rank, stillPlay;

    // This function is called outside the do...while loop and should only be executed once for the greeting message. 
    //The rest of the code, which needs to be repeated, should be placed inside the loop.

    printGreeting();

    // Repeats each time the user plays a round of Draw Poker.
    for (;;)
    {
        bet = getBet();
        srand(time(&t));
        getFirstHand(cardRank, cardSuit);

        printf("Your Five Cards: \n");

        for (int i = 0; i < 5; i++)
        {
            suit = getSuit(cardSuit[i]);
            rank = getRank(cardRank[i]);
            printf("Card #%d: %c%c\n", i + 1, rank, suit);
        }
       // These two arrays are used to calculate the player's hand card values. They should be initialized to 0 before use.
        for (i = 0; i < 4; i++)
        {
            suitsinHand[i] = 0;
        }
        for (i = 0; i < 13; i++)
        {
            ranksinHand[i] = 0;
        }

        getFinalHand(cardRank, cardSuit, finalRank, finalSuit, ranksinHand, suitsinHand);

        printf("Your Final Card: \n");

        for (i = 0; i < 5; i++)
        {
            suit = getSuit(cardSuit[i]);
            rank = getRank(cardRank[i]);
            printf("Card #%d: %c%c\n", i + 1, rank, suit);
        }

        winnings = analyzeHand(ranksinHand, suitsinHand);

        printf("You Win!: %d! \n", bet * winnings);

        bank = bank - bet + (bet * winnings);

        printf("\nYour current balance %d. \n", bank);

        printf("\nContinue? y or n");
        for (;;)
        {
            scanf(" %c", &stillPlay);
            if (stillPlay == 'y')
            {
                break;
            }
            else if (stillPlay =='n')
            {
                exit(0);
            }
            else
            {
                printf("Input Invalid. Choose between c and q");
            }
        }
    }
}

void printGreeting()
{
    printf("*******************************************************\n");
    printf("\n\tWelcome to the casino of a complete novice. \n\n");
    printf("\tHome of Draw Poker. \n\n");
    printf("*******************************************************\n");
    printf("The rules are as follows: \n");
    printf("It starts with 100 points. Once you bet, ");
    printf("It's between 1 and 5. \n");
    printf("You will receive 5 cards at first. ");
    printf("Which card to throw away and which card to keep ");
    printf("You can choose from them. \n");
    printf("\nThe score for the card combination is as follows: I bet one point.\n");
    printf("Assume Points Below! \n");
    printf("\nHigh Card\t\t\t0 Point");
    printf("\nPair\t\t\t\t1 Point");
    printf("\nTwo Pair\t\t\t2 Point");
    printf("\nThree Card\t\t\t3 Point");
    printf("\nStraight\t\t\t4 Point");
    printf("\nFlush\t\t\t\t5 Point");
    printf("\nFull House\t\t\t8 Point");
    printf("\nPoker\t\t\t\t10 Point");
    printf("\nStraight Flush\t\t\t20 Point");
    printf("\n\nHave a Good time!!\n\n");
}

// Function to handle the first 5 cards.
void getFirstHand(int cardRank[], int cardSuit[])
{
    int i, j;
    int cardDup;
    for (i = 0; i < 5; i++){
        cardDup = 0;
        do
        {
            // The card rank is one of (2 - 10, 3, Q, K, A).
            cardRank[i] = (rand() % 13);

            // The card suit is one of the four types.
            // (club, diamond, heart, spade)
            cardSuit[i] = (rand() % 4);
            // Repeat to ensure each card has a unique value.
            for (j = 0; j < i; j++){
                if ((cardRank[i] == cardRank[j]) && (cardSuit[i] == cardSuit[j])){
                    cardDup = 1;
                }
            }
        } while (cardDup == 1);
    }
}

// Function to assign a character based on the card suit.
char getSuit(int suit)
{
    switch (suit)
    {
        case 0:
            return ('c');
        case 1:
            return ('d');
        case 2:
            return ('h');
        case 3:
            return ('s');
    }
    return 0;
}

// Function to convert card numbers into rank-representing characters.
char getRank(int rank)
{
    switch (rank)
    {
    case 0:
        return ('A');
    case 1:
        return ('2');
    case 2:
        return ('3');
    case 3:
        return ('4');
    case 4:
        return ('5');
    case 5:
        return ('6');
    case 6:
        return ('7');
    case 7:
        return ('8');
    case 8:
        return ('9');
    case 9:
        return ('T');
    case 10:
        return ('J');
    case 11:
        return ('Q');
    case 12:
        return ('K');
    }
    return 0;
}

// Function to receive a bet input from the user ranging from 1 to 5.
int getBet()
{
    int bet;
    do
    { // Repeats as long as the user inputs a number between 0 and 5.
        printf("How much would you like to bet? (Enter as a number ");
        printf("1 through 5, 0 to exit): ");
        scanf(" %d", &bet);
        if (bet >= 1 && bet <= 5)
        {
            return (bet);
        }
        else if (bet == 0)
        {
            exit(1);
        }
        else
        {
            printf("\n\nPlease enter only numbers from 1 to 5. ");
            printf("Please enter 0 to exit. \n");
        }
    } while ((bet < 0) || (bet > 5));
    return 0;
}

// As the final function, it analyzes the final set of cards and calculates the score.
int analyzeHand(int ranksinHand[], int suitsinHand[])
{
    int num_consec = 0;
    int i, rank, suit;
    int straight = FALSE;
    int flush = FALSE;
    int four = FALSE;
    int three = FALSE;
    int pairs = 0;

    for (suit = 0; suit < 4; suit++)
        if (suitsinHand[suit] == 5)
            flush = TRUE;
    rank = 0;

    while (ranksinHand[rank] == 0)
        rank++;

    for (; rank < 13 && ranksinHand[rank]; rank++)
        num_consec++;

    if (num_consec == 5)
    {
        straight = TRUE;
    }
    for (rank = 0; rank < 13; rank++)
    {
        if (ranksinHand[rank] == 4)
            four = TRUE;
        if (ranksinHand[rank] == 3)
            three = TRUE;
        if (ranksinHand[rank] == 2)
            pairs++;
    }
    if (straight && flush)
    {
        printf("Straight Flush\n\n");
        return (20);
    }
    else if (four)
    {
        printf("Poker\n\n");
        return (10);
    }
    else if (three && (pairs == 1))
    {
        printf("Full House\n\n");
        return (8);
    }
    else if (flush)
    {
        printf("Plus\n\n");
        return (5);
    }

    else if (straight)
    {
        printf("Straight\n\n");
        return (4);
    }
    else if (three)
    {
        printf("Three Card\n\n");
        return (3);
    }
    else if (pairs == 2)
    {
        printf("Two Pairs\n\n");
        return (2);
    }
    else if (pairs == 1)
    {
        printf("Pair\n\n");
        return (1);
    }
    else
    {
        printf("High Card\n\n");
        return (0);
    }
}

// This function iterates through the initial five cards and asks the user whether they want to keep each card.
// If the user selects "No," the card is replaced.
void getFinalHand(int cardRank[], int cardSuit[], int finalRank[], int finalSuit[], int ranksinHand[], int suitsinHand[])
{
    int i, j, cardDup;
    char suit, rank, ans;
    for (i = 0; i < 5; i++)
    {
        suit = getSuit(cardSuit[i]);
        rank = getRank(cardRank[i]);
        printf("Do you want to keep this card? #%d: %c%c?", i + 1, rank, suit);
        printf("\nPlease answer. (Y/N): ");
        scanf(" %c", &ans);

        if (toupper(ans) == 'Y')
        {
            finalRank[i] = cardRank[i];
            finalSuit[i] = cardSuit[i];
            ranksinHand[finalRank[i]]++;
            suitsinHand[finalSuit[i]]++;
            continue;
        }
        else if (toupper(ans) == 'N')
        {
            cardDup = 0;
            do
            {
                cardDup = 0;
                
                finalRank[1] = (rand() % 13);
                finalSuit[i] = (rand() % 4);
                // 새로운 카드를 5개의 원 카드와 겹치지 않는지 검사한다•
                for (j = 0; j < 5; j++)
                {
                    if ((finalRank[i] == cardRank[j]) && (finalSuit[i] == cardSuit[j]))
                        {
                            cardDup = 1;
                        }
                }
                // 새로 꺼낸 카드끼리 겹치지 않는지 검사한다.
                for (j = 0; j < i; j++)
                {
                    if ((finalRank[i] == finalRank[j]) && (finalSuit[i] == finalSuit[j]))
                    {
                        cardDup = 1;
                    }
                }
            } while (cardDup == 1);
            ranksinHand[finalRank[i]]++;
            suitsinHand[finalSuit[i]]++;
        }
    }
}