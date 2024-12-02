#include <iostream>
#include <stack>
#include <string>

class BracketChecker {
private:
    std::string input;

    bool isMatchingPair(char open, char close) const {
        return (open == '(' && close == ')') ||
            (open == '{' && close == '}') ||
            (open == '[' && close == ']');
    }

public:
    BracketChecker(const std::string& str) : input(str) {}

    bool checkBrackets(std::string& errorPosition) {
        std::stack<std::pair<char, size_t>> bracketStack;

        for (size_t i = 0; i < input.size(); ++i) {
            char ch = input[i];

            if (ch == '(' || ch == '{' || ch == '[') {
                bracketStack.push({ ch, i });
            }
            else if (ch == ')' || ch == '}' || ch == ']') {
                if (bracketStack.empty() || !isMatchingPair(bracketStack.top().first, ch)) {
                    errorPosition = input.substr(0, i + 1);
                    return false;
                }
                bracketStack.pop();
            }
            else if (ch == ';') {
                break; 
            }
        }

        if (!bracketStack.empty()) {
            errorPosition = input.substr(0, bracketStack.top().second + 1);
            return false;
        }

        return true;
    }
};

int main() {
    std::string input = "({x-y-z}*[x+2y]-(z+4x));";

    std::cout << "Input string: " << input << "\n";
    BracketChecker checker(input);

    std::string errorPosition;
    if (checker.checkBrackets(errorPosition)) {
        std::cout << "The string is correct.\n";
    }
    else {
        std::cout << "Error in the string at: " << errorPosition << "\n";
    }

    return 0;
}
