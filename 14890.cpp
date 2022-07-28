//
// Created by ღ 𝚂𝚑𝚒𝚗𝚎 𝚈𝚎𝚘𝚗 ღ on 2022/07/28.
//

#include <iostream>
using namespace std;
int N, L;
int Road[101][101];
int Road2[101][101];

bool canPut(int road[][101], int x, int y) {
    int standard = road[x][y+1];
    for(int i=y+1; i<y+1+L; i++) {
        if(road[x][i]!=standard) return false;
    }
    return true;
}


int sol(int road[][101]) {
    int ans = 0;
    for(int i=0; i<N; i++){
        bool canMake = true;
        int count = 1;
        for(int j=0; j<N-1; j++) {
            if(road[i][j] == road[i][j+1]) {
                count++;
            }
            else if(road[i][j] == road[i][j+1]+1) {
                if(canPut(road, i, j)){ //경사로 놓을 수 있는지 확인
                    j = j+L-1; //L만큼 경사로를 놨으니까 j도 이동해야 함
                    count = 0;
                }
                else{
                    canMake = false;
                    break;
                }
            }
            else if(road[i][j]+1 == road[i][j+1]) {
                if(count >= L) { //경사로 놓을 수 있으면 count 변수 초기화
                    count = 1;
                }
                else{
                    canMake = false;
                    break;
                }
            }
            else if(abs(road[i][j] - road[i][j+1]) >=2) {
                canMake = false;
                break;
            }
        }
        if(canMake) {
            ans++;
        }
    }
    return ans;
}

int main() {
    cin>>N>>L;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            int tmp;
            cin>>tmp;
            Road[i][j] = tmp;
            Road2[j][i] = tmp;
        }
    }
   cout<<sol(Road) + sol(Road2)<<"\n";


}