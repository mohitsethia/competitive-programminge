#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
#define int long long
const int N = 1e5 + 1;
const int BLK = 700;
struct query{
    int l, r, i, k;
};
query Q[N];
vector<int> ar[N];
int S[N], T[N], FT[2*N], FF[N], nodeF[N], col[N], eleF[N], bucket[N];
int ans[N];
int n;
int timer = 1;
int getBlock(int idx){
    return (idx+BLK-1)/BLK;
}
bool comp(query a, query b){
    int x = a.l/BLK;
    int y = b.l/BLK;
    if(x != y){
        return x < y;
    }
    if(x%2){
        return a.r < b.r;
    }
    else{
        return a.r > b.r;
    }
}
void add(int idx){
    int node = FT[idx];
    int c = col[node];
    nodeF[node]++;
    if(nodeF[node] == 2){
        eleF[c]++;
        FF[eleF[c]]++;
        bucket[getBlock(eleF[c])]++;
        FF[eleF[c]-1]--;
        bucket[getBlock(eleF[c]-1)]--;
    }
}
void remove(int idx){
    int node = FT[idx];
    int c = col[node];
    nodeF[node]--;
    if(nodeF[node] == 1){
        eleF[c]--;
        FF[eleF[c]]++;
        bucket[getBlock(eleF[c])]++;
        FF[eleF[c]+1]--;
        bucket[getBlock(eleF[c]+1)]--;
    }
}
int getAns(int k, int n){
    int res = 0;
    int LB = getBlock(k);
    int RB = getBlock(n);
    if(LB == RB){
        for(int i = k; i <= n; i++){
            res += FF[i];
        }
    }
    else{
        for(int i = k; i <= LB*BLK; i++){
            res += FF[i];
        }
        for(int i = LB+1; i < RB; i++){
            res += bucket[i];
        }
        for(int i = RB*BLK + 1; i <= n; i++){
            res += FF[i];
        }
    }
    return res;
}

void dfs(int node, int par){
    S[node] = timer;
    FT[timer] = node;
    timer++;
    for(int &child: ar[node]){
        if(child != par) 
            dfs(child, node);
    }
    T[node] = timer;
    FT[timer] = node;
    timer++;
}
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int q, a, b, k;
    cin >> n >> q;
    for(int i = 1; i <= n; i++){
        cin >> col[i];
    }
    for(int i = 1; i < n; i++){
        cin >> a >> b;
        ar[a].emplace_back(b);
        ar[b].emplace_back(a);
    }
    dfs(1, -1);
    for(int i = 1; i <= q; i++){
        cin >> a >> k;
        Q[i].l = S[a];
        Q[i].r = T[a];
        Q[i].k = k;
        Q[i].i = i;
    }
    sort(Q+1, Q+q+1, comp);
    int ML = 1, MR = 0;
    for(int i = 1; i <= q; i++){
        int L = Q[i].l;
        int R = Q[i].r;
        int idx = Q[i].i;
        k = Q[i].k;
        while(MR < R)
            MR++, add(MR);
        while(ML > L)
            ML--, add(ML);
        while(MR > R)
            remove(MR), MR--;
        while(ML < L)
            remove(ML), ML++;
        ans[idx] = getAns(k, n);
    }
    for(int i = 1; i <= q; i++){
        cout << ans[i] << "\n";
    }
    return 0;
}