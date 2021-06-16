#include <bits/stdc++.h>
#include"z3++.h"
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
int pairingsolution(vector<vector<int>> &board, vector<vector<pii>> &shapes, int turn) {

    //Getting the input
    int n = board.size(), m = board[0].size();
    context c;
    vector<vector<vector<vector<expr>>>> edge;
    for(int i = 0; i < n; ++i){
        edge.pb(vector<vector<vector<expr>>>());
        for(int j = 0; j < m; ++j){
            edge[i].pb(vector<vector<expr>>());
            for(int x = 0; x < n; ++x){
                edge[i][j].pb(vector<expr>());
                for(int y = 0; y < m; ++y)
                    edge[i][j][x].pb(c.bool_const((to_string(i)+"-"+to_string(j)+"-"+to_string(x)+"-"+to_string(y)).c_str()));    
            }
        }
    }
    
    vector<vector<expr>> taken;
    ///////////////////turn2
    for(int i = 0; i < n; ++i){
        taken.pb(vector<expr>());
        for(int j = 0; j < m; ++j)
            taken[i].pb(c.bool_const((to_string(i)+"-"+to_string(j)).c_str()));
    }
    
    solver s(c);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            for(int x = 0; x < n; ++x)
                for(int y = 0; y < m; ++y)
                    s.add(edge[i][j][x][y] == edge[x][y][i][j]);

    ////////////////////turn2
    expr_vector onetaken(c);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            onetaken.pb(taken[i][j]);
    if(onetaken.size())
        s.add(atmost(onetaken, 1));

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j){
            expr_vector onefriend(c);
            for(int x = 0; x < n; ++x)
                for(int y = 0; y < m; ++y)
                    onefriend.pb(edge[i][j][x][y]);
            s.add(atmost(onefriend, 1));
        }

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            for(auto shape : shapes){
                int ok = 1;
                for(auto u : shape){
                    if(i+u.ff >= n || j+u.ss >= m || board[i+u.ff][j+u.ss] == 2)
                        ok = 0;
                }
                if(ok == 0) continue;
                expr_vector vec(c);
                for(int x = 0; x < shape.size(); ++x){
                    pii u1 = {i+shape[x].ff, j+shape[x].ss};
                    if(board[u1.ff][u1.ss] == 0){
                        if(turn == 2){
                            vec.pb(taken[u1.ff][u1.ss]);
                        }
                    }
                    else
                        continue;
                    for(int y = x+1; y < shape.size(); ++y){
                        pii u2 = {i+shape[y].ff, j+shape[y].ss};
                        if(board[u2.ff][u2.ss])
                            continue;
                        vec.pb(edge[u1.ff][u1.ss][u2.ff][u2.ss]);
                    }
                }
                if(vec.size())
                    s.add(atleast(vec, 1));
            }

    if(s.check() == unsat)
        return 0;
    return 2;
    
}