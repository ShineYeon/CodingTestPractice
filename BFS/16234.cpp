//
// Created by α¦ πππππ ππππ α¦ on 2022/10/05.
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

    //ν λ€μ΄ κ°κΈ° μ  μΈν
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
                if(!visited[i][j] && canGo(i, j)) { //μ¬κΈ°μ canGo κ²μ¬ μνλ©΄ λ£¨νκ° μλλλ κ² κ°μ. μμ§?
                    // μνμ’μ° μΈκ΅¬ μ°¨κ° λ²μ λ΄μΈμ§ νμΈνλ κ±΄λ°, νμΈ μνκ³  κ·Έλ₯ λ€μ΄κ°λ©΄ λ§¨ λ§μ§λ§μμ κ³μ checkλ₯Ό trueλ‘ λ§λ€μ΄μ? μ νν λͺ¨λ₯΄κ² λ€ γγ

                    bfs(i, j);
                    check = true;
                    //ans++λ₯Ό μ¬κΈ°λ€ λ£μΌλ©΄ λ§κ² μ λΈ. μμ§?
                    // ν λ² μΈκ΅¬ μ΄λ ν  λ (νλ£¨μ) μ°ν©μ΄ νλλ§ μκΈ°λ κ² μλλΌ
                    // μ¬λ¬ κ°κ° μκΈΈ μ μμ => κ³ λ €ν΄ μ€μΌ ν¨!!
                    // κ·Έλμ ans μ¦κ° μ½λλ μ¬κΈ°κ° μλλΌ, νλ£¨κ° μ¨μ ν λ€ μ§λ¬μ λ (2μ€ for λ¬Έ λ°, whileλ¬Έ μμ λ£λ κ² λ§λ€.)
                }
            }
        }
        if(check) ans++;
        memset(visited, false, sizeof(visited));
    }
    cout<<ans<<"\n";

}