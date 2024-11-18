#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <cstdlib> // rand(), srand()
#include <ctime>   // time()
#include <windows.h>

#undef max // windows.h에서 정의된 max 매크로 제거

using namespace std;

const int trackLength = 50; // 경주 길이
const int numSnail = 5;    // 달팽이의 수
int money=0; // 플레이어 포인트

// 콘솔 초기화
void clearScreen() {
	cout << "\033[2J\033[1;1H"; // 콘솔 초기화
}

// 글씨 변경
void textcolor(int foreground, int background) {
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 달팽이 타이틀
void SnailTitle(int color) {
	textcolor(color, 0);
	cout << endl;
	cout << "     ┌―――――――――――┐ " << endl;
	cout << "     │ @_/' 달팽이 게임 @/' │ " << endl;
	cout << "     └―――――――――――┘ " << endl;
}

// 달팽이 그리기
void drawRace(const vector<int>& positions) {
	clearScreen();

	for (int i = 0; i < numSnail; ++i) {
		cout << (i + 1) << " "; // 달팽이 번호 출력
		for (int j = 0; j < trackLength; ++j) {
			if (j == positions[i]) {
				cout << "@_/'"; // 달팽이
			}
			else if (j == trackLength - 1) {
				cout << "|"; // 결승선 표시
			}
			else {
				cout << " "; // 빈 공간
			}
		}
		cout << endl; // 다음 줄로 이동
	}
	cout << endl;
}

// 달팽이 선택
int SnailSelect() {
	int select_snail;

	while (true) {
		cout << "     1번 ~ 5번 달팽이 중 선택해주세요: ";
		cin >> select_snail;

		if (cin.fail()) {
			cin.clear(); // 오류 플래그 초기화
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 스트림 비우기
			cout << "     숫자로 입력해주세요." << endl;
		}
		else {
			break;
		}
	}
	return select_snail;
}

// 배팅금 설정
int SnailPayin() {
	cout << endl;
	cout << "     현재 플레이어의 포인트는 " << money << "원 입니다." << endl;
	int betting;

	while (true) {
		cout << "     배팅할 금액을 입력하세요: ";
		cin >> betting;

		if (cin.fail()) {
			cin.clear(); // 오류 플래그 초기화
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 스트림 비우기
			cout << "     숫자로 입력해주세요." << endl;
		}
		else if (betting > money) {
			cin.clear(); // 오류 플래그 초기화
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 스트림 비우기
			cout << "     보유하신 포인트가 부족합니다. 다시 입력해주세요." << endl;
		}
		else {
			break;
		}
	}
	return betting;
}

// 게임 시작
int SnailStart() {
	srand((unsigned)time(NULL)); // 시드 값을 현재 시간으로 설정

	vector<int> positions(numSnail, 0); // 각 달팽이의 초기 위치

	while (true) {
		drawRace(positions);

		// 달팽이들의 위치 업데이트
		for (int i = 0; i < numSnail; ++i) {
			if (positions[i] < trackLength - 1) {
				positions[i] += rand() % 2 + 1; // 무작위로 1 또는 2만큼 이동
			}
		}

		// 종료 조건: 하나의 달팽이가 경주 끝에 도달한 경우
		for (int i = 0; i < numSnail; ++i) {
			if (positions[i] >= trackLength - 1) {
				drawRace(positions);
				cout << i + 1 << "번 달팽이가 결승선을 통과했습니다!" << endl;
				return i + 1;
			}
		}

		this_thread::sleep_for(chrono::milliseconds(200)); // 0.2초 대기
	}
}

// 배당금
void SnailPayout(int select_snail, int betting, int win_snail) {
	int select;

	if (select_snail == win_snail) {
		money += betting;
		cout << "축하드립니다! 1등을 맞추셨습니다! 배당금이 지급됩니다! (0: 돌아가기)" << endl;
		cout << "현재 플레이어 포인트는 " << money << "원 입니다.";
		while (true) {
			cin >> select;

			// 입력이 숫자가 아닐 경우 예외처리
			if (cin.fail()) {
				cin.clear(); // 오류 플래그 초기화
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 스트림 비우기
				cout << "숫자로 입력해주세요." << endl;
			}
			else if (select != 0) {
				cin.clear(); // 오류 플래그 초기화
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 스트림 비우기
				cout << "메뉴로 돌아가려면 0번을 눌러주세요." << endl;
			}
			else {
				break;
			}
		}
	}
	else {
		money -= betting;
		cout << "안타깝게도 1등 달팽이를 맞추지 못했습니다. 다시 도전해보세요! (0: 돌아가기)" << endl;
		cout << "현재 플레이어 포인트는 " << money << "원 입니다.";
		while (true) {
			cin >> select;

			// 입력이 숫자가 아닐 경우 예외처리
			if (cin.fail()) {
				cin.clear(); // 오류 플래그 초기화
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 스트림 비우기
				cout << "숫자로 입력해주세요." << endl;
			}
			else if (select != 0) {
				cin.clear(); // 오류 플래그 초기화
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 스트림 비우기
				cout << "메뉴로 돌아가려면 0번을 눌러주세요." << endl;
			}
			else {
				break;
			}
		}
	}
}

// 게임 설명
void SnailDescription() {
	cout << endl;
	cout << "     5마리의 달팽이 중 어떤 달팽이가 레이스에서 1등하는지 맞춰보세요 !" << endl;
	cout << "     1등을 맞추면 배팅금 X 3배 당장 즐겨보세요 !" << endl << endl;
	cout << "     *메뉴로 돌아가려면 1번을 입력해주세요" << endl;

	int select;
	while (true) {
		cin >> select;

		// 입력이 숫자가 아닐 경우 및 1번이 아닐 경우 예외처리
		if (cin.fail() || select != 1) {
			cin.clear(); // 오류 플래그 초기화
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 스트림 비우기
			cout << "     *메뉴로 돌아가려면 1번을 입력해주세요" << endl;
		}
		else {
			break;
		}
	}
}

void Play_Snail(int* num) {
	money = *num;
	while (1) {
		int select; // 메뉴 선택
		int betting; // 배팅금
		int select_snail; // 선택한 달팽이
		int win_snail; // 1등 달팽이

		clearScreen(); // 콘솔 초기화
		SnailTitle(rand() % 14 + 1); // 타이틀 색상을 랜덤하게 변경
		textcolor(15, 0);

		cout << endl;
		cout << "          1. 게임 설명" << endl;
		cout << "          2. 게임 시작" << endl;
		cout << "          3. 종료" << endl;
		cout << "          선택: ";
		cin >> select;

		switch (select)
		{
		case 1:
			clearScreen(); // 콘솔 초기화
			SnailTitle(rand() % 14 + 1); // 타이틀 색상을 랜덤하게 변경
			textcolor(15, 0);

			SnailDescription();
			break;
		case 2:
			clearScreen(); // 콘솔 초기화
			SnailTitle(rand() % 14 + 1); // 타이틀 색상을 랜덤하게 변경
			textcolor(15, 0);

			betting = SnailPayin();
			select_snail = SnailSelect();
			win_snail = SnailStart();
			SnailPayout(select_snail, betting, win_snail);
			break;
		case 3:
			*num = money;
			return;
			break;
		default:
			break;
		}
	}
}

