#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    while(1) {
        vector<pair<string, long>> program;

        while(1) {
            string command;
            long n = 0;
            cin >> command;
            if (command == "QUIT") return 0;
            if (command == "END") break;
            if (command == "NUM")
                cin >> n;

            program.push_back({command, n});
        }

        int n;
        cin >> n;

        //숫자입력받음
        for (int i = 0; i < n; i++) {
            long k;
            bool flag = true;

            cin >> k;

            int programSize = program.size();

            stack<long> num;
            num.push(k);
            //숫자들을 가지고 명령어 수행해야함.
            for(int j=0; j<programSize; j++) {
                auto cmd = program[j];
                if (cmd.first == "NUM") {
                    long number = cmd.second;
                    num.push(number);
                    if (abs(number) > 1000000000) {
                        flag = false;
                        break;
                    }
                }
                else if (cmd.first == "POP") {
                    if (num.empty()) {
                        flag = false;
                        break;
                    }
                    num.pop();
                }
                else if (cmd.first == "INV") {
                    if (num.empty()) {
                        flag = false;
                        break;
                    }
                    long tmp = num.top();
                    num.pop();
                    tmp *= -1;
                    num.push(tmp);
                }
                else if (cmd.first == "DUP") {
                    if (num.empty()) {
                        flag = false;
                        break;
                    }
                    long tmp = num.top();
                    num.push(tmp);
                }
                else if (cmd.first == "SWP") {
                    if (num.size() < 2) {
                        flag = false;
                        break;
                    }
                    long tmp1 = num.top();
                    num.pop();
                    long tmp2 = num.top();
                    num.pop();
                    num.push(tmp1);
                    num.push(tmp2);
                }
                else if (cmd.first == "ADD") {
                    if (num.size() < 2) {
                        flag = false;
                        break;
                    }
                    long tmp1 = num.top();
                    num.pop();
                    long tmp2 = num.top();
                    num.pop();
                    long add = tmp1+tmp2;

                    if(abs(add) > 1000000000){
                        flag=false;
                        break;
                    }
                    num.push(add);
                } else if (cmd.first == "SUB") {
                    if (num.size() < 2) {
                        flag = false;
                        break;
                    }
                    long tmp1 = num.top();
                    num.pop();
                    long tmp2 = num.top();
                    num.pop();
                    long sub = tmp1*tmp2;

                    if(abs(sub) > 1000000000){
                        flag=false;
                        break;
                    }
                    num.push(sub);
                } else if (cmd.first == "MUL") {
                    if (num.size() < 2) {
                        flag = false;
                        break;
                    }
                    long tmp1 = num.top();
                    num.pop();
                    long tmp2 = num.top();
                    num.pop();

                    long mul = tmp1*tmp2;

                    if(abs(mul) > 1000000000){
                        flag=false;
                        break;
                    }
                    num.push(mul);
                } else if (cmd.first == "DIV") {
                    if (num.size() < 2) {
                        flag = false;
                        break;
                    }
                    long first = num.top(); num.pop();
                    long second = num.top(); num.pop();

                    if (first == 0) {
                        flag = false;
                        break;
                    }

                    long div = abs(second) / abs(first);
                    if (first > 0 && second < 0 || first < 0 && second > 0) {
                        div = div * -1;
                    }
                    if (abs(div) > 1000000000) {
                        flag = false;
                        break;
                    }
                    num.push(div);

                } else if (cmd.first == "MOD") {
                    if (num.size() < 2) {
                        flag = false;
                        break;
                    }
                    long first = num.top(); num.pop();
                    long second = num.top(); num.pop();

                    if (first == 0) {
                        flag = false;
                        break;
                    }

                    long mod = abs(second) % abs(first);
                    if (second < 0) {
                        mod = mod * -1;
                    }
                    if (abs(mod) > 1000000000) {
                        flag = false;
                        break;
                    }
                    num.push(mod);
                }
            }
            if (!flag || num.size() > 1 || num.empty()) {
                cout << "ERROR" << '\n';
            }
            else{
                cout<<num.top()<<"\n";
            }

        }
        cout<<"\n";

    }
    return 0;
}