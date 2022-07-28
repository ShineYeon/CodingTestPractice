//
// Created by ღ 𝚂𝚑𝚒𝚗𝚎 𝚈𝚎𝚘𝚗 ღ on 2022/07/22.
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int n, m;
int a[9][9]; //입력받는 배열
int tmp[9][9]; //계산하는 배열
int dx[4] ={0, 0, 1, -1};
int dy[4]={1, -1, 0, 0};
bool visited[9*9];
int ans=0;
vector<pair<int, int>> space;

void copy(int tmp[9][9], int a[9][9]){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            tmp[i][j] = a[i][j];
        }
    }
}

void bfs() {
    queue<pair<int, int>> q;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(tmp[i][j] == 2)
                q.push({i, j});
        }
    }

    while(!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for(int k=0; k<4; k++){
            int nx = x+dx[k];
            int ny=y+dy[k];
            if(nx<0||nx>=n||ny<0||ny>=m) continue;
            if(tmp[nx][ny] == 0){
                tmp[nx][ny]=2;
                q.push({nx, ny});
            }
        }
    }
    int cnt =0;
    for(int i=0; i<n; i++){
        for(int j=0;j<m; j++){
            if(tmp[i][j]==0)
                cnt++;
        }
    }
    if(ans<cnt) ans=cnt;
}

void wall(int cur, int idx) {
    if(cur==3) {
        copy(tmp, a);
        //int cnt = 0;
        for(int i=0; i<space.size(); i++){
            //if(cnt==3) break;
            if(visited[i]){
                int x=space[i].first;
                int y=space[i].second;
                tmp[x][y] = 1;
                //cnt++;
            }
        }
        bfs();
        return;
    }
    for(int i=idx; i<space.size(); i++){
        if(visited[i]) continue;
        visited[i] = true;
        wall(cur+1, i+1);
        visited[i] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin>>a[i][j];
            if(a[i][j]==0){
                space.push_back({i, j});
            }
        }
    }
    wall(0, 0);
    cout<<ans<<"\n";


}