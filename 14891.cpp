//
// Created by ღ 𝚂𝚑𝚒𝚗𝚎 𝚈𝚎𝚘𝚗 ღ on 2022/07/29.
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
    while(tmp+1 < 4) { //뒤로 가면서 뒤의 톱니바퀴 회전 방향 바꿈
        if(gear[tmp][2] == gear[tmp+1][6]) //바로 뒤의 톱니바퀴와 극이 같다면 더이상 뒤로 갈 필요 없음
            break;
        else {
            direction[tmp+1] = direction[tmp] * (-1); //바로 뒤의 톱니바퀴와 극이 다르다면 방향 전환해야 함
            tmp++;
        }
    }

    //앞으로 갈 때도 마찬가지
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