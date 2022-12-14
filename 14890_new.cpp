//
// Created by α¦ πππππ ππππ α¦ on 2022/07/28.
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
            else if(road[i][j] == road[i][j+1] +1) { //μμκΊΌκ° 1 λ λμ λ
                if(canPut(road, i, j)) { //λ€μλ€κ° κ²½μ¬λ‘λ₯Ό λμ μ μλμ§ νμΈ,
                    j = j+L-1; //λμ μ μμΌλ©΄ jλ₯Ό μ΄λμμΌμΌ ν¨
                    count = 0; //κ²½μ¬λ‘λ₯Ό μ΄λ―Έ λ¨μΌλκΉ 0μ λ§λ€μ΄ μ€μΌ ν¨. (κΈΈμ΄ Lλ§νΌλ§ κ²½μ¬λ‘ λκΈ°)
                }
                else{
                    canMake = false; //λμ μ μμΌλ©΄ canMakeλ³μλ₯Ό falseλ‘ λ§λ€μ΄μ£Όκ³  νμΆ
                    break;
                }
            }
            else if(road[i][j]+1 == road[i][j+1]) { //λ€μκΊΌκ° 1 λ λμ λ
                if(count >= L) { //κ²½μ¬λ‘ λμ μ μλ κ²½μ°
                    count = 1; //μ΄κ±΄ μ΄μ΄μ μ§ννλ κ±°λκΉ 1λ‘ λ§λ¦ (μ΅μ΄μ 1μμ μμν κ²μ²λΌ -μλλ©΄ μΈλ±μ€κ° 0->1μ΄ νλμ)
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