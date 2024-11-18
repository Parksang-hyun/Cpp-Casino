#pragma once
#ifndef SUTDAGAME_H
#define SUTDAGAME_H

#include <iostream>
#include <string>


using namespace std;

enum JOKBO {
    KK_00, // ����
    KK_01,
    KK_02,
    KK_03,
    KK_04,
    KK_05,
    KK_06,
    KK_07,
    KK_08,
    KK_09, // ����
    TJ_46 = 11, // ����
    TJ_40, // ���
    TJ_10, // ���
    TJ_19, // ����
    TJ_14, // ����
    TR_49, // ����
    MGU_49, // �۱�
    TJ_12, // �˸�
    DD_01 = 31, // ��
    DD_02,
    DD_03,
    DD_04,
    DD_05,
    DD_06,
    DD_07,
    DD_08,
    DD_09,
    DD_10, // �嶯
    DJ_XX = 50, // ������
    KD_13 = 100,
    KD_18,
    KD_38 = 200,
    AM_XX = 500 // ������
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
