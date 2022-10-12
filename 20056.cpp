//
// Created by ღ 𝚂𝚑𝚒𝚗𝚎 𝚈𝚎𝚘𝚗 ღ on 2022/10/11.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

int N;
int board[21][21];
int dist[21][21];
int sharkX, sharkY; //아기상어 위치 저장
int sharkSize = 2; //아기상어 크기 저장

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int minX = -1, minY = -1;
int minDist = 98765432; //최단경로 저장
vector<pair<int, int>> minLoc; // 먹을 수 있는 물고기 위치 저장
int ans = 0;
int nowStack = 0; //현재까지 누적해서 먹은 물고기 수 저장

bool cmp(pair<int, int> a, pair<int, int> b){
    if(a.first==b.first)
        return a.second<b.second;
    else return a.first<b.first;
}

// 먹을 수 있는 물고기가 있는 경우 먹을 물고기를 선정 (minX, minY, minDist 갱신)
void targeting() {
    bool ret = false;
    // 먹을 수 있는 물고기가 있을 때 타겟 선정

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            if(board[i][j] <sharkSize && board[i][j]!=0 && dist[i][j]!=-1 && dist[i][j] < minDist) {
                minDist = dist[i][j];
                minX = i, minY = j;
                //ret = true;
            }
        }
    }

    //return ret; // true 반환 시 물고기 선정된 것
}

// 지금 제일 가까운 공간에 먹을 수 있는 물고기 찾기
void BFS() {

    queue<pair<int, int>> q;
    q.push(make_pair(sharkX, sharkY));

    while(!q.empty()) {

        int nowX = q.front().first;
        int nowY = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int newX = nowX + dx[i];
            int newY = nowY + dy[i];

            if (newX < 0 || newX >= N || newY < 0 || newY >= N ||
            sharkSize < board[newX][newY] || dist[newX][newY] != -1)
                continue;

            //거쳐가는 공간마다 거리 갱신, 거쳐간 공간을 distLoc으로 벡터에 저장
            dist[newX][newY] = dist[nowX][nowY] + 1;
            q.push(make_pair(newX, newY));

            //if(sharkSize>board[newX][newY])
            //    minLoc.push_back(make_pair(newX, newY));

        }

    }
}

// 선정한 물고기 먹기
bool eat() {
    // minDist가 초기 98765432와 같은 수라면 갱신이 안 된 것임 (먹을 물고기가 없다는 뜻)
    if(minDist == 98765432) return false;

    sharkX = minX, sharkY = minY; // 해당 위치로 상어 이동
    nowStack+=1; // 먹었으니까 이제까지 먹은 물고기 수 +1
    board[minX][minY] = 0;
    if(nowStack == sharkSize) { //이제까지 먹은 물고기 수가 상어 크기와 같다면 상어 사이즈 커지게 해야함
        nowStack = 0;
        sharkSize+=1;
    }
    ans+=minDist;
    return true;
}

void sol() {
    while(1) {

        minDist = 98765432;
        minX=-1, minY=-1;
        memset(dist, -1, sizeof(dist));
        dist[sharkX][sharkY] = 0;
        //minLoc.clear();

        BFS();

        targeting();

        if(!eat()) break;

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
                board[i][j] = 0;
                sharkX = i, sharkY=j;
                sharkSize=2;
            }
        }
    }
    sol();
    cout<<ans<<"\n";
}