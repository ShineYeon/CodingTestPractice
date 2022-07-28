//
// Created by ღ 𝚂𝚑𝚒𝚗𝚎 𝚈𝚎𝚘𝚗 ღ on 2022/06/04.
//

#include <iostream>
#include <vector>
using namespace std;
int N;
int arr[1001];
int dp[1001][2];
vector<int> ans;

void sol() {
    dp[0][0] = 1;
    dp[0][1] = -1;
    for(int i=1; i<N; i++){
        if(arr[i]>=arr[i-1]){
            dp[i][0]=dp[i-1][0]+1;
            dp[i][1] = dp[i-1][1];
        }
        else{
            dp[i][0] = dp[i-1][0];
            dp[i][1] = i-1;
        }
    }

    ans.push_back(N-1);
    int now = dp[N-1][1];
    while(now!=-1){
        ans.push_back(now);
    }

}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin>>N;
    for(int i=0; i<N; i++){
        cin>>arr[i];
    }



}