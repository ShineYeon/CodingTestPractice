//
// Created by ღ 𝚂𝚑𝚒𝚗𝚎 𝚈𝚎𝚘𝚗 ღ on 2022/07/26.
//
#include <iostream>
using namespace std;
int N, M, x, y, K;
int board[21][21];
int direction[1001];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};
int dice[7];
int change[4][6] = {{3, 2, 0, 1, 4, 5},
                    {2, 3, 1, 0, 4, 5},
                    {4, 5, 2, 3, 1, 0},
                    {5, 4, 2, 3, 0, 1}};

//주사위 정보 바꿈
int changeDice(int dir, int thereX, int thereY) {
    int tmp[7] ={0, };
    for(int i=0; i<6; i++) {
        tmp[i] = dice[i];
    }
    for(int i=0; i<6; i++) {
        dice[i] = tmp[change[dir][i]];
        //cout<<"here"<<dice[i];
    }
    if(board[thereX][thereY] == 0){
        board[thereX][thereY] = dice[1];
    }
    else {
        dice[1] = board[thereX][thereY];
        board[thereX][thereY] = 0;

    }
    return dice[0];
}

//보드 위에서 주사위 움직임
bool moveDice(int dir) {
    if(x+dx[dir] < 0 || x+dx[dir]>=N || y+dy[dir]<0 || y+dy[dir]>=M)
        return false;
    else{
        x+=dx[dir];
        y+=dy[dir];
        return true;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>N>>M>>x>>y>>K;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++) {
            cin>>board[i][j];
        }
    }
    for(int i=0; i<K; i++){
        int dir;
        cin>>dir;
        direction[i] = dir-1;
    }
    bool isOk=true;
    for(int i=0; i<K; i++){
        isOk = moveDice(direction[i]);
        if(isOk) {
            cout<<changeDice(direction[i], x, y)<<"\n";
            //cout<<x<<y<<"\n";
        }
        else continue;
    }



}