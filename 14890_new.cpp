//
// Created by ღ 𝚂𝚑𝚒𝚗𝚎 𝚈𝚎𝚘𝚗 ღ on 2022/07/28.
//

#include <iostream>
using namespace std;
int N, L;
int map1[101][101];
int map2[101][101];

bool canPut(int road[][101], int x, int y) {
    int standard = road[x][y+1];
    for(int i=y+1; i<y+1+L; i++){
        if(standard != road[x][i])
            return false;
    }
    return true;
}

int sol(int road[][101]) {
    int ans = 0;
    for(int i=0; i<N; i++){
        int count = 1;
        bool canMake = true;
        for(int j=0; j<N-1; j++){
            if(road[i][j] == road[i][j+1]) {
                count++;
            }
            else if(road[i][j] == road[i][j+1] +1) { //앞에꺼가 1 더 높을 때
                if(canPut(road, i, j)) { //뒤에다가 경사로를 놓을 수 있는지 확인,
                    j = j+L-1; //놓을 수 있으면 j를 이동시켜야 함
                    count = 0; //경사로를 이미 놨으니까 0을 만들어 줘야 함. (길이 L만큼만 경사로 놓기)
                }
                else{
                    canMake = false; //놓을 수 없으면 canMake변수를 false로 만들어주고 탈출
                    break;
                }
            }
            else if(road[i][j]+1 == road[i][j+1]) { //뒤에꺼가 1 더 높을 때
                if(count >= L) { //경사로 놓을 수 있는 경우
                    count = 1; //이건 이어서 진행하는 거니까 1로 만듦 (최초에 1에서 시작한 것처럼 -왜냐면 인덱스가 0->1이 하나임)
                }
                else{
                    canMake = false;
                    break;
                }
            }
            else if(abs(road[i][j] - road[i][j+1]) >= 2) {
                canMake = false;
                break;
            }
        }
        if(canMake)
            ans++;
    }
    return ans;
}

int main() {
    cin>>N>>L;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) {
            int tmp;
            cin>>tmp;
            map1[i][j] = tmp;
            map2[j][i] = tmp;
        }
    }
    cout<<sol(map1) + sol(map2) <<"\n";

}