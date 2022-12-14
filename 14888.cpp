//
// Created by áĶ ððððð ðððð áĶ on 2022/07/19.
//

#include <iostream>
#include <vector>
using namespace std;
int N;
int arr[12];
int op[4];
long long maxNum = -1000000001, minNum = 1000000001;


void sol(int nowNum, int nowIdx) {
    if(nowIdx == N) {
        if(nowNum>maxNum) maxNum=nowNum;
        if(nowNum<minNum) minNum=nowNum;
        return;
    }
    for(int i=0; i<4; i++) {
        if(op[i] >=1 ){
            op[i]--;
           if(i==0) {
               sol(nowNum + arr[nowIdx], nowIdx+1);
           }
           else if(i==1) {
               sol(nowNum - arr[nowIdx], nowIdx+1);
           }
           else if(i==2) {
               sol(nowNum * arr[nowIdx], nowIdx+1);
           }
           else if(i==3){
               sol(nowNum / arr[nowIdx], nowIdx+1);
           }
            op[i]++;
        }

    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin>>N;
    //Nę° ė ėë Ĩë°ė
    for(int i=0; i<N; i++){
        cin>>arr[i];
    }
    //4ę° ė°ė°ė ėë Ĩë°ė
    for(int i=0; i<4; i++) {
        cin>>op[i];
    }
    vector<int> ops;
    sol(arr[0], 1);

    cout<<maxNum <<" "<< minNum<<'\n';


}