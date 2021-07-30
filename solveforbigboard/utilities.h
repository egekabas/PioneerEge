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
    std::sort(all(vec));
    vec.resize(unique(all(vec))-vec.begin());
}
void normalize(vector<vector<pii>> &vec){
    for(auto u : vec)
        normalize(u);
    std::sort(all(vec));
    vec.resize(unique(all(vec))-vec.begin());
}
pii rotate(pii x){
    return {x.ss, -x.ff};
}
void transform(vector<pii> &cur, pii (*func)(pii)){
    for(auto &u : cur)
        u = func(u);
    normalize(cur);
}
void transform(vector<vector<pii>> &cur, pii (*func)(pii)){
    for(auto &u : cur)
        transform(u, func);
    normalize(cur);
}
void transformboard(vector<vector<int>> &board, char type){
    static int boardtmp[20][20];
    for(int i = 0; i < board.size(); ++i)
        for(int j = 0; j < board[0].size(); ++j){
            int x, y;
            //rotate
            if(type == 'r'){
                x = j;
                y = (board[0].size()-1-i);
            }
            //reflect
            else{
                x = board.size()-1-i;
                y = j;
            }
            boardtmp[x][y] = board[i][j];
        }
    for(int i = 0; i < board.size(); ++i)
        for(int j = 0; j < board[0].size(); ++j)
            board[i][j] = boardtmp[i][j];
}
pii syy(pii x){
    return {-x.ff, x.ss};
}
void print(vector<pii> &vec, ostream &file){
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