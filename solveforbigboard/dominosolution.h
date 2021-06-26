#include <bits/stdc++.h>
#include "z3++.h"
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
int tilehere[20][20];
//works when its breakers turn
int dominosolution(vector<vector<int>> &board, vector<vector<pii>> &shapes){
    int n = board.size();
    int m = board[0].size();

    context c;
    vector<vector<expr>> up(n);
    vector<vector<expr>> down(n);
    vector<vector<expr>> left(n);
    vector<vector<expr>> right(n);
    vector<vector<expr>> taken(n);
    
    //Initializing the boolean constants
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            up[i].pb(c.bool_const(("u" + to_string(i) + "_" + to_string(j)).c_str()));
            down[i].pb(c.bool_const(("d" + to_string(i) + "_" + to_string(j)).c_str()));
            left[i].pb(c.bool_const(("l" + to_string(i) + "_" + to_string(j)).c_str()));
            right[i].pb(c.bool_const(("r" + to_string(i) + "_" + to_string(j)).c_str()));
            taken[i].pb(c.bool_const(("t" + to_string(i) + "_" + to_string(j)).c_str()));
        }
    }
    

    //A tile at each location can point towards only one direction
    solver s(c);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j){
            expr_vector v(c);
            
            v.push_back(up[i][j]);
            v.push_back(down[i][j]);
            v.push_back(left[i][j]);
            v.push_back(right[i][j]);
            
            s.add(atmost(v, 1));
        }   
    expr_vector onetaken(c);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            onetaken.pb(taken[i][j]);
    s.add(atmost(onetaken, 1));
    
    //Each domino tile is 2 blocks long
    
    //We shoulnt be able to place any of the shapes without at least covering one full
    //domino tile
    for(auto shape : shapes){
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j){
                int ok = 1;
                for(auto u : shape){
                    int x = u.ff+i;
                    int y = u.ss+j;
                    if(x >= n || y >= m){
                        ok = 0;
                        break;
                    }
                    if(board[x][y] == 2){
                        ok = 0;
                        break;
                    }
                }
                if(ok == 0) continue;
                
                expr_vector v(c);
                for(auto u : shape){
                    int x = u.ff+i;
                    int y = u.ss+j;
                    if(board[x][y] == 0){
                        tilehere[x][y] = 1;
                        if(x > 0 && tilehere[x-1][y])
                            v.pb(up[x][y] && down[x-1][y]);
                        if(y > 0 && tilehere[x][y-1])
                            v.pb(left[x][y] && right[x][y-1]);
                        v.pb(taken[x][y]);
                    }
                }
                for(auto u : shape){
                    int x = u.ff+i;
                    int y = u.ss+j;
                    tilehere[x][y] = 0;
                }
                if(v.empty())
                    return 0;
                s.add(atleast(v, 1));
            }
    }
    
    if(s.check() == unsat)
        return 0;
    return 2;
}