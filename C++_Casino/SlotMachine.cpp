#include <iostream>
#include <time.h>
#include <string>
#include <windows.h> // 딜레이 Sleep 함수 사용
#include <thread>
#include <atomic>
#include <conio.h>
#include <chrono> // 시간 제어를 위한 라이브러리
#include <windows.h>

int money_slot=0;


using namespace std;

volatile int numa1; // 슬롯 머신 첫째줄의 숫자 초기값
volatile int numa2; // 슬롯 머신 둘째줄의 숫자 초기값
volatile int numa3; // 슬롯 머신 셋째줄의 숫자 초기값

volatile int num1[3]; // 첫번째 슬롯 넘버
volatile int num2[3]; // 두번째 슬롯 넘버
volatile int num3[3]; // 세번째 슬롯 넘버

void SetConsoleFontSize(int fontSize) {
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;               // 가로 크기 (0으로 설정하여 자동으로)
    cfi.dwFontSize.Y = fontSize;        // 폰트 크기 설정
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas"); // 원하는 폰트 이름
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}


// 컬러 설정 함수
void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void SetConsole() {
    system("title Slot Game"); // 콘솔창 이름 설정
    system("mode con:cols=65 lines=25"); // 콘솔창 크기설정
}

void CursorView(bool show) // 커서 깜빡임 제거/활성화
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

// 콘솔 커서 위치 조정 함수
void SetCursorPosition(int x, int y) {
    COORD position = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void Arr_rand_num_1(volatile int* arr, volatile int* num) // 슬롯 랜덤 넘버
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

void Init_Slot() // 슬롯 초기화 함수
{
    numa1 = (rand() % 9 + 1);
    numa2 = (rand() % 9 + 1);
    numa3 = (rand() % 9 + 1);
    Arr_rand_num_1(num1, &numa1);
    Arr_rand_num_1(num2, &numa2);
    Arr_rand_num_1(num3, &numa3);
}
void ClearNumbers() {
    // 슬롯 숫자 위치를 빈칸으로 덮어서 숫자를 지우는 함수
    SetCursorPosition(18, 10); // 숫자 위치 1
    cout << "   " << "   " << "   ";

    SetCursorPosition(18, 11); // 숫자 위치 2
    cout << "   " << "   " << "   ";

    SetCursorPosition(18, 12); // 숫자 위치 3
    cout << "   " << "   " << "   ";
    SetCursorPosition(32, 21);// 입력 위치 조정
}

void PrintNumbers() {
    // ClearNumbers 함수를 먼저 호출하여 이전 숫자를 지움
    ClearNumbers();

    // 슬롯 숫자 출력
    SetColor(15); // 흰색
    SetCursorPosition(18, 10); // 숫자 위치 1
    cout << num1[0] << "   " << num2[0] << "   " << num3[0];

    SetCursorPosition(18, 11); // 숫자 위치 2
    cout << num1[1] << "   " << num2[1] << "   " << num3[1];

    SetCursorPosition(18, 12); // 숫자 위치 3
    cout << num1[2] << "   " << num2[2] << "   " << num3[2];
    SetCursorPosition(32, 21); // 입력 위치 조정

}

void SlotMachine(atomic<bool>& running, atomic<bool> stopFlags[]) {
    while (running) {
        // 슬롯 숫자 업데이트
        if (!stopFlags[0]) Arr_rand_num_1(num1, &numa1);
        if (!stopFlags[1]) Arr_rand_num_1(num2, &numa2);
        if (!stopFlags[2]) Arr_rand_num_1(num3, &numa3);

        PrintNumbers(); // 숫자 출력
        Sleep(70); // 딜레이
    }
}

void PrintTemplate() // 슬롯 틀 출력 (틀은 한 번만 출력)
{
    SetCursorPosition(0, 0);
    SetColor(14); // 노랑
    cout << "\t___________________________" << endl;
    cout << "\t  ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ" << endl;
    cout << "\t  ㅁㅁㅁ";
    SetColor(15); // 흰색
    cout << "    SLOT    ";
    SetColor(14); // 노랑
    cout << "ㅁㅁㅁ" << endl;
    cout << "\t  ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ     머니: "<<money_slot<< endl;
    cout << "\t  ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ     플레이 한번에 1000원~~" << endl;
    cout << "\t  ㅁㅁㅁ";
    SetColor(15); // 흰색
    cout << "JackPot x100";
    SetColor(14); // 노랑
    cout << "ㅁㅁㅁ     777 is Jack Pot !!!!!" << endl;
    cout << "\t  ㅁㅁㅁ";
    SetColor(15); // 흰색
    cout << "3match x10";
    SetColor(14); // 노랑
    cout << "  ㅁㅁㅁ" << endl;
    cout << "\t  ㅁㅁㅁ";
    SetColor(15); // 흰색
    cout << "2match x2";
    SetColor(14); // 노랑
    cout << "   ㅁㅁㅁ" << endl;

    cout << "\t  ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ" << endl;
    cout << "\t  ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ" << endl;
    cout << "\t  ㅁㅁㅁ            ㅁㅁㅁ" << endl;
    SetColor(4); // 흰색
    cout << "\t  ㅁㅁㅁ            ㅁㅁㅁ" << endl;
    SetColor(14); // 노랑
    cout << "\t  ㅁㅁㅁ            ㅁㅁㅁ" << endl;
    cout << "\t  ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ" << endl;
    cout << "\t  ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ" << endl;
    cout << "\t  ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ" << endl;
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
        return 3; // 3개 일치
    }
    else if (num1[1] == num2[1] || num2[1] == num3[1] || num1[1] == num3[1])
    {
        return 2; // 2개 일치
    }
    else
    {
        return 0; // 일치하지 않음
    }
}

void PrintJackpot() {
    // 고정된 JACKPOT 메시지 출력
    SetCursorPosition(0, 8);
    SetColor(14); // 노란색

    cout << "****************************************************************\n";
    cout << "*                                                              *\n";
    cout << "*                      ★★★ JACKPOT ★★★                   *\n";
    cout << "*                                                              *\n";
    cout << "****************************************************************\n";
}

void PrintFireworks() {
    // 폭죽 터지는 효과
    SetCursorPosition(0, 0);
    SetColor(12); // 빨간색
    cout << "              *    .  *         *        .   *      .  \n";
    cout << "        *   .    *   .   *        *   .    *         *    .\n";
    cout << "           *     .   .     *   .     .    *     *     .     \n";
    cout << "              *      .      *     .    *        *      .     \n";
    cout << "              *    .  *         *        .   *      .  \n";
    cout << "        *   .    *   .   *        *   .    *         *    .\n";
    cout << "           *     .   .     *   .     .    *     *     .     \n";
    cout << "              *      .      *     .    *        *      .     \n";
    SetCursorPosition(0, 14);
    SetColor(12); // 빨간색
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
    // 폭죽 터지는 부분을 공백으로 덮어씌워서 깜빡이는 효과를 만듦
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

    // JACKPOT 메시지 한 번 출력 (고정)

    PrintJackpot();

    for (int i = 0; i < 7; i++) { // 7번 폭죽 깜빡임
        PrintFireworks();  // 폭죽 출력
        Sleep(200); // 0.2초 대기

        ClearFireworks();  // 폭죽 지우기
        Sleep(200); // 0.2초 대기
    }
}


void Flash3Match() {
    Sleep(1000);
    for (int i = 0; i < 3; i++) { // 3번 깜빡임
        system("cls");
        SetColor(10); // 초록색
        cout << "\n\n\n\n\n\n";
        cout << "========================= Well Done! ============================\n";
        cout << "                      3개의 숫자가 일치합니다!\n";
        cout << "=================================================================\n";
        Sleep(500); // 0.5초 대기

        system("cls");
        Sleep(500); // 0.5초 대기
    }

    // 조롱하는 메시지 출력
    system("cls");
    SetColor(14); // 노란색
    cout << "\n\n\n\n\n\n";
    cout << "=================================================================\n";
    cout << "                      오! 3개가 맞았네요!\n";
    cout << "=================================================================\n";
    Sleep(1000); // 1초 대기

    SetColor(12); // 빨간색으로 변경
    cout << "\n\n하지만... '777'은 아니네요! :))" << endl;
    cout << "JACKPOT은 다음 기회에! 돈 좀 더 써봐요!!!" << endl;

    Sleep(2000); // 2초 대기
}


void Flash2Match() {
    Sleep(1000);
    system("cls");
    SetColor(11); // 파란색
    cout << "\n\n\n\n\n\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "                     2개의 숫자가 일치합니다!\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    Sleep(1000); // 1초 대기

    // 약올리는 메시지 출력
    SetColor(14); // 노란색으로 변경
    cout << "\n\n\n";
    cout << "   오! 거의 다 맞췄네요! ;)" << endl;
    cout << "   하나만 더 맞췄다면... 3Match이었을 텐데!:(" << endl;
    Sleep(1000); // 1초 대기

    SetColor(12); // 빨간색으로 변경
    cout << "\n   아쉬워요 아쉬워 ;)" << endl;
    cout << "   순발력이 부족하네요 :)" << endl;

    Sleep(2000); // 2초 대기
}

void FlashSkullPirate() {
    Sleep(1000);
    for (int i = 0; i < 5; i++) { // 3번 깜빡임
        system("cls");
        SetColor(12); // 빨간색
        cout << "\n\n\n\n\n\n";
        cout << "*****************************************************************\n";
        cout << "*                                                               *\n";
        cout << "*                            YOU LOSE!                          *\n";
        cout << "*                                                               *\n";
        cout << "*****************************************************************\n";

        // 해골 해적을 문자로 표현
        SetColor(15); // 흰색으로 변경
        cout << "                             _____      " << endl;
        cout << "                           /      |     " << endl;
        cout << "                          | () () |    " << endl;
        cout << "                          |  ___  |    " << endl;
        cout << "                          |___  __/     " << endl;
        cout << "                        ___/     |___  " << endl;
        cout << "                       /              | " << endl;
        cout << "                      |    메렁메렁~  |" << endl;
        cout << "                      |_______________| " << endl;

        Sleep(500); // 0.5초 대기

        system("cls");
        Sleep(500); // 0.5초 대기
    }
}
void Print_Slot() // 슬롯 동작
{
    CursorView(false);
    atomic<bool> running(false);
    atomic<bool> stopFlags[3] = { false, false, false }; // 각 슬롯 멈춤 상태
    int stopIndex = 0;
    int key = 0;

    while (true) {
        // 사용자로부터 시작 입력 받기
        while (key != 1) {
            PrintTemplate();
            SetColor(15); // 흰색
            cout << "\n1을 누르면 슬롯 실행 : ";
            SetCursorPosition(24, 18); // 입력 커서 위치 조정
            cin >> key;
            if (key == 1 && money_slot < 1000)
            {
                cout << "ㅋㅋㅋ 잔액 부족" << endl;
                return;
                break;
            }

            if (key != 1) {
                SetCursorPosition(0, 19); // 메시지 출력 위치 조정
                cout << "1을 입력해야 슬롯이 시작됩니다." << endl;
                Sleep(1000); // 메시지 잠시 표시
                system("cls");
            }
        }

        running = true; // 슬롯 실행 상태
        thread slotThread(SlotMachine, ref(running), stopFlags); // 슬롯 숫자 업데이트 스레드 시작
        system("cls");
        PrintTemplate();
        SetColor(15); // 흰색
        cout << "\n스페이스 바를 누르면 한칸 씩 멈춥니다.";

     

        while (stopIndex < 3) {
           
            char ch = _getch();
            if (ch == ' ') {
            stopFlags[stopIndex] = true;
            stopIndex++;
            }
        }

        running = false; // 슬롯 종료 상태
        slotThread.join(); // 슬롯 업데이트 스레드 종료 대기
       

        // 숫자 매칭 결과 출력
        int matchResult = Check_Num();
        SetColor(15); // 흰색
        if (matchResult == 7) {
            money_slot *= 100;
            FlashJackpot(); // Jackpot 당첨 시 화려한 화면
            SetCursorPosition(0, 14);
        }
        else if (matchResult == 3) {
            money_slot *= 10;
            Flash3Match(); // 3개 일치 시 화면 깜빡임
        }
        else if (matchResult == 2) {
            money_slot *= 2;
            Flash2Match(); // 2개 일치 시 표시
        }
        else {
            money_slot -= 1000;
            FlashSkullPirate();
        }

        // 다시 실행할지 묻기
        SetColor(15); // 흰색
        cout << "\n슬롯을 다시 실행하시겠습니까? (1: 예, 0: 아니오) : ";
        cin >> key;
        if (key == 1 && money_slot < 1000)
        {
            cout << "ㅋㅋㅋ 잔액 부족" << endl;
            break;
        }
        Init_Slot(); // 슬롯 초기화
        if (key == 0) {
            break; // 종료
        }

        // 슬롯 상태 초기화
        for (int i = 0; i < 3; i++) {
            stopFlags[i] = false;
        }
        stopIndex = 0; // 인덱스 초기화
        system("cls");
    }
    SetColor(15); // 흰색
    cout << "슬롯 머신을 종료합니다." << endl;
}
void Play_Slot(int*num)
{
    money_slot = *num;
    
    SetConsoleFontSize(28);
    SetConsole();
    srand(static_cast<unsigned int>(time(NULL)));
    Init_Slot(); // 슬롯 초기화
    Print_Slot(); // 슬롯 출력
    *num = money_slot;
    return;
}