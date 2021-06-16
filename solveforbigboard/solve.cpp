#include <bits/stdc++.h>
#include "utilities.h"
#include "dominosolution.h"
#include "becksolution.h"
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
map<vector<vector<int>>, int> res;
vector<vector<pii>> shapes;
const int n = 6, m = 6;
const int maxdepth = 5;
const int symmetric = 1;

int tot = 0;
int calc(vector<vector<int>> board, int turn, int depth){
    if(depth >= maxdepth)
        return 3;
    int &dpval = res[board];
    if(dpval) return dpval;
    
    if(symmetric){
        for(int i = 0; i < 4; ++i){
            transformboard(board, rotate);
            if(res[board])
                return dpval = res[board];
        }
        transformboard(board, syy);
        for(int i = 0; i < 4; ++i){
            if(res[board])
                return dpval = res[board];
            transformboard(board, rotate);
        }
        transformboard(board, syy);
    }

    ++tot;
    if(tot%10 == 0)
        cout << tot << endl;
    int val = becksolution(board, shapes);
    if(val)
        return dpval = val;
    
    if(turn == 2){
        //++numer;
        //cout << numer << ' ' << depth << endl;
        val = pairingsolution(board, shapes, 2);
        if(val){
            return dpval = val;
        }
    }
     
    int nxtturn;
    if(turn == 1)
        nxtturn = 2;
    else
        nxtturn = 1;
    int movecnt = 0;
    int ambigious = 0;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j){
            if(board[i][j]) continue;
            movecnt = 1;
            board[i][j] = turn;
            int res = calc(board, nxtturn, depth+1);
            if(res == turn)
                return dpval = turn;
            else if(res == 3)
                ambigious = 1;
            board[i][j] = 0;
            movecnt = 1;
        }
    if(movecnt == 0) return dpval = 2;
    if(ambigious)
        return dpval = 3;
    return dpval = nxtturn;    
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);

    /*vector<vector<pii>> tmp = {{{0, 0}, {0, 1}}};
    vector<vector<int>> brd(4, vector<int>(4));
    cout << dominosolution (brd, tmp) << '\n';
    return 0;*/

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

    cout << calc(vector<vector<int>>(n, vector<int>(m)), 1, 0) << '\n';
    cout<< "Calcuated in " << fixed << setprecision(3) << (ld)clock() / CLOCKS_PER_SEC<< " seconds\n";
    cout << tot << " total positions analyzed\n";
}