//
// Created by ღ 𝚂𝚑𝚒𝚗𝚎 𝚈𝚎𝚘𝚗 ღ on 2022/10/11.
//

#include <iostream>
#include <vector>

using namespace std;

int N;
int board[21][21];
bool visited[21][21];
int sharkX, sharkY; //아기상어 위치 저장
int sharkSize = 2; //아기상어 크기 저장

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int minLength = 98765432; //최단경로 저장
vector<pair<int, int>> minLoc;  // 최단 경로에 있는 물고기 위치 저장
int ans = 0;
int nowStack = 0; //현재까지 누적해서 먹은 물고기 수 저장

bool cmp (pair<int, int> a, pair<int, int> b) {
    if(a.first == b.first)
        return a.second<b.second;
    else return a.first<b.first;
}

// destX, destY에 있는 물고기가 최단 경로인지 확인
void minRoad(int startX, int startY, int destX, int destY, int cnt) {
    if((startX == destX) && (startY==destY)) {
        if(cnt < minLength) {
            minLength = cnt;
            minLoc.clear();
            minLoc.push_back(make_pair(destX, destY));
        }
        else if(cnt==minLength) {
            minLoc.push_back(make_pair(destX, destY));
        }
        return;
    }
    //visited[startX][startY] = true;
    for(int i=0; i<4; i++) {
        int newX = startX + dx[i];
        int newY = startY + dy[i];
        if(newX<0 || newX>=N || newY<0 || newY>=N || visited[newX][newY]) continue;
        if(board[newX][newY] <= board[sharkX][sharkY]) {
            visited[newX][newY] = true;
            minRoad(newX, newY, destX, destY, cnt + 1);
            visited[newX][newY] = false;
        }
    }
}

// 최단경로 내에 있는 물고기 찾기
bool findFish() {
    bool check = false;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            if(i==sharkX && j==sharkY) continue;
            if(board[i][j] >= 1 && board[i][j]<=6 && (board[i][j] < board[sharkX][sharkY])){ //물고기 찾았으니까 최단경로 갱신해야 함
                check = true;
                minRoad(sharkX, sharkY, i, j, 0);
            }
        }
    }

    return check;
}

// 찾은 곳으로 가서 먹기
void go() {
    sort(minLoc.begin(), minLoc.end(), cmp);
    cout<<minLength<<"\n";
    ans += minLength;
    if(nowStack + 1 < sharkSize) {
        nowStack+=1;
    }
    else if (nowStack + 1 == sharkSize) {
        nowStack = 0;
        sharkSize+=1;
    }
    int newX = minLoc[0].first;
    int newY = minLoc[0].second;
    board[newX][newY] = 9;
    board[sharkX][sharkY] = 0;
    sharkX = newX, sharkY = newY;
}

void sol() {
    while(findFish()) {
        go();
        memset(visited, false, sizeof(visited));
        minLength = 98765432;
        minLoc.clear();
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin>>N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) {
            cin>>board[i][j];
            if(board[i][j] == 9){
                sharkX = i, sharkY=j;
            }
        }
    }
    sol();
    cout<<ans<<"\n";
}