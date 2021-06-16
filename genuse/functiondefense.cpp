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
int main() {
    
    context c;
    expr x = c.int_const("x");
    func_decl func = c.function("func", c.int_sort(), c.int_sort());
    
    solver s(c);
    s.add( forall(x, implies(x >= 0 && x <= 10, func(func(x)) == x)) );
    //s.add(forall(x, func(x) == x)); If you uncomment this part, it will find a solution
    if(s.check() == unsat){
        cout << "Unsat\n";
        return 0;
    }
    model m = s.get_model();
    cout << m << '\n';
}