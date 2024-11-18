#include <iostream>
#include <time.h>
#include <string>
#include <windows.h> // ������ Sleep �Լ� ���
#include <thread>
#include <atomic>
#include <conio.h>
#include <chrono> // �ð� ��� ���� ���̺귯��
#include <windows.h>

int money_slot=0;


using namespace std;

volatile int numa1; // ���� �ӽ� ù°���� ���� �ʱⰪ
volatile int numa2; // ���� �ӽ� ��°���� ���� �ʱⰪ
volatile int numa3; // ���� �ӽ� ��°���� ���� �ʱⰪ

volatile int num1[3]; // ù��° ���� �ѹ�
volatile int num2[3]; // �ι�° ���� �ѹ�
volatile int num3[3]; // ����° ���� �ѹ�

void SetConsoleFontSize(int fontSize) {
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;               // ���� ũ�� (0���� �����Ͽ� �ڵ�����)
    cfi.dwFontSize.Y = fontSize;        // ��Ʈ ũ�� ����
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas"); // ���ϴ� ��Ʈ �̸�
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}


// �÷� ���� �Լ�
void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void SetConsole() {
    system("title Slot Game"); // �ܼ�â �̸� ����
    system("mode con:cols=65 lines=25"); // �ܼ�â ũ�⼳��
}

void CursorView(bool show) // Ŀ�� ������ ����/Ȱ��ȭ
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

// �ܼ� Ŀ�� ��ġ ���� �Լ�
void SetCursorPosition(int x, int y) {
    COORD position = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void Arr_rand_num_1(volatile int* arr, volatile int* num) // ���� ���� �ѹ�
{
    if (*num > 9) {
        (*num) = 1;
    }
    int x = *num;
    (*num)++;

    for (int i = 0; i < 3; i++) {
        if (x > 9) {
            x = 1;
        }
        arr[i] = x;
        x++;
    }
}

void Init_Slot() // ���� �ʱ�ȭ �Լ�
{
    numa1 = (rand() % 9 + 1);
    numa2 = (rand() % 9 + 1);
    numa3 = (rand() % 9 + 1);
    Arr_rand_num_1(num1, &numa1);
    Arr_rand_num_1(num2, &numa2);
    Arr_rand_num_1(num3, &numa3);
}
void ClearNumbers() {
    // ���� ���� ��ġ�� ��ĭ���� ��� ���ڸ� ����� �Լ�
    SetCursorPosition(18, 10); // ���� ��ġ 1
    cout << "   " << "   " << "   ";

    SetCursorPosition(18, 11); // ���� ��ġ 2
    cout << "   " << "   " << "   ";

    SetCursorPosition(18, 12); // ���� ��ġ 3
    cout << "   " << "   " << "   ";
    SetCursorPosition(32, 21);// �Է� ��ġ ����
}

void PrintNumbers() {
    // ClearNumbers �Լ��� ���� ȣ���Ͽ� ���� ���ڸ� ����
    ClearNumbers();

    // ���� ���� ���
    SetColor(15); // ���
    SetCursorPosition(18, 10); // ���� ��ġ 1
    cout << num1[0] << "   " << num2[0] << "   " << num3[0];

    SetCursorPosition(18, 11); // ���� ��ġ 2
    cout << num1[1] << "   " << num2[1] << "   " << num3[1];

    SetCursorPosition(18, 12); // ���� ��ġ 3
    cout << num1[2] << "   " << num2[2] << "   " << num3[2];
    SetCursorPosition(32, 21); // �Է� ��ġ ����

}

void SlotMachine(atomic<bool>& running, atomic<bool> stopFlags[]) {
    while (running) {
        // ���� ���� ������Ʈ
        if (!stopFlags[0]) Arr_rand_num_1(num1, &numa1);
        if (!stopFlags[1]) Arr_rand_num_1(num2, &numa2);
        if (!stopFlags[2]) Arr_rand_num_1(num3, &numa3);

        PrintNumbers(); // ���� ���
        Sleep(70); // ������
    }
}

void PrintTemplate() // ���� Ʋ ��� (Ʋ�� �� ���� ���)
{
    SetCursorPosition(0, 0);
    SetColor(14); // ���
    cout << "\t___________________________" << endl;
    cout << "\t  ������������������������" << endl;
    cout << "\t  ������";
    SetColor(15); // ���
    cout << "    SLOT    ";
    SetColor(14); // ���
    cout << "������" << endl;
    cout << "\t  ������������������������     �Ӵ�: "<<money_slot<< endl;
    cout << "\t  ������������������������     �÷��� �ѹ��� 1000��~~" << endl;
    cout << "\t  ������";
    SetColor(15); // ���
    cout << "JackPot x100";
    SetColor(14); // ���
    cout << "������     777 is Jack Pot !!!!!" << endl;
    cout << "\t  ������";
    SetColor(15); // ���
    cout << "3match x10";
    SetColor(14); // ���
    cout << "  ������" << endl;
    cout << "\t  ������";
    SetColor(15); // ���
    cout << "2match x2";
    SetColor(14); // ���
    cout << "   ������" << endl;

    cout << "\t  ������������������������" << endl;
    cout << "\t  ������������������������" << endl;
    cout << "\t  ������            ������" << endl;
    SetColor(4); // ���
    cout << "\t  ������            ������" << endl;
    SetColor(14); // ���
    cout << "\t  ������            ������" << endl;
    cout << "\t  ������������������������" << endl;
    cout << "\t  ������������������������" << endl;
    cout << "\t  ������������������������" << endl;
    cout << "\t___________________________" << endl;
}

int Check_Num()
{
    if (num1[1] == 7 && num2[1] == 7 && num3[1] == 7)
    {
        return 7; // Jack Pot!!!!!
    }
    else if (num1[1] == num2[1] && num2[1] == num3[1])
    {
        return 3; // 3�� ��ġ
    }
    else if (num1[1] == num2[1] || num2[1] == num3[1] || num1[1] == num3[1])
    {
        return 2; // 2�� ��ġ
    }
    else
    {
        return 0; // ��ġ���� ����
    }
}

void PrintJackpot() {
    // ������ JACKPOT �޽��� ���
    SetCursorPosition(0, 8);
    SetColor(14); // �����

    cout << "****************************************************************\n";
    cout << "*                                                              *\n";
    cout << "*                      �ڡڡ� JACKPOT �ڡڡ�                   *\n";
    cout << "*                                                              *\n";
    cout << "****************************************************************\n";
}

void PrintFireworks() {
    // ���� ������ ȿ��
    SetCursorPosition(0, 0);
    SetColor(12); // ������
    cout << "              *    .  *         *        .   *      .  \n";
    cout << "        *   .    *   .   *        *   .    *         *    .\n";
    cout << "           *     .   .     *   .     .    *     *     .     \n";
    cout << "              *      .      *     .    *        *      .     \n";
    cout << "              *    .  *         *        .   *      .  \n";
    cout << "        *   .    *   .   *        *   .    *         *    .\n";
    cout << "           *     .   .     *   .     .    *     *     .     \n";
    cout << "              *      .      *     .    *        *      .     \n";
    SetCursorPosition(0, 14);
    SetColor(12); // ������
    cout << "              *    .  *         *        .   *      .  \n";
    cout << "        *   .    *   .   *        *   .    *         *    .\n";
    cout << "           *     .   .     *   .     .    *     *     .     \n";
    cout << "              *      .      *     .    *        *      .     \n";
    cout << "              *    .  *         *        .   *      .  \n";
    cout << "        *   .    *   .   *        *   .    *         *    .\n";
    cout << "           *     .   .     *   .     .    *     *     .     \n";
    cout << "              *      .      *     .    *        *      .     \n";
}

void ClearFireworks() {
    // ���� ������ �κ��� �������� ������� �����̴� ȿ���� ����
    SetCursorPosition(0, 0);
    cout << "                                                            \n";
    cout << "                                                             \n";
    cout << "                                                             \n";
    cout << "                                                              \n";
    cout << "                                                              \n";
    cout << "                                                                \n";
    cout << "                                                               \n";
    cout << "                                                             \n";
    SetCursorPosition(0, 14);
    cout << "                                                            \n";
    cout << "                                                             \n";
    cout << "                                                             \n";
    cout << "                                                              \n";
    cout << "                                                              \n";
    cout << "                                                                \n";
    cout << "                                                               \n";
    cout << "                                                             \n";
}

void FlashJackpot() {
    Sleep(1000);
    system("cls");

    // JACKPOT �޽��� �� �� ��� (����)

    PrintJackpot();

    for (int i = 0; i < 7; i++) { // 7�� ���� ������
        PrintFireworks();  // ���� ���
        Sleep(200); // 0.2�� ���

        ClearFireworks();  // ���� �����
        Sleep(200); // 0.2�� ���
    }
}


void Flash3Match() {
    Sleep(1000);
    for (int i = 0; i < 3; i++) { // 3�� ������
        system("cls");
        SetColor(10); // �ʷϻ�
        cout << "\n\n\n\n\n\n";
        cout << "========================= Well Done! ============================\n";
        cout << "                      3���� ���ڰ� ��ġ�մϴ�!\n";
        cout << "=================================================================\n";
        Sleep(500); // 0.5�� ���

        system("cls");
        Sleep(500); // 0.5�� ���
    }

    // �����ϴ� �޽��� ���
    system("cls");
    SetColor(14); // �����
    cout << "\n\n\n\n\n\n";
    cout << "=================================================================\n";
    cout << "                      ��! 3���� �¾ҳ׿�!\n";
    cout << "=================================================================\n";
    Sleep(1000); // 1�� ���

    SetColor(12); // ���������� ����
    cout << "\n\n������... '777'�� �ƴϳ׿�! :))" << endl;
    cout << "JACKPOT�� ���� ��ȸ��! �� �� �� �����!!!" << endl;

    Sleep(2000); // 2�� ���
}


void Flash2Match() {
    Sleep(1000);
    system("cls");
    SetColor(11); // �Ķ���
    cout << "\n\n\n\n\n\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "                     2���� ���ڰ� ��ġ�մϴ�!\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    Sleep(1000); // 1�� ���

    // ��ø��� �޽��� ���
    SetColor(14); // ��������� ����
    cout << "\n\n\n";
    cout << "   ��! ���� �� ����׿�! ;)" << endl;
    cout << "   �ϳ��� �� ����ٸ�... 3Match�̾��� �ٵ�!:(" << endl;
    Sleep(1000); // 1�� ���

    SetColor(12); // ���������� ����
    cout << "\n   �ƽ����� �ƽ��� ;)" << endl;
    cout << "   ���߷��� �����ϳ׿� :)" << endl;

    Sleep(2000); // 2�� ���
}

void FlashSkullPirate() {
    Sleep(1000);
    for (int i = 0; i < 5; i++) { // 3�� ������
        system("cls");
        SetColor(12); // ������
        cout << "\n\n\n\n\n\n";
        cout << "*****************************************************************\n";
        cout << "*                                                               *\n";
        cout << "*                            YOU LOSE!                          *\n";
        cout << "*                                                               *\n";
        cout << "*****************************************************************\n";

        // �ذ� ������ ���ڷ� ǥ��
        SetColor(15); // ������� ����
        cout << "                             _____      " << endl;
        cout << "                           /      |     " << endl;
        cout << "                          | () () |    " << endl;
        cout << "                          |  ___  |    " << endl;
        cout << "                          |___  __/     " << endl;
        cout << "                        ___/     |___  " << endl;
        cout << "                       /              | " << endl;
        cout << "                      |    �޷��޷�~  |" << endl;
        cout << "                      |_______________| " << endl;

        Sleep(500); // 0.5�� ���

        system("cls");
        Sleep(500); // 0.5�� ���
    }
}
void Print_Slot() // ���� ����
{
    CursorView(false);
    atomic<bool> running(false);
    atomic<bool> stopFlags[3] = { false, false, false }; // �� ���� ���� ����
    int stopIndex = 0;
    int key = 0;

    while (true) {
        // ����ڷκ��� ���� �Է� �ޱ�
        while (key != 1) {
            PrintTemplate();
            SetColor(15); // ���
            cout << "\n1�� ������ ���� ���� : ";
            SetCursorPosition(24, 18); // �Է� Ŀ�� ��ġ ����
            cin >> key;
            if (key == 1 && money_slot < 1000)
            {
                cout << "������ �ܾ� ����" << endl;
                return;
                break;
            }

            if (key != 1) {
                SetCursorPosition(0, 19); // �޽��� ��� ��ġ ����
                cout << "1�� �Է��ؾ� ������ ���۵˴ϴ�." << endl;
                Sleep(1000); // �޽��� ��� ǥ��
                system("cls");
            }
        }

        running = true; // ���� ���� ����
        thread slotThread(SlotMachine, ref(running), stopFlags); // ���� ���� ������Ʈ ������ ����
        system("cls");
        PrintTemplate();
        SetColor(15); // ���
        cout << "\n�����̽� �ٸ� ������ ��ĭ �� ����ϴ�.";

     

        while (stopIndex < 3) {
           
            char ch = _getch();
            if (ch == ' ') {
            stopFlags[stopIndex] = true;
            stopIndex++;
            }
        }

        running = false; // ���� ���� ����
        slotThread.join(); // ���� ������Ʈ ������ ���� ���
       

        // ���� ��Ī ��� ���
        int matchResult = Check_Num();
        SetColor(15); // ���
        if (matchResult == 7) {
            money_slot *= 100;
            FlashJackpot(); // Jackpot ��÷ �� ȭ���� ȭ��
            SetCursorPosition(0, 14);
        }
        else if (matchResult == 3) {
            money_slot *= 10;
            Flash3Match(); // 3�� ��ġ �� ȭ�� ������
        }
        else if (matchResult == 2) {
            money_slot *= 2;
            Flash2Match(); // 2�� ��ġ �� ǥ��
        }
        else {
            money_slot -= 1000;
            FlashSkullPirate();
        }

        // �ٽ� �������� ����
        SetColor(15); // ���
        cout << "\n������ �ٽ� �����Ͻðڽ��ϱ�? (1: ��, 0: �ƴϿ�) : ";
        cin >> key;
        if (key == 1 && money_slot < 1000)
        {
            cout << "������ �ܾ� ����" << endl;
            break;
        }
        Init_Slot(); // ���� �ʱ�ȭ
        if (key == 0) {
            break; // ����
        }

        // ���� ���� �ʱ�ȭ
        for (int i = 0; i < 3; i++) {
            stopFlags[i] = false;
        }
        stopIndex = 0; // �ε��� �ʱ�ȭ
        system("cls");
    }
    SetColor(15); // ���
    cout << "���� �ӽ��� �����մϴ�." << endl;
}
void Play_Slot(int*num)
{
    money_slot = *num;
    
    SetConsoleFontSize(28);
    SetConsole();
    srand(static_cast<unsigned int>(time(NULL)));
    Init_Slot(); // ���� �ʱ�ȭ
    Print_Slot(); // ���� ���
    *num = money_slot;
    return;
}