#pragma once
#ifndef SNAILRACE_H
#define SNAILRACE_H

#include <vector>
using namespace std;

// 전역 변수 선언
extern const int trackLength; // 경주 길이
extern const int numSnail;    // 달팽이의 수
extern int money;             // 플레이어 포인트

// 함수 선언
void clearScreen();
void textcolor(int foreground, int background);
void SnailTitle(int color);
void drawRace(const vector<int>& positions);
int SnailSelect();
int SnailPayin();
int SnailStart();
void SnailPayout(int select_snail, int betting, int win_snail);
void SnailDescription();
void Play_Snail(int *num);

#endif // SNAILRACE_H
