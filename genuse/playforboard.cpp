#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <bits/stdc++.h>
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
map<int, int> nxtst;
int p[30];
int board[6][6];
int calc(int bit){
    if(res[bit]) return res[bit];
    
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
                if(ok){
                    nxtst[bit] = -1;
                    return res[bit] = 1;
                }
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
    if(nxt.empty()){
        nxtst[bit] = -1;
        return res[bit] = 2;
    }
    if(turn == 0){
        for(auto u : nxt)
            if(calc(bit+u) == 1){
                nxtst[bit] = bit+u;
                return res[bit] = 1;
            }
        nxtst[bit] = bit+nxt[0];
        return res[bit] = 2; 
    }
    else{
        for(auto u : nxt)
            if(calc(bit+2*u) == 2){
                nxtst[bit] = bit+2*u;
                return res[bit] = 2;
            }
        nxtst[bit] = bit+2*nxt[0];
        return res[bit] = 1; 
    }
}
void printboard(int bit){
    cout << "  ";
    for(int j = 0; j < m; ++j)
        cout << j;
    cout << "\n\n";
    for(int i = 0; i < n; ++i){
        cout << i << ' ';
        for(int j = 0; j < m; ++j){
            cout << bit%3;
            bit /= 3;
        }
        cout << '\n';
    }
}
int main() {
    
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
    calc(0);
    cout << "Which player do you want to play as(1 or 2)?\n";
    int player;
    cin >> player;
    --player;
    player ^= 1;
    
    int turn = 0;
    int curbit = 0;
    while(1){
        calc(curbit);
        if(nxtst[curbit] == -1){
            cout << "Player " << res[curbit] << " wins.\n";
            return 0;
        }
        if(turn == player){
            cout << "\nComputers turn\n";
            curbit = nxtst[curbit];
            printboard(curbit);
        }
        else{
            cout << "\nYour turn\n";
            int x, y;
            cin >> x >> y;
            curbit += (turn+1)*p[x*m+y];
            cout << '\n';printboard(curbit);cout << '\n';
            sleep(1);
        }
        turn ^= 1;
    }   
}
/*
(declare-sort A)
(declare-const x A)
(declare-const y A)
(declare-fun f (A) A)
(assert (= (f (f x)) x))
(assert (= (f x) y))
(assert (not (= x y)))
(check-sat)
(get-model)
*/