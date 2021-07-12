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
    ofstream sol("coolpatterns.txt", ofstream::out);
    srand(4);

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
    random_shuffle(all(fin));

    vector<int> cur(fin.size());
    cur[0] = cur[1] = cur[2] = cur[3] = 1;
    std::sort(all(cur));

    int cnt = 0;
    int tot = 0;
    while(1){
        ++cnt;
        cout << cnt << endl;

        vector<vector<pii>> myshape;
        for(int i = 0; i < fin.size(); ++i)
            if(cur[i])
                myshape.pb(fin[i]);
        
        vector<vector<char>> ans = checkdefence(myshape);
        if(ans.size() > 6 || (ans.size() && ans[0].size() > 6)){
            tot++;
            for(auto u : myshape)
                print(u, sol);
            for(auto u : ans){
                for(auto v : u)
                    sol << v;
                sol << endl;
            }
            sol << endl << "----------------------------------\n" << endl;
            return 0;
        }
        if(next_permutation(all(cur)) == 0)
            return 0;
    }
}