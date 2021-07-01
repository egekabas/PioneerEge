#include <bits/stdc++.h>
#include "utilities.h"
#define all(x) (x).begin(), (x).end()
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ull, ull> pull;
typedef pair<int, int> pii;
typedef pair<ld, ld> pld;
int main() {
    ofstream sol("shapesol.txt", ofstream::out);
    ofstream nosol("shapenosol.txt", ofstream::out);
    

    vector<pii> shapy = {{1, 0}, {1, 1}, {1, 2}, {1, 3}, {0, 3}, {0, 4}};
    normalize(shapy);

    vector<vector<pii>> all;

    all.pb(shapy);
    transform(shapy, rotate);
    all.pb(shapy);
    transform(shapy, rotate);
    all.pb(shapy);
    transform(shapy, rotate);
    all.pb(shapy);
    transform(shapy, rotate);
    
    transform(shapy, syy);
    all.pb(shapy);
    transform(shapy, rotate);
    all.pb(shapy);
    transform(shapy, rotate);
    all.pb(shapy);
    transform(shapy, rotate);
    all.pb(shapy);
    transform(shapy, rotate);
    transform(shapy, syy);

    
    normalize(all);
    vector<vector<vector<pii>>> fin;
    map<vector<vector<pii>>, int> mpp;
    for(int bit = 1; bit < (1<<all.size()); ++bit){
        vector<vector<pii>> cur;
        for(int i = 0; i < all.size(); ++i)
            if(bit&(1<<i))
                cur.pb(all[i]);
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
        fin.pb(cur);
    }
    int idx = 0;
    for(auto cur : fin){
        ++idx;
        cout << fin.size() << ' ' << idx << '\n'; 
        vector<vector<char>> ans = checkdefence(cur);
        if(ans.empty()){
            for(auto u : cur)
                print(u, nosol);
            nosol << "--------------------------\n";
        }
        else{
            for(auto u : cur)
                print(u, sol);
            for(auto u1 : ans){
                for(auto u2 : u1)
                    sol << u2;
                sol << '\n';
            }
            sol << "---------------------------------\n";
        }
    }

}