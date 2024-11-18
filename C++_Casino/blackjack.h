#pragma once
#pragma once
// blackjack.h
#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Card {
    int value;      // 카드의 값 (1~13)
    char suit;      // 카드의 슈트 (스위트 모양)
};

// 함수 선언
char getSuitSymbol(char suit);
void clearScreen();
int GameMenu();
vector<Card> createDeck();
int calculateHandValue(const vector<Card>& hand);
void printCardsHorizontally(const vector<Card>& cards);
void printHand(const vector<Card>& hand, const string& name);
void printGameDescription();
void playBlackjack(int* num);
void Play_BlackJack(int* num);

#endif // BLACKJACK_H
