#include <iostream>
#include <time.h>
#include <string>
#include <windows.h> // 渠傾戚 Sleep 敗呪 紫遂
#include <thread>
#include <atomic>
#include <conio.h>
#include <chrono> // 獣娃 薦嬢研 是廃 虞戚崎君軒
#include <windows.h>

int money_slot=0;


using namespace std;

volatile int numa1; // 十茎 袴重 湛属匝税 収切 段奄葵
volatile int numa2; // 十茎 袴重 却属匝税 収切 段奄葵
volatile int numa3; // 十茎 袴重 実属匝税 収切 段奄葵

volatile int num1[3]; // 湛腰属 十茎 角獄
volatile int num2[3]; // 砧腰属 十茎 角獄
volatile int num3[3]; // 室腰属 十茎 角獄

void SetConsoleFontSize(int fontSize) {
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;               // 亜稽 滴奄 (0生稽 竺舛馬食 切疑生稽)
    cfi.dwFontSize.Y = fontSize;        // 肉闘 滴奄 竺舛
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas"); // 据馬澗 肉闘 戚硯
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}


// 鎮君 竺舛 敗呪
void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void SetConsole() {
    system("title Slot Game"); // 嬬車但 戚硯 竺舛
    system("mode con:cols=65 lines=25"); // 嬬車但 滴奄竺舛
}

void CursorView(bool show) // 朕辞 鉛冊績 薦暗/醗失鉢
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

// 嬬車 朕辞 是帖 繕舛 敗呪
void SetCursorPosition(int x, int y) {
    COORD position = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void Arr_rand_num_1(volatile int* arr, volatile int* num) // 十茎 沓棋 角獄
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

void Init_Slot() // 十茎 段奄鉢 敗呪
{
    numa1 = (rand() % 9 + 1);
    numa2 = (rand() % 9 + 1);
    numa3 = (rand() % 9 + 1);
    Arr_rand_num_1(num1, &numa1);
    Arr_rand_num_1(num2, &numa2);
    Arr_rand_num_1(num3, &numa3);
}
void ClearNumbers() {
    // 十茎 収切 是帖研 朔牒生稽 気嬢辞 収切研 走酔澗 敗呪
    SetCursorPosition(18, 10); // 収切 是帖 1
    cout << "   " << "   " << "   ";

    SetCursorPosition(18, 11); // 収切 是帖 2
    cout << "   " << "   " << "   ";

    SetCursorPosition(18, 12); // 収切 是帖 3
    cout << "   " << "   " << "   ";
    SetCursorPosition(32, 21);// 脊径 是帖 繕舛
}

void PrintNumbers() {
    // ClearNumbers 敗呪研 胡煽 硲窒馬食 戚穿 収切研 走崇
    ClearNumbers();

    // 十茎 収切 窒径
    SetColor(15); // 避事
    SetCursorPosition(18, 10); // 収切 是帖 1
    cout << num1[0] << "   " << num2[0] << "   " << num3[0];

    SetCursorPosition(18, 11); // 収切 是帖 2
    cout << num1[1] << "   " << num2[1] << "   " << num3[1];

    SetCursorPosition(18, 12); // 収切 是帖 3
    cout << num1[2] << "   " << num2[2] << "   " << num3[2];
    SetCursorPosition(32, 21); // 脊径 是帖 繕舛

}

void SlotMachine(atomic<bool>& running, atomic<bool> stopFlags[]) {
    while (running) {
        // 十茎 収切 穣汽戚闘
        if (!stopFlags[0]) Arr_rand_num_1(num1, &numa1);
        if (!stopFlags[1]) Arr_rand_num_1(num2, &numa2);
        if (!stopFlags[2]) Arr_rand_num_1(num3, &numa3);

        PrintNumbers(); // 収切 窒径
        Sleep(70); // 渠傾戚
    }
}

void PrintTemplate() // 十茎 堂 窒径 (堂精 廃 腰幻 窒径)
{
    SetCursorPosition(0, 0);
    SetColor(14); // 葛櫛
    cout << "\t___________________________" << endl;
    cout << "\t  けけけけけけけけけけけけ" << endl;
    cout << "\t  けけけ";
    SetColor(15); // 避事
    cout << "    SLOT    ";
    SetColor(14); // 葛櫛
    cout << "けけけ" << endl;
    cout << "\t  けけけけけけけけけけけけ     袴艦: "<<money_slot<< endl;
    cout << "\t  けけけけけけけけけけけけ     巴傾戚 廃腰拭 1000据~~" << endl;
    cout << "\t  けけけ";
    SetColor(15); // 避事
    cout << "JackPot x100";
    SetColor(14); // 葛櫛
    cout << "けけけ     777 is Jack Pot !!!!!" << endl;
    cout << "\t  けけけ";
    SetColor(15); // 避事
    cout << "3match x10";
    SetColor(14); // 葛櫛
    cout << "  けけけ" << endl;
    cout << "\t  けけけ";
    SetColor(15); // 避事
    cout << "2match x2";
    SetColor(14); // 葛櫛
    cout << "   けけけ" << endl;

    cout << "\t  けけけけけけけけけけけけ" << endl;
    cout << "\t  けけけけけけけけけけけけ" << endl;
    cout << "\t  けけけ            けけけ" << endl;
    SetColor(4); // 避事
    cout << "\t  けけけ            けけけ" << endl;
    SetColor(14); // 葛櫛
    cout << "\t  けけけ            けけけ" << endl;
    cout << "\t  けけけけけけけけけけけけ" << endl;
    cout << "\t  けけけけけけけけけけけけ" << endl;
    cout << "\t  けけけけけけけけけけけけ" << endl;
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
        return 3; // 3鯵 析帖
    }
    else if (num1[1] == num2[1] || num2[1] == num3[1] || num1[1] == num3[1])
    {
        return 2; // 2鯵 析帖
    }
    else
    {
        return 0; // 析帖馬走 省製
    }
}

void PrintJackpot() {
    // 壱舛吉 JACKPOT 五獣走 窒径
    SetCursorPosition(0, 8);
    SetColor(14); // 葛空事

    cout << "****************************************************************\n";
    cout << "*                                                              *\n";
    cout << "*                      【【【 JACKPOT 【【【                   *\n";
    cout << "*                                                              *\n";
    cout << "****************************************************************\n";
}

void PrintFireworks() {
    // 賑宋 斗走澗 反引
    SetCursorPosition(0, 0);
    SetColor(12); // 察娃事
    cout << "              *    .  *         *        .   *      .  \n";
    cout << "        *   .    *   .   *        *   .    *         *    .\n";
    cout << "           *     .   .     *   .     .    *     *     .     \n";
    cout << "              *      .      *     .    *        *      .     \n";
    cout << "              *    .  *         *        .   *      .  \n";
    cout << "        *   .    *   .   *        *   .    *         *    .\n";
    cout << "           *     .   .     *   .     .    *     *     .     \n";
    cout << "              *      .      *     .    *        *      .     \n";
    SetCursorPosition(0, 14);
    SetColor(12); // 察娃事
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
    // 賑宋 斗走澗 採歳聖 因拷生稽 気嬢昇趨辞 鉛冊戚澗 反引研 幻糾
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

    // JACKPOT 五獣走 廃 腰 窒径 (壱舛)

    PrintJackpot();

    for (int i = 0; i < 7; i++) { // 7腰 賑宋 鉛冊績
        PrintFireworks();  // 賑宋 窒径
        Sleep(200); // 0.2段 企奄

        ClearFireworks();  // 賑宋 走酔奄
        Sleep(200); // 0.2段 企奄
    }
}


void Flash3Match() {
    Sleep(1000);
    for (int i = 0; i < 3; i++) { // 3腰 鉛冊績
        system("cls");
        SetColor(10); // 段系事
        cout << "\n\n\n\n\n\n";
        cout << "========================= Well Done! ============================\n";
        cout << "                      3鯵税 収切亜 析帖杯艦陥!\n";
        cout << "=================================================================\n";
        Sleep(500); // 0.5段 企奄

        system("cls");
        Sleep(500); // 0.5段 企奄
    }

    // 繕荊馬澗 五獣走 窒径
    system("cls");
    SetColor(14); // 葛空事
    cout << "\n\n\n\n\n\n";
    cout << "=================================================================\n";
    cout << "                      神! 3鯵亜 限紹革推!\n";
    cout << "=================================================================\n";
    Sleep(1000); // 1段 企奄

    SetColor(12); // 察娃事生稽 痕井
    cout << "\n\n馬走幻... '777'精 焼艦革推! :))" << endl;
    cout << "JACKPOT精 陥製 奄噺拭! 儀 岨 希 潤坐推!!!" << endl;

    Sleep(2000); // 2段 企奄
}


void Flash2Match() {
    Sleep(1000);
    system("cls");
    SetColor(11); // 督空事
    cout << "\n\n\n\n\n\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "                     2鯵税 収切亜 析帖杯艦陥!\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    Sleep(1000); // 1段 企奄

    // 鉦臣軒澗 五獣走 窒径
    SetColor(14); // 葛空事生稽 痕井
    cout << "\n\n\n";
    cout << "   神! 暗税 陥 限宙革推! ;)" << endl;
    cout << "   馬蟹幻 希 限宙陥檎... 3Match戚醸聖 度汽!:(" << endl;
    Sleep(1000); // 1段 企奄

    SetColor(12); // 察娃事生稽 痕井
    cout << "\n   焼習趨推 焼習趨 ;)" << endl;
    cout << "   授降径戚 採膳馬革推 :)" << endl;

    Sleep(2000); // 2段 企奄
}

void FlashSkullPirate() {
    Sleep(1000);
    for (int i = 0; i < 5; i++) { // 3腰 鉛冊績
        system("cls");
        SetColor(12); // 察娃事
        cout << "\n\n\n\n\n\n";
        cout << "*****************************************************************\n";
        cout << "*                                                               *\n";
        cout << "*                            YOU LOSE!                          *\n";
        cout << "*                                                               *\n";
        cout << "*****************************************************************\n";

        // 背茨 背旋聖 庚切稽 妊薄
        SetColor(15); // 避事生稽 痕井
        cout << "                             _____      " << endl;
        cout << "                           /      |     " << endl;
        cout << "                          | () () |    " << endl;
        cout << "                          |  ___  |    " << endl;
        cout << "                          |___  __/     " << endl;
        cout << "                        ___/     |___  " << endl;
        cout << "                       /              | " << endl;
        cout << "                      |    五祁五祁~  |" << endl;
        cout << "                      |_______________| " << endl;

        Sleep(500); // 0.5段 企奄

        system("cls");
        Sleep(500); // 0.5段 企奄
    }
}
void Print_Slot() // 十茎 疑拙
{
    CursorView(false);
    atomic<bool> running(false);
    atomic<bool> stopFlags[3] = { false, false, false }; // 唖 十茎 誇茶 雌殿
    int stopIndex = 0;
    int key = 0;

    while (true) {
        // 紫遂切稽採斗 獣拙 脊径 閤奄
        while (key != 1) {
            PrintTemplate();
            SetColor(15); // 避事
            cout << "\n1聖 刊牽檎 十茎 叔楳 : ";
            SetCursorPosition(24, 18); // 脊径 朕辞 是帖 繕舛
            cin >> key;
            if (key == 1 && money_slot < 1000)
            {
                cout << "せせせ 接衝 採膳" << endl;
                return;
                break;
            }

            if (key != 1) {
                SetCursorPosition(0, 19); // 五獣走 窒径 是帖 繕舛
                cout << "1聖 脊径背醤 十茎戚 獣拙桔艦陥." << endl;
                Sleep(1000); // 五獣走 節獣 妊獣
                system("cls");
            }
        }

        running = true; // 十茎 叔楳 雌殿
        thread slotThread(SlotMachine, ref(running), stopFlags); // 十茎 収切 穣汽戚闘 什傾球 獣拙
        system("cls");
        PrintTemplate();
        SetColor(15); // 避事
        cout << "\n什凪戚什 郊研 刊牽檎 廃牒 梢 誇嫡艦陥.";

     

        while (stopIndex < 3) {
           
            char ch = _getch();
            if (ch == ' ') {
            stopFlags[stopIndex] = true;
            stopIndex++;
            }
        }

        running = false; // 十茎 曽戟 雌殿
        slotThread.join(); // 十茎 穣汽戚闘 什傾球 曽戟 企奄
       

        // 収切 古暢 衣引 窒径
        int matchResult = Check_Num();
        SetColor(15); // 避事
        if (matchResult == 7) {
            money_slot *= 100;
            FlashJackpot(); // Jackpot 雁歎 獣 鉢形廃 鉢檎
            SetCursorPosition(0, 14);
        }
        else if (matchResult == 3) {
            money_slot *= 10;
            Flash3Match(); // 3鯵 析帖 獣 鉢檎 鉛冊績
        }
        else if (matchResult == 2) {
            money_slot *= 2;
            Flash2Match(); // 2鯵 析帖 獣 妊獣
        }
        else {
            money_slot -= 1000;
            FlashSkullPirate();
        }

        // 陥獣 叔楳拝走 康奄
        SetColor(15); // 避事
        cout << "\n十茎聖 陥獣 叔楳馬獣畏柔艦猿? (1: 森, 0: 焼艦神) : ";
        cin >> key;
        if (key == 1 && money_slot < 1000)
        {
            cout << "せせせ 接衝 採膳" << endl;
            break;
        }
        Init_Slot(); // 十茎 段奄鉢
        if (key == 0) {
            break; // 曽戟
        }

        // 十茎 雌殿 段奄鉢
        for (int i = 0; i < 3; i++) {
            stopFlags[i] = false;
        }
        stopIndex = 0; // 昔畿什 段奄鉢
        system("cls");
    }
    SetColor(15); // 避事
    cout << "十茎 袴重聖 曽戟杯艦陥." << endl;
}
void Play_Slot(int*num)
{
    money_slot = *num;
    
    SetConsoleFontSize(28);
    SetConsole();
    srand(static_cast<unsigned int>(time(NULL)));
    Init_Slot(); // 十茎 段奄鉢
    Print_Slot(); // 十茎 窒径
    *num = money_slot;
    return;
}