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
int pairingsolution(vector<vector<int>> &board, vector<vector<pii>> &shapes, int turn, vector<vector<int>> &solution) {

    //Initializing boolean variables to hold if two cells are in a pair
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
    
    //Initializing boolean variables to hold if player two marks a cell in his current turn
    vector<vector<expr>> taken;
    for(int i = 0; i < n; ++i){
        taken.pb(vector<expr>());
        for(int j = 0; j < m; ++j)
            taken[i].pb(c.bool_const((to_string(i)+"-"+to_string(j)).c_str()));
    }
    
    //If x and y are in a pair, then y and x must be in a pair
    solver s(c);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            for(int x = 0; x < n; ++x)
                for(int y = 0; y < m; ++y)
                    s.add(edge[i][j][x][y] == edge[x][y][i][j]);

    //Player 2 can mark only one cell in one turn
    expr_vector onetaken(c);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            onetaken.pb(taken[i][j]);
    if(onetaken.size())
        s.add(atmost(onetaken, 1));

    //each cell must be in at most one pair
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
                //every cell must either contain a pair or a cell marked by player 2
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

    if(s.check() == sat){
        
        model ml = s.get_model();
        vector<vector<int>> res(n, vector<int>(m));

        int curpair = 1;
        for(int i = 0; i < ml.size(); ++i){
            func_decl v = ml[i];
            assert(v.arity() == 0);
            if(ml.get_const_interp(v).bool_value() == -1)
                continue;
            
            string s = v.name().str();
            vector<int> curvec;
            int last = 0;
            for(int i = 0; i < s.size(); ++i)
                if(s[i] == '-'){
                    curvec.pb(stoi(s.substr(last, i-last)));
                    last = i+1;
                }
            curvec.pb(stoi(s.substr(last, s.size()-last)));
            if(curvec.size() == 2)
                res[curvec[0]][curvec[1]] = -2;
            else{
                if(res[curvec[0]][curvec[1]] != 0)
                    continue;
                
                res[curvec[0]][curvec[1]] = curpair;
                res[curvec[2]][curvec[3]] = curpair;
                
                ++curpair;
            }
        }
        int cnt = 0;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                if(res[i][j] < 0)
                    ++cnt;
            }
        }

        solution = res;

       return 2;
    }
    return 0;   
}

int checksol(int turn, vector<vector<int>> &board, vector<vector<int>> &sol, vector<vector<pii>> &shapes){
    int n = board.size();
    int m = board[0].size();

    int changed = 0;
    if(turn == 2){
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(sol[i][j] == -2 && board[i][j] == 0){
                    board[i][j] = 2;
                    changed = 1;
                }
    }

    int ret = 2;
    for(int i = 0; i < n && ret; ++i)
        for(int j = 0; j < m && ret; ++j)
            for(auto shape : shapes){
                int ok = 1;
                for(auto u : shape){
                    if(i+u.ff >= n || j+u.ss >= m || board[i+u.ff][j+u.ss] == 2)
                        ok = 0;
                }
                if(ok == 0) continue;

                //every cell must either contain a pair or a cell marked by player 2
                int blocked = 0;
                for(int x = 0; x < shape.size(); ++x){
                    pii u1 = {i+shape[x].ff, j+shape[x].ss};
                    if(board[u1.ff][u1.ss])
                        continue;
                    for(int y = x+1; y < shape.size(); ++y){
                        pii u2 = {i+shape[y].ff, j+shape[y].ss};
                        if(board[u2.ff][u2.ss])
                            continue;
                        if(sol[u1.ff][u1.ss] && sol[u1.ff][u1.ss] == sol[u2.ff][u2.ss])
                            blocked = 1;
                    }
                }
                if(blocked == 0){
                    ret = 0;
                    break;
                }
            }

    if(turn == 2 && changed){
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(sol[i][j] == -2)
                    board[i][j] = 0;
    }
    return ret;
}