//
// Created by α¦ πππππ ππππ α¦ on 2022/07/28.
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
                if(canPut(road, i, j)){ //κ²½μ¬λ‘ λμ μ μλμ§ νμΈ
                    j = j+L-1; //Lλ§νΌ κ²½μ¬λ‘λ₯Ό λ¨μΌλκΉ jλ μ΄λν΄μΌ ν¨
                    count = 0;
                }
                else{
                    canMake = false;
                    break;
                }
            }
            else if(road[i][j]+1 == road[i][j+1]) {
                if(count >= L) { //κ²½μ¬λ‘ λμ μ μμΌλ©΄ count λ³μ μ΄κΈ°ν
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