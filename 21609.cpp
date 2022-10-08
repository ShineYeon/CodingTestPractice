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
int score = 0; //점수
bool flag = true; //그룹핑이 일어났었는지를 저장하기 위한 boolean 변수


void BFS(int x, int y) {
    int color = board[x][y];
    visited[x][y] = true;
    queue<pair<int, int>> q;
    q.push(make_pair(x, y));
    vector<pair<int, int>> vp;
    int grpSize = 1;
    int rainbowSize = 0;
    vp.push_back(make_pair(x, y));
    while(!q.empty()) {
        int curX = q.front().first;
        int curY = q.front().second;
        q.pop();
        for(int k=0; k<4; k++) {
            int newX = curX+dx[k];
            int newY = curY+dy[k];
            if(newX<0 || newX>=N || newY<0 || newY>=N) continue;
            if(!visited[newX][newY] &&
            board[newX][newY]!=-1 && board[newX][newY]!=DEL && (board[newX][newY] == color || board[newX][newY] == 0)) {
                visited[newX][newY] = true;
               q.push(make_pair(newX, newY));
               vp.push_back(make_pair(newX, newY));
               grpSize += 1;
               if (board[newX][newY] == 0)
                   rainbowSize+=1;
            }
        }
    }
    if(groupMaxSize < grpSize){
        targetGroup.clear();
        groupMaxSize = grpSize;
        rainbowMaxSize = rainbowSize;
        targetGroup = vp;
    }
    else if(groupMaxSize == grpSize) {
        if(rainbowSize > rainbowMaxSize) {
            rainbowMaxSize = rainbowSize;
            targetGroup.clear();
            targetGroup = vp;
        }
    }

}

bool canGo (int x, int y) {
    for(int k=0; k<4; k++) {
        int nx = x+dx[k];
        int ny = y+dy[k];
        if(!visited[nx][ny] && board[nx][ny]!=-1)
            return true;
    }
    return false;
}

void grouping () {
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {

            if(!visited[i][j] && canGo(i, j) && board[i][j]!=-1) {
                BFS(i, j);
            }

        }
    }
    cout << targetGroup.size() << "\n";
    if(targetGroup.size() >= 2)
        flag = true;
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
            int nx = i+1, ny = j;
            if(board[x][y] == -1 || board[x][y] == DEL)
                continue;
            while(1) {
                if(board[nx][ny] != DEL) break;
                if(nx==N) break;
                nx += 1;
            }
            nx--;
            board[nx][ny] = board[x][y];
            board[x][y] = DEL;

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
    grouping();
    while(flag) {
        flag = false;
        autoPlay_deleting();
        autoPlay_gravity();
        autoPlay_rotation();
        autoPlay_gravity();
        memset(visited, false, sizeof(visited));
        groupMaxSize = -98765432;
        targetGroup.clear();
        grouping();

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