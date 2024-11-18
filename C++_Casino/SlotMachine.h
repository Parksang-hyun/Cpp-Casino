#pragma once
#ifndef SLOTMACHINE_H
#define SLOTMACHINE_H

#include <iostream>
#include <thread>
#include <atomic>

// 전역 변수 선언
extern volatile int numa1;
extern volatile int numa2;
extern volatile int numa3;

extern volatile int num1[3];
extern volatile int num2[3];
extern volatile int num3[3];

// 함수 선언
void SetConsoleFontSize(int fontSize);
void SetColor(int color);
void SetConsole();
void CursorView(bool show);
void SetCursorPosition(int x, int y);
void Arr_rand_num_1(volatile int* arr, volatile int* num);
void Init_Slot();
void ClearNumbers();
void PrintNumbers();
void SlotMachine(std::atomic<bool>& running, std::atomic<bool> stopFlags[]);
void PrintTemplate();
int Check_Num();
void FlashJackpot();
void Flash3Match();
void Flash2Match();
void FlashSkullPirate();
void PrintJackpot();
void PrintFireworks();
void ClearFireworks();
void Print_Slot();
void Play_Slot(int* num);

#endif // SLOTMACHINE_H
