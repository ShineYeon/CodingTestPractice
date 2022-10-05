//
// Created by ღ 𝚂𝚑𝚒𝚗𝚎 𝚈𝚎𝚘𝚗 ღ on 2022/10/05.
//

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
int N, L, R;
int A[101][101];
bool visited[101][101];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};

bool canGo(int x, int y) {
    for(int i=0; i<4; i++){
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(nx<0 || nx>=N || ny<0 || ny>=N) continue;
        else{
            if( L<=abs(A[nx][ny]-A[x][y]) && abs(A[nx][ny]-A[x][y])<=R) return true;
        }
    }
    return false;
}

void bfs(int x, int y) {
    queue<pair<int, int>> q;
    queue<pair<int, int>> for_grouping;

    int cnt = 0;
    int sum = 0;

    //큐 들어 가기 전 세팅
    visited[x][y] = true;
    q.push(make_pair(x, y));
    for_grouping.push(make_pair(x, y));

    while(!q.empty()) {
        int curX = q.front().first;
        int curY = q.front().second;
        q.pop();
        sum += A[curX][curY];
        cnt += 1;
        for(int i=0; i<4; i++){
            int nextX = curX + dx[i];
            int nextY = curY + dy[i];
            if(nextX<0 || nextX>=N || nextY<0 || nextY>=N) continue;
            if(visited[nextX][nextY]) continue;
            if(L<=abs(A[nextX][nextY] - A[curX][curY]) && abs(A[nextX][nextY] - A[curX][curY])<=R) {
                q.push(make_pair(nextX, nextY));
                for_grouping.push(make_pair(nextX, nextY));
                visited[nextX][nextY] = true;
            }
        }
    }

    int newPeople = sum/cnt;
    while(!for_grouping.empty()) {
        int nowX = for_grouping.front().first;
        int nowY = for_grouping.front().second;
        for_grouping.pop();
        A[nowX][nowY] = newPeople;
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin>>N>>L>>R;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) {
            cin>>A[i][j];
        }
    }

    int ans = 0;
    bool check = true;
    while(check) {
        check = false;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++) {
                if(!visited[i][j] && canGo(i, j)) { //여기서 canGo 검사 안하면 루프가 안끝나는 것 같음. 왜지?
                    // 상하좌우 인구 차가 범위 내인지 확인하는 건데, 확인 안하고 그냥 들어가면 맨 마지막에서 계속 check를 true로 만들어서? 정확히 모르겠다 ㅜㅜ

                    bfs(i, j);
                    check = true;
                    //ans++를 여기다 넣으면 맞게 안 뜸. 왜지?
                    // 한 번 인구 이동 할 때 (하루에) 연합이 하나만 생기는 게 아니라
                    // 여러 개가 생길 수 있음 => 고려해 줘야 함!!
                    // 그래서 ans 증가 코드는 여기가 아니라, 하루가 온전히 다 지났을 때 (2중 for 문 밖, while문 안에 넣는 게 맞다.)
                }
            }
        }
        if(check) ans++;
        memset(visited, false, sizeof(visited));
    }
    cout<<ans<<"\n";

}