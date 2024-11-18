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
#include <fstream>  // 파일 입출력
using namespace std;

extern int gameMoney;

// 게임머니 저장 함수
void saveGameMoney() {
    ofstream outFile("game_money.txt");
    if (outFile.is_open()) {
        outFile << gameMoney;
        outFile.close();
        cout << "게임머니가 성공적으로 저장되었습니다!\n";
    }
    else {
        cout << "게임머니를 저장하는데 실패했습니다.\n";
    }
}

// 게임머니 불러오기 함수
void loadGameMoney() {
    ifstream inFile("game_money.txt");
    if (inFile.is_open()) {
        inFile >> gameMoney;
        inFile.close();
        cout << "게임머니를 성공적으로 불러왔습니다! 현재 게임머니: " << gameMoney << "\n";
    }
    else {
        cout << "저장된 게임머니가 없습니다. 기본 게임머니로 시작합니다.\n";
    }
}

// 로딩 화면 (카지노 글자 출력)
void showLoadingScreen() {
    SetColor(14);
    clearScreen();
    cout << "\n\n" << endl;
    cout << "============================================================\n";
    cout << "||                                                        ||\n";
    cout << "||                     C A S I N O                        ||\n";
    cout << "||                                                        ||\n";
    cout << "||           ★☆★ WELCOME TO THE CASINO ★☆★          ||\n";
    cout << "||                                                        ||\n";
    cout << "============================================================\n";
    cout << "\n\n로딩 중입니다. 잠시만 기다려주세요...\n";

    // 로딩 시간 동안 대기 (2초)
    this_thread::sleep_for(chrono::seconds(4));
}

int displayMainMenu() {
    int choice;
    cout << "" << endl;
    cout << "현재 게임 머니 : " << gameMoney << endl;
    cout << "==================== 카지노 게임 ====================\n";
    cout << "1. 슬롯 머신 (Slot Machine)\n";
    cout << "2. 달팽이 경주 (Snail Race)\n";
    cout << "3. 섰다 (Seotda)\n";
    cout << "4. 러시안 룰렛 (Russian Roulette)\n";
    cout << "5. 블랙잭 (Blackjack)\n";
    cout << "6. Save\n";
    cout << "7. 머니 충전\n";
    cout << "8. 종료 (Exit)\n";
    cout << "=====================================================\n";
    cout << "원하는 게임을 선택하세요: ";
    cin >> choice;
    return choice;
}

void PlaySlotMachine() {
    cout << "슬롯 머신 게임을 시작합니다...\n";
    Play_Slot(&gameMoney);
   
}

void PlaySnailRace() {
    cout << "달팽이 경주 게임을 시작합니다...\n";
    SetColor(15);
    Play_Snail(&gameMoney);
}

void PlaySeotda() {
    cout << "섰다 게임을 시작합니다...\n";
    SetColor(15);
    Play_Sutda(&gameMoney);
}

void PlayRussianRoulette() {
    cout << "러시안 룰렛 게임을 시작합니다...\n";
    SetColor(15);
    Play_Roulette(&gameMoney);
}

void PlayBlackjack() {
    cout << "블랙잭 게임을 시작합니다...\n";
    SetColor(15);
    Play_BlackJack(&gameMoney);
}

void Print_Casino()
{
    // 게임 시작 시 저장된 게임머니 불러오기
    loadGameMoney();

    
    // 처음에 로딩 화면을 보여줌
    showLoadingScreen();

    int choice;

    while (true) {
        clearScreen();
        SetColor(14);
        choice = displayMainMenu();

        switch (choice) {
        case 1:
            PlaySlotMachine();
            saveGameMoney();  // 게임머니 저장
            break;
        case 2:
            PlaySnailRace();
            saveGameMoney();  // 게임머니 저장
            break;
        case 3:
            PlaySeotda();
            saveGameMoney();  // 게임머니 저장
            break;
        case 4:
            PlayRussianRoulette();
            saveGameMoney();  // 게임머니 저장
            break;
        case 5:
            PlayBlackjack();
            saveGameMoney();  // 게임머니 저장
            break;
        case 6:
            saveGameMoney();  // 게임머니 저장
            cout << "게임을 저장하고 종료합니다. 감사합니다!\n";
            return;
            break;
        case 7:
            cout << "게임머니 충전을 원하시면 \"권사장\"을 찾아오세요\n";
            break;
        case 8:
            cout << "게임 종료\n";
            break;
        default:
            cout << "잘못된 선택입니다. 다시 선택해주세요.\n";
        }

        cout << "아무 키나 눌러 계속하세요...\n";
        cin.ignore();
        cin.get();
    }

}

