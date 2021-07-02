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

vector<vector<pii>> shapes;
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
const int maxn = 16, maxm = 16;
vector<vector<char>> checkdefence(vector<vector<pii>> shapes){
    for(auto u : shapes)
        normalize(u);
    for(int n = 1; n <= maxn; n += 1)
    for(int m = 1; m <= maxm; m += 1)
    {
            int maxn = 0;
            int maxm = 0;
            for(auto u : shapes)
                for(auto x : u){
                    maxn = max(maxn, x.ff+1);
                    maxm = max(maxm, x.ss+1);
                }
            

            context c;
            vector<vector<expr>> up;
            vector<vector<expr>> down;
            vector<vector<expr>> left;
            vector<vector<expr>> right;
            //Initializing the boolean constants
            for(int i = 0; i < n; ++i){
                up.pb(vector<expr>());
                down.pb(vector<expr>());
                left.pb(vector<expr>());
                right.pb(vector<expr>());
                for(int j = 0; j < m; ++j){
                    up.back().pb(c.bool_const(("u" + to_string(i) + "_" + to_string(j)).c_str()));
                    down.back().pb(c.bool_const(("d" + to_string(i) + "_" + to_string(j)).c_str()));
                    left.back().pb(c.bool_const(("l" + to_string(i) + "_" + to_string(j)).c_str()));
                    right.back().pb(c.bool_const(("r" + to_string(i) + "_" + to_string(j)).c_str()));
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
            //Each domino tile is 2 blocks long
            
            //We shoulnt be able to place any of the shapes without at least covering one full
            //domino tile
            vector<vector<int>> curvis(maxn, vector<int>(maxm));
            for(auto shape : shapes){
                for(int i = 0; i < n; ++i)
                    for(int j = 0; j < m; ++j){

                        expr_vector v(c);
                        for(auto u : shape){
                            int x = u.ff;
                            int y = u.ss;
                            curvis[x][y] = 1;
                            
                            
                            if(x > 0 && curvis[x-1][y]){
                                v.pb(up[(x+i)%n][(y+j)%m] && down[(x+i-1+n)%n][(y+j)%m]);
                                //cout << "up " << x << ' ' << y << '\n';
                            }
                            if(y > 0 && curvis[x][y-1]){
                                v.pb(left[(x+i)%n][(y+j)%m] && right[(x+i)%n][(y+j-1+m)%m]);
                                //cout << "left " << x << ' ' << y << '\n';
                            }
                        }
                        for(auto u : shape){
                            int x = u.ff;
                            int y = u.ss;
                            curvis[x][y] = 0;
                        }
                        //cout << '\n';
                        if(v.size())
                            s.add(atleast(v, 1));
                    }
            }
            
            if(s.check() == unsat)
                continue;

            model ml = s.get_model();
            vector<vector<char>> res(n, vector<char>(m, '.'));
            //Making the output of z3 more meaningful to look at
            for(int i = 0; i < ml.size(); ++i){
                func_decl v = ml[i];
                assert(v.arity() == 0);
                if(ml.get_const_interp(v).bool_value() == -1)
                    continue;
                
                string s = v.name().str();
                int x = 0, y = 0;
                char c = s[0];
                for(int i = 1; i < s.size(); ++i)
                    if(s[i] == '_'){
                        x = stoi(s.substr(1, i-1));
                        y = stoi(s.substr(i+1, s.size()-(i+1)));
                        break;
                    }
                res[x][y] = c;
            }
            
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < m; ++j){
                    if(res[i][j] == 'l' && res[i][(j-1+m)%m] != 'r')
                        res[i][j] = '.';
                    else if(res[i][j] == 'r' && res[i][(j+1)%m] != 'l')
                        res[i][j] = '.';
                    else if(res[i][j] == 'd' && res[(i+1)%n][j] != 'u')
                        res[i][j] = '.';
                    else if(res[i][j] == 'u' && res[(i-1+n)%n][j] != 'd')
                        res[i][j] = '.';
                }
            return res;
        }
    return vector<vector<char>>();   
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
pii syx(pii x){
    return {x.ff, -x.ss};
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