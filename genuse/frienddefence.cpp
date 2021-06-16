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
struct ansstruct{
    int x, y, bx, by;
};
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
    vector<expr> edgebool;
    int edgeidx[16][16][16][16][2][2];
    //Initializing the boolean constants
    int curidx = 0;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            for(int x = 0; x < n; ++x)
                for(int y = 0; y < m; ++y)
                    for(int bx = 0; bx < 2; ++bx)
                        for(int by = 0; by < 2; ++by){
                            if(bx == 1 && by == 1) continue;
                            if(bx == 0 && by == 0 && pii(x, y) <= pii(i, j))
                                continue;
                            if(bx == 0 && by == 0){
                                edgeidx[i][j][x][y][bx][by] = curidx;
                                edgeidx[x][y][i][j][bx][by] = curidx;
                            }
                            else
                                edgeidx[i][j][x][y][bx][by] = curidx;
                            edgebool.pb(c.bool_const((to_string(i)+"-"+to_string(j)+"-"+to_string(x)+"-"+to_string(y)+"-"+to_string(bx)+"-"+to_string(by)).c_str()));
                            ++curidx;
                        }

    solver s(c);
    //A grid can only have one friend
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j){
            expr_vector vec(c);
            for(int x = 0; x < n; ++x)
                for(int y = 0; y < m; ++y)
                    for(int bx = 0; bx < 2; ++bx)
                        for(int by = 0; by < 2; ++by){
                            if(bx == 1 && by == 1) continue;
                            if(bx == 0 && by == 0 && pii(x, y) == pii(i, j))
                                continue;
                            if(bx == 0 && by == 0){
                                vec.push_back(edgebool[edgeidx[i][j][x][y][bx][by]]);
                            }
                            else{
                                vec.push_back(edgebool[edgeidx[i][j][x][y][bx][by]]);
                                vec.push_back(edgebool[edgeidx[x][y][i][j][bx][by]]);
                            }
                        }
            s.add(atmost(vec, 1));

        }
    
    //You shouldnt be able to place a shape without containing a pair of friends
    for(auto shape : shapes)
        for(int x = 0; x < n; ++x)
            for(int y = 0; y < m; ++y){
                expr_vector vec(c);
                for(int i = 0; i < shape.size(); ++i)
                    for(int j = i+1; j < shape.size(); ++j){
                        pii p1 = {shape[i].ff+x,shape[i].ss+y};
                        pii p2 = {shape[j].ff+x,shape[j].ss+y};
                        if(p1.ff/n > p2.ff/n || p1.ss/m > p2.ss/m)
                            swap(p1, p2);
                        int bx = p2.ff/n-p1.ff/n;
                        int by = p2.ss/m-p1.ss/m;
                        if((bx == 1 && by == 1) || (bx != 0 && bx != 1) || (by != 0 && by != 1))
                            continue;
                        if(bx == 0 && by == 0)
                            if(p1 > p2)
                                swap(p1, p2);
                        vec.push_back(edgebool[edgeidx[p1.ff%n][p1.ss%m][p2.ff%n][p2.ss%m][bx][by]]);
                        
                    }
                if(vec.size())
                    s.add(atleast(vec, 1));
            }

    cout <<  "Calculating\n";
    check_result cres = s.check();
    cout<< "Calcuated in " << fixed << setprecision(3) << (ld)clock() / CLOCKS_PER_SEC<< " seconds\n";
    cout << cres << "\n\n";
    if(cres == unsat)
        return 0;

    model ml = s.get_model();
    vector<vector<ansstruct>> res(n, vector<ansstruct>(m));
    //Making the output of z3 more meaningful to look at
    for(int i = 0; i < ml.size(); ++i){
        func_decl v = ml[i];
        assert(v.arity() == 0);
        if(ml.get_const_interp(v).bool_value() == -1)
            continue;
        
        string s = v.name().str();
        vector<int> vec;
        int last = 0;
        for(int i = 0; i < s.size(); ++i)
            if(s[i] == '-'){
                vec.pb(stoi(s.substr(last, i-last)));
                last = i+1;
            }
        vec.pb(stoi(s.substr(last, s.size()-last)));
        
        res[vec[0]][vec[1]] = {vec[2], vec[3], vec[4], vec[5]};
        res[vec[2]][vec[3]] = {vec[0], vec[1], -vec[4], -vec[5]};
    }
    
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cout << res[i][j].x << ' ' << res[i][j].y << ' ' << res[i][j].bx << ' ' << res[i][j].by << "    ";
        }
        cout << '\n';
    }
}
/*
4 4
2
6
0 0
0 1
0 2
0 3
1 3
1 4
6
0 0
1 0
1 1
2 1
3 1
4 1
*/