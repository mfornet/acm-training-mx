#include <bits/stdc++.h>

using namespace std;

typedef long long int64;
typedef pair<int64, int64> pii;

const int MAXN = (int)1e6 + 10;

int B, E;
struct Line{
    int64 m, n;
    int64 eval(int64 x){
        return m * x + n;
    }
    void print(){
        cout << m << "*x + " << n << endl;
    }
} Stack[MAXN];

bool bad(Line a, Line b, Line c){
    return (c.n - a.n) * (a.m - b.m) < (b.n - a.n) * (a.m - c.m);
}

void insert(Line l){
    while (E - B > 1 && bad(Stack[E - 2], Stack[E - 1], l)) --E;
    Stack[E++] = l;
}

int64 query(int x){
    while (E - B > 1 && Stack[B].eval(x) <= Stack[B + 1].eval(x)) ++B;
    return Stack[B].eval(x);
}

int main()
{
    B = E = 0;
    int n; cin >> n;
    int a, b, c; cin >> a >> b >> c;

    int64 S; cin >> S;

    int64 DP = a * S * S + b * S + c;
    insert( (Line){-2 * a * S, -b * S + a * S * S + DP} );

    for (int i = 2; i <= n; ++i){
        int64 v; cin >> v;
        S += v;
        DP = max(a * S * S + b * S + c, query( S ) + a * S * S + b * S + c);
        if (i != n) insert( (Line){-2 * a * S, -b * S + a * S * S + DP} );
    }
    cout << DP << endl;
    return 0;
}
