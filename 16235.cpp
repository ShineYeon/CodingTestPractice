//
// Created by α¦ πππππ ππππ α¦ on 2022/10/13.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, K; //N:λμ κ°λ‘, μΈλ‘ν¬κΈ° / M: λ§¨μ²μμ μ¬λ λλ¬΄μ μ / K: λ μ
int addingTree[11][11]; //κ²¨μΈμ μΆκ°λλ μλΆ
int food[11][11]; // νμ¬ λλ¬΄μ μλ μλΆμ μ

vector<int> alive[200]; //μ΄μμλ λλ¬΄ λ°°μ΄, μΈλ±μ€λ (x-1)*N + yλ₯Ό μλ―Έ, λ€μ΄μλ μμλ κ·Έ λλ¬΄μ λμ΄
vector<int> dead[200]; //μ£½μ΄μλ λλ¬΄ λ°°μ΄

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
            if(food[x][y] >= alive[i][j]) { // λ¨Ήμ μ μμΌλκΉ μλΆ μ­μ·¨νκ³  λμ΄ μ¦κ°
                food[x][y] -= alive[i][j];
                tmp.push_back(alive[i][j]+1);
            }
            else{ // λ¨Ήμ μ μμΌλκΉ μ΄μμλ λλ¬΄μμ λΉΌκ³  μ£½μ λλ¬΄μ μΆκ°
                dead[i].push_back(alive[i][j]); //μ£½μ λλ¬΄μ μΆκ°
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
            int tree_age = dead[i][j]; //μ£½μ λλ¬΄μ λμ΄ μ°ΎκΈ°
            int x = (i-1)/N +1; //μΈλ±μ€ μ°ΎκΈ° => μλΆ λ°°μ΄μ μΆκ°νκΈ° μν΄
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
            if(alive[i][j]%5 == 0){ //5μ λ°°μμΌ λ λ²μ
                int x = (i-1)/N +1; //μλΆ λ°°μ΄μ μΆκ°νκΈ° μν΄ μΈλ±μ€ μ°ΎκΈ°
                int y = i%N;
                if(y==0) y=N;
                for(int k=0; k<8; k++) { //μνμ’μ° λκ°μ 
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

    // λ§¨ μ²μμ κ° μΉΈμ μλΆμ μμ 5λ‘ μ΄κΈ°ν
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            food[i][j] = 5;
        }
    }
    //cout<<food[1][1]<<"\n";
    cout<<sol()<<"\n";

}