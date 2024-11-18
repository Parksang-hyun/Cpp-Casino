#pragma once
#ifndef SNAILRACE_H
#define SNAILRACE_H

#include <vector>
using namespace std;

// ���� ���� ����
extern const int trackLength; // ���� ����
extern const int numSnail;    // �������� ��
extern int money;             // �÷��̾� ����Ʈ

// �Լ� ����
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
