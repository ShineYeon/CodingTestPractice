//
// Created by α¦ πππππ ππππ α¦ on 2022/10/14.
//

#include <iostream>
#include <algorithm>
using namespace std;

int N, M, H; //μΈλ‘μ κ°μ, κ°λ‘μ κ°μ, κ° μΈλ‘μ λ§λ€ λμ μ μλ κ°λ‘μ μ κ°μ
bool visited[400][20];
int answer = 98765432;

bool doLadder() {
    for(int i=1; i<=N; i++) {
        int curNum = i;
        for(int j=1; j<=H; j++) {
            if(visited[j][curNum]) curNum += 1;
            else if(visited[j][curNum-1]) curNum-=1;
        }
        if(curNum!=i) return false;
    }
    return true;
}

void selectLine(int idx, int cnt ) { //νμ¬ κ³ λ₯Έ κ°λ‘ (idx), μ§κΈκΉμ§ λμ μ¬λ€λ¦¬ (cnt)
    if(cnt > 3) return;
    if(doLadder() ) { //μ¬λ€λ¦¬ λκΈ° μ±κ³΅νμ κ²½μ°
        answer = min(answer, cnt); //μ΅μ cntκ° κ°±μ ν΄μΌ ν¨
        return;
    }

    for(int i=idx; i<=H; i++) {
        for(int j=1; j<N; j++) {
            if(visited[i][j] == true) continue;
            if(visited[i][j-1] == true) continue;
            if(visited[i][j+1] == true) continue;

            visited[i][j] = true;
            selectLine(i, cnt+1);
            visited[i][j] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin>>N>>M>>H;
    for(int i=0; i<M; i++) {
        int a, b;
        cin>>a>>b;
        visited[a][b] = true; //aλ²μ§Έ λΌμΈμ μΈλ‘μ  b, b+1μ μ°κ²°νλ μ μ΄ μ‘΄μ¬νλ€.
    }
    selectLine(1, 0);
    if(answer>3) answer = -1;
    cout<<answer<<"\n";

}