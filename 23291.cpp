//
// Created by ღ 𝚂𝚑𝚒𝚗𝚎 𝚈𝚎𝚘𝚗 ღ on 2022/10/06.
//

#include <iostream>
#include <queue>
using namespace std;

deque<int> map[101];
int N, K; //N:어항 수

int dx[2] = {-1, 0};
int dy[2] = { 0, 1};

// 최소인 어항에 1마리씩 추가하는 함수
void addFish() {
    int min = 987654321;
    vector<int> idx;
    for(int i=0; i<map[0].size(); i++){
        if(map[0][i] < min){
            min = map[0][i];
            idx.clear();
            idx.push_back(i);
        }
        else if(map[0][i]==min){
            idx.push_back(i);
        }
    }
    for(int i=0; i<idx.size(); i++) {
        map[0][idx[i]]++;
    }
}

//첫번째 회전
int firstRotate() {
    int w=1, h=1;
    int nowFloor = w;

    while(map[0].size()-w >= h) {

        nowFloor=w;

        for(int i=0; i<w; i++, nowFloor--) {
            int idx = 0;
            for(int j=0; j<h; j++) {
                map[nowFloor].push_back(map[j][i]);
            }
        }
        for(int i=0; i<h; i++){
            for(int j=0; j<w; j++){
                map[i].pop_front();
            }
        }
        if(w==h) h++;
        else w++;
    }


    return h;
}

// 물고기 수 조절
void adjustFish(int h) {
    deque<int> tmp[101];
    for(int i=0; i<h; i++){
        tmp[i] = map[i];
    }

    for(int i=h-1; i>=0; i--) {
        for(int j=0; j<tmp[i].size(); j++) {
            for(int k=0; k<2; k++){
                int newX = i+dx[k];
                int newY = j+dy[k];
                if(newX>=0 && newY<map[i].size()) {
                    int diff = abs(map[i][j] - map[newX][newY]) / 5;
                    if (diff > 0) {
                        if (map[i][j] > map[newX][newY]) {
                            tmp[i][j] -= diff;
                            tmp[newX][newY] += diff;
                        } else {
                            tmp[i][j] += diff;
                            tmp[newX][newY] -= diff;
                        }
                    }
                }
            }
        }
    }
    for(int i=0; i<h; i++) {
        map[i] = tmp[i];
    }
}

//바닥에 내려 놓기
void toFloor(int h) {
    int w = map[h-1].size();
    int forLast = map[0].size();

    for(int i=0; i<w; i++) {
        for(int j=0; j<h; j++) {
            map[0].push_back(map[j][i]);
        }
    }

    for(int i=1; i<h; i++){
        map[i].clear();
    }

    for(int i=w; i<forLast; i++){
        map[0].push_back(map[0][i]);
    }
    for(int i=0; i<forLast; i++) {
        map[0].pop_front();
    }

}

// 두번째 회전
void secondRotate() {
    int sz = map[0].size();
    // 1차 쌓음
    for(int i=0; i<sz/2; i++) {
        map[1].push_front(map[0][i]);
    }
    for(int i=0; i<sz/2; i++){
        map[0].pop_front();
    }

    for(int i=0; i<sz/4; i++) {
        map[2].push_front(map[1][i]);
        map[3].push_front(map[0][i]);
    }
    for(int i=0; i<sz/4; i++){
        map[0].pop_front();
        map[1].pop_front();
    }

}

bool check() {
    int maxFish = -98765432, minFish=98765432;
    for(int i=0; i<map[0].size(); i++) {
        maxFish = max(maxFish, map[0][i]);
        minFish = min(minFish, map[0][i]);
    }

    return maxFish-minFish <= K ? true : false;
}

// 한 번의 어항 정리
int sol () {
    int cnt = 0;
    while(1) {
        if(check() == true){
            return cnt;
        }
        addFish();
        int height = firstRotate();
        adjustFish(height);
        toFloor(height);
        secondRotate();
        adjustFish(4);
        toFloor(4);

        cnt+=1;
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin>>N>>K;
    int tmp;
    for(int i=0; i<N; i++){
        cin>>tmp;
        map[0].push_back(tmp);
    }

    int ans = sol();
    cout<<ans<<"\n";

}