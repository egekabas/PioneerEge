#include <bits/stdc++.h>
#include "utilities.h"
#include "pairingsolution.h"
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
const int n = 8, m = 8;
int maxdepth = 3;
int main(){
    vector<vector<pii>> shapes;

    vector<pii> shapy = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 3}, {1, 4}};
    normalize(shapy);

    shapes.pb(shapy);
    transform(shapy, rotate);
    shapes.pb(shapy);
    transform(shapy, rotate);
    shapes.pb(shapy);
    transform(shapy, rotate);
    shapes.pb(shapy);
    transform(shapy, rotate);
    
    transform(shapy, syy);
    shapes.pb(shapy);
    transform(shapy, rotate);
    shapes.pb(shapy);
    transform(shapy, rotate);
    shapes.pb(shapy);
    transform(shapy, rotate);
    shapes.pb(shapy);
    transform(shapy, rotate);
    transform(shapy, syy);
    
    normalize(shapes);

    srand(0);
    for(int curcnt = 0; curcnt < 100; ++curcnt){
        freopen(("data/file" + to_string(curcnt) + ".smt2").c_str(), "w", stdout);
        vector<vector<int>> board(n, vector<int>(m));
        vector<pii> vec;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                vec.pb({i, j});
        random_shuffle(all(vec));
        int curdepth = rand()%maxdepth+1;
        for(int i = 0; i < curdepth; ++i){
            board[vec.back().ff][vec.back().ss] = 1;
            vec.pop_back();
        }
        for(int i = 0; i < curdepth-1; ++i){
            board[vec.back().ff][vec.back().ss] = 2;
            vec.pop_back();
        }
        pairingsolution(board, shapes, 2);
    }
}