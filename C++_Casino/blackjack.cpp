#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

struct Card {
    int value;      // 카드의 값 (1~13)
    char suit;      // 카드의 슈트 (스위트 모양)
};

// 카드 슈트 모양 출력 함수
inline char getSuitSymbol(char suit) {
    switch (suit) {
    case 'S': return '@♠'; // Spades
    case 'C': return '@♣'; // Clubs
    case 'H': return '@♥'; // Hearts
    case 'D': return '@♦'; // Diamonds
    default: return '@?';   // Unknown suit
    }
}

inline void clearScreen();

inline int GameMenu() {
    int choice = 0;
    cout << "====== 블랙잭 게임 ======\n";
    cout << "1. 게임 시작\n";
    cout << "2. 게임 설명\n";
    cout << "3. 종료\n";
    cout << "=========================\n";
    cout << "선택: ";
    cin >> choice;
    return choice;
}

// 카드 덱 생성
inline vector<Card> createDeck() {
    vector<Card> deck;
    char suits[] = { 'S', 'C', 'H', 'D' }; // Spades, Clubs, Hearts, Diamonds

    for (int i = 1; i <= 13; i++) {
        for (int j = 0; j < 4; j++) {
            Card card;
            card.value = i;                 // 카드 값 할당
            card.suit = suits[j];           // 해당 슈트 할당
            deck.push_back(card);           // 덱에 카드 추가
        }
    }
    random_shuffle(deck.begin(), deck.end());  // 덱 섞기
    return deck;
}

// 카드의 실제 값 계산
inline int calculateHandValue(const vector<Card>& hand) {
    int sum = 0;
    int aceCount = 0;

    for (const Card& card : hand) {
        if (card.value > 10) {
            sum += 10; // J, Q, K는 모두 10으로 처리
        }
        else if (card.value == 1) {
            sum += 11; // 에이스는 우선 11로 처리
            aceCount++;
        }
        else {
            sum += card.value; // 그 외의 카드는 그대로 값 사용
        }
    }

    // 합이 21을 넘고 에이스가 있을 때, 에이스를 1로 계산
    while (sum > 21 && aceCount > 0) {
        sum -= 10; // 에이스를 11에서 1로 변경
        aceCount--;
    }

    return sum;
}

// 카드의 각 줄을 생성하여 가로로 출력하는 함수
inline void printCardsHorizontally(const vector<Card>& cards) {
    vector<string> topLine, midLine1, midLine2, midLine3, midLine4, midLine5, botLine;

    for (const Card& card : cards) {
        string value;
        if (card.value == 1) {
            value = "A"; // 에이스
        }
        else if (card.value == 11) {
            value = "J"; // 잭
        }
        else if (card.value == 12) {
            value = "Q"; // 퀸
        }
        else if (card.value == 13) {
            value = "K"; // 킹
        }
        else {
            value = to_string(card.value); // 숫자 카드
        }

        // 카드 모양 구성
        topLine.push_back("+-------+");
        midLine1.push_back("| " + value + string(5 - value.length(), ' ') + " |");
        midLine2.push_back("|       |");
        midLine3.push_back("| " + value + string(5 - value.length(), ' ') + " |");
        midLine4.push_back("|       |");
        midLine5.push_back("|   " + string(1, getSuitSymbol(card.suit)) + "   |"); // 카드 슈트 출력
        botLine.push_back("+-------+");
    }

    // 카드 출력
    for (const string& line : topLine) cout << line << " ";
    cout << endl;
    for (const string& line : midLine1) cout << line << " ";
    cout << endl;
    for (const string& line : midLine2) cout << line << " ";
    cout << endl;
    for (const string& line : midLine3) cout << line << " ";
    cout << endl;
    for (const string& line : midLine4) cout << line << " ";
    cout << endl;
    for (const string& line : midLine5) cout << line << " ";
    cout << endl;
    for (const string& line : botLine) cout << line << " ";
    cout << endl;
}

// 손패 출력 함수 (각 플레이어의 카드 가로로 출력)
inline void printHand(const vector<Card>& hand, const string& name) {
    cout << "\n" << name << "의 카드:\n";
    printCardsHorizontally(hand);
    cout << name << "의 총합: " << calculateHandValue(hand) << "\n\n";
}

// 게임 설명 출력 함수
inline void printGameDescription() {
    cout << "\n===== 블랙잭 게임 설명 =====\n";
    cout << "블랙잭은 21을 넘지 않는 선에서, 카드의 총합이 딜러보다 더 높은 쪽이 승리하는 게임입니다.\n";
    cout << "각 카드는 다음과 같은 값을 가집니다:\n";
    cout << "  - 숫자 카드: 해당 숫자의 값\n";
    cout << "  - J, Q, K: 각 10점\n";
    cout << "  - A(에이스): 1점 또는 11점 (상황에 따라 유리한 쪽으로 계산)\n";
    cout << "플레이어는 카드를 계속 뽑을(Hit) 수 있으며, 총합이 21을 넘으면 패배합니다.\n";
    cout << "딜러는 17 이상일 때까지 카드를 뽑아야 합니다.\n";
    cout << "===========================\n\n";
}

// 블랙잭 게임 메인 함수
inline void playBlackjack(int* num) {
    srand(static_cast<unsigned int>(time(0))); // 난수 생성기 초기화
    vector<Card> deck = createDeck(); // 덱 생성

    vector<Card> playerHand;
    vector<Card> dealerHand;

    int playerMoney = *num;; // 플레이어 초기 금액
    int dealerMoney = 1000; // 딜러 초기 금액

    while (playerMoney > 0 && dealerMoney > 0) {
        int betAmount;

        // 배팅 금액 설정
        cout << "현재 플레이어 금액: " << playerMoney << endl;
        cout << "배팅할 금액을 입력하세요: ";
        cin >> betAmount;

        while (betAmount > playerMoney) {
            cout << "배팅 금액이 너무 많습니다. 다시 입력하세요: ";
            cin >> betAmount;
        }

        playerHand.clear();
        dealerHand.clear();
        playerHand.push_back(deck.back()); deck.pop_back();
        playerHand.push_back(deck.back()); deck.pop_back();
        dealerHand.push_back(deck.back()); deck.pop_back();
        dealerHand.push_back(deck.back()); deck.pop_back();

        cout << "\n딜러의 공개 카드:\n";
        printCardsHorizontally({ dealerHand[0] });  // 가로로 출력

        printHand(playerHand, "플레이어");

        char choice;
        while (true) {
            cout << "행동을 선택하세요 (H: 히트, S: 스탠드): ";
            cin >> choice;
            if (choice == 'H' || choice == 'h') {
                playerHand.push_back(deck.back());
                deck.pop_back();
                printHand(playerHand, "플레이어");

                if (calculateHandValue(playerHand) > 21) {
                    cout << "플레이어가 버스트되었습니다! 딜러 승!" << endl;
                    playerMoney -= betAmount;
                    dealerMoney += betAmount;
                    break;
                }
            }
            else if (choice == 'S' || choice == 's') {
                break;
            }
        }

        if (calculateHandValue(playerHand) <= 21) {
            cout << "딜러의 카드 공개\n";
            printHand(dealerHand, "딜러");

            while (calculateHandValue(dealerHand) < 17) {
                dealerHand.push_back(deck.back());
                deck.pop_back();
                printHand(dealerHand, "딜러");

                if (calculateHandValue(dealerHand) > 21) {
                    cout << "딜러가 버스트되었습니다! 플레이어 승!" << endl;
                    playerMoney += betAmount;
                    dealerMoney -= betAmount;
                    break;
                }
            }

            if (calculateHandValue(dealerHand) <= 21) {
                int playerTotal = calculateHandValue(playerHand);
                int dealerTotal = calculateHandValue(dealerHand);

                cout << "플레이어 총합: " << playerTotal << endl;
                cout << "딜러 총합: " << dealerTotal << endl;

                if (playerTotal > dealerTotal) {
                    cout << "플레이어 승리!" << endl;
                    playerMoney += betAmount;
                    dealerMoney -= betAmount;
                }
                else if (playerTotal < dealerTotal) {
                    cout << "딜러 승리!" << endl;
                    playerMoney -= betAmount;
                    dealerMoney += betAmount;
                }
                else {
                    cout << "무승부!" << endl; // 무승부 처리
                }
            }
        }

        // 게임 진행 여부 결정
        char playAgain;
        cout << "계속 게임을 하시겠습니까? (Y/N): ";
        cin >> playAgain;
        if (playAgain != 'Y' && playAgain != 'y') {
            break;
        }
        clearScreen();
    }

    cout << "게임이 종료되었습니다. 최종 플레이어 금액: " << playerMoney << endl;
    *num = playerMoney;
}

void Play_BlackJack(int* num) {
   
    while (true) {
        // 메뉴 출력
        int choice = GameMenu();

        if (choice == 1) {
            // 게임 시작
            clearScreen();
            playBlackjack(num);
        }
        else if (choice == 2) {
            // 게임 설명 출력
            clearScreen();
            printGameDescription();

        }
        else if (choice == 3) {
            // 종료
            cout << "게임을 종료합니다.\n";

            return;
            break;
        }
        else {
            // 유효하지 않은 입력 처리
            cout << "잘못된 선택입니다. 다시 선택하세요.\n";
        }
    }

    
}
