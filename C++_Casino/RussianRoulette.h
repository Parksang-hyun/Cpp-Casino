#pragma once
#ifndef RUSSIANROULETTE_H
#define RUSSIANROULETTE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ����� �ؽ�Ʈ ��� �Լ�
void displayYellowText(const string& text);

// �޴� ��� �Լ�
void displayMenu();

// ���� ���� ��� �Լ�
void displayGameDescription();

// ���� �ݾ� ���� �Լ�
int bettingMenu(int availableAmount);

// �÷��̾� Ŭ���� ����
class Player {
public:
    string name;
    int health;
    vector<string> items;

    Player(string n);

    // ������ �߰� �Լ�
    void addItem(const string& item);

    // ���� ��� �Լ�
    void showStatus() const;

    // �� ��� �Լ�
    bool shoot(Player* opponent, vector<string>& bullets, bool nextShotDoubleDamage, bool isDealer = false);

    // ������ ��� �Լ� (���� ����)
    bool useItem(const string& item, Player* opponent, vector<string>& bullets, bool& skipOpponentTurn, bool& nextShotDoubleDamage);

    // �ڵ� ������ ��� �Լ�
    void useRandomItems(Player* opponent, vector<string>& bullets, bool& skipOpponentTurn, bool& nextShotDoubleDamage);

    // ���� ������ ���� �Լ�
    void useSelectedItems(Player* opponent, vector<string>& bullets, bool& skipOpponentTurn, bool& nextShotDoubleDamage);
};

// ���� Ŭ���� ����
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

    // �Ѿ� �ʱ�ȭ
    void initializeBullets();

    // ������ �й� �Լ�
    void distributeItems();

    // ���� ��� �Լ�
    void showPlayersStatus() const;

    // ���� �� �Լ�
    bool dealerTurn();

    // �÷��̾��� �� �Լ�
    bool playerTurn();

    // ���� ���� �Լ�
    void startGame();

    // ��ź�� �¾Ҵ��� Ȯ���ϴ� �Լ�
    void resolveShot(const string& bullet, Player& target);

    // ���� ��� �Ѿ��� ��ź���� Ȯ���ϴ� �Լ�
    bool areAllRemainingBulletsLive();
};

// ���� �÷��� �Լ�
void Play_Roulette(int *num);

#endif // RUSSIANROULETTE_H
