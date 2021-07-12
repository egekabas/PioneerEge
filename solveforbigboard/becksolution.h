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
int commonval[20][20];

int becksolution(vector<vector<int>> &board, vector<vector<pii>> &shapes, int turn){
    int n = board.size();
    int m = board[0].size();
    
    ld impval = 0;
    //calculating sum of 2^-A
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
                    //if blocked, break
                    if(board[x][y] == 2){
                        ok = 0;
                        break;
                    }
                    if(board[x][y] == 0)
                        ++cursize;
                }
                if(ok == 0) continue;
                //if already won, return
                if(cursize == 0)
                    return 1;
                impval += pow(2, -cursize);
            }
    //One of Becks Theorems
    if(impval < 0.5)
        return 2;
    if(turn == 1){
        int dtwo = 0;
        int vertices = 0;
        //calculating v and d2 as in the article
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j){
                if(board[i][j])
                    continue;
                ++vertices;
                //for every shape and every node in that shape that can cover
                //our cell, we increase all the cells covered by that shape
                for(auto shape : shapes)
                    for(int k = 0; k < shape.size(); ++k){
                        int ok = 1;
                        for(pii point : shape){
                            int x = point.ff+i-shape[k].ff;
                            int y = point.ss+j-shape[k].ss;
                            if(x < 0 || x >= n || y < 0 || y >= m || board[i][j] == 2){
                                ok = 0;
                                break;
                            }
                        }
                        if(ok == 0) continue;
                        for(pii point : shape){
                            int x = point.ff+i-shape[k].ff;
                            int y = point.ss+j-shape[k].ss;
                            if(board[x][y] == 0)
                                commonval[x][y]++;
                        }
                    }
                for(int x = 0; x < n; ++x)
                    for(int y = 0; y < m; ++y){
                        if(i != x || j != y)
                            dtwo = max(dtwo, commonval[x][y]);
                        commonval[x][y] = 0;
                    }
            }
        //One of Beck's theorems
        if(impval > dtwo*vertices/ld(8))
            return 1;
    }

    return 0;
}