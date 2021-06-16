#include <bits/stdc++.h>
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
void normalize(vector<pii> &vec){
    int minx = 1e9, miny = 1e9;
    for(auto u : vec){
        minx = min(minx, u.ff);
        miny = min(miny, u.ss);
    }
    for(auto &u : vec){
        u.ff -= minx;
        u.ss -= miny;
    }
    sort(all(vec));
    vec.resize(unique(all(vec))-vec.begin());
}
int totcnt;
void print(vector<pii> &vec){
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
                cout << '*';
                ++cur;
            }
            else
                cout << '.';
        }
        cout << '\n';
    }
    cout << '\n';
}
vector<pii> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    //freopen("in.txt", "r", stdin);
    freopen("shapes.txt", "w", stdout);

    vector<vector<pii>> vec = {{{0, 0}}};
    int maxsz;
    cin >> maxsz;
    for(int i = 1; i <= maxsz; ++i){
        vector<vector<pii>> nw;
        for(auto &u : vec)
            normalize(u);
        sort(all(vec));
        vec.resize(unique(all(vec))-vec.begin());
        for(auto u : vec){
            if(u.size() != i) continue;
            print(u);
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
    cout << "Total number of unique shapes of size less or equal to " << maxsz << ": " << totcnt << '\n';
}