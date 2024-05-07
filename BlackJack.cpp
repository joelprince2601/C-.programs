#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

enum CardRank
{
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
};

enum CardSuit
{
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

struct Card
{
    CardRank rank;
    CardSuit suit;
};

int GetCardValue(const Card &card)
{
    switch (card.rank)
    {
    case ACE:
        return 11;
    case TWO:
        return 2;
    case THREE:
        return 3;
    case FOUR:
        return 4;
    case FIVE:
        return 5;
    case SIX:
        return 6;
    case SEVEN:
        return 7;
    case EIGHT:
        return 8;
    case NINE:
        return 9;
    case TEN:
    case JACK:
    case QUEEN:
    case KING:
        return 10;
    default:
        return 0;
    }
}

void PrintCard(const Card &card)
{
    std::string rankStr;
    switch (card.rank)
    {
    case ACE:
        rankStr = "Ace";
        break;
    case TWO:
        rankStr = "2";
        break;
    case THREE:
        rankStr = "3";
        break;
    case FOUR:
        rankStr = "4";
        break;
    case FIVE:
        rankStr = "5";
        break;
    case SIX:
        rankStr = "6";
        break;
    case SEVEN:
        rankStr = "7";
        break;
    case EIGHT:
        rankStr = "8";
        break;
    case NINE:
        rankStr = "9";
        break;
    case TEN:
        rankStr = "10";
        break;
    case JACK:
        rankStr = "Jack";
        break;
    case QUEEN:
        rankStr = "Queen";
        break;
    case KING:
        rankStr = "King";
        break;
    }

    std::string suitStr;
    switch (card.suit)
    {
    case CLUBS:
        suitStr = "Clubs";
        break;
    case DIAMONDS:
        suitStr = "Diamonds";
        break;
    case HEARTS:
        suitStr = "Hearts";
        break;
    case SPADES:
        suitStr = "Spades";
        break;
    }

    std::cout << rankStr << " of " << suitStr;
}

void PlayBlackjack()
{
    std::vector<Card> deck;
    for (int suit = CLUBS; suit <= SPADES; ++suit)
    {
        for (int rank = ACE; rank <= KING; ++rank)
        {
            deck.push_back({static_cast<CardRank>(rank), static_cast<CardSuit>(suit)});
        }
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::random_shuffle(deck.begin(), deck.end());

    // Deal the cards
    Card playerCard1 = deck.back();
    deck.pop_back();
    Card dealerCard1 = deck.back();
    deck.pop_back();
    Card playerCard2 = deck.back();
    deck.pop_back();
    Card dealerCard2 = deck.back();
    deck.pop_back();

    int playerScore = GetCardValue(playerCard1) + GetCardValue(playerCard2);
    int dealerScore = GetCardValue(dealerCard1) + GetCardValue(dealerCard2);

    // Display the cards
    std::cout << "Player's cards: ";
    PrintCard(playerCard1);
    std::cout << ", ";
    PrintCard(playerCard2);
    std::cout << std::endl;

    std::cout << "Dealer's cards: ";
    PrintCard(dealerCard1);
    std::cout << ", ?" << std::endl;

    // Player's turn
    char choice;
    while (playerScore < 21)
    {
        std::cout << "Do you want to hit (h) or stand (s)? ";
        std::cin >> choice;

        if (choice == 'h')
        {
            Card newCard = deck.back();
            deck.pop_back();
            std::cout << "New card: ";
            PrintCard(newCard);
            std::cout << std::endl;
            playerScore += GetCardValue(newCard);
        }
        else if (choice == 's')
        {
            break;
        }
    }

    // Dealer's turn
    while (dealerScore < 17)
    {
        Card newCard = deck.back();
        deck.pop_back();
        std::cout << "Dealer draws a new card: ";
        PrintCard(newCard);
        std::cout << std::endl;
        dealerScore += GetCardValue(newCard);
    }

    // Determine the winner
    std::cout << "Player's score: " << playerScore << std::endl;
    std::cout << "Dealer's score: " << dealerScore << std::endl;

    if (playerScore > 21)
    {
        std::cout << "Player busts! Dealer wins." << std::endl;
    }
    else if (dealerScore > 21)
    {
        std::cout << "Dealer busts! Player wins." << std::endl;
    }
    else if (playerScore == dealerScore)
    {
        std::cout << "It's a tie." << std::endl;
    }
    else if (playerScore > dealerScore)
    {
        std::cout << "Player wins." << std::endl;
    }
    else
    {
        std::cout << "Dealer wins." << std::endl;
    }
}

int main()
{
    char playAgain;
    do
    {
        PlayBlackjack();
        std::cout << "Do you want to play again? (y/n) ";
        std::cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}
