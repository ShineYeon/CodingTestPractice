//
// Created by ღ 𝚂𝚑𝚒𝚗𝚎 𝚈𝚎𝚘𝚗 ღ on 2022/08/01.
//

#include <iostream>
#include <vector>
using namespace std;
int N, M;
char board[9][9];
char boardCpy[9][9];
int cctv = 0;
int answer = 99999999;
vector<pair<int, int>> vii; //CCTV들이 있는 좌표
vector<pair<char, int>> vci; //first: CCTV 종류(1~5), second: CCTV 방향


void right(int x, int y) {
    for(int i=y+1; i<M; i++) {
        if(boardCpy[x][i] == '6')
            break;
        if(boardCpy[x][i]>='1' && boardCpy[x][i] <= '5')
            continue;
        boardCpy[x][i] = '#';
    }
}

void left(int x, int y) {
    for(int i=y-1; i>=0; i--) {
        if(boardCpy[x][i] == '6')
            break;
        if(boardCpy[x][i]>='1' && boardCpy[x][i] <= '5')
            continue;
        boardCpy[x][i] = '#';
    }
}

void up(int x, int y) {
    for(int i=x-1; i>=0; i--){
        if(boardCpy[i][y] == '6')
            break;
        if(boardCpy[i][y]>='1' && boardCpy[i][y] <= '5')
            continue;
        boardCpy[i][y] = '#';

    }
}

void down(int x, int y) {
    for(int i=x+1; i<N; i++) {
        if(boardCpy[i][y] == '6')
            break;
        if(boardCpy[i][y]>='1' && boardCpy[i][y] <= '5')
            continue;
        boardCpy[i][y] = '#';

    }
}




int calc() {
    //계산, ans 갱신
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++){
            boardCpy[i][j] = board[i][j];
        }
    }


    for(int i=0; i<vci.size(); i++){
        char which = vci[i].first;
        int dir = vci[i].second;
        if(which=='1') {
            if(dir==0) {
                right(vii[i].first, vii[i].second);
                continue;
            }
            else if(dir==1) {
                down(vii[i].first, vii[i].second);
                continue;
            }
            else if(dir==2) {
                left(vii[i].first, vii[i].second);
                continue;
            }
            else if(dir==3) {
                up( vii[i].first, vii[i].second);
                continue;
            }

        }
        else if(which=='2') {
            if(dir==0||dir==1) {
                left(vii[i].first, vii[i].second);
                right(vii[i].first, vii[i].second);
                continue;
            }
            else if(dir==2||dir==3){
                up(vii[i].first, vii[i].second);
                down(vii[i].first, vii[i].second);
                continue;
            }

        }
        else if(which=='3'){
            if(dir==0) {
                up(vii[i].first, vii[i].second);
                right( vii[i].first, vii[i].second);
                continue;
            }
            else if(dir==1) {
                right(vii[i].first, vii[i].second);
                down(vii[i].first, vii[i].second);
                continue;
            }
            else if(dir==2) {
                left(vii[i].first, vii[i].second);
                down(vii[i].first, vii[i].second);
                continue;
            }
            else if(dir==3) {
                up(vii[i].first, vii[i].second);
                left(vii[i].first, vii[i].second);
                continue;
            }
        }
        else if(which=='4'){
            if(dir==0) {
                left( vii[i].first, vii[i].second);
                up(vii[i].first, vii[i].second);
                right(vii[i].first, vii[i].second);
                continue;
            }
            else if(dir==1) {
                up(vii[i].first, vii[i].second);
                right( vii[i].first, vii[i].second);
                down(vii[i].first, vii[i].second);
                continue;
            }
            else if(dir==2) {
                left(vii[i].first, vii[i].second);
                right(vii[i].first, vii[i].second);
                down(vii[i].first, vii[i].second);
                continue;
            }
            else if(dir==3) {
                up(vii[i].first, vii[i].second);
                left(vii[i].first, vii[i].second);
                down(vii[i].first, vii[i].second);
                continue;
            }

        }
        else if(which=='5'){
            right(vii[i].first, vii[i].second);
            up( vii[i].first, vii[i].second);
            left(vii[i].first, vii[i].second);
            down(vii[i].first, vii[i].second);
            continue;
        }
    }
    int cnt = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(boardCpy[i][j] == '0')
                cnt++;
        }
    }
    return cnt;

}

void sol(int curCnt) {
    if(curCnt == cctv) {
        int ret = calc();
        if(ret<answer) answer =ret;
        return;
    }
    vci[curCnt].second = 0;
    sol(curCnt+1);
    vci[curCnt].second = 1;
    sol(curCnt+1);
    vci[curCnt].second = 2;
    sol(curCnt+1);
    vci[curCnt].second = 3;
    sol(curCnt+1);

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>N>>M;
    char tmp;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin>>tmp;
            board[i][j] = tmp;
            if(tmp>='1' && tmp<='5') {
                cctv++;
                vci.push_back(make_pair(tmp, -1));
                vii.push_back(make_pair(i, j));
            }
        }
    }
    sol(0);
    cout<<answer<<"\n";
}