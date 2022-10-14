//
// Created by ღ 𝚂𝚑𝚒𝚗𝚎 𝚈𝚎𝚘𝚗 ღ on 2022/10/14.
//

#include <iostream>
#include <algorithm>
using namespace std;

int N, M, H; //세로선개수, 가로선개수, 각 세로선마다 놓을 수 있는 가로선의 개수
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

void selectLine(int idx, int cnt ) { //현재 고른 가로 (idx), 지금까지 놓은 사다리 (cnt)
    if(cnt > 3) return;
    if(doLadder() ) { //사다리 놓기 성공했을 경우
        answer = min(answer, cnt); //최소 cnt값 갱신해야 함
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
        visited[a][b] = true; //a번째 라인에 세로선 b, b+1을 연결하는 선이 존재한다.
    }
    selectLine(1, 0);
    if(answer>3) answer = -1;
    cout<<answer<<"\n";

}