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

#undef max // windows.h���� ���ǵ� max ��ũ�� ����

using namespace std;

const int trackLength = 50; // ���� ����
const int numSnail = 5;    // �������� ��
int money=0; // �÷��̾� ����Ʈ

// �ܼ� �ʱ�ȭ
void clearScreen() {
	cout << "\033[2J\033[1;1H"; // �ܼ� �ʱ�ȭ
}

// �۾� ����
void textcolor(int foreground, int background) {
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ������ Ÿ��Ʋ
void SnailTitle(int color) {
	textcolor(color, 0);
	cout << endl;
	cout << "     �������������������������� " << endl;
	cout << "     �� @_/' ������ ���� @/' �� " << endl;
	cout << "     �������������������������� " << endl;
}

// ������ �׸���
void drawRace(const vector<int>& positions) {
	clearScreen();

	for (int i = 0; i < numSnail; ++i) {
		cout << (i + 1) << " "; // ������ ��ȣ ���
		for (int j = 0; j < trackLength; ++j) {
			if (j == positions[i]) {
				cout << "@_/'"; // ������
			}
			else if (j == trackLength - 1) {
				cout << "|"; // ��¼� ǥ��
			}
			else {
				cout << " "; // �� ����
			}
		}
		cout << endl; // ���� �ٷ� �̵�
	}
	cout << endl;
}

// ������ ����
int SnailSelect() {
	int select_snail;

	while (true) {
		cout << "     1�� ~ 5�� ������ �� �������ּ���: ";
		cin >> select_snail;

		if (cin.fail()) {
			cin.clear(); // ���� �÷��� �ʱ�ȭ
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �Է� ��Ʈ�� ����
			cout << "     ���ڷ� �Է����ּ���." << endl;
		}
		else {
			break;
		}
	}
	return select_snail;
}

// ���ñ� ����
int SnailPayin() {
	cout << endl;
	cout << "     ���� �÷��̾��� ����Ʈ�� " << money << "�� �Դϴ�." << endl;
	int betting;

	while (true) {
		cout << "     ������ �ݾ��� �Է��ϼ���: ";
		cin >> betting;

		if (cin.fail()) {
			cin.clear(); // ���� �÷��� �ʱ�ȭ
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �Է� ��Ʈ�� ����
			cout << "     ���ڷ� �Է����ּ���." << endl;
		}
		else if (betting > money) {
			cin.clear(); // ���� �÷��� �ʱ�ȭ
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �Է� ��Ʈ�� ����
			cout << "     �����Ͻ� ����Ʈ�� �����մϴ�. �ٽ� �Է����ּ���." << endl;
		}
		else {
			break;
		}
	}
	return betting;
}

// ���� ����
int SnailStart() {
	srand((unsigned)time(NULL)); // �õ� ���� ���� �ð����� ����

	vector<int> positions(numSnail, 0); // �� �������� �ʱ� ��ġ

	while (true) {
		drawRace(positions);

		// �����̵��� ��ġ ������Ʈ
		for (int i = 0; i < numSnail; ++i) {
			if (positions[i] < trackLength - 1) {
				positions[i] += rand() % 2 + 1; // �������� 1 �Ǵ� 2��ŭ �̵�
			}
		}

		// ���� ����: �ϳ��� �����̰� ���� ���� ������ ���
		for (int i = 0; i < numSnail; ++i) {
			if (positions[i] >= trackLength - 1) {
				drawRace(positions);
				cout << i + 1 << "�� �����̰� ��¼��� ����߽��ϴ�!" << endl;
				return i + 1;
			}
		}

		this_thread::sleep_for(chrono::milliseconds(200)); // 0.2�� ���
	}
}

// ����
void SnailPayout(int select_snail, int betting, int win_snail) {
	int select;

	if (select_snail == win_snail) {
		money += betting;
		cout << "���ϵ帳�ϴ�! 1���� ���߼̽��ϴ�! ������ ���޵˴ϴ�! (0: ���ư���)" << endl;
		cout << "���� �÷��̾� ����Ʈ�� " << money << "�� �Դϴ�.";
		while (true) {
			cin >> select;

			// �Է��� ���ڰ� �ƴ� ��� ����ó��
			if (cin.fail()) {
				cin.clear(); // ���� �÷��� �ʱ�ȭ
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �Է� ��Ʈ�� ����
				cout << "���ڷ� �Է����ּ���." << endl;
			}
			else if (select != 0) {
				cin.clear(); // ���� �÷��� �ʱ�ȭ
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �Է� ��Ʈ�� ����
				cout << "�޴��� ���ư����� 0���� �����ּ���." << endl;
			}
			else {
				break;
			}
		}
	}
	else {
		money -= betting;
		cout << "��Ÿ���Ե� 1�� �����̸� ������ ���߽��ϴ�. �ٽ� �����غ�����! (0: ���ư���)" << endl;
		cout << "���� �÷��̾� ����Ʈ�� " << money << "�� �Դϴ�.";
		while (true) {
			cin >> select;

			// �Է��� ���ڰ� �ƴ� ��� ����ó��
			if (cin.fail()) {
				cin.clear(); // ���� �÷��� �ʱ�ȭ
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �Է� ��Ʈ�� ����
				cout << "���ڷ� �Է����ּ���." << endl;
			}
			else if (select != 0) {
				cin.clear(); // ���� �÷��� �ʱ�ȭ
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �Է� ��Ʈ�� ����
				cout << "�޴��� ���ư����� 0���� �����ּ���." << endl;
			}
			else {
				break;
			}
		}
	}
}

// ���� ����
void SnailDescription() {
	cout << endl;
	cout << "     5������ ������ �� � �����̰� ���̽����� 1���ϴ��� ���纸���� !" << endl;
	cout << "     1���� ���߸� ���ñ� X 3�� ���� ��ܺ����� !" << endl << endl;
	cout << "     *�޴��� ���ư����� 1���� �Է����ּ���" << endl;

	int select;
	while (true) {
		cin >> select;

		// �Է��� ���ڰ� �ƴ� ��� �� 1���� �ƴ� ��� ����ó��
		if (cin.fail() || select != 1) {
			cin.clear(); // ���� �÷��� �ʱ�ȭ
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �Է� ��Ʈ�� ����
			cout << "     *�޴��� ���ư����� 1���� �Է����ּ���" << endl;
		}
		else {
			break;
		}
	}
}

void Play_Snail(int* num) {
	money = *num;
	while (1) {
		int select; // �޴� ����
		int betting; // ���ñ�
		int select_snail; // ������ ������
		int win_snail; // 1�� ������

		clearScreen(); // �ܼ� �ʱ�ȭ
		SnailTitle(rand() % 14 + 1); // Ÿ��Ʋ ������ �����ϰ� ����
		textcolor(15, 0);

		cout << endl;
		cout << "          1. ���� ����" << endl;
		cout << "          2. ���� ����" << endl;
		cout << "          3. ����" << endl;
		cout << "          ����: ";
		cin >> select;

		switch (select)
		{
		case 1:
			clearScreen(); // �ܼ� �ʱ�ȭ
			SnailTitle(rand() % 14 + 1); // Ÿ��Ʋ ������ �����ϰ� ����
			textcolor(15, 0);

			SnailDescription();
			break;
		case 2:
			clearScreen(); // �ܼ� �ʱ�ȭ
			SnailTitle(rand() % 14 + 1); // Ÿ��Ʋ ������ �����ϰ� ����
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

