
#include <iostream>
#include <time.h>
#include <string>
#include <cstdlib>

using namespace std;

enum JOKBO {
    KK_00, // 망통
    KK_01,
    KK_02,
    KK_03,
    KK_04,
    KK_05,
    KK_06,
    KK_07,
    KK_08,
    KK_09, // 갑오
    TJ_46 = 11, // 세륙
    TJ_40, // 장사
    TJ_10, // 장삥
    TJ_19, // 구삥
    TJ_14, // 독사
    TR_49, // 구사
    MGU_49, // 멍구
    TJ_12, // 알리
    DD_01 = 31, // 땡
    DD_02,
    DD_03,
    DD_04,
    DD_05,
    DD_06,
    DD_07,
    DD_08,
    DD_09,
    DD_10, // 장땡
    DJ_XX = 50, // 땡잡이
    KD_13 = 100,
    KD_18,
    KD_38 = 200,
    AM_XX = 500//암행어사
};

struct sutda {
    int number;
    string shape;
};

struct User {
    string name;
    int money=0;
    sutda deck1;
    sutda deck2;
    int jokbo;

    void Print(User* player, int input, int max, int wincount) {
        cout << name << "\t" <<
            deck1.number << deck1.shape << "\t" <<
            deck2.number << deck2.shape << "\t";

        if (jokbo == max) {
            cout << (money += ((500 * input) / wincount)) << "\t";
        }
        else {
            cout << money << "\t";
        }

        if (jokbo == AM_XX) {
            cout << "<암행어사>" << endl;
        }
        else if (jokbo >= KD_13) {
            cout << "광땡" << endl;
        }
        else if (jokbo == DJ_XX) {
            cout << "땡잡이" << endl;
        }
        else if (jokbo > TJ_12) {
            cout << (jokbo - 30) << "땡" << endl;
        }
        else if (jokbo == TJ_12) {
            cout << "알리" << endl;
        }
        else if (jokbo == TJ_14) {
            cout << "독사" << endl;
        }
        else if (jokbo == TJ_19) {
            cout << "구삥" << endl;
        }
        else if (jokbo == TJ_10) {
            cout << "장삥" << endl;
        }
        else if (jokbo == TJ_40) {
            cout << "장사" << endl;
        }
        else if (jokbo == TJ_46) {
            cout << "세륙" << endl;
        }
        else if (jokbo == KK_09) {
            cout << "갑오" << endl;
        }
        else if (jokbo == KK_00) {
            cout << "망통" << endl;
        }
        else if (jokbo == MGU_49) {
            cout << "멍텅구리 구사" << endl;
        }
        else if (jokbo == TR_49) {
            cout << "구사" << endl;
        }
        else {
            cout << jokbo << "끗" << endl;
        }
    }
};

void Swap(sutda* Card, int sour, int dest) {
    sutda temp = Card[sour];
    Card[sour] = Card[dest];
    Card[dest] = temp;
}

void Shuffle(sutda* Card) {
    for (int i = 0; i < 1000; i++) {
        int sour = rand() % 20;
        int dest = rand() % 20;
        Swap(Card, sour, dest);
    }
}

void MakeJokbo(User* player) {
    for (int i = 0; i < 1; i++) { // 플레이어 한명만 처리
        if (player[i].deck1.shape == "光" && player[i].deck2.shape == "光") { // 광땡 일때
            if (player[i].deck1.number + player[i].deck2.number == 4) {
                player[i].jokbo = KD_13;
            }
            else if (player[i].deck1.number + player[i].deck2.number == 9) {
                player[i].jokbo = KD_18;
            }
            else if (player[i].deck1.number + player[i].deck2.number == 11) {
                player[i].jokbo = KD_38;
            }
        }
        //암행어사
        else if (player[i].deck1.shape == "十" && player[i].deck2.shape == "十")
        {
            if ((player[i].deck1.number == 4 && player[i].deck2.number == 7) || (player[i].deck1.number == 7 && player[i].deck2.number == 4))
            {
                player[i].jokbo = AM_XX;
            }
        }

        else if (player[i].deck1.number == player[i].deck2.number) { // 땡일때
            player[i].jokbo = DD_01 + player[i].deck1.number - 1;
        }
        else if ((player[i].deck1.number == 1 && player[i].deck2.number == 2) ||
            (player[i].deck1.number == 2 && player[i].deck2.number == 1)) { // 알리
            player[i].jokbo = TJ_12;
        }
        else if ((player[i].deck1.number == 1 && player[i].deck2.number == 4) ||
            (player[i].deck1.number == 4 && player[i].deck2.number == 1)) { // 독사
            player[i].jokbo = TJ_14;
        }
        else if ((player[i].deck1.number == 1 && player[i].deck2.number == 9) ||
            (player[i].deck1.number == 9 && player[i].deck2.number == 1)) { // 구삥
            player[i].jokbo = TJ_19;
        }
        else if ((player[i].deck1.number == 1 && player[i].deck2.number == 10) ||
            (player[i].deck1.number == 10 && player[i].deck2.number == 1)) { // 장삥
            player[i].jokbo = TJ_10;
        }
        else if ((player[i].deck1.number == 4 && player[i].deck2.number == 10) ||
            (player[i].deck1.number == 10 && player[i].deck2.number == 4)) { // 장사
            player[i].jokbo = TJ_40;
        }
        else if ((player[i].deck1.number == 4 && player[i].deck2.number == 6) ||
            (player[i].deck1.number == 6 && player[i].deck2.number == 4)) { // 세륙
            player[i].jokbo = TJ_46;
        }
        else if ((player[i].deck1.number == 4 && player[i].deck2.number == 9) ||
            (player[i].deck1.number == 9 && player[i].deck2.number == 4)) { // 구사
            if (player[i].deck1.shape == "十" && player[i].deck2.shape == "十")
            {
                player[i].jokbo = MGU_49;
            }
            else
            {
                player[i].jokbo = TR_49;
            }
        }
        else { // 끗일때
            player[i].jokbo = (player[i].deck1.number + player[i].deck2.number) % 10;
        }
    }
}

void Play_Sutda(int* num)
{
    
    srand(time(NULL));

    sutda* Card = new sutda[20];
    User player;

    // 사용자 이름 입력
    cout << "플레이어의 이름을 입력하세요: ";
    cin >> player.name;
    player.money = *num;

    // 컴퓨터 이름 설정
    User computer;
    computer.name = "컴퓨터";

    while (true) {
        // 덱 정의
        for (int i = 0; i < 20; i++) {
            Card[i].number = i % 10 + 1;
            Card[i].shape = "月"; // 비어놓으면 오류 뜸 공백 설정해줘야함
        }
        Card[0].shape = "光";
        Card[2].shape = "光";
        Card[7].shape = "光";
        Card[3].shape = "十";
        Card[6].shape = "十";
        Card[8].shape = "十";


        Shuffle(Card);

        // 플레이어와 컴퓨터가 각각 1000원 배팅
        player.money -= 1000;
        computer.money -= 1000;

        // 카드 분배
        player.deck1 = Card[0];
        player.deck2 = Card[1];
        computer.deck1 = Card[2];
        computer.deck2 = Card[3];

        MakeJokbo(&player); // 플레이어 족보 생성
        MakeJokbo(&computer); // 컴퓨터 족보 생성

        // 플레이어 패 출력
        cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
            << player.deck2.number << player.deck2.shape << endl;

        // 배팅 선택
        cout << "배팅금액:1000원\n(1: Call, 0: Die): ";
        int betChoice;
        cin >> betChoice;

        // 게임 결과 처리
        if (betChoice == 1) { // Call
            // 땡잡이와 땡
            if ((player.jokbo == DJ_XX && ((DD_01 <= computer.jokbo) && (computer.jokbo <= DD_09))) || (computer.jokbo == DJ_XX && ((DD_01 <= player.jokbo)&& (player.jokbo <= DD_09))))
            {
                if (player.jokbo == DJ_XX)
                {
                    cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    cout << "!땡잡이!" << endl;
                    player.money += 2000; // 이기면 배팅 금액을 돌려받고 이김
                    cout << player.name << "의 승리!\n" << endl;
                }
                if (computer.jokbo == DJ_XX)
                {
                    cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    cout << "!땡잡이!" << endl;
                    computer.money += 2000; // 이기면 배팅 금액을 돌려받고 이김
                    cout << computer.name << "의 승리!\n" << endl;
                }
            }
            else if (player.jokbo == DJ_XX && (DD_01 > computer.jokbo || computer.jokbo > DD_09))
            {
                player.jokbo = KK_00;
                if (computer.jokbo > player.jokbo)
                {
                    cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    computer.money += 2000;
                    cout << computer.name << "의 승리!\n" << endl;
                }
                else if (computer.jokbo == player.jokbo)
                {
                    cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    cout << "무승부!\n" << endl;
                    player.money += 1000; // 각자 배팅금 반환
                    computer.money += 1000;
                }
            }
            else if (computer.jokbo == DJ_XX && (DD_01 > player.jokbo || player.jokbo > DD_09))
            {
                computer.jokbo = KK_00;
                if (computer.jokbo < player.jokbo)
                {
                    cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    player.money += 2000;
                    cout << player.name << "의 승리!\n" << endl;
                }
                else if (computer.jokbo == player.jokbo)
                {
                    cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    cout << "무승부!\n" << endl;
                    player.money += 1000; // 각자 배팅금 반환
                    computer.money += 1000;
                }
            }
            //암행어사
            else if (player.jokbo == AM_XX || computer.jokbo == AM_XX)
            {
                if (player.jokbo == AM_XX)
                {
                    if (computer.jokbo == KD_13 || computer.jokbo == KD_18)
                    {
                        cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                            << player.deck2.number << player.deck2.shape << endl;
                        cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                            << computer.deck2.number << computer.deck2.shape << endl;
                        cout << "!암행어사!" << endl;
                        player.money += 2000; // 이기면 배팅 금액을 돌려받고 이김
                        cout << player.name << "의 승리!\n" << endl;
                    }
                    else
                    {
                        player.jokbo = KK_01;
                        if (player.jokbo == computer.jokbo)
                        {
                            cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                                << player.deck2.number << player.deck2.shape << endl;
                            cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                                << computer.deck2.number << computer.deck2.shape << endl;
                            cout << "무승부!\n" << endl;
                            player.money += 1000; // 각자 배팅금 반환
                            computer.money += 1000;
                        }
                        else if (computer.jokbo > KK_01)
                        {
                            cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                                << player.deck2.number << player.deck2.shape << endl;
                            cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                                << computer.deck2.number << computer.deck2.shape << endl;
                            computer.money += 2000; // 이기면 배팅 금액을 돌려받고 이김
                            cout << computer.name << "의 승리!\n" << endl;
                        }
                        else
                        {
                            cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                                << player.deck2.number << player.deck2.shape << endl;
                            cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                                << computer.deck2.number << computer.deck2.shape << endl;
                            player.money += 2000; // 이기면 배팅 금액을 돌려받고 이김
                            cout << player.name << "의 승리!\n" << endl;
                        }

                    }
                }
                else
                {
                    if (player.jokbo == KD_13 || player.jokbo == KD_18)
                    {
                        cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                            << player.deck2.number << player.deck2.shape << endl;
                        cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                            << computer.deck2.number << computer.deck2.shape << endl;
                        cout << "!암행어사!" << endl;
                        computer.money += 2000; // 이기면 배팅 금액을 돌려받고 이김
                        cout << computer.name << "의 승리!\n" << endl;
                    }
                    else
                    {
                        computer.jokbo = KK_01;
                        if (player.jokbo == computer.jokbo)
                        {
                            cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                                << player.deck2.number << player.deck2.shape << endl;
                            cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                                << computer.deck2.number << computer.deck2.shape << endl;
                            cout << "무승부!\n" << endl;
                            player.money += 1000; // 각자 배팅금 반환
                            computer.money += 1000;
                        }
                        else if (player.jokbo > KK_01)
                        {
                            cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                                << player.deck2.number << player.deck2.shape << endl;
                            cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                                << computer.deck2.number << computer.deck2.shape << endl;
                            player.money += 2000; // 이기면 배팅 금액을 돌려받고 이김
                            cout << player.name << "의 승리!\n" << endl;
                        }
                        else
                        {
                            cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                                << player.deck2.number << player.deck2.shape << endl;
                            cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                                << computer.deck2.number << computer.deck2.shape << endl;
                            computer.money += 2000; // 이기면 배팅 금액을 돌려받고 이김
                            cout << computer.name << "의 승리!\n" << endl;
                        }
                    }
                }

            }
            // 구사와 멍구의 경우 무승부
            else if ((player.jokbo == TR_49 || computer.jokbo == TR_49) || (player.jokbo == MGU_49 || computer.jokbo == MGU_49))
            {
                if ((player.jokbo == TR_49 && computer.jokbo < DD_01) || (computer.jokbo == TR_49 && player.jokbo < DD_01) || (player.jokbo == MGU_49 && computer.jokbo < DD_10) || (computer.jokbo == MGU_49 && player.jokbo < DD_10))
                {
                    cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    cout << "!49파토!\n" << endl;
                    player.money += 1000; // 각자 배팅금 반환
                    computer.money += 1000;
                }
                else if (player.jokbo == TR_49 && computer.jokbo >= DD_01)
                {
                    player.jokbo = KK_03;
                    cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    computer.money += 2000;
                    cout << computer.name << "의 승리!\n" << endl;
                }
                else if (computer.jokbo == TR_49 && player.jokbo >= DD_01)
                {
                    computer.jokbo = KK_03;
                    cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    player.money += 2000; // 이기면 배팅 금액을 돌려받고 이김
                    cout << player.name << "의 승리!\n" << endl;
                }
                else if (player.jokbo == MGU_49 && computer.jokbo >= DD_10)
                {
                    player.jokbo = KK_03;
                    cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    computer.money += 2000;
                    cout << computer.name << "의 승리!\n" << endl;
                }
                else if (computer.jokbo == MGU_49 && player.jokbo >= DD_10)
                {
                    computer.jokbo = KK_03;
                    cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    player.money += 2000; // 이기면 배팅 금액을 돌려받고 이김
                    cout << player.name << "의 승리!\n" << endl;
                }
            }
            //족보대로
            else if (player.jokbo > computer.jokbo) {
                cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                    << player.deck2.number << player.deck2.shape << endl;
                cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                    << computer.deck2.number << computer.deck2.shape << endl;
                player.money += 2000; // 이기면 배팅 금액을 돌려받고 이김
                cout << player.name << "의 승리!\n" << endl;
            }
            else if (player.jokbo < computer.jokbo) {
                cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                    << player.deck2.number << player.deck2.shape << endl;
                cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                    << computer.deck2.number << computer.deck2.shape << endl;
                computer.money += 2000;
                cout << computer.name << "의 승리!\n" << endl;
            }
            // 무승부 처리
            else {
                cout << "\n플레이어 패: " << player.deck1.number << player.deck1.shape << ", "
                    << player.deck2.number << player.deck2.shape << endl;
                cout << "컴퓨터 패: " << computer.deck1.number << computer.deck1.shape << ", "
                    << computer.deck2.number << computer.deck2.shape << endl;
                cout << "무승부!\n" << endl;
                player.money += 1000; // 각자 배팅금 반환
                computer.money += 1000;
            }
        }
        else if (betChoice == 0) { // Die
            player.money += 500; // 500원 보상
            computer.money += 1500; // 컴퓨터 배팅금
            cout << player.name << "는 포기하였습니다.\n" << endl;
        }

        // 현재 잔고 출력
        cout << player.name << " 잔고: " << player.money << "원" << endl;
        cout << computer.name << " 잔고: " << computer.money << "원" << endl;

        // 게임 종료 여부 확인
        if (player.money <= 0 || computer.money <= 0) {
            cout << "게임 종료!" << endl;
            break;
        }

        cout << "계속하시겠습니까? (1: 예, 0: 아니오): ";
        int continueGame;
        cin >> continueGame;
        if (continueGame == 1) {
            system("cls"); // 또는 system("clear"); // 운영체제에 따라 선택
        }

        if (continueGame == 0) {
            cout << "게임 종료!" << endl;
            *num = player.money;
            return;
            break;
        }
    }

    delete[] Card; // 메모리 해제
}



