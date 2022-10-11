//
// Created by ღ 𝚂𝚑𝚒𝚗𝚎 𝚈𝚎𝚘𝚗 ღ on 2022/10/08.
//

#include <iostream>
#include <queue>
#include <math.h>
#include <cstring>
using namespace std;

int N, M; //한 변의 크기, 색상의 개수
int board[21][21]; //격자
bool visited[21][21] = {0, };

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
#define DEL -98765432

int rainbowMaxSize = -98765432;
int groupMaxSize = -98765432; // 최대 블록 그룹을 계산하기 위한 maxSize
vector<pair<int, int>> targetGroup; // 블록들을 저장할 배열 => grouping 이후에는 삭제 대상 블록그룹이 담겨 있음
pair<int, int> targetStandard; //삭제 대상 기준 블록
int score = 0; //점수

bool canGo(vector<pair<int, int>> tmpGroup, int rainbowSize, int x, int y) {
    //for(auto group:tmpGroup) {
    //    cout<<group.first<<" "<<group.second<<"\n";
    //}
    //cout<<targetGroup.size()<<"\n";
    //cout<<groupMaxSize<<"\n";
    //cout<<tmpGroup.size()<<"\n";
    if(targetGroup.size() < tmpGroup.size()) { //**********************이부분!
        //cout<<"1\n";
        return true;
    }
    else if(targetGroup.size() == tmpGroup.size()) {
        if(rainbowMaxSize < rainbowSize) {
            //cout<<"2\n";
            return true;
        }
        else if(rainbowMaxSize == rainbowSize){
            if(targetStandard.first < x) {
                //cout<<"3\n";
                return true;
            }
            else if(targetStandard.second < y) {
               cout<<"4\n";
                return true;
            }
        }
    }
    //cout<<"failed\n";
    return false;
}

void BFS(int x, int y) {
    queue<pair<int, int>> q; // bfs 위함
    vector<pair<int, int>> tmpGroup; //현재 블록들
    vector<pair<int, int>> tmpRainbow; //현재 블록에서 무지개 블록들

    int color = board[x][y]; //지금 색깔 저장해야지

    //bfs part
    visited[x][y] = true; // 일단 true로 만들고
    q.push(make_pair(x, y)); //push해.

    tmpGroup.push_back(make_pair(x, y));

    while(!q.empty()) {
        int curX = q.front().first;
        int curY = q.front().second;
        q.pop();
        for(int k=0; k<4; k++) {
            int newX = curX+dx[k];
            int newY = curY+dy[k];
            if(newX<0 || newX>=N || newY<0 || newY>=N || visited[newX][newY]) continue;
            else if(board[newX][newY] == color || board[newX][newY] == 0) {
                //cout<<"here\n";
                visited[newX][newY] = true;
                q.push(make_pair(newX, newY));
                tmpGroup.push_back(make_pair(newX, newY));
                if (board[newX][newY] == 0){
                    tmpRainbow.push_back(make_pair(newX, newY));
                }
            }
        }
    }

    if(canGo(tmpGroup, tmpRainbow.size(), x, y)) {
        targetGroup = tmpGroup; //삭제할 그룹 갱신
        targetStandard.first = x; //삭제할 그룹의 기준 블록 갱신
        targetStandard.second = y;
        rainbowMaxSize = tmpRainbow.size(); //rainbow size 갱신
        groupMaxSize = tmpGroup.size();
    }

    for(int i=0; i<tmpRainbow.size(); i++) {
        int tmpX = tmpRainbow[i].first;
        int tmpY = tmpRainbow[i].second;
        visited[tmpX][tmpY] = false;
    }

}


bool grouping () {
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            if(!visited[i][j] && board[i][j] > 0) {
                BFS(i, j);
            }
        }
    }
    //cout<<groupMaxSize<<"\n";
    //cout<<targetGroup.size()<<"\n";
    return groupMaxSize>1;
}

// 찾은 블록 그룹 삭제
void autoPlay_deleting() {
    int cnt = 0;
    for(int i=0; i < targetGroup.size(); i++) {
        int x = targetGroup[i].first;
        int y = targetGroup[i].second;
        cnt++;
        board[x][y] = DEL;
    }
    //cout<<cnt<<"\n";
    score += pow(cnt, 2);
}

// 중력 작용 (블록들을 아래로 내리기)
void autoPlay_gravity() {
    for(int i=N-2; i>=0; i--) {
        for(int j=0; j<N; j++) {
            int x = i, y = j;
            if(board[x][y] == -1 || board[x][y] == DEL)
                continue;
            for(int k=i+1; k<N; k++) {
                if(board[k][j] == DEL) {
                    board[k][j] = board[k-1][j];
                    board[k-1][j] = DEL;

                }
                else
                    break;
            }

        }
    }
}

// 90도 반시계 방향 회전
void autoPlay_rotation() {
    int tmp[21][21];
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            tmp[N-1-j][i] = board[i][j];
        }
    }
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            board[i][j] = tmp[i][j];
        }
    }
}

void sol() {
    while(grouping()) {
        autoPlay_deleting();
        autoPlay_gravity();
        autoPlay_rotation();
        autoPlay_gravity();

        memset(visited, false, sizeof(visited));
        groupMaxSize = -98765432;
        targetGroup.clear();
        rainbowMaxSize = -98765432;
    }


}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin>>N>>M;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin>>board[i][j];
        }
    }
    sol();
    cout<<score<<"\n";
}