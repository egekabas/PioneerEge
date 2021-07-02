#include <bits/stdc++.h>
#include"z3++.h"
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
int totcnt;
void print(vector<pii> &vec, ofstream &file){
    totcnt++;
    int n = 0, m = 0;
    for(auto u : vec){
        n = max(n, u.ff);
        m = max(m, u.ss);
    }
    int cur = 0;
    for(int i = 0; i <= n; ++i){
        for(int j = 0; j <= m; ++j){
            if(cur != vec.size() && vec[cur] == pii(i, j)){
                file << '*';
                ++cur;
            }
            else
                file << '.';
        }
        file << '\n';
    }
    file << '\n';
}
vector<pii> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int main() {

    //ofstream nosol("nosolution.txt", ofstream::out);
    ofstream sol("shapessolution.txt", ofstream::out);
    
    vector<vector<pii>> vec = {{{0, 0}}};
    int maxsz;
    cin >> maxsz;
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
    for(int cnt = 0; cnt < 1; ++cnt){
        cout << cnt << endl << '\n';
        int bit = (1<<16);
        cout << bit << endl;
        vector<vector<pii>> cur;    
        for(int i = 0; i < fin.size(); ++i)
            if(bit&(1<<i))
                cur.pb(fin[i]);
        
        vector<vector<char>> ans = checkdefence(cur);
        if(ans.size()){
            for(auto u : cur)
                print(u, sol);
            for(auto u : ans){
                for(auto v : u)
                    sol << v;
                sol << '\n';
            }
            sol << "\n\n\n------------------------------------\n\n\n" << endl;
        }

    }
}