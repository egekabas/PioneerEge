#include <bits/stdc++.h>
#include "utilities.h"
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
vector<vector<vector<int>>> sols;

//set the board size, starting depth and symmetry here
const int n = 8, m = 8;
const int symmetric = 1;
int maxdepth = 6;

int tot = 0;
int calc(vector<vector<int>> board, int turn, int depth){
    int &dpval = res[board];
    
    //stop if previously visited or deeper than maxdepth
    if(depth >= maxdepth)
        return dpval = 3;
    
    if(dpval) return dpval;
    
    //check all the roations and reflections to see if weve been here before
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

    //if we didnt apply our checking algorithms, we do it here
    static int newsol = 0, oldsol = 0;
    if(calcvis[board] == 0){
        ++tot;
        if(tot%100 == 0)
            cout << maxdepth << ' ' << tot << ' ' << newsol << ' ' << oldsol << endl;
        calcvis[board] = 1;
        int val = becksolution(board, shapes, turn);
        if(val)
            return dpval = val;
        for(auto &u : sols)
            if(checksol(turn, board, u, shapes)){
                ++oldsol;
                return dpval = 2;
            }
        if(turn == 2){
            vector<vector<int>> cursol;
            val = pairingsolution(board, shapes, 2, cursol);
            if(val){
                ++newsol;
                sols.pb(cursol);
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

    //coordinates sorted by beck value
    vector<pii> coordinates_sorted = orderusingbeck(board, shapes);
    for(auto u : coordinates_sorted){
        
        int i = u.ff, j = u.ss;
        movecnt = 1;
        board[i][j] = turn;
        int res = calc(board, nxtturn, depth+1);
        //if the player can force a win, no need to calculate further
        if(res == turn)
            return dpval = turn;
        else if(res == 3)
            ambiguous = 1;
        board[i][j] = 0;
        movecnt = 1;
    }
    if(movecnt == 0) return dpval = 2;
    //if the player cant force a win and if some states are ambigious than the current state is
    //ambigious as well
    if(ambiguous)
        return dpval = 3;
    return dpval = nxtturn;    
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);

    //change this part to create the desired set of shapes
    vector<pii> shapy = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 3}, {1, 4}};
    normalize(shapy);

    for(int i = 0; i < 4; ++i){
        shapes.pb(shapy);
        transform(shapy, rotate);
    }
    transform(shapy, syy);
    for(int i = 0; i < 4; ++i){
        shapes.pb(shapy);
        transform(shapy, rotate);
    }
    normalize(shapes);

    


    int val;
    while(1){
        //we only check states that were previously marked as ambigious or werent reached at all
        for(auto &u : res)
            if(u.ss == 3)
                u.ss = 0;
        //increasing the maximum search depth
        maxdepth += 2;
        val = calc(vector<vector<int>>(n, vector<int>(m)), 1, 0);
        //break only after finding a definite result
        if(val != 3)
            break;
    }
    cout << val << '\n';
    cout<< "Calcuated in " << fixed << setprecision(3) << (ld)clock() / CLOCKS_PER_SEC<< " seconds\n";
    cout << tot << " total positions analyzed\n";
}