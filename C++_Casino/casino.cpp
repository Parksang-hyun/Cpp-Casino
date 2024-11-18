#include <iostream>
#include <thread>   // for sleep functionality
#include <chrono>   // for time-based sleep
#include <cstdlib>  // for system("cls/clear")
#include <windows.h>
#include "SlotMachine.h"
#include "SnailRace.h"
#include "RussianRoulette.h"
#include "SutdaGame.h"
#include "blackjack.h"
#include <fstream>  // ���� �����
using namespace std;

extern int gameMoney;

// ���ӸӴ� ���� �Լ�
void saveGameMoney() {
    ofstream outFile("game_money.txt");
    if (outFile.is_open()) {
        outFile << gameMoney;
        outFile.close();
        cout << "���ӸӴϰ� ���������� ����Ǿ����ϴ�!\n";
    }
    else {
        cout << "���ӸӴϸ� �����ϴµ� �����߽��ϴ�.\n";
    }
}

// ���ӸӴ� �ҷ����� �Լ�
void loadGameMoney() {
    ifstream inFile("game_money.txt");
    if (inFile.is_open()) {
        inFile >> gameMoney;
        inFile.close();
        cout << "���ӸӴϸ� ���������� �ҷ��Խ��ϴ�! ���� ���ӸӴ�: " << gameMoney << "\n";
    }
    else {
        cout << "����� ���ӸӴϰ� �����ϴ�. �⺻ ���ӸӴϷ� �����մϴ�.\n";
    }
}

// �ε� ȭ�� (ī���� ���� ���)
void showLoadingScreen() {
    SetColor(14);
    clearScreen();
    cout << "\n\n" << endl;
    cout << "============================================================\n";
    cout << "||                                                        ||\n";
    cout << "||                     C A S I N O                        ||\n";
    cout << "||                                                        ||\n";
    cout << "||           �ڡ١� WELCOME TO THE CASINO �ڡ١�          ||\n";
    cout << "||                                                        ||\n";
    cout << "============================================================\n";
    cout << "\n\n�ε� ���Դϴ�. ��ø� ��ٷ��ּ���...\n";

    // �ε� �ð� ���� ��� (2��)
    this_thread::sleep_for(chrono::seconds(4));
}

int displayMainMenu() {
    int choice;
    cout << "" << endl;
    cout << "���� ���� �Ӵ� : " << gameMoney << endl;
    cout << "==================== ī���� ���� ====================\n";
    cout << "1. ���� �ӽ� (Slot Machine)\n";
    cout << "2. ������ ���� (Snail Race)\n";
    cout << "3. ���� (Seotda)\n";
    cout << "4. ���þ� �귿 (Russian Roulette)\n";
    cout << "5. ���� (Blackjack)\n";
    cout << "6. Save\n";
    cout << "7. �Ӵ� ����\n";
    cout << "8. ���� (Exit)\n";
    cout << "=====================================================\n";
    cout << "���ϴ� ������ �����ϼ���: ";
    cin >> choice;
    return choice;
}

void PlaySlotMachine() {
    cout << "���� �ӽ� ������ �����մϴ�...\n";
    Play_Slot(&gameMoney);
   
}

void PlaySnailRace() {
    cout << "������ ���� ������ �����մϴ�...\n";
    SetColor(15);
    Play_Snail(&gameMoney);
}

void PlaySeotda() {
    cout << "���� ������ �����մϴ�...\n";
    SetColor(15);
    Play_Sutda(&gameMoney);
}

void PlayRussianRoulette() {
    cout << "���þ� �귿 ������ �����մϴ�...\n";
    SetColor(15);
    Play_Roulette(&gameMoney);
}

void PlayBlackjack() {
    cout << "���� ������ �����մϴ�...\n";
    SetColor(15);
    Play_BlackJack(&gameMoney);
}

void Print_Casino()
{
    // ���� ���� �� ����� ���ӸӴ� �ҷ�����
    loadGameMoney();

    
    // ó���� �ε� ȭ���� ������
    showLoadingScreen();

    int choice;

    while (true) {
        clearScreen();
        SetColor(14);
        choice = displayMainMenu();

        switch (choice) {
        case 1:
            PlaySlotMachine();
            saveGameMoney();  // ���ӸӴ� ����
            break;
        case 2:
            PlaySnailRace();
            saveGameMoney();  // ���ӸӴ� ����
            break;
        case 3:
            PlaySeotda();
            saveGameMoney();  // ���ӸӴ� ����
            break;
        case 4:
            PlayRussianRoulette();
            saveGameMoney();  // ���ӸӴ� ����
            break;
        case 5:
            PlayBlackjack();
            saveGameMoney();  // ���ӸӴ� ����
            break;
        case 6:
            saveGameMoney();  // ���ӸӴ� ����
            cout << "������ �����ϰ� �����մϴ�. �����մϴ�!\n";
            return;
            break;
        case 7:
            cout << "���ӸӴ� ������ ���Ͻø� \"�ǻ���\"�� ã�ƿ�����\n";
            break;
        case 8:
            cout << "���� ����\n";
            break;
        default:
            cout << "�߸��� �����Դϴ�. �ٽ� �������ּ���.\n";
        }

        cout << "�ƹ� Ű�� ���� ����ϼ���...\n";
        cin.ignore();
        cin.get();
    }

}

