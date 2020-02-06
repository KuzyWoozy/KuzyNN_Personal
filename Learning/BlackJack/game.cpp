#include <iostream>
#include <string>
#include <random>

void shuffleDeck(int *deck) {
    int* addr1;
    int* addr2;
    int* buffer;

    std::mt19937 mersenne(static_cast<std::mt19937::result_type>(0));
    std::uniform_int_distribution<int> die(0, 51);

    for (int count{0}; count < 100; count++) {
        
        addr1 = deck+die(mersenne);
        addr2 = deck+die(mersenne);

        buffer = addr2;

        *addr2 = *addr1;
        *addr1 = *buffer;

    }
    for (int count{0} ; count < 52;count++) {
        std::cout << *(deck+count) << '\n';
    }
}

int* createDeck() {
    int *deck {new int[52]};
    int count{0};
    while(count < 12) {
        deck[count] = 10;
        count++;
    }
    while(count < 16) {
        deck[count] = 11;
        count++;
    }
    int ref;
    for (int value{2}; value <= 10; value++) {
        ref = (count+4);
        while(count<ref) {
            deck[count] = value;
            count++;
        }
    }

    shuffleDeck(deck);
    return deck;
}

int draw() {
    static int* deck {createDeck()};
    static int acc{0};
    return *(deck+acc++);
}

void playerPlay(int* playerHand) {
    std::string playerChoice;
    int card;
    do {
        std::cout << "would you like to stay or tap? ";    
        std::getline(std::cin, playerChoice);
        if (playerChoice != "tap") {
            break;
        }
        card = draw();
        *(playerHand) += card;
        std::cout << card << " " << *(playerHand) << '\n';
    }
    while (*(playerHand) < 21);
}

void dealerPlay(int* dealerHand) {
    while (*(dealerHand) < 17) {
        *(dealerHand) += draw();
    }
}

void evaluate(int playerHand, int dealerHand) {
    if ((playerHand > 21) || ((21-playerHand) > (21-dealerHand))) {
        std::cout << "The house wins!" << '\n';
        std::cout << playerHand << " " << dealerHand << '\n';
    }
    else if ((21-playerHand) == (21-dealerHand)) {
        std::cout << "It's a draw!" << '\n';
    }
    else {
        std::cout << "The player wins!" << '\n';
    }
}

void play() {
    int playerHand = draw();
    int dealerHand = draw();
    
    playerPlay(&playerHand);
    dealerPlay(&dealerHand);
    evaluate(playerHand, dealerHand);
    
}


int main() {
    play();
    return 0;
}
