#pragma once
#ifndef CASINO_H
#define CASINO_H
int gameMoney = 1000;  // �⺻ ���ӸӴ�
void saveGameMoney();
void loadGameMoney();
// �ε� ȭ�� ��� �Լ�
void showLoadingScreen();

// ���� �޴� ��� �Լ�
int displayMainMenu();

// �� ���� ���� �Լ�
void PlaySlotMachine();
void PlaySnailRace();
void PlaySeotda();
void PlayRussianRoulette();
void PlayBlackjack();
void Print_Casino();

#endif // CASINO_H
