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
/*
if turn is 2
The total beck value is 
sum of 2^-|A|
So to minimize this value, we block the tile with the highest value 
sum 2^-|A|

we can multiply all values with 2^MAXSIZE to avoid dealing with floating numbers
*/

/*
if the turn is 1, we try to maximize the beck value
so we compare by
sum 2^-(|A|-1)-2^-|A|
=
sum 2^-|A|

so evertyhing is the same
*/

int beckval[20][20];
//sorting by decreasing beckval
int sortbyprob(pii x, pii y){
    return beckval[x.ff][x.ss] > beckval[y.ff][y.ss];   
}
vector<pii> orderusingbeck(vector<vector<int>> &board, vector<vector<pii>> &shapes){
    int n = board.size(), m = board[0].size();
    
    vector<pii> vec;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            if(board[i][j] == 0)
                vec.pb({i, j});
        
    int maxsize = 0;
    for(auto shape : shapes)
        maxsize = max(maxsize, (int)shape.size());
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            beckval[i][j] = 0;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            for(auto shape : shapes){
                int ok = 1;
                int sz = 0;
                for(auto u : shape){
                    int x = i+u.ff;
                    int y = j+u.ss;
                    if(x < 0 || x >= n || y < 0 || y >= m || board[x][y] == 2){
                        ok = 0;
                        break;
                    }
                    if(board[x][y] == 0)
                        ++sz;
                }
                if(ok == 0) continue;
                for(auto u : shape){
                    int x = i+u.ff;
                    int y = j+u.ss;
                    if(board[x][y] == 0)
                        beckval[x][y] += (1<<(maxsize-sz));
                    //adding 2^-A to all covered by any placement of a shape
                }
            }
    

    std::sort(all(vec), sortbyprob);
    return vec;        
}
