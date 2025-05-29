#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <regex>

using namespace std;

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\n\r");
    return s.substr(start, end - start + 1);
}

string normalizeBetInput(const string& s) {
    string temp = trim(s);
    temp = regex_replace(temp, regex("\\s+"), " ");
    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

    if (temp == "1st12" || temp == "1st 12") return "1st 12";
    if (temp == "2nd12" || temp == "2nd 12") return "2nd 12";
    if (temp == "3rd12" || temp == "3rd 12") return "3rd 12";

    if (temp == "1st2to1" || temp == "1st 2 to 1") return "1st 2 to 1";
    if (temp == "2nd2to1" || temp == "2nd 2 to 1") return "2nd 2 to 1";
    if (temp == "3rd2to1" || temp == "3rd 2 to 1") return "3rd 2 to 1";

    return temp;
}

string toLowerString(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(),
              [](unsigned char c) { return tolower(c); });
    return result;
}

class RouletteWheel {
private:
    vector<string> slots;
    unordered_map<string, string> colors;

    void initSlotsAndColors() {
        set<int> redNumbers = {
            1, 3, 5, 7, 9, 12, 14, 16, 18,
            19, 21, 23, 25, 27, 30, 32, 34, 36
        };

        for (int i = 1; i <= 36; ++i) {
            string numStr = to_string(i);
            slots.push_back(numStr);
            colors[numStr] = redNumbers.count(i) ? "Red" : "Black";
        }

        slots.push_back("0");
        colors["0"] = "Green";

        slots.push_back("00");
        colors["00"] = "Green";
    }

public:
    RouletteWheel() {
        initSlotsAndColors();
        srand(static_cast<unsigned int>(time(nullptr)));
    }

    string spin() {
        int index = rand() % slots.size();
        return slots[index];
    }

    // For display only: emoji dots for colors
    string getColor(const string& slot) {
        string colorWord = colors.at(slot);
        if (colorWord == "Red") return "🔴";
        if (colorWord == "Black") return "⚫";
        if (colorWord == "Green") return "🟢";
        return colorWord;
    }

    // For logic checks: return color word as string
    string getColorWord(const string& slot) {
        return colors.at(slot);
    }

    bool isNumber(const string& slot) {
        return slot != "0" && slot != "00";
    }

    int toInt(const string& slot) {
        return isNumber(slot) ? stoi(slot) : -1;
    }

    bool isEven(const string& slot) {
        return isNumber(slot) && stoi(slot) % 2 == 0;
    }

    bool isOdd(const string& slot) {
        return isNumber(slot) && stoi(slot) % 2 == 1;
    }

    bool isLow(const string& slot) {
        int val = toInt(slot);
        return val >= 1 && val <= 18;
    }

    bool isHigh(const string& slot) {
        int val = toInt(slot);
        return val >= 19 && val <= 36;
    }

    bool isDozen(const string& slot, int dozen) {
        int val = toInt(slot);
        return val >= 1 + (dozen - 1) * 12 && val <= dozen * 12;
    }

    bool isColumn(const string& slot, int column) {
        int val = toInt(slot);
        if (val == -1) return false;
        if (column == 1) return (val - 1) % 3 == 0;
        if (column == 2) return (val - 2) % 3 == 0;
        if (column == 3) return val % 3 == 0;
        return false;
    }
};

bool isValidBetTarget(const string& target) {
    static const set<string> validBets = {
        "red", "black", "even", "odd", "low", "high",
        "0", "00", "1st 12", "2nd 12", "3rd 12",
        "1st 2 to 1", "2nd 2 to 1", "3rd 2 to 1"
    };

    string normalized = normalizeBetInput(target);
    if (validBets.count(normalized)) return true;

    try {
        int val = stoi(normalized);
        return val >= 1 && val <= 36;
    } catch (...) {
        return false;
    }
}

int getPayout(const string& betTargetOrig, const string& result, RouletteWheel& wheel, int wager) {
    string betTarget = normalizeBetInput(betTargetOrig);

    if (betTarget == result) return wager * 35;

    // Use getColorWord() here for correct logic
    if ((betTarget == "red" || betTarget == "black") && toLowerString(wheel.getColorWord(result)) == betTarget)
        return wager;

    if (betTarget == "even" && wheel.isEven(result)) return wager;
    if (betTarget == "odd" && wheel.isOdd(result)) return wager;
    if (betTarget == "low" && wheel.isLow(result)) return wager;
    if (betTarget == "high" && wheel.isHigh(result)) return wager;

    if (betTarget == "1st 12" && wheel.isDozen(result, 1)) return wager * 2;
    if (betTarget == "2nd 12" && wheel.isDozen(result, 2)) return wager * 2;
    if (betTarget == "3rd 12" && wheel.isDozen(result, 3)) return wager * 2;

    if (betTarget == "1st 2 to 1" && wheel.isColumn(result, 1)) return wager * 2;
    if (betTarget == "2nd 2 to 1" && wheel.isColumn(result, 2)) return wager * 2;
    if (betTarget == "3rd 2 to 1" && wheel.isColumn(result, 3)) return wager * 2;

    return 0;
}

int main() {
    RouletteWheel wheel;
    int balance;

    cout << "Welcome to Double Zero Roulette\n";
    cout << "How many units do you have?\n> ";
    cin >> balance;
    cin.ignore();

    vector<string> history;

    while (balance > 0) {
        vector<pair<string, int>> bets;
        cout << "\nCurrent balance: " << balance << " units.\n";
        cout << "Place your bets (type 'done' to spin or 'quit' to exit).\n";
        cout << "Valid bets: Red, Black, Even, Odd, Low, High, 0, 00,\n";
        cout << "1st 12, 2nd 12, 3rd 12, 1st 2 to 1, 2nd 2 to 1, 3rd 2 to 1, or 1–36.\n";

        while (true) {
            cout << "Bet target (or 'done'/'quit'):\n> ";
            string inputRaw;
            getline(cin, inputRaw);
            string input = normalizeBetInput(inputRaw);

            if (input == "quit") {
                cout << "Thanks for playing!\n";
                return 0;
            }
            if (input == "done") break;

            if (!isValidBetTarget(inputRaw)) {
                cout << "Invalid bet.\n";
                continue;
            }

            string wagerInput;
            int wager;

            cout << "Wager amount:\n> ";
            getline(cin, wagerInput);

            try {
                size_t pos;
                wager = stoi(wagerInput, &pos);
                if (pos != wagerInput.size() || wager <= 0 || wager > balance) {
                    cout << "Invalid wager. Must be a positive integer and less than or equal to your balance.\n";
                    continue;
                }
            } catch (...) {
                cout << "Invalid wager. Must be a positive integer.\n";
                continue;
            }

            bets.emplace_back(input, wager);
            balance -= wager;
        }

        string result = wheel.spin();
        string color = wheel.getColor(result);

        if (bets.empty()) {
            cout << "Spinning wheel, no bet placed.\n";
            cout << "Result: " << result << " (" << color << ")\n";
        } else {
            cout << "\nResult: " << result << " (" << color << ")\n";

            int winnings = 0;
            for (const auto& [betTarget, wager] : bets) {
                int payout = getPayout(betTarget, result, wheel, wager);
                if (payout > 0) {
                    cout << "Win on " << betTarget << "! +" << payout << "\n";
                    winnings += payout + wager;
                } else {
                    cout << "Loss on " << betTarget << ".\n";
                }
            }

            balance += winnings;
            cout << "Updated balance: " << balance << " units\n";
        }

        history.push_back(result + " (" + color + ")");
        cout << "\nPrevious outcomes:\n";
        for (const auto& h : history) {
            cout << h << "  ";
        }
        cout << "\n";
    }

    cout << "\nYou're out of units. Game over!\n";
    return 0;
}
