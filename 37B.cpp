#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
int n,Max,reg;
int TIME=0;
vector<int> T,W;
bool used[1010];
int p[1010],dmg[1010];
int main(){
    //system("pause");
    int i,j,k,l,x,y;
    cin>>n>>Max>>reg;
    for(i=0;i<n;++i)cin>>p[i]>>dmg[i];
    int ch=Max,cd=0;
    while(1){
        ch-=cd;
        ch=min(Max,ch+reg);
        if(ch<=0)break;
        j=-1;
        for(i=0;i<n;++i){
            if(used[i] || p[i]*Max<100*ch)continue;
            if(j==-1 || dmg[j]<dmg[i])j=i;
        }
        if(j!=-1 && dmg[j]>=0){
            if(dmg[j]>cd || true){
                T.push_back(TIME);W.push_back(j+1);
                used[j]=true;
                cd+=dmg[j];
            }
        }
        ++TIME;
        if(TIME>=10000)break;
    }
    if(ch>0)cout<<"NO\n";
    else{
        cout<<"YES\n";
        cout<<TIME<<' '<<T.size()<<endl;
        for(i=0;i<T.size();++i)cout<<T[i]<<' '<<W[i]<<endl;
    }
    //system("pause");
    return 0;
}
