#pragma once
#ifndef SUTDAGAME_H
#define SUTDAGAME_H

#include <iostream>
#include <string>


using namespace std;

enum JOKBO {
    KK_00, // ∏¡≈Î
    KK_01,
    KK_02,
    KK_03,
    KK_04,
    KK_05,
    KK_06,
    KK_07,
    KK_08,
    KK_09, // ∞©ø¿
    TJ_46 = 11, // ºº∑˙
    TJ_40, // ¿ÂªÁ
    TJ_10, // ¿ÂªÊ
    TJ_19, // ±∏ªÊ
    TJ_14, // µ∂ªÁ
    TR_49, // ±∏ªÁ
    MGU_49, // ∏€±∏
    TJ_12, // æÀ∏Æ
    DD_01 = 31, // ∂Ø
    DD_02,
    DD_03,
    DD_04,
    DD_05,
    DD_06,
    DD_07,
    DD_08,
    DD_09,
    DD_10, // ¿Â∂Ø
    DJ_XX = 50, // ∂Ø¿‚¿Ã
    KD_13 = 100,
    KD_18,
    KD_38 = 200,
    AM_XX = 500 // æœ«‡æÓªÁ
};

struct sutda {
    int number;
    string shape;
};

struct User {
    string name;
    int money = 10000;
    sutda deck1;
    sutda deck2;
    int jokbo;

    void Print(User* player, int input, int max, int wincount);
};

void Swap(sutda* Card, int sour, int dest);
void Shuffle(sutda* Card);
void MakeJokbo(User* player);
void Play_Sutda(int* num);

#endif // SUTDAGAME_H
