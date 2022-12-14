//
// Created by แฆ ๐๐๐๐๐ ๐๐๐๐ แฆ on 2022/10/11.
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
int sharkX, sharkY; //์๊ธฐ์์ด ์์น ์ ์ฅ
int sharkSize = 2; //์๊ธฐ์์ด ํฌ๊ธฐ ์ ์ฅ

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int minX = -1, minY = -1;
int minDist = 98765432; //์ต๋จ๊ฒฝ๋ก ์ ์ฅ
vector<pair<int, int>> minLoc; // ๋จน์ ์ ์๋ ๋ฌผ๊ณ ๊ธฐ ์์น ์ ์ฅ
int ans = 0;
int nowStack = 0; //ํ์ฌ๊น์ง ๋์ ํด์ ๋จน์ ๋ฌผ๊ณ ๊ธฐ ์ ์ ์ฅ

bool cmp(pair<int, int> a, pair<int, int> b){
    if(a.first==b.first)
        return a.second<b.second;
    else return a.first<b.first;
}

// ๋จน์ ์ ์๋ ๋ฌผ๊ณ ๊ธฐ๊ฐ ์๋ ๊ฒฝ์ฐ ๋จน์ ๋ฌผ๊ณ ๊ธฐ๋ฅผ ์ ์  (minX, minY, minDist ๊ฐฑ์ )
void targeting() {
    bool ret = false;
    // ๋จน์ ์ ์๋ ๋ฌผ๊ณ ๊ธฐ๊ฐ ์์ ๋ ํ๊ฒ ์ ์ 

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            if(board[i][j] <sharkSize && board[i][j]!=0 && dist[i][j]!=-1 && dist[i][j] < minDist) {
                minDist = dist[i][j];
                minX = i, minY = j;
                //ret = true;
            }
        }
    }

    //return ret; // true ๋ฐํ ์ ๋ฌผ๊ณ ๊ธฐ ์ ์ ๋ ๊ฒ
}

// ์ง๊ธ ์ ์ผ ๊ฐ๊น์ด ๊ณต๊ฐ์ ๋จน์ ์ ์๋ ๋ฌผ๊ณ ๊ธฐ ์ฐพ๊ธฐ
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

            //๊ฑฐ์ณ๊ฐ๋ ๊ณต๊ฐ๋ง๋ค ๊ฑฐ๋ฆฌ ๊ฐฑ์ , ๊ฑฐ์ณ๊ฐ ๊ณต๊ฐ์ distLoc์ผ๋ก ๋ฒกํฐ์ ์ ์ฅ
            dist[newX][newY] = dist[nowX][nowY] + 1;
            q.push(make_pair(newX, newY));

            //if(sharkSize>board[newX][newY])
            //    minLoc.push_back(make_pair(newX, newY));

        }

    }
}

// ์ ์ ํ ๋ฌผ๊ณ ๊ธฐ ๋จน๊ธฐ
bool eat() {
    // minDist๊ฐ ์ด๊ธฐ 98765432์ ๊ฐ์ ์๋ผ๋ฉด ๊ฐฑ์ ์ด ์ ๋ ๊ฒ์ (๋จน์ ๋ฌผ๊ณ ๊ธฐ๊ฐ ์๋ค๋ ๋ป)
    if(minDist == 98765432) return false;

    sharkX = minX, sharkY = minY; // ํด๋น ์์น๋ก ์์ด ์ด๋
    nowStack+=1; // ๋จน์์ผ๋๊น ์ด์ ๊น์ง ๋จน์ ๋ฌผ๊ณ ๊ธฐ ์ +1
    board[minX][minY] = 0;
    if(nowStack == sharkSize) { //์ด์ ๊น์ง ๋จน์ ๋ฌผ๊ณ ๊ธฐ ์๊ฐ ์์ด ํฌ๊ธฐ์ ๊ฐ๋ค๋ฉด ์์ด ์ฌ์ด์ฆ ์ปค์ง๊ฒ ํด์ผํจ
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