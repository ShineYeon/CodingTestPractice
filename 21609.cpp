//
// Created by α¦ πππππ ππππ α¦ on 2022/10/08.
//

#include <iostream>
#include <queue>
#include <math.h>
#include <cstring>
using namespace std;

int N, M; //ν λ³μ ν¬κΈ°, μμμ κ°μ
int board[21][21]; //κ²©μ
bool visited[21][21] = {0, };

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
#define DEL -98765432

int rainbowMaxSize = -98765432;
int groupMaxSize = -98765432; // μ΅λ λΈλ‘ κ·Έλ£Ήμ κ³μ°νκΈ° μν maxSize
vector<pair<int, int>> targetGroup; // λΈλ‘λ€μ μ μ₯ν  λ°°μ΄ => grouping μ΄νμλ μ­μ  λμ λΈλ‘κ·Έλ£Ήμ΄ λ΄κ²¨ μμ
pair<int, int> targetStandard; //μ­μ  λμ κΈ°μ€ λΈλ‘
int score = 0; //μ μ

bool canGo(vector<pair<int, int>> tmpGroup, int rainbowSize, int x, int y) {
    //for(auto group:tmpGroup) {
    //    cout<<group.first<<" "<<group.second<<"\n";
    //}
    //cout<<targetGroup.size()<<"\n";
    //cout<<groupMaxSize<<"\n";
    //cout<<tmpGroup.size()<<"\n";
    if(targetGroup.size() < tmpGroup.size()) { //**********************μ΄λΆλΆ!
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
    queue<pair<int, int>> q; // bfs μν¨
    vector<pair<int, int>> tmpGroup; //νμ¬ λΈλ‘λ€
    vector<pair<int, int>> tmpRainbow; //νμ¬ λΈλ‘μμ λ¬΄μ§κ° λΈλ‘λ€

    int color = board[x][y]; //μ§κΈ μκΉ μ μ₯ν΄μΌμ§

    //bfs part
    visited[x][y] = true; // μΌλ¨ trueλ‘ λ§λ€κ³ 
    q.push(make_pair(x, y)); //pushν΄.

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
        targetGroup = tmpGroup; //μ­μ ν  κ·Έλ£Ή κ°±μ 
        targetStandard.first = x; //μ­μ ν  κ·Έλ£Ήμ κΈ°μ€ λΈλ‘ κ°±μ 
        targetStandard.second = y;
        rainbowMaxSize = tmpRainbow.size(); //rainbow size κ°±μ 
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

// μ°Ύμ λΈλ‘ κ·Έλ£Ή μ­μ 
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

// μ€λ ₯ μμ© (λΈλ‘λ€μ μλλ‘ λ΄λ¦¬κΈ°)
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

// 90λ λ°μκ³ λ°©ν₯ νμ 
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