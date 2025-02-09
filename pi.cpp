#include <vector>
#include <iostream>
void pi_iteration(std::vector<long long>& v, std::vector<long long> &ans){
    size_t sz = v.size();
    for(int i  = sz - 1; i >=0 ; i--){
        v[i] *= 10;
    }
    for(int i =  sz- 2; i>=0; i--){
        v[i] += v[i+1]/(2*i+3)*(i+1);
    }
    for(int i =  sz- 1; i>=1; i--){
        v[i] %= 2*i+1;
    }
    ans.push_back(v[0]/10);
    v[0] %= 10;

}

void pi(int n){
    n+=2;
    std::vector<long long>v(n*10/3,2);
    std::vector<long long> ans;
    for(int i = 0; i < n; i++){pi_iteration(v,ans);}
    int to_next = 0;
    for(int i  = ans.size(); i>=0; i--){
        ans[i] += to_next;
        to_next = ans[i] / 10;
        ans[i] %=10;
    }

    std::cout<<ans[0]<<".";
    for(int i = 1; i < n-1;i++){
        std::cout<<ans[i];
    }
}
