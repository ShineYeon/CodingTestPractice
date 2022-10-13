//
// Created by ღ 𝚂𝚑𝚒𝚗𝚎 𝚈𝚎𝚘𝚗 ღ on 2022/10/13.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, K; //N:땅의 가로, 세로크기 / M: 맨처음에 심는 나무의 수 / K: 년 수
int addingTree[11][11]; //겨울에 추가되는 양분
int food[11][11]; // 현재 나무에 있는 양분의 양

vector<int> alive[200]; //살아있는 나무 배열, 인덱스는 (x-1)*N + y를 의미, 들어있는 원소는 그 나무의 나이
vector<int> dead[200]; //죽어있는 나무 배열

int dx[8] = {0, 0, 1, 1, 1, -1, -1, -1};
int dy[8] = {1, -1, 1, -1, 0, 1, -1, 0};

void spring() {

    for(int i=1; i<=N*N; i++) {
        if(alive[i].empty()) continue;
        sort(alive[i].begin(), alive[i].end());
        vector<int> tmp;
        int tmpFood = 0;
        int x = (i-1)/N + 1;
        int y = i%N;
        if(y==0) y=N;
        for(int j=0; j<alive[i].size(); j++) {

            //cout<<x<<" "<<y<<"\n";
            //cout<<food[x][y] <<" "<<alive[i][j]<<"\n";
            if(food[x][y] >= alive[i][j]) { // 먹을 수 있으니까 양분 섭취하고 나이 증가
                food[x][y] -= alive[i][j];
                tmp.push_back(alive[i][j]+1);
            }
            else{ // 먹을 수 없으니까 살아있는 나무에서 빼고 죽은 나무에 추가
                dead[i].push_back(alive[i][j]); //죽은 나무에 추가
            }
        }
        alive[i].clear();
        for(int j=0; j<tmp.size(); j++) {
            alive[i].push_back(tmp[j]);
        }
    }
}

void summer() {
    for(int i=1; i<=N*N; i++) {
        if(dead[i].empty()) continue;
        for(int j = 0; j<dead[i].size(); j++){
            int tree_age = dead[i][j]; //죽은 나무의 나이 찾기
            int x = (i-1)/N +1; //인덱스 찾기 => 양분 배열에 추가하기 위해
            int y = i%N;
            if(y==0) y=N;
            food[x][y] += tree_age/2;
        }
        dead[i].clear();
    }

}


void autumn() {
    for(int i=1; i<=N*N; i++) {
        if(alive[i].empty()) continue;
        for(int j=0; j<alive[i].size(); j++){
            if(alive[i][j]%5 == 0){ //5의 배수일 때 번식
                int x = (i-1)/N +1; //양분 배열에 추가하기 위해 인덱스 찾기
                int y = i%N;
                if(y==0) y=N;
                for(int k=0; k<8; k++) { //상하좌우 대각선
                    int nx = x+dx[k];
                    int ny = y+dy[k];
                    if(nx<1 || nx>N || ny<1 || ny>N) continue;
                    int loc = (nx-1) * N +ny;
                    alive[loc].push_back(1);
                }
            }
        }
    }
}

void winter() {
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++){
            food[i][j] += addingTree[i][j];
        }
    }
}

int countTree() {
    int cnt = 0;
    for(int i=1; i<=N*N; i++) {
        cnt += alive[i].size();
    }
    return cnt;
}

int sol() {

    while(K--) {
        //cout<<alive[1].size()<<"\n";
        spring();
        summer();
        autumn();
        winter();
    }
    //cout<<alive[1].size()<<"\n";
    return countTree();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin>>N >> M >> K;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            cin>>addingTree[i][j];
        }
    }

    int x, y, age;
    for(int i=0; i<M; i++) {
        cin>>x>>y>>age;
        int loc = (x-1) * N + y;
        alive[loc].push_back(age);
    }

    // 맨 처음에 각 칸의 양분의 양을 5로 초기화
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            food[i][j] = 5;
        }
    }
    //cout<<food[1][1]<<"\n";
    cout<<sol()<<"\n";

}