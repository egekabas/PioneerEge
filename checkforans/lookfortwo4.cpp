#include <bits/stdc++.h>
#include "utilities.h"
#define all(x) (x).begin(), (x).end()
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
using namespace std;
using namespace z3;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ull, ull> pull;
typedef pair<int, int> pii;
typedef pair<ld, ld> pld;
vector<pii> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};


int main() { 

    vector<vector<pii>> vec = {{{0, 0}}};
    int maxsz;
    cin >> maxsz;
    ofstream file("2-" + to_string(maxsz) + "nosol.txt", ofstream::out);

    vector<vector<pii>> fin;
    for(int i = 1; i <= maxsz; ++i){
        vector<vector<pii>> nw;
        for(auto &u : vec)
            normalize(u);
        std::sort(all(vec));
        vec.resize(unique(all(vec))-vec.begin());
        for(auto u : vec){
            if(u.size() != i) continue;
            if(u.size() <= maxsz && u.size() > 3)
                fin.pb(u);
            for(auto el : u)
                for(auto curdir : dir){
                    pii newel = el;
                    newel.ff += curdir.ff;
                    newel.ss += curdir.ss;
                    
                    vector<pii> nvec = u;
                    nvec.pb(newel);
                    nw.pb(nvec);
                }
        }
        vec = nw;
    }
    fin.pb({{0, 0}, {0, 1}, {0, 2}});
    fin.pb({{0, 0}, {1, 0}, {2, 0}});
    
    vector<vector<vector<pii>>> allstate;
    map<vector<vector<pii>>, int> mpp;
    for(int i = 0; i < fin.size(); ++i)
        for(int j = i+1; j < fin.size(); ++j){
            vector<vector<pii>> cur = {fin[i], fin[j]};
            normalize(cur);
            if(mpp[cur]) continue;
            transform(cur, &rotate);
            if(mpp[cur]) continue;
            transform(cur, &rotate);
            if(mpp[cur]) continue;
            transform(cur, &rotate);
            if(mpp[cur]) continue;
            transform(cur, &rotate);
            
            transform(cur, &syx);
            if(mpp[cur]) continue;
            transform(cur, &rotate);
            if(mpp[cur]) continue;
            transform(cur, &rotate);
            if(mpp[cur]) continue;
            transform(cur, &rotate);
            if(mpp[cur]) continue;
            transform(cur, &rotate);
            transform(cur, &syx);
            
            transform(cur, &syy);
            if(mpp[cur]) continue;
            transform(cur, &rotate);
            if(mpp[cur]) continue;
            transform(cur, &rotate);
            if(mpp[cur]) continue;
            transform(cur, &rotate);
            if(mpp[cur]) continue;
            transform(cur, &rotate);
            transform(cur, &syy);
            
            mpp[cur] = 1;
            allstate.pb(cur);     
        }
    file << allstate.size() << ' ';    

    int totcnt = 0, answercnt = 0;
    vector<vector<vector<pii>>> sol;
    for(auto cur : allstate){
            cout << totcnt << ' ' << answercnt << '\n';
            ++totcnt;
            vector<vector<char>> ans = checkdefence(cur);
            
            if(ans.empty()){
                sol.pb(cur);
                continue;
            }
            answercnt++;
            //return 0;
        }
    cout << totcnt << ' ' << answercnt << '\n';

    //sol = { {{{0, 0}, {1, 0}}} , {{{0, 0}, {0, 1}}} };
    file << sol.size() << '\n';
    for(auto &cur : sol){
        for(auto u : cur)
            print(u, file);
        file << "--------------------------------\n";
        
    }
    
}