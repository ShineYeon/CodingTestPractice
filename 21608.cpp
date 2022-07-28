//
// Created by ღ 𝚂𝚑𝚒𝚗𝚎 𝚈𝚎𝚘𝚗 ღ on 2022/07/22.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N;
int classroom[21][21];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
bool like[401][401];
int stuSeq[401];

bool cmp(pair<pair<int, int>, pair<int, int>>& a, pair<pair<int, int>, pair<int, int>>& b){
    if(a.first.first==b.first.first){
        if(a.first.second==b.first.second){
            if(a.second.first==b.second.first){
                return a.second.second<b.second.second;
            }
            return a.second.first<a.second.first;
        }
        return a.first.second>b.first.second;
    }
    return a.first.first>b.first.first;
}

void sit( int idx) {
    int student = stuSeq[idx];
    vector<pair<pair<int, int>, pair<int, int>>> candidate;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(classroom[i][j]) continue;
            int likeStudent = 0;
            int empty=0;
            for(int k=0; k<4; k++){
                int newX = i+dx[k], newY=j+dy[k];
                if(newX<0 || newX>=N || newY<0 || newY>=N)
                    continue;

                if(like[student][classroom[newX][newY]] != 0)
                    likeStudent++;
                else if(!classroom[newX][newY])
                    empty++;

            }
            candidate.push_back({{likeStudent, empty}, {i, j}});
        }
    }
    sort(candidate.begin(), candidate.end(), cmp);
    int seatR = candidate[0].second.first;
    int seatC = candidate[0].second.second;
    classroom[seatR][seatC] = student;

}

int score() {
    int ans=0;
    int satis[5] = {0, 1, 10, 100, 1000};
    for(int i=0;i<N; i++){
        for(int j=0; j<N; j++){
            int likeCnt = 0;
            int stuNum = classroom[i][j];
            for(int k=0; k<4; k++){ //위아래양옆
                int newX = i+dx[k], newY=j+dy[k];
                if(newX<0 || newX>=N || newY<0 || newY>=N) continue;

                if(like[stuNum][classroom[newX][newY]] != 0)
                    likeCnt++;

            }
           ans += satis[likeCnt];

        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>N;
    for(int i=0; i<N*N; i++){
        int student, a, b, c, d;
        cin>>student>>a>>b>>c>>d;
        stuSeq[i] = student;
        like[student][a] = true;
        like[student][b] = true;
        like[student][c] = true;
        like[student][d] = true;
    }
    for(int i=0; i<N*N; i++){
        sit(i);
    }

    cout<<score()<<"\n";

}