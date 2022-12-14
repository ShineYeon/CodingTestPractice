//
// Created by α¦ πππππ ππππ α¦ on 2022/07/29.
//

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
string gear[4];
int score[4] = {1, 2, 4, 8};
int K;

void clockwise(int x) {
    string tmp[4];
    for(int i=0; i<4; i++){
        tmp[i] = gear[i];
    }

    for(int j=0; j<7; j++){
        gear[x][j+1] = tmp[x][j];
    }
    gear[x][0] = tmp[x][7];


}

void counterclock(int x) {
    string tmp[4];
    for(int i=0; i<4; i++){
        tmp[i] = gear[i];
    }

    for(int j=0; j<7; j++){
        gear[x][j] = tmp[x][j+1];
    }
    gear[x][7] = tmp[x][0];

}

void setDirection(int which, int (&direction)[4]) {
    int tmp = which;
    while(tmp+1 < 4) { //λ€λ‘ κ°λ©΄μ λ€μ ν±λλ°ν΄ νμ  λ°©ν₯ λ°κΏ
        if(gear[tmp][2] == gear[tmp+1][6]) //λ°λ‘ λ€μ ν±λλ°ν΄μ κ·Ήμ΄ κ°λ€λ©΄ λμ΄μ λ€λ‘ κ° νμ μμ
            break;
        else {
            direction[tmp+1] = direction[tmp] * (-1); //λ°λ‘ λ€μ ν±λλ°ν΄μ κ·Ήμ΄ λ€λ₯΄λ€λ©΄ λ°©ν₯ μ νν΄μΌ ν¨
            tmp++;
        }
    }

    //μμΌλ‘ κ° λλ λ§μ°¬κ°μ§
    tmp = which;
    while(tmp-1>=0) {
        if(gear[tmp][6] == gear[tmp-1][2])
            break;
        else{
            direction[tmp-1] = direction[tmp]*(-1);
            tmp--;
        }
    }
}

void rotate(const int (&direction)[4]) {
    for(int i=0; i<4; i++){
        if(direction[i] == -1){
            counterclock(i);
        }
        else if(direction[i] == 1) {
            clockwise(i);
        }
        else
            continue;
    }
}


int main(){
    for(int i=0; i<4; i++){
        cin>>gear[i];
    }
    cin>>K;
    for(int i=0; i<K; i++){
        int which, dir;
        cin>>which>>dir;
        int direction[4] = {0, };
        direction[which-1] = dir;
        setDirection(which-1, direction);
        rotate(direction);
    }
    int answer = 0;
    for(int i=0; i<4; i++){
        if(gear[i][0] == '1')
            answer+=score[i];
    }
    cout<<answer<<"\n";


}