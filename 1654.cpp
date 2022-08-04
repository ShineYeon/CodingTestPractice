//
// Created by ღ 𝚂𝚑𝚒𝚗𝚎 𝚈𝚎𝚘𝚗 ღ on 2022/08/04.
//

#include <iostream>
#include <algorithm>
using namespace std;
int K, N;
int lines[10001];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>K>>N;
    for(int i=0; i<K; i++){
        cin>>lines[i];
    }
    sort(lines, lines+K);
    int ans = 0;

    long long pl=1, pr=lines[K-1];
    long long pc;
    while(pl<=pr){
        pc=(pl+pr)/2;
        int cnt = 0;
        for(int i=0; i<K; i++){
            cnt+=(lines[i]/pc);
        }
        if (cnt>=N) {
            pl = pc+1;
            if(ans < pc) ans = pc;
        }
        else {
            pr = pc-1;
        }
    }
    cout<<ans<<"\n";
}