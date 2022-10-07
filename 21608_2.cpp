//
// Created by ღ 𝚂𝚑𝚒𝚗𝚎 𝚈𝚎𝚘𝚗 ღ on 2022/10/07.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int N;
int classroom[404][404];
vector<int> likes[404];
vector<int> order;
int score[5] = {0, 1, 10, 100, 1000};

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

bool cmp (pair<int, int> a, pair<int, int> b) {
    if(a.first==b.first)
        return a.second<b.second;
    else
        return a.first<b.first;
}

vector<pair<int, int>> first(int n) {
    int maxlike = -98765432;
    vector<pair<int, int>> ret;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            int cnt = -1;
            if(classroom[i][j] !=0 ) continue;
            for(int k=0; k<4; k++) {
                int nx = i+dx[k];
                int ny = j+dy[k];
                if(nx<0 || nx>=N || ny<0 || ny>=N ) continue;
                for(auto like : likes[n]) {
                    if(like == classroom[nx][ny])
                        cnt++;
                }
            }
            if(maxlike < cnt){
                maxlike = cnt;
                ret.clear();
                ret.push_back(make_pair(i, j));
            }
            else if(maxlike == cnt) {
                ret.push_back(make_pair(i, j));
            }
        }
    }
    return ret;
}

vector<pair<int, int>> second(vector<pair<int, int>> first) {
    int maxzero = -98765432;
    vector<pair<int, int>> ret;

    for(int i=0; i<first.size(); i++){
        int x = first[i].first;
        int y = first[i].second;
        int cnt = 0;
        for(int k=0; k<4; k++) {
            int nx = x+dx[k];
            int ny = y+dy[k];
            if(nx<0 || nx>=N || ny<0 || ny>=N ) continue;
            if(classroom[nx][ny] == 0)
                cnt++;
        }
        if(maxzero < cnt){
            maxzero = cnt;
            ret.clear();
            ret.push_back(make_pair(x, y));
        }
        else if(maxzero == cnt) {
            ret.push_back(make_pair(x, y));
        }
    }

    return ret;
}

int scoring() {
    int ret = 0;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            int student = classroom[i][j]; //likes 배열에 접근 하기 위해 해당 칸에 있는 학생 번호 저장
            int cnt = 0;
            for(int k=0; k<4; k++) {
                int nx = i+dx[k];
                int ny = j+dy[k];
                if(nx<0 || nx>=N || ny<0 || ny>=N ) continue;
                else{
                    for(auto like : likes[student]) {
                        if(like == classroom[nx][ny])
                            cnt++;
                    }
                }
            }
            ret += score[cnt];
        }
    }
    return ret;
}

void sol () {
    for(int i=0; i<pow(N, 2); i++) {
        vector<pair<int, int>> first_ret = first(order[i]);

        if(first_ret.size() > 1) { // 자리가 여려개 있는 경우
            vector<pair<int, int>> second_ret = second(first_ret);
            if(second_ret.size() > 1 ){
                sort(second_ret.begin(), second_ret.end(), cmp);
                int x = second_ret[0].first;
                int y = second_ret[0].second;
                classroom[x][y] = order[i];
                continue;
            }
            else if (second_ret.size() == 1){
                int x = second_ret[0].first;
                int y = second_ret[0].second;
                classroom[x][y] = order[i];
                continue;
            }

        }
        else if (first_ret.size() == 1){ //한 자리 밖에 없는 경우
            int x = first_ret[0].first;
            int y = first_ret[0].second;
            classroom[x][y] = order[i];
            continue;
        }
    }


}



int main (){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin>>N;
    for(int i=0; i<pow(N, 2); i++){
            int student, a, b, c, d;
            cin>>student>>a>>b>>c>>d;
            likes[student].push_back(a);
            likes[student].push_back(b);
            likes[student].push_back(c);
            likes[student].push_back(d);
            order.push_back(student);

    }


    sol();
    cout<<scoring() <<"\n";



}