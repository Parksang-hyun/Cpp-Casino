#pragma once
#ifndef RUSSIANROULETTE_H
#define RUSSIANROULETTE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 노란색 텍스트 출력 함수
void displayYellowText(const string& text);

// 메뉴 출력 함수
void displayMenu();

// 게임 설명 출력 함수
void displayGameDescription();

// 배팅 금액 설정 함수
int bettingMenu(int availableAmount);

// 플레이어 클래스 정의
class Player {
public:
    string name;
    int health;
    vector<string> items;

    Player(string n);

    // 아이템 추가 함수
    void addItem(const string& item);

    // 상태 출력 함수
    void showStatus() const;

    // 총 쏘기 함수
    bool shoot(Player* opponent, vector<string>& bullets, bool nextShotDoubleDamage, bool isDealer = false);

    // 아이템 사용 함수 (수갑 포함)
    bool useItem(const string& item, Player* opponent, vector<string>& bullets, bool& skipOpponentTurn, bool& nextShotDoubleDamage);

    // 자동 아이템 사용 함수
    void useRandomItems(Player* opponent, vector<string>& bullets, bool& skipOpponentTurn, bool& nextShotDoubleDamage);

    // 수동 아이템 선택 함수
    void useSelectedItems(Player* opponent, vector<string>& bullets, bool& skipOpponentTurn, bool& nextShotDoubleDamage);
};

// 게임 클래스 정의
class BuckshotRoulette {
public:
    vector<string> bullets;
    Player& dealer;
    Player& player;
    bool skipOpponentTurn;
    bool nextShotDoubleDamage;
    int betAmount;
    int turnCounter;
    int& availableAmount;

    BuckshotRoulette(Player& p1, Player& p2, int bet, int& amount);

    // 총알 초기화
    void initializeBullets();

    // 아이템 분배 함수
    void distributeItems();

    // 상태 출력 함수
    void showPlayersStatus() const;

    // 딜러 턴 함수
    bool dealerTurn();

    // 플레이어의 턴 함수
    bool playerTurn();

    // 게임 시작 함수
    void startGame();

    // 실탄을 맞았는지 확인하는 함수
    void resolveShot(const string& bullet, Player& target);

    // 남은 모든 총알이 실탄인지 확인하는 함수
    bool areAllRemainingBulletsLive();
};

// 게임 플레이 함수
void Play_Roulette(int *num);

#endif // RUSSIANROULETTE_H
