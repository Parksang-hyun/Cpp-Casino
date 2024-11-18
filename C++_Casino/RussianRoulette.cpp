// ����


#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include <random>
#include <unordered_set>
#include <thread>   // �ð� ������ ����

using namespace std;

// ����� �ؽ�Ʈ ��� �Լ�
void displayYellowText(const string& text) {
    cout << "\033[1;33m" << text << "\033[0m";
}

// �޴� ��� �Լ�
void displayMenu() {
    cout << "\n----- �޴� -----\n";
    cout << "1. ���� ����\n";
    cout << "2. ���� ����\n";
    cout << "3. ������\n";
    cout << "����: ";
}

// ���� ���� ��� �Լ�
void displayGameDescription() {
    cout << "\n*** ���þ� �귿 ���� ***\n";
    cout << "���� vs �÷��̾�. ������ ü���� 0�� �Ǹ� �¸��մϴ�!\n";
    cout << "�¸� �� ���� �ݾ��� 3�踦 ȹ���մϴ�.\n\n";
    cout << "----������ ����----\n";
    cout << "������: ���� ��ź�ѿ� ������ źȯ�� Ȯ���� �� �ֽ��ϴ�.\n";
    cout << "����ĵ: ���� ������ źȯ�� �����ϰ� �����Ͽ� ���� �ѱ� �� �ֽ��ϴ�.\n";
    cout << "��: ��ź�� ������ ��� �� ���� �������� �����ϴ�.\n";
    cout << "����: ������ ���� ���� �ǳʶٰ� ����ϴ�.\n\n";
    cout << "----�÷��� �߰� ����----\n";
    cout << "�� �Ͽ� ���� ������ �ι� ����, ȿ�� 2��(X) \n";
    cout << "���帶�� ������ 3�� �߰� ���� \n";
    cout << "��ź�� �ڽſ��� �� ��� ���� �̾ \n\n";

}

// ���� �ݾ� ���� �Լ�
int bettingMenu(int availableAmount) {
    int betAmount;
    while (true) {
        cout << "\n1. ���� ���� �ݾ�: " << availableAmount << endl;
        cout << "2. ���� �� �ݾ�: ";
        cin >> betAmount;

        if (betAmount <= 0) {
            cout << "�߸��� �ݾ��Դϴ�. �ٽ� �Է��ϼ���." << endl;
        }
        else if (betAmount > availableAmount) {
            cout << "������ �ݾ��� �����մϴ�. �ٽ� �Է��ϼ���." << endl;
        }
        else {
            cout << "������ �Ϸ�Ǿ����ϴ�. ������ �����մϴ�!\n\n";

            // ������ �κ�: 3�� ���� �� ���ھ� ���
            string dealerMessage = "����: \"���� �Ѿ��� �����ϰڼ�. ������ �ƹ��� ����...\"";
            for (char c : dealerMessage) {
                cout << c << flush;
                this_thread::sleep_for(chrono::milliseconds(100));  // 0.1�ʸ��� �� ���ھ� ���
            }
            cout << endl;

            return betAmount;
        }
    }
}

// �÷��̾� Ŭ���� ����
class Player {
public:
    string name;
    int health;
    vector<string> items;

    Player(string n) : name(n), health(4) {}

    // ������ �߰� �Լ�
    void addItem(const string& item) {
        items.push_back(item);
    }

    // ���� ��� �Լ�
    void showStatus() const {
        cout << name << "�� ü��: " << health << endl;
        cout << "������ ������: ";
        for (const string& item : items) {
            cout << item << " ";
        }
        cout << endl;
    }

    // �� ��� �Լ�
    bool shoot(Player* opponent, vector<string>& bullets, bool nextShotDoubleDamage, bool isDealer = false) {
        if (bullets.empty()) return false;

        string bullet = bullets.back();
        bullets.pop_back();

        int target = (isDealer) ? (rand() % 2 + 1) : 0;

        if (!isDealer) {
            cout << name << "�� �������� ��ڽ��ϱ�? (1: �ڽ�, 2: ����): ";
            cin >> target;
        }

        int damage = (bullet == "��ź") ? (nextShotDoubleDamage ? 2 : 1) : 0;

        if (target == 1) {
            cout << name << "�� �ڽſ��� " << bullet << "��(��) ��ҽ��ϴ�! ü���� " << damage << " �����մϴ�." << endl;
            health -= damage;
        }
        else {
            cout << name << "�� " << opponent->name << "���� " << bullet << "��(��) ��ҽ��ϴ�! ������ ü���� " << damage << " �����մϴ�." << endl;
            opponent->health -= damage;
        }

        return (bullet == "��ź");
    }

    // ������ ��� �Լ� (���� ����)
    bool useItem(const string& item, Player* opponent, vector<string>& bullets, bool& skipOpponentTurn, bool& nextShotDoubleDamage) {
        if (item == "������") {
            if (!bullets.empty()) {
                cout << name << "�� �����⸦ ����Ͽ� ù ��° źȯ�� Ȯ���߽��ϴ�: " << bullets.back() << endl;
            }
            else {
                cout << name << "�� �����⸦ ���������, źȯ�� �����ϴ�." << endl;
            }
            return true;
        }
        else if (item == "����ĵ") {
            if (!bullets.empty()) {
                string discardedBullet = bullets.back();
                bullets.pop_back();  // źȯ ����
                cout << name << "�� ����ĵ�� ����Ͽ� �����ϰ� źȯ�� �����߽��ϴ�. ����� źȯ: " << discardedBullet << endl;
                return true;
            }
        }
        else if (item == "��") {
            cout << name << "�� ���� ����Ͽ� ���� ��ź�� �������� �� ��� ����ϴ�!" << endl;
            nextShotDoubleDamage = true;
            return true;
        }
        else if (item == "����") {
            cout << name << "�� ������ ����Ͽ� " << opponent->name << "�� ���� �ǳʶٰ� ����ϴ�!" << endl;
            skipOpponentTurn = true;
            return true;
        }
        return false;
    }

    // �ڵ� ������ ��� �Լ�
    void useRandomItems(Player* opponent, vector<string>& bullets, bool& skipOpponentTurn, bool& nextShotDoubleDamage) {
        while (!items.empty()) {
            int randomIdx = rand() % items.size();
            string item = items[randomIdx];
            items.erase(items.begin() + randomIdx);
            useItem(item, opponent, bullets, skipOpponentTurn, nextShotDoubleDamage);
            if (rand() % 100 >= 50) break;
        }
    }

    // ���� ������ ���� �Լ�
    void useSelectedItems(Player* opponent, vector<string>& bullets, bool& skipOpponentTurn, bool& nextShotDoubleDamage) {
        while (true) {
            if (!items.empty()) {
                cout << "\n����� �������� �����ϼ���:\n";
                for (int i = 0; i < items.size(); ++i) {
                    cout << i + 1 << ". " << items[i] << endl;
                }

                int choice;
                cout << "����: ";
                cin >> choice;

                if (choice < 1 || choice > items.size()) {
                    cout << "�߸��� �����Դϴ�.\n";
                    continue;
                }

                string item = items[choice - 1];
                items.erase(items.begin() + (choice - 1));
                useItem(item, opponent, bullets, skipOpponentTurn, nextShotDoubleDamage);
            }
            else {
                cout << "����� �������� �����ϴ�.\n";
                break;
            }

            cout << "�������� �� ����Ͻðڽ��ϱ�? (y/n): ";
            char another;
            cin >> another;
            if (another != 'y') break;
        }
    }
};

// ���� Ŭ���� ����
class BuckshotRoulette {
public:
    vector<string> bullets;
    Player& dealer;
    Player& player;
    bool skipOpponentTurn = false;
    bool nextShotDoubleDamage = false;
    int betAmount;
    int turnCounter = 1;
    int& availableAmount;

    BuckshotRoulette(Player& p1, Player& p2, int bet, int& amount) : dealer(p1), player(p2), betAmount(bet), availableAmount(amount) {}

    void initializeBullets() {
        bullets.clear();
        int bulletCount = rand() % 5 + 2;
        int shellCount = rand() % (bulletCount - 1) + 1;

        cout << "\n========= ���� ���� =========\n";
        cout << "�̹� ���忡 ���� źȯ�� ����: ";
        for (int i = 0; i < shellCount; ++i) {
            bullets.push_back("��ź");
            cout << "��ź ";
        }
        for (int i = shellCount; i < bulletCount; ++i) {
            bullets.push_back("��ź");
            cout << "��ź ";
        }
        cout << endl;

        std::mt19937 rng(time(0));
        shuffle(bullets.begin(), bullets.end(), rng);
    }

    // ������ �й� �Լ�
    void distributeItems() {
        vector<string> availableItems = { "������", "����ĵ", "��", "����" };
        for (Player* p : { &dealer, &player }) {
            p->items.clear();
            for (int i = 0; i < 3; ++i) {
                int randIndex = rand() % availableItems.size();
                p->addItem(availableItems[randIndex]);
            }
        }
    }

    // ���� ��� �Լ�
    void showPlayersStatus() const {
        cout << "\n���� ����:\n";
        dealer.showStatus();
        cout << "\n�÷��̾� ����:\n";
        player.showStatus();
    }

    // ���� �� �Լ�
    bool dealerTurn() {
        cout << "\n*" << turnCounter << "�� �� - ������ ����*\n";
        turnCounter++;

        if (skipOpponentTurn) {
            cout << "�÷��̾��� ���� ������� ������ ���� ����Ǿ����ϴ�.\n";
            skipOpponentTurn = false;
            return true;
        }

        // ������ �������� �������� ���������, ���� �������� �� �� ������� �ʵ���
        unordered_set<string> usedItems;  // unordered_set ��� �߰��� �ذ�
        bool shootToSelf = false;  // �ڽſ��� ���� ���θ� �Ǵ��ϴ� ����

        while (!dealer.items.empty()) {   // items�� dealer ��ü�� ��� ������
            int randomIdx = rand() % dealer.items.size();
            string item = dealer.items[randomIdx];

            // ������ �̹� ����� �������̶�� �ǳʶ�
            if (usedItems.count(item)) continue;

            dealer.items.erase(dealer.items.begin() + randomIdx);  // dealer.items�� ����
            usedItems.insert(item);  // ����� �������� ���

            // ������ ��� ó��
            if (dealer.useItem(item, &player, bullets, skipOpponentTurn, nextShotDoubleDamage)) {
                // �����⸦ ����Ͽ� ��ź�� Ȯ���߰ų� ���� �Ѿ��� ��� ��ź�� ���, �ڽſ��� ���� ����
                if (item == "������") {
                    if (bullets.back() == "��ź") {
                        cout << "źȯ ��ź.\n";
                        continue;
                    }
                    else if (bullets.back() == "��ź") {
                        cout << "źȯ ��ź.\n";
                        shootToSelf = true;  // ��ź�̸� �ڽſ��� ��� ���� Ȱ��ȭ
                        continue;
                    }
                }

                // ���� ��� ź�� ��ź�� ���
                if (areAllRemainingBulletsLive()) {
                    resolveShot(bullets.back(), player);  // �÷��̾�� �߻�
                    return dealer.health > 0;
                }

                // ���� ��� ź�� ��ź�� ��� �ڽſ��� ��� ����
                if (!areAllRemainingBulletsLive()) {
                    shootToSelf = true;
                }
            }

            if (rand() % 100 >= 50) break;
        }

        // ��ź�� �ڽſ��� ��� ����
        if (shootToSelf) {
            cout << "������ �ڽſ��� ��Ƽ踦 ���ϴ�." << endl;
            dealer.shoot(&dealer, bullets, nextShotDoubleDamage, true);  // �ڽſ��� �߻�
        }
        else {
            cout << "������ ��Ƽ踦 ���ϴ�." << endl;
            dealer.shoot(&player, bullets, nextShotDoubleDamage, true);  // �÷��̾�� �߻�
        }


        nextShotDoubleDamage = false;
        return dealer.health > 0;
    }

    // resolveShot �Լ� ����
    void resolveShot(const string& bullet, Player& target) {
        if (bullet == "��ź") {
            cout << target.name << "�� ��ź�� �¾ҽ��ϴ�! ü���� 1 �����մϴ�.\n";
            target.health -= 1;  // ��ź�� ������ ü���� 1 ����
        }
        else {
            cout << target.name << "�� ��ź�� �¾ҽ��ϴ�. �ƹ��� ������ �����ϴ�.\n";
        }

        if (target.health <= 0) {
            cout << target.name << "�� ���������ϴ�!\n";
        }
    }

    // ���� ��� �Ѿ��� ��ź���� Ȯ���ϴ� �Լ�
    bool areAllRemainingBulletsLive() {
        for (const string& bullet : bullets) {
            if (bullet == "��ź") return false;
        }
        return true;
    }

    // �÷��̾��� �� �Լ�
    bool playerTurn() {
        cout << "\n*" << turnCounter << "�� �� - �÷��̾��� ����*\n";
        turnCounter++;

        if (skipOpponentTurn) {
            cout << "������ ���� ������� �÷��̾��� ���� ����Ǿ����ϴ�.\n";
            skipOpponentTurn = false;
            return true;
        }

        cout << "�÷��̾��� �������� ����� ���Դϱ�? (y/n): ";
        char useItem;
        cin >> useItem;
        if (useItem == 'y') {
            player.useSelectedItems(&dealer, bullets, skipOpponentTurn, nextShotDoubleDamage);
        }

        cout << "�÷��̾ ��Ƽ踦 ���ϴ�." << endl;
        player.shoot(&dealer, bullets, nextShotDoubleDamage);

        //skipOpponentTurn = false;
        nextShotDoubleDamage = false;
        return player.health > 0;
    }

    // ���� ���� �Լ�
    void startGame() {
        int playerskip = 0;
        while (dealer.health > 0 && player.health > 0) {
            turnCounter = 1;
            initializeBullets();
            distributeItems();
            showPlayersStatus();

            skipOpponentTurn = false;
            playerskip = 0;

            while (!bullets.empty() && dealer.health > 0 && player.health > 0) {
                if (!skipOpponentTurn && !dealerTurn()) break;
                if (playerskip == 2) { // ������ ��ŵ���� ��� ���� ����
                    skipOpponentTurn = false;
                }
                else if (skipOpponentTurn) {
                    playerskip = 1;
                }
                if (!skipOpponentTurn && !playerTurn()) break;
                if (playerskip == 1) { // ������ ��ŵ���� ��� �ʱ�ȭ
                    skipOpponentTurn = false;
                    playerskip = 0;
                }
                if (skipOpponentTurn) playerskip = 2; // �÷��̾ ��ŵ���� ��� ���� ����
                if (dealer.health <= 0 || player.health <= 0) break;

                if (bullets.empty()) {
                    cout << "��� źȯ�� �����Ǿ����ϴ�. ���尡 ����˴ϴ�.\n";
                    break;
                }

                if (playerskip == 2) { // �÷��̾ ��ŵ���� ���
                    skipOpponentTurn = true; // ��ŵ ����
                }
                /*else if (playerskip == 2) {
                    skipOpponentTurn = true;
                }*/
                else {
                    skipOpponentTurn = false;
                    playerskip = 0;
                }
            }

            if (dealer.health <= 0 || player.health <= 0) break;

            // ������ �κ�: ���� ������ 2.5�� ���� ���
            this_thread::sleep_for(chrono::milliseconds(2500));
        }

        if (dealer.health <= 0) {
            cout << player.name << "�� �¸��߽��ϴ�!" << endl;
            availableAmount += betAmount * 3;
            cout << "���� �ݾ��� 3�踦 ȹ���߽��ϴ�:" << betAmount << endl;
        }
        else if (player.health <= 0) {
            cout << dealer.name << "�� �¸��߽��ϴ�!" << endl;
            availableAmount -= betAmount;
            cout << "���� �ݾ��� �Ҿ����ϴ�: " << betAmount * 3 << endl;
        }
    }
};

void Play_Roulette(int* num)
{
    srand(time(0));

    displayYellowText("\n*** ���þ� �귿 ***\n");

    int availableAmount = *num;

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;

        if (choice == 1) {
            int betAmount = bettingMenu(availableAmount);
            Player dealer("����");
            Player player("�÷��̾�");
            BuckshotRoulette game(dealer, player, betAmount, availableAmount);
            game.startGame();
        }
        else if (choice == 2) {
            displayGameDescription();
        }
        else if (choice == 3) {
            cout << "������ �����մϴ�.\n";
            *num = availableAmount;
            return;
            break;
        }
        else {
            cout << "�߸��� �����Դϴ�. �ٽ� �������ּ���.\n";
        }
    }

}

