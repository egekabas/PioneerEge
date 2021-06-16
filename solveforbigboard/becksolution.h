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
int cnt[20][20];
int becksolution(vector<vector<int>> &board, vector<vector<pii>> &shapes){
    int n = board.size();
    int m = board[0].size();
    
    ld impval = 0;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            for(auto shape : shapes){
                int cursize = 0;
                int ok = 1;
                for(auto u : shape){
                    int x = u.ff+i, y = u.ss+j;
                    if(x >= n || y >= m){
                        ok = 0;
                        break;
                    }
                    if(board[x][y] == 2){
                        ok = 0;
                        break;
                    }
                    if(board[x][y] == 0)
                        ++cursize;
                }
                if(ok == 0) continue;
                if(cursize == 0)
                    return 1;
                impval += pow(2, -cursize);
            }
    //cout << impval << '\n';
    if(impval < 0.5)
        return 2;
    return 0;
    //implement winning finder later
}