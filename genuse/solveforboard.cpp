#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define int long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ull, ull> pull;
typedef pair<int, int> pii;
typedef pair<ld, ld> pld;
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
    sort(all(vec));
    vec.resize(unique(all(vec))-vec.begin());
}
vector<vector<pii>> shapes;
int n, m;
map<int, int> res;
int p[30];
int board[30][30];
int calc(int bit){
    if(res[bit]) return res[bit];
    //cout << bit << '\n';
    int tmp = bit;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j){
            board[i][j] = tmp%3;
            tmp /= 3;
        }
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j){
            for(auto shape : shapes){
                int ok = 1;
                for(auto u : shape){
                    int ni = i+u.ff;
                    int nj = j+u.ss;
                    if(ni < 0 || ni >= n || nj < 0 || nj >= m || board[ni][nj] != 1)
                        ok = 0;
                }
                if(ok)
                    return res[bit] = 1;
            }
        }
    vector<int> nxt;
    int turn = 0;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j){
            if(board[i][j] == 0)
                nxt.pb(p[i*m+j]);
            else if(board[i][j] == 1)
                ++turn;
            else
                --turn;
        }
    if(nxt.empty()) return res[bit] = 2;
    if(turn == 0){
        for(auto u : nxt)
            if(calc(bit+u) == 1)
                return res[bit] = 1;
        return res[bit] = 2; 
    }
    else{
        for(auto u : nxt)
            if(calc(bit+2*u) == 2)
                return res[bit] = 2;
        return res[bit] = 1; 
    }
}

int32_t main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
    
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);

    p[0] = 1;
    for(int i = 1; i < 30; ++i)
        p[i] = 3*p[i-1];

    cout << "Enter the board dimensions\n";
    cin >> n >> m;

    cout << "Enter the number of shapes\n";
    int shapenum;
    cin >> shapenum;
    shapes.resize(shapenum);
    for(int i = 0; i < shapenum; ++i){
        int shapesize;
        cout << "Enter the size of shape " << i+1 << " and the coordinates of its elements\n";
        cin >> shapesize;
        while(shapesize--){
            int x, y;
            cin >> x >> y;
            shapes[i].pb({x, y});
        }
        normalize(shapes[i]);
    }
    cout << "Calculating\n";
    cout << "Player " << calc(0) << " wins.";
    //cout << res.size() << '\n';
    cout<<endl<<fixed<<setprecision(2)<<1000.0 * clock() / CLOCKS_PER_SEC<< " milliseconds ";
}