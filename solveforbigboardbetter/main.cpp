#include <bits/stdc++.h>
#define MAXBOARD 20
#define all(x) (x).begin(), (x).end()
#define ff first
#define ss second
#define pb push_back
using namespace std;
typedef pair<int, int> pii;
class Polyomino : vector<pair<int, int>>{
    public:
        Polyomino(){}
        void normalize(){
            int minx = 1e9+7, miny = 1e9+7;
            for(auto u : *this){
                minx = min(minx, u.ff);
                miny = min(miny, u.ss);
            }
            for(auto &u : *this){
                u.ff -= minx;
                u.ss -= miny;
            }
            sort(all(*this));
        }
        Polyomino(initializer_list<pii> list) : vector<pii>(list){
            normalize();
        }
        void transform(pii (*func)(pii)){
            for(auto &u : *this)
                u = func(u);
            normalize();
        }
        void print(ostream &outputstream){
            normalize();
            int n = 0, m = 0;
            for(auto u : *this){
                n = max(n, u.ff);
                m = max(m, u.ss);
            }
            int cur = 0;
            for(int i = 0; i <= n; ++i){
                for(int j = 0; j <= m; ++j){
                    if(cur != size() && (*this)[cur] == pii(i, j)){
                        outputstream << '*';
                        ++cur;
                    }
                    else
                        outputstream << '.';
                }
                outputstream << '\n';
            }
            outputstream << '\n';
        }
        bool operator<(Polyomino &oth){
            for(int i = 0; i < size(); ++i){
                if(i >= oth.size())
                    return 0;
                if((*this)[i] != oth[i])
                    return (*this)[i] < oth[i];
            }
            return 1;
        }
};
pii rotate(pii x){
    return {x.ss, -x.ff};
}
pii reflect(pii x){
    return {-x.ff, x.ss};
}
class PolyominoSet : vector<Polyomino>{
    public:
        PolyominoSet(){}
        void normalize(){
            for(auto &u : *this)
                u.normalize();
            sort(all(*this));
        }
        PolyominoSet(Polyomino shape){
            shape.normalize();
            
            for(int i = 0; i < 4; ++i){
                pb(shape);
                shape.transform(rotate);
            }
            shape.transform(reflect);
            for(int i = 0; i < 4; ++i){
                pb(shape);
                shape.transform(rotate);
            }
            sort(all(*this));
        }
        void transform(pii (*func)(pii)){
            for(auto &u : *this)
                u.transform(func);
            sort(all(*this));
        }
        void print(ostream &outputstream){
            for(auto u : *this){
                u.print(outputstream);
                outputstream << '\n';
            }
        }
};
class Board : vector<vector<int>>{
    public:
        int n, m;
        Board(int n, int m) : vector<vector<int>>(n, vector<int>(m)){
            this->n = n;
            this->m = m;
        }
        void rotateboard(){
            static int boardtmp[MAXBOARD][MAXBOARD];
            if(n != m){
                cerr << "The board must be a square/n";
                return;
            }
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < m; ++j){
                    int x = j;
                    int y = m-1-i;
                    
                    boardtmp[x][y] = (*this)[i][j];
                }
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < m; ++j)
                    (*this)[i][j] = boardtmp[i][j];
        }
        void reflectboard(){
            static int boardtmp[MAXBOARD][MAXBOARD];
            if(n != m){
                cerr << "The board must be a square/n";
                return;
            }
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < m; ++j){
                    int x = n-1-i;
                    int y = j;
                    
                    boardtmp[x][y] = (*this)[i][j];
                }
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < m; ++j)
                    (*this)[i][j] = boardtmp[i][j];    
        }
        bool operator<(Board &oth){
            for(int i = 0; i < n; ++i){
                if(i >= oth.n)
                    return 0;
                if( (*this)[i] != oth[i])
                    return (*this)[i] < oth[i];
            }
            [0][4] = 1;
            return 1;
        }
};
class GameSolver{
    private:
        PolyominoSet gameset;
        map<Board, int> res;
};


int main(){
    Polyomino snaky = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 3}, {1, 4}};
    PolyominoSet gameset(snaky);

}