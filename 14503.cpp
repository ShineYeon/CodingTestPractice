#include <iostream>
using namespace std;
int N, M, r, c, d;
int room[51][51];
bool isCleaned[51][51];

int forwardDx[4] = {-1, 0, 1, 0};
int forwardDy[4] = {0, 1, 0, -1};
int backwardDx[4] = {1, 0, -1, 0};
int backwardDy[4] = {0, -1, 0, 1};
int directions[4] = {3, 0, 1, 2};

int ans = 0;

void sol(int x, int y, int dir) {
    int tmp = dir;
    for(int i=0; i<4; i++){
        tmp = directions[tmp];
        int nx = x+forwardDx[tmp];
        int ny = y+forwardDy[tmp];
        if(nx<0 || nx>=N || ny<0 || ny>=M || room[nx][ny] == 1)
            continue;

        if(!isCleaned[nx][ny] && room[nx][ny]==0) {
            isCleaned[nx][ny]=true;
            ans++;
            sol(nx, ny, tmp);
        }

    }

    int nx = x+backwardDx[dir];
    int ny = y+backwardDy[dir];
    if(nx>=0 && nx<N && ny>=0 && ny<M ) {
        if(room[nx][ny] == 0 )
            sol(nx, ny, dir);
        else{
            cout<<ans<<"\n";
            exit(0);
        }
    }

}

int main() {
    cin>>N>>M>>r>>c>>d;
    for(int i =0; i<N; i++){
        for(int j=0; j<M; j++){
            cin>>room[i][j];
        }
    }

    isCleaned[r][c] = 1;
    ans++;
    sol(r, c, d);
   cout<<ans<<"\n";

}