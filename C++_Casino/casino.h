#pragma once
#ifndef CASINO_H
#define CASINO_H
int gameMoney = 1000;  // 기본 게임머니
void saveGameMoney();
void loadGameMoney();
// 로딩 화면 출력 함수
void showLoadingScreen();

// 메인 메뉴 출력 함수
int displayMainMenu();

// 각 게임 시작 함수
void PlaySlotMachine();
void PlaySnailRace();
void PlaySeotda();
void PlayRussianRoulette();
void PlayBlackjack();
void Print_Casino();

#endif // CASINO_H
