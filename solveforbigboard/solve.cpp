#include <bits/stdc++.h>
#include "utilities.h"
#include "dominosolution.h"
#include "becksolution.h"
#include "pairingsolution.h"
#include "orderusingbeckdefense.h"

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
map<vector<vector<int>>, int> calcvis;
vector<vector<pii>> shapes;

const int n = 8, m = 8;
const int symmetric = 1;
int maxdepth = 0;

vector<pii> coordinates_sorted;
int sortbycenter(pii a, pii b){
    return abs(2*a.ff-(n-1))+abs(2*a.ss-(m-1)) < abs(2*b.ff-(n-1))+abs(2*b.ss-(m-1)); 
}
int tot = 0;
int calc(vector<vector<int>> board, int turn, int depth){
    int &dpval = res[board];
    if(depth >= maxdepth)
        return dpval = 3;
    
    if(dpval) return dpval;
    
    if(symmetric){
        for(int i = 0; i < 4; ++i){
            transformboard(board, 'r');
            if(res[board])
                return dpval = res[board];
        }
        transformboard(board, 's');
        for(int i = 0; i < 4; ++i){
            if(res[board])
                return dpval = res[board];
            transformboard(board, 'r');
        }
        transformboard(board, 's');
    }
    if(calcvis[board] == 0){
        ++tot;
        if(tot%10 == 0)
            cout << tot << endl;
        calcvis[board] = 1;
        int val = becksolution(board, shapes, turn);
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
    }
     
    int nxtturn;
    if(turn == 1)
        nxtturn = 2;
    else
        nxtturn = 1;
    int movecnt = 0;
    int ambiguous = 0;
    
    for(auto u : coordinates_sorted){
        int i = u.ff, j = u.ss;
        if(board[i][j]) continue;
        movecnt = 1;
        board[i][j] = turn;
        int res = calc(board, nxtturn, depth+1);
        if(res == turn)
            return dpval = turn;
        else if(res == 3)
            ambiguous = 1;
        board[i][j] = 0;
        movecnt = 1;
    }
    if(movecnt == 0) return dpval = 2;
    if(ambiguous)
        return dpval = 3;
    return dpval = nxtturn;    
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            coordinates_sorted.pb({i, j});
    std::sort(all(coordinates_sorted), sortbycenter);

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

    int val;
    while(1){
        for(auto &u : res)
            if(u.ss == 3)
                u.ss = 0;
        maxdepth += 2;
        val = calc(vector<vector<int>>(n, vector<int>(m)), 1, 0);
        if(val != 3)
            break;
    }
    cout << val << '\n';
    cout<< "Calcuated in " << fixed << setprecision(3) << (ld)clock() / CLOCKS_PER_SEC<< " seconds\n";
    cout << tot << " total positions analyzed\n";
}