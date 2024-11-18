// 최종


#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include <random>
#include <unordered_set>
#include <thread>   // 시간 지연을 위해

using namespace std;

// 노란색 텍스트 출력 함수
void displayYellowText(const string& text) {
    cout << "\033[1;33m" << text << "\033[0m";
}

// 메뉴 출력 함수
void displayMenu() {
    cout << "\n----- 메뉴 -----\n";
    cout << "1. 게임 시작\n";
    cout << "2. 게임 설명\n";
    cout << "3. 나가기\n";
    cout << "선택: ";
}

// 게임 설명 출력 함수
void displayGameDescription() {
    cout << "\n*** 러시안 룰렛 게임 ***\n";
    cout << "딜러 vs 플레이어. 상대방의 체력이 0이 되면 승리합니다!\n";
    cout << "승리 시 베팅 금액의 3배를 획득합니다.\n\n";
    cout << "----아이템 설명----\n";
    cout << "돋보기: 현재 산탄총에 장전된 탄환을 확인할 수 있습니다.\n";
    cout << "맥주캔: 현재 장전된 탄환을 안전하게 배출하여 턴을 넘길 수 있습니다.\n";
    cout << "톱: 실탄이 장전될 경우 두 배의 데미지를 입힙니다.\n";
    cout << "수갑: 상대방의 다음 턴을 건너뛰게 만듭니다.\n\n";
    cout << "----플레이 추가 설명----\n";
    cout << "한 턴에 같은 아이템 두번 사용시, 효과 2배(X) \n";
    cout << "라운드마다 아이템 3개 추가 지급 \n";
    cout << "공탄을 자신에게 쏠 경우 턴을 이어감 \n\n";

}

// 배팅 금액 설정 함수
int bettingMenu(int availableAmount) {
    int betAmount;
    while (true) {
        cout << "\n1. 배팅 가능 금액: " << availableAmount << endl;
        cout << "2. 배팅 할 금액: ";
        cin >> betAmount;

        if (betAmount <= 0) {
            cout << "잘못된 금액입니다. 다시 입력하세요." << endl;
        }
        else if (betAmount > availableAmount) {
            cout << "배팅할 금액이 부족합니다. 다시 입력하세요." << endl;
        }
        else {
            cout << "베팅이 완료되었습니다. 게임을 시작합니다!\n\n";

            // 수정된 부분: 3초 동안 한 글자씩 출력
            string dealerMessage = "딜러: \"내가 총알을 장전하겠소. 순서는 아무도 몰라...\"";
            for (char c : dealerMessage) {
                cout << c << flush;
                this_thread::sleep_for(chrono::milliseconds(100));  // 0.1초마다 한 글자씩 출력
            }
            cout << endl;

            return betAmount;
        }
    }
}

// 플레이어 클래스 정의
class Player {
public:
    string name;
    int health;
    vector<string> items;

    Player(string n) : name(n), health(4) {}

    // 아이템 추가 함수
    void addItem(const string& item) {
        items.push_back(item);
    }

    // 상태 출력 함수
    void showStatus() const {
        cout << name << "의 체력: " << health << endl;
        cout << "보유한 아이템: ";
        for (const string& item : items) {
            cout << item << " ";
        }
        cout << endl;
    }

    // 총 쏘기 함수
    bool shoot(Player* opponent, vector<string>& bullets, bool nextShotDoubleDamage, bool isDealer = false) {
        if (bullets.empty()) return false;

        string bullet = bullets.back();
        bullets.pop_back();

        int target = (isDealer) ? (rand() % 2 + 1) : 0;

        if (!isDealer) {
            cout << name << "는 누구에게 쏘겠습니까? (1: 자신, 2: 상대방): ";
            cin >> target;
        }

        int damage = (bullet == "실탄") ? (nextShotDoubleDamage ? 2 : 1) : 0;

        if (target == 1) {
            cout << name << "가 자신에게 " << bullet << "을(를) 쏘았습니다! 체력이 " << damage << " 감소합니다." << endl;
            health -= damage;
        }
        else {
            cout << name << "가 " << opponent->name << "에게 " << bullet << "을(를) 쏘았습니다! 상대방의 체력이 " << damage << " 감소합니다." << endl;
            opponent->health -= damage;
        }

        return (bullet == "공탄");
    }

    // 아이템 사용 함수 (수갑 포함)
    bool useItem(const string& item, Player* opponent, vector<string>& bullets, bool& skipOpponentTurn, bool& nextShotDoubleDamage) {
        if (item == "돋보기") {
            if (!bullets.empty()) {
                cout << name << "가 돋보기를 사용하여 첫 번째 탄환을 확인했습니다: " << bullets.back() << endl;
            }
            else {
                cout << name << "가 돋보기를 사용했지만, 탄환이 없습니다." << endl;
            }
            return true;
        }
        else if (item == "맥주캔") {
            if (!bullets.empty()) {
                string discardedBullet = bullets.back();
                bullets.pop_back();  // 탄환 배출
                cout << name << "가 맥주캔을 사용하여 안전하게 탄환을 배출했습니다. 배출된 탄환: " << discardedBullet << endl;
                return true;
            }
        }
        else if (item == "톱") {
            cout << name << "가 톱을 사용하여 다음 실탄의 데미지를 두 배로 만듭니다!" << endl;
            nextShotDoubleDamage = true;
            return true;
        }
        else if (item == "수갑") {
            cout << name << "가 수갑을 사용하여 " << opponent->name << "의 턴을 건너뛰게 만듭니다!" << endl;
            skipOpponentTurn = true;
            return true;
        }
        return false;
    }

    // 자동 아이템 사용 함수
    void useRandomItems(Player* opponent, vector<string>& bullets, bool& skipOpponentTurn, bool& nextShotDoubleDamage) {
        while (!items.empty()) {
            int randomIdx = rand() % items.size();
            string item = items[randomIdx];
            items.erase(items.begin() + randomIdx);
            useItem(item, opponent, bullets, skipOpponentTurn, nextShotDoubleDamage);
            if (rand() % 100 >= 50) break;
        }
    }

    // 수동 아이템 선택 함수
    void useSelectedItems(Player* opponent, vector<string>& bullets, bool& skipOpponentTurn, bool& nextShotDoubleDamage) {
        while (true) {
            if (!items.empty()) {
                cout << "\n사용할 아이템을 선택하세요:\n";
                for (int i = 0; i < items.size(); ++i) {
                    cout << i + 1 << ". " << items[i] << endl;
                }

                int choice;
                cout << "선택: ";
                cin >> choice;

                if (choice < 1 || choice > items.size()) {
                    cout << "잘못된 선택입니다.\n";
                    continue;
                }

                string item = items[choice - 1];
                items.erase(items.begin() + (choice - 1));
                useItem(item, opponent, bullets, skipOpponentTurn, nextShotDoubleDamage);
            }
            else {
                cout << "사용할 아이템이 없습니다.\n";
                break;
            }

            cout << "아이템을 더 사용하시겠습니까? (y/n): ";
            char another;
            cin >> another;
            if (another != 'y') break;
        }
    }
};

// 게임 클래스 정의
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

        cout << "\n========= 라운드 시작 =========\n";
        cout << "이번 라운드에 사용될 탄환의 종류: ";
        for (int i = 0; i < shellCount; ++i) {
            bullets.push_back("실탄");
            cout << "실탄 ";
        }
        for (int i = shellCount; i < bulletCount; ++i) {
            bullets.push_back("공탄");
            cout << "공탄 ";
        }
        cout << endl;

        std::mt19937 rng(time(0));
        shuffle(bullets.begin(), bullets.end(), rng);
    }

    // 아이템 분배 함수
    void distributeItems() {
        vector<string> availableItems = { "돋보기", "맥주캔", "톱", "수갑" };
        for (Player* p : { &dealer, &player }) {
            p->items.clear();
            for (int i = 0; i < 3; ++i) {
                int randIndex = rand() % availableItems.size();
                p->addItem(availableItems[randIndex]);
            }
        }
    }

    // 상태 출력 함수
    void showPlayersStatus() const {
        cout << "\n딜러 상태:\n";
        dealer.showStatus();
        cout << "\n플레이어 상태:\n";
        player.showStatus();
    }

    // 딜러 턴 함수
    bool dealerTurn() {
        cout << "\n*" << turnCounter << "번 턴 - 딜러의 차례*\n";
        turnCounter++;

        if (skipOpponentTurn) {
            cout << "플레이어의 수갑 사용으로 딜러의 턴이 종료되었습니다.\n";
            skipOpponentTurn = false;
            return true;
        }

        // 딜러가 아이템을 랜덤으로 사용하지만, 같은 아이템을 두 번 사용하지 않도록
        unordered_set<string> usedItems;  // unordered_set 헤더 추가로 해결
        bool shootToSelf = false;  // 자신에게 쏠지 여부를 판단하는 변수

        while (!dealer.items.empty()) {   // items는 dealer 객체의 멤버 변수임
            int randomIdx = rand() % dealer.items.size();
            string item = dealer.items[randomIdx];

            // 딜러가 이미 사용한 아이템이라면 건너뜀
            if (usedItems.count(item)) continue;

            dealer.items.erase(dealer.items.begin() + randomIdx);  // dealer.items로 접근
            usedItems.insert(item);  // 사용한 아이템을 기록

            // 아이템 사용 처리
            if (dealer.useItem(item, &player, bullets, skipOpponentTurn, nextShotDoubleDamage)) {
                // 돋보기를 사용하여 실탄을 확인했거나 남은 총알이 모두 실탄인 경우, 자신에게 쏘지 않음
                if (item == "돋보기") {
                    if (bullets.back() == "실탄") {
                        cout << "탄환 실탄.\n";
                        continue;
                    }
                    else if (bullets.back() == "공탄") {
                        cout << "탄환 공탄.\n";
                        shootToSelf = true;  // 공탄이면 자신에게 쏘는 로직 활성화
                        continue;
                    }
                }

                // 남은 모든 탄이 실탄일 경우
                if (areAllRemainingBulletsLive()) {
                    resolveShot(bullets.back(), player);  // 플레이어에게 발사
                    return dealer.health > 0;
                }

                // 남은 모든 탄이 공탄일 경우 자신에게 쏘는 로직
                if (!areAllRemainingBulletsLive()) {
                    shootToSelf = true;
                }
            }

            if (rand() % 100 >= 50) break;
        }

        // 공탄을 자신에게 쏘는 로직
        if (shootToSelf) {
            cout << "딜러가 자신에게 방아쇠를 당깁니다." << endl;
            dealer.shoot(&dealer, bullets, nextShotDoubleDamage, true);  // 자신에게 발사
        }
        else {
            cout << "딜러가 방아쇠를 당깁니다." << endl;
            dealer.shoot(&player, bullets, nextShotDoubleDamage, true);  // 플레이어에게 발사
        }


        nextShotDoubleDamage = false;
        return dealer.health > 0;
    }

    // resolveShot 함수 정의
    void resolveShot(const string& bullet, Player& target) {
        if (bullet == "실탄") {
            cout << target.name << "가 실탄을 맞았습니다! 체력이 1 감소합니다.\n";
            target.health -= 1;  // 실탄을 맞으면 체력이 1 감소
        }
        else {
            cout << target.name << "가 공탄을 맞았습니다. 아무런 영향이 없습니다.\n";
        }

        if (target.health <= 0) {
            cout << target.name << "가 쓰러졌습니다!\n";
        }
    }

    // 남은 모든 총알이 실탄인지 확인하는 함수
    bool areAllRemainingBulletsLive() {
        for (const string& bullet : bullets) {
            if (bullet == "공탄") return false;
        }
        return true;
    }

    // 플레이어의 턴 함수
    bool playerTurn() {
        cout << "\n*" << turnCounter << "번 턴 - 플레이어의 차례*\n";
        turnCounter++;

        if (skipOpponentTurn) {
            cout << "딜러의 수갑 사용으로 플레이어의 턴이 종료되었습니다.\n";
            skipOpponentTurn = false;
            return true;
        }

        cout << "플레이어의 아이템을 사용할 것입니까? (y/n): ";
        char useItem;
        cin >> useItem;
        if (useItem == 'y') {
            player.useSelectedItems(&dealer, bullets, skipOpponentTurn, nextShotDoubleDamage);
        }

        cout << "플레이어가 방아쇠를 당깁니다." << endl;
        player.shoot(&dealer, bullets, nextShotDoubleDamage);

        //skipOpponentTurn = false;
        nextShotDoubleDamage = false;
        return player.health > 0;
    }

    // 게임 시작 함수
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
                if (playerskip == 2) { // 딜러가 스킵했을 경우 정보 저장
                    skipOpponentTurn = false;
                }
                else if (skipOpponentTurn) {
                    playerskip = 1;
                }
                if (!skipOpponentTurn && !playerTurn()) break;
                if (playerskip == 1) { // 딜러가 스킵했을 경우 초기화
                    skipOpponentTurn = false;
                    playerskip = 0;
                }
                if (skipOpponentTurn) playerskip = 2; // 플레이어가 스킵했을 경우 정보 저장
                if (dealer.health <= 0 || player.health <= 0) break;

                if (bullets.empty()) {
                    cout << "모든 탄환이 소진되었습니다. 라운드가 종료됩니다.\n";
                    break;
                }

                if (playerskip == 2) { // 플레이어가 스킵했을 경우
                    skipOpponentTurn = true; // 스킵 유지
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

            // 수정된 부분: 라운드 끝나고 2.5초 동안 대기
            this_thread::sleep_for(chrono::milliseconds(2500));
        }

        if (dealer.health <= 0) {
            cout << player.name << "가 승리했습니다!" << endl;
            availableAmount += betAmount * 3;
            cout << "베팅 금액의 3배를 획득했습니다:" << betAmount << endl;
        }
        else if (player.health <= 0) {
            cout << dealer.name << "가 승리했습니다!" << endl;
            availableAmount -= betAmount;
            cout << "베팅 금액을 잃었습니다: " << betAmount * 3 << endl;
        }
    }
};

void Play_Roulette(int* num)
{
    srand(time(0));

    displayYellowText("\n*** 러시안 룰렛 ***\n");

    int availableAmount = *num;

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;

        if (choice == 1) {
            int betAmount = bettingMenu(availableAmount);
            Player dealer("딜러");
            Player player("플레이어");
            BuckshotRoulette game(dealer, player, betAmount, availableAmount);
            game.startGame();
        }
        else if (choice == 2) {
            displayGameDescription();
        }
        else if (choice == 3) {
            cout << "게임을 종료합니다.\n";
            *num = availableAmount;
            return;
            break;
        }
        else {
            cout << "잘못된 선택입니다. 다시 선택해주세요.\n";
        }
    }

}

