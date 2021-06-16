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
int n, m;

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
int main() {

    //Getting the input
    cout << "Enter the dimensions of the repeating pattern\n";
    cin >> n >> m;
    cout << "Enter the number of shapes\n";
    int shapenum;
    cin >> shapenum;
    shapes.resize(shapenum);
    for(int i = 0; i < shapenum; ++i){
        cout << "Enter the size of shape " << i+1 << '\n';
        int sz;
        cin >> sz;
        cout << "Enter the coordinates of shape " << i+1 << '\n';
        shapes[i].resize(sz);
        for(auto &u : shapes[i])
            cin >> u.ff >> u.ss;
        normalize(shapes[i]);
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
            s.add(atleast(v, 1));
        }   
    //Each domino tile is 2 blocks long
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j){
            s.add(implies(up[i][j], down[(i-1+n)%n][j]));
            s.add(implies(down[i][j], up[(i+1)%n][j]));
            
            s.add(implies(left[i][j], right[i][(j-1+m)%m]));
            s.add(implies(right[i][j], left[i][(j+1)%m]));
        }
    
    //We shoulnt be able to place any of the shapes without at least covering one full
    //domino tile
    vector<vector<int>> curvis(n, vector<int>(m));
    for(auto shape : shapes){
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j){
                
                expr_vector v(c);
                for(auto u : shape){
                    int x = (i+u.ff)%n;
                    int y = (j+u.ss)%m;
                    curvis[x][y] = 1;
                    if(curvis[(x-1+n)%n][y]){
                        v.pb(up[x][y]);
                        //cout << "up " << x << ' ' << y << '\n';
                    }
                    if(curvis[x][(y-1+m)%m]){
                        v.pb(left[x][y]);
                        //cout << "left " << x << ' ' << y << '\n';
                    }
                }
                for(auto u : shape){
                    int x = (i+u.ff)%n;
                    int y = (j+u.ss)%m;
                    curvis[x][y] = 0;
                }
                //cout << '\n';
                s.add(atleast(v, 1));
            }
    }
    
    check_result cres = s.check();
    cout << cres << "\n\n";
    if(cres == unsat)
        return 0;

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
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cout << res[i][j];
        }
        cout << '\n';
    }
}
/*
The input for a pattern size of 4 by 4 and shapes
***** and *
          *
          * 
          * 
          * 

4 4 ---> if you change these values to 6 6, it is impossible to create a working domino tiling
2
5
0 0
0 1
0 2
0 3
0 4
5
0 0
1 0
2 0
3 0
4 0
*/