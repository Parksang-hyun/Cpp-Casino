
#include <iostream>
#include <time.h>
#include <string>
#include <cstdlib>

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
    AM_XX = 500//������
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
            cout << "<������>" << endl;
        }
        else if (jokbo >= KD_13) {
            cout << "����" << endl;
        }
        else if (jokbo == DJ_XX) {
            cout << "������" << endl;
        }
        else if (jokbo > TJ_12) {
            cout << (jokbo - 30) << "��" << endl;
        }
        else if (jokbo == TJ_12) {
            cout << "�˸�" << endl;
        }
        else if (jokbo == TJ_14) {
            cout << "����" << endl;
        }
        else if (jokbo == TJ_19) {
            cout << "����" << endl;
        }
        else if (jokbo == TJ_10) {
            cout << "���" << endl;
        }
        else if (jokbo == TJ_40) {
            cout << "���" << endl;
        }
        else if (jokbo == TJ_46) {
            cout << "����" << endl;
        }
        else if (jokbo == KK_09) {
            cout << "����" << endl;
        }
        else if (jokbo == KK_00) {
            cout << "����" << endl;
        }
        else if (jokbo == MGU_49) {
            cout << "���ֱ��� ����" << endl;
        }
        else if (jokbo == TR_49) {
            cout << "����" << endl;
        }
        else {
            cout << jokbo << "��" << endl;
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
    for (int i = 0; i < 1; i++) { // �÷��̾� �Ѹ� ó��
        if (player[i].deck1.shape == "��" && player[i].deck2.shape == "��") { // ���� �϶�
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
        //������
        else if (player[i].deck1.shape == "�" && player[i].deck2.shape == "�")
        {
            if ((player[i].deck1.number == 4 && player[i].deck2.number == 7) || (player[i].deck1.number == 7 && player[i].deck2.number == 4))
            {
                player[i].jokbo = AM_XX;
            }
        }

        else if (player[i].deck1.number == player[i].deck2.number) { // ���϶�
            player[i].jokbo = DD_01 + player[i].deck1.number - 1;
        }
        else if ((player[i].deck1.number == 1 && player[i].deck2.number == 2) ||
            (player[i].deck1.number == 2 && player[i].deck2.number == 1)) { // �˸�
            player[i].jokbo = TJ_12;
        }
        else if ((player[i].deck1.number == 1 && player[i].deck2.number == 4) ||
            (player[i].deck1.number == 4 && player[i].deck2.number == 1)) { // ����
            player[i].jokbo = TJ_14;
        }
        else if ((player[i].deck1.number == 1 && player[i].deck2.number == 9) ||
            (player[i].deck1.number == 9 && player[i].deck2.number == 1)) { // ����
            player[i].jokbo = TJ_19;
        }
        else if ((player[i].deck1.number == 1 && player[i].deck2.number == 10) ||
            (player[i].deck1.number == 10 && player[i].deck2.number == 1)) { // ���
            player[i].jokbo = TJ_10;
        }
        else if ((player[i].deck1.number == 4 && player[i].deck2.number == 10) ||
            (player[i].deck1.number == 10 && player[i].deck2.number == 4)) { // ���
            player[i].jokbo = TJ_40;
        }
        else if ((player[i].deck1.number == 4 && player[i].deck2.number == 6) ||
            (player[i].deck1.number == 6 && player[i].deck2.number == 4)) { // ����
            player[i].jokbo = TJ_46;
        }
        else if ((player[i].deck1.number == 4 && player[i].deck2.number == 9) ||
            (player[i].deck1.number == 9 && player[i].deck2.number == 4)) { // ����
            if (player[i].deck1.shape == "�" && player[i].deck2.shape == "�")
            {
                player[i].jokbo = MGU_49;
            }
            else
            {
                player[i].jokbo = TR_49;
            }
        }
        else { // ���϶�
            player[i].jokbo = (player[i].deck1.number + player[i].deck2.number) % 10;
        }
    }
}

void Play_Sutda(int* num)
{
    
    srand(time(NULL));

    sutda* Card = new sutda[20];
    User player;

    // ����� �̸� �Է�
    cout << "�÷��̾��� �̸��� �Է��ϼ���: ";
    cin >> player.name;
    player.money = *num;

    // ��ǻ�� �̸� ����
    User computer;
    computer.name = "��ǻ��";

    while (true) {
        // �� ����
        for (int i = 0; i < 20; i++) {
            Card[i].number = i % 10 + 1;
            Card[i].shape = "��"; // �������� ���� �� ���� �����������
        }
        Card[0].shape = "��";
        Card[2].shape = "��";
        Card[7].shape = "��";
        Card[3].shape = "�";
        Card[6].shape = "�";
        Card[8].shape = "�";


        Shuffle(Card);

        // �÷��̾�� ��ǻ�Ͱ� ���� 1000�� ����
        player.money -= 1000;
        computer.money -= 1000;

        // ī�� �й�
        player.deck1 = Card[0];
        player.deck2 = Card[1];
        computer.deck1 = Card[2];
        computer.deck2 = Card[3];

        MakeJokbo(&player); // �÷��̾� ���� ����
        MakeJokbo(&computer); // ��ǻ�� ���� ����

        // �÷��̾� �� ���
        cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
            << player.deck2.number << player.deck2.shape << endl;

        // ���� ����
        cout << "���ñݾ�:1000��\n(1: Call, 0: Die): ";
        int betChoice;
        cin >> betChoice;

        // ���� ��� ó��
        if (betChoice == 1) { // Call
            // �����̿� ��
            if ((player.jokbo == DJ_XX && ((DD_01 <= computer.jokbo) && (computer.jokbo <= DD_09))) || (computer.jokbo == DJ_XX && ((DD_01 <= player.jokbo)&& (player.jokbo <= DD_09))))
            {
                if (player.jokbo == DJ_XX)
                {
                    cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    cout << "!������!" << endl;
                    player.money += 2000; // �̱�� ���� �ݾ��� �����ް� �̱�
                    cout << player.name << "�� �¸�!\n" << endl;
                }
                if (computer.jokbo == DJ_XX)
                {
                    cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    cout << "!������!" << endl;
                    computer.money += 2000; // �̱�� ���� �ݾ��� �����ް� �̱�
                    cout << computer.name << "�� �¸�!\n" << endl;
                }
            }
            else if (player.jokbo == DJ_XX && (DD_01 > computer.jokbo || computer.jokbo > DD_09))
            {
                player.jokbo = KK_00;
                if (computer.jokbo > player.jokbo)
                {
                    cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    computer.money += 2000;
                    cout << computer.name << "�� �¸�!\n" << endl;
                }
                else if (computer.jokbo == player.jokbo)
                {
                    cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    cout << "���º�!\n" << endl;
                    player.money += 1000; // ���� ���ñ� ��ȯ
                    computer.money += 1000;
                }
            }
            else if (computer.jokbo == DJ_XX && (DD_01 > player.jokbo || player.jokbo > DD_09))
            {
                computer.jokbo = KK_00;
                if (computer.jokbo < player.jokbo)
                {
                    cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    player.money += 2000;
                    cout << player.name << "�� �¸�!\n" << endl;
                }
                else if (computer.jokbo == player.jokbo)
                {
                    cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    cout << "���º�!\n" << endl;
                    player.money += 1000; // ���� ���ñ� ��ȯ
                    computer.money += 1000;
                }
            }
            //������
            else if (player.jokbo == AM_XX || computer.jokbo == AM_XX)
            {
                if (player.jokbo == AM_XX)
                {
                    if (computer.jokbo == KD_13 || computer.jokbo == KD_18)
                    {
                        cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                            << player.deck2.number << player.deck2.shape << endl;
                        cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                            << computer.deck2.number << computer.deck2.shape << endl;
                        cout << "!������!" << endl;
                        player.money += 2000; // �̱�� ���� �ݾ��� �����ް� �̱�
                        cout << player.name << "�� �¸�!\n" << endl;
                    }
                    else
                    {
                        player.jokbo = KK_01;
                        if (player.jokbo == computer.jokbo)
                        {
                            cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                                << player.deck2.number << player.deck2.shape << endl;
                            cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                                << computer.deck2.number << computer.deck2.shape << endl;
                            cout << "���º�!\n" << endl;
                            player.money += 1000; // ���� ���ñ� ��ȯ
                            computer.money += 1000;
                        }
                        else if (computer.jokbo > KK_01)
                        {
                            cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                                << player.deck2.number << player.deck2.shape << endl;
                            cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                                << computer.deck2.number << computer.deck2.shape << endl;
                            computer.money += 2000; // �̱�� ���� �ݾ��� �����ް� �̱�
                            cout << computer.name << "�� �¸�!\n" << endl;
                        }
                        else
                        {
                            cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                                << player.deck2.number << player.deck2.shape << endl;
                            cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                                << computer.deck2.number << computer.deck2.shape << endl;
                            player.money += 2000; // �̱�� ���� �ݾ��� �����ް� �̱�
                            cout << player.name << "�� �¸�!\n" << endl;
                        }

                    }
                }
                else
                {
                    if (player.jokbo == KD_13 || player.jokbo == KD_18)
                    {
                        cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                            << player.deck2.number << player.deck2.shape << endl;
                        cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                            << computer.deck2.number << computer.deck2.shape << endl;
                        cout << "!������!" << endl;
                        computer.money += 2000; // �̱�� ���� �ݾ��� �����ް� �̱�
                        cout << computer.name << "�� �¸�!\n" << endl;
                    }
                    else
                    {
                        computer.jokbo = KK_01;
                        if (player.jokbo == computer.jokbo)
                        {
                            cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                                << player.deck2.number << player.deck2.shape << endl;
                            cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                                << computer.deck2.number << computer.deck2.shape << endl;
                            cout << "���º�!\n" << endl;
                            player.money += 1000; // ���� ���ñ� ��ȯ
                            computer.money += 1000;
                        }
                        else if (player.jokbo > KK_01)
                        {
                            cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                                << player.deck2.number << player.deck2.shape << endl;
                            cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                                << computer.deck2.number << computer.deck2.shape << endl;
                            player.money += 2000; // �̱�� ���� �ݾ��� �����ް� �̱�
                            cout << player.name << "�� �¸�!\n" << endl;
                        }
                        else
                        {
                            cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                                << player.deck2.number << player.deck2.shape << endl;
                            cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                                << computer.deck2.number << computer.deck2.shape << endl;
                            computer.money += 2000; // �̱�� ���� �ݾ��� �����ް� �̱�
                            cout << computer.name << "�� �¸�!\n" << endl;
                        }
                    }
                }

            }
            // ����� �۱��� ��� ���º�
            else if ((player.jokbo == TR_49 || computer.jokbo == TR_49) || (player.jokbo == MGU_49 || computer.jokbo == MGU_49))
            {
                if ((player.jokbo == TR_49 && computer.jokbo < DD_01) || (computer.jokbo == TR_49 && player.jokbo < DD_01) || (player.jokbo == MGU_49 && computer.jokbo < DD_10) || (computer.jokbo == MGU_49 && player.jokbo < DD_10))
                {
                    cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    cout << "!49����!\n" << endl;
                    player.money += 1000; // ���� ���ñ� ��ȯ
                    computer.money += 1000;
                }
                else if (player.jokbo == TR_49 && computer.jokbo >= DD_01)
                {
                    player.jokbo = KK_03;
                    cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    computer.money += 2000;
                    cout << computer.name << "�� �¸�!\n" << endl;
                }
                else if (computer.jokbo == TR_49 && player.jokbo >= DD_01)
                {
                    computer.jokbo = KK_03;
                    cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    player.money += 2000; // �̱�� ���� �ݾ��� �����ް� �̱�
                    cout << player.name << "�� �¸�!\n" << endl;
                }
                else if (player.jokbo == MGU_49 && computer.jokbo >= DD_10)
                {
                    player.jokbo = KK_03;
                    cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    computer.money += 2000;
                    cout << computer.name << "�� �¸�!\n" << endl;
                }
                else if (computer.jokbo == MGU_49 && player.jokbo >= DD_10)
                {
                    computer.jokbo = KK_03;
                    cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                        << player.deck2.number << player.deck2.shape << endl;
                    cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                        << computer.deck2.number << computer.deck2.shape << endl;
                    player.money += 2000; // �̱�� ���� �ݾ��� �����ް� �̱�
                    cout << player.name << "�� �¸�!\n" << endl;
                }
            }
            //�������
            else if (player.jokbo > computer.jokbo) {
                cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                    << player.deck2.number << player.deck2.shape << endl;
                cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                    << computer.deck2.number << computer.deck2.shape << endl;
                player.money += 2000; // �̱�� ���� �ݾ��� �����ް� �̱�
                cout << player.name << "�� �¸�!\n" << endl;
            }
            else if (player.jokbo < computer.jokbo) {
                cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                    << player.deck2.number << player.deck2.shape << endl;
                cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                    << computer.deck2.number << computer.deck2.shape << endl;
                computer.money += 2000;
                cout << computer.name << "�� �¸�!\n" << endl;
            }
            // ���º� ó��
            else {
                cout << "\n�÷��̾� ��: " << player.deck1.number << player.deck1.shape << ", "
                    << player.deck2.number << player.deck2.shape << endl;
                cout << "��ǻ�� ��: " << computer.deck1.number << computer.deck1.shape << ", "
                    << computer.deck2.number << computer.deck2.shape << endl;
                cout << "���º�!\n" << endl;
                player.money += 1000; // ���� ���ñ� ��ȯ
                computer.money += 1000;
            }
        }
        else if (betChoice == 0) { // Die
            player.money += 500; // 500�� ����
            computer.money += 1500; // ��ǻ�� ���ñ�
            cout << player.name << "�� �����Ͽ����ϴ�.\n" << endl;
        }

        // ���� �ܰ� ���
        cout << player.name << " �ܰ�: " << player.money << "��" << endl;
        cout << computer.name << " �ܰ�: " << computer.money << "��" << endl;

        // ���� ���� ���� Ȯ��
        if (player.money <= 0 || computer.money <= 0) {
            cout << "���� ����!" << endl;
            break;
        }

        cout << "����Ͻðڽ��ϱ�? (1: ��, 0: �ƴϿ�): ";
        int continueGame;
        cin >> continueGame;
        if (continueGame == 1) {
            system("cls"); // �Ǵ� system("clear"); // �ü���� ���� ����
        }

        if (continueGame == 0) {
            cout << "���� ����!" << endl;
            *num = player.money;
            return;
            break;
        }
    }

    delete[] Card; // �޸� ����
}



