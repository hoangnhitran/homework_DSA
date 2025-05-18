#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
bool isOperator (char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}
int precedence (char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return -1;
}
bool compareBigInt (vector<int> operand1, vector<int> operand2) {
    if (operand1.size() > operand2.size()) {
        return true;
    } else if (operand1.size() < operand2.size()) {
        return false;
    } else {
        for (int i = 0; i < operand1.size(); i++) {
            if (operand1[i] < operand2[i]) {
                return false;
            } else if (operand1[i] > operand2[i]) {
                return true;
            }
        }
    }
    return true;
}
void removeLeadingZero (vector<int> &operand) {
    while (operand.size() > 1 && operand.front() == 0) {
        operand.erase(operand.begin());
    }
}
void printVector (vector<int> v) {
    int size = v.size();
    for (int i = 0; i < size; i++) {
        cout << v[i];
    }
    cout << endl;
}
vector<int> add (vector<int> operand1, vector<int> operand2);
vector<int> subtract (vector<int> operand1, vector<int> operand2) {
    vector<int> res;
    int size1 = operand1.size() - 1;
    int size2 = operand2.size() - 1;
    int borrow = 0;
    while (size1 >= 0 && size2 >= 0) {
        int sub = operand1[size1] - operand2[size2] - borrow;
        if (sub < 0) {
            sub += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res.push_back(sub);
        size1--;
        size2--;
    }
    while (size1 >= 0) {
        int sub = operand1[size1] - borrow;
        if (sub < 0) {
            sub += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res.push_back(sub);
        size1--;
    }
    reverse(res.begin(), res.end());
    return res;
}
vector<int> add (vector<int> operand1, vector<int> operand2) {
    vector<int> res;
    int size1 = operand1.size() - 1;
    int size2 = operand2.size() - 1;
    int carry = 0;
    while (size1 >= 0 && size2 >= 0) {
        int sum = operand1[size1] + operand2[size2] + carry;
        res.push_back(sum % 10);
        carry = sum / 10;
        size1--;
        size2--; 
    }
    while (size1 >= 0) {
        int sum = operand1[size1] + carry;
        res.push_back(sum % 10);
        carry = sum / 10;
        size1--;
    }
    while (size2 >= 0) {
        int sum = operand2[size2] + carry;
        res.push_back(sum % 10);
        carry = sum / 10;
        size2--;
    }
    if (carry != 0) {
        res.push_back(carry);
    }
    reverse(res.begin(), res.end());
    return res;
}
void normalizeForMultiply (vector<int> &operand1, vector<int> &operand2) {
    int size = max(operand1.size(), operand2.size());
    if (size % 2 != 0) {
        size++;
    }
    operand1.insert(operand1.begin(), size - operand1.size(), 0);
    operand2.insert(operand2.begin(), size - operand2.size(), 0);
}

vector<int> multiplyByKaratsuba (vector<int> operand1, vector<int> operand2) {
    if (operand1.size() == 1 || operand2.size() == 1) {
        if (operand1.size() < operand2.size()) {
            swap(operand1, operand2);
        }
        vector<int> res;
        int carry = 0;
        for (int i = operand1.size() - 1; i >= 0; i--) {
            int sum = operand1[i] * operand2.front() + carry;
            res.push_back(sum % 10);
            carry = sum / 10;
        }
        if (carry != 0) {
            res.push_back(carry);
        }
        reverse(res.begin(), res.end());
        return res;
    }
    int n = max(operand1.size(), operand2.size());
    int m = n / 2;
    vector<int> high1;
    vector<int> low1;
    vector<int> high2;
    vector<int> low2;
    if (operand1.size() > m) {
        high1 = vector<int>(operand1.begin(), operand1.end() - m);
        low1 = vector<int>(operand1.end() - m, operand1.end());
    }
    else {
        high1 = {0};
        low1 = operand1;
    }
    if (operand2.size() > m) {
        high2 = vector<int>(operand2.begin(), operand2.end() - m);
        low2 = vector<int>(operand2.end() - m, operand2.end());
    } else {
        high2 = {0};
        low2 = operand2;    
    }
    vector<int> z1 = multiplyByKaratsuba (high1, high2);
    vector<int> z2 = multiplyByKaratsuba (low1, low2);
    vector<int> z3 = multiplyByKaratsuba (add(high1, low1), add(high2, low2));
    vector<int> temp1 = z1;
    temp1.insert(temp1.end(), 2*m, 0); // thêm 2m chữ số 0 vào cuối
    vector<int> temp2 = subtract(subtract(z3, z1), z2);
    temp2.insert(temp2.end(), m, 0); // thêm m chữ số 0 vào cuối
    vector<int> res = add(add(temp1, temp2), z2);
    return res;
}
vector<int> divide (vector<int> operand1, vector<int> operand2) {
    if (operand2.empty() || (operand2.size() == 1 && operand2.front() == 0)) {
        return {};
    }
    vector<int> res;
    vector<int> curr;
    while (!operand1.empty()) {
        curr.push_back(operand1.front());
        operand1.erase(operand1.begin());
        int i = 0;
        removeLeadingZero(curr);
        while (i <= 9 && compareBigInt(curr, multiplyByKaratsuba({i}, operand2))) {
            i++;
        }
        if (i == 0) {
            res.push_back(0);
        }
        else {
            res.push_back(i - 1);
        }
        curr = subtract(curr, multiplyByKaratsuba({i - 1}, operand2));
    }
    return res;
}
vector<int> applyOperator(vector<int> operand1, vector<int> operand2, char op) {
    switch (op)
    {
        case '+': {
            bool isNegative = false;
            if (operand1.front() < 0 && operand2.front() < 0) { // xử lí cùng dấu âm
            operand1.front() = -operand1.front();
            operand2.front() = -operand2.front();
            isNegative = true;
            }
            // trái dấu chuyển sang phép trừ
            if (operand1.front() < 0 && operand2.front() > 0) { 
                operand1.front() = -operand1.front();
                 return subtract (operand1, operand2);
            }
            if (operand1.front() > 0 && operand2.front() < 0) {
                operand2.front() = -operand2.front();
                return subtract (operand1, operand2);
            }
            vector<int> res = add(operand1, operand2);
            if (isNegative) {
                res.front() = -res.front();
            }
            return res;
        }
        case '-': {
            if (operand1.front() < 0 && operand2.front() > 0) { // số âm trừ cho số dương thì chuyển sang phép cộng 2 số âm
                operand2.front() = -operand2.front();
                return add(operand1, operand2);
            }
            if (operand1.front() > 0 && operand2.front() < 0) { // số dương trừ cho số âm thì chuyển sang phép cộng 2 số dương
                operand2.front() = -operand2.front();
                return add(operand1, operand2);
            }
            bool swapped = false;
            if (!compareBigInt(operand1, operand2)) {
                swap(operand1, operand2);
                swapped = true;
            }
            vector<int> res = subtract(operand1, operand2);
            removeLeadingZero(res);
            if (swapped) {
                res.front() = -res.front();
            }
            return res;
        }
        case '*': {
            bool isNegative = false;
            // xử lí dấu của kết quả phép nhân
            if (operand1.front() < 0 && operand2.front() < 0) {
                operand1.front() = -operand1.front();
                operand2.front() = -operand2.front();
            }
            if (operand1.front() < 0 && operand2.front() > 0) {
                operand1.front() = -operand1.front();
                isNegative = true;
            }
            if (operand1.front() > 0 && operand2.front() < 0) {
                operand2.front() = -operand2.front();
                isNegative = true;
            }
            vector<int> res = multiplyByKaratsuba(operand1, operand2);
            removeLeadingZero(res);
            if (isNegative) {
                res.front() = -res.front();
            }
            return res;
        }
        case '/': {
            bool isNegative = false;
            if (operand1.front() < 0 && operand2.front() < 0) {
                operand1.front() = -operand1.front();
                operand2.front() = -operand2.front();
            }
            if (operand1.front() < 0 && operand2.front() > 0) {
                operand1.front() = -operand1.front();
                isNegative = true;
            }
            if (operand1.front() > 0 && operand2.front() < 0) {
                operand2.front() = -operand2.front();
                isNegative = true;
            }
            vector<int> res = divide(operand1, operand2);
            removeLeadingZero(res);
            if (isNegative) {
                res.front() = -res.front();
            }
            return res;
        }
        default:
            return {};
    }
}
void saveResult (ofstream &ofs, vector<int> res) {
    if (res.empty()) {
        cout << "Error" << endl;
        ofs << "Error" << endl;
        return;
    }
    for (int i = 0; i < res.size(); i++) {
        ofs << res[i];
    }
    ofs << endl;
    printVector(res);
}
int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }
    ifstream ifs(argv[1]);
    ofstream ofs(argv[2], ios:: app);

    if (!ifs.is_open()) {
        cout << "Can not open the input file." << endl;
        return 1;
    }
    if (!ofs.is_open()) {
        cout << "Can not create an output file." << endl;
        return 1;
    }
    string exp;
    while (getline(ifs, exp)) {
        stack <char> operators;
        int i = 0;
        stack <vector<int>> values;
        while (i < exp.length()) {
            if (isdigit(exp[i])) {
                vector<int> operand;
                while (i < exp.length() && isdigit(exp[i])) {
                    operand.push_back(exp[i] - '0');
                    i++; 
                }
                if (!operand.empty()) {
                    values.push (operand);
                }
            }
            else if (exp[i] == '(') {
                if (i + 1 < exp.length() && exp[i + 1] == '-' && i + 2 < exp.length() && isdigit(exp[i + 2])) {
                    vector<int> operand;
                    operand.push_back(-(exp[i + 2] - '0'));
                    i += 3;
                    while (i < exp.length() && isdigit(exp[i])) {
                        operand.push_back(exp[i] - '0');
                        i++;
                    }
                    values.push(operand);
                    i++;
                }
                else {
                    operators.push(exp[i]);
                    i++;
                }
            }
            else if (exp[i] == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    char op = operators.top();
                    operators.pop();
                    vector<int> operand2 = values.top();
                    values.pop();
                    vector<int> operand1 = values.top();
                    values.pop();
                    values.push(applyOperator(operand1, operand2, op)); 
                }  
                if (!operators.empty()) {
                    operators.pop();
                }
                i++;
            }
            else if (isOperator(exp[i])) {
                while (!operators.empty() && precedence(operators.top()) >= precedence(exp[i])) {
                    if (values.size() < 2) {
                        cout << "Error" << endl;
                        ofs << "Error" << endl;
                    }
                    else {
                        char op = operators.top();
                        operators.pop();
                        vector<int> operand2 = values.top();
                        values.pop();
                        vector<int> operand1 = values.top();
                        values.pop();
                        values.push(applyOperator(operand1, operand2, op));
                    }
                }
                operators.push(exp[i]);
                i++;
            }
            else if (isspace(exp[i])) {
                i++;
            } 
            else {
                cout << "Error" << endl;
                ofs << "Error" << endl;
                break;
            }
        }
        while(values.size() > 1) {
            char op = operators.top();
            operators.pop();
            vector<int> operand2 = values.top();
            values.pop();
            vector<int> operand1 = values.top();
            values.pop();
            values.push(applyOperator(operand1, operand2, op)); 
        }
        if (!operators.empty()) {
            cout << "Error" << endl;
            ofs << "Error" << endl;
        }
        else if (!values.top().empty()){
            saveResult(ofs, values.top());
        } else {
            cout << "Error" << endl;
            ofs << "Error" << endl;
        }
    }
    ifs.close();
    ofs.close();
}