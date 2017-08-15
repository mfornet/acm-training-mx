#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define DB(x) cout << #x << " = " << x << endl << flush;
#define SZ(x) (int)((x).size())
#define MP make_pair

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double EPS = 1e-9;
const int MAXN = (int)1e5 + 10;

struct rect{
    int64 m, n;

    rect(){
        m = n = 0;
    }

    rect(int64 M, int64 N){
        m = M, n = N;
    }

    int64 eval(int64 x){
        return m * x + n;
    }
};

rect STK[MAXN];
pair<int64,int64> B[MAXN];
int BEGIN = 0, END = 0;

bool bad(rect r2, rect r1, rect r){
    return (r.n - r2.n) *(r2.m - r1.m)< (r1.n - r2.n) * (r2.m - r.m)  ;
}

void push(rect r){
    while (END > BEGIN + 1 && bad(STK[END - 2], STK[END - 1], r)) END--;
    STK[END++] = r;
}

int64 eval(int64 x){
    while (END > BEGIN + 1 && STK[BEGIN].eval(x) >= STK[BEGIN + 1].eval(x)) ++BEGIN;
    return STK[BEGIN].eval(x);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> B[i].first >> B[i].second;

    sort(B, B + n);
    int cur = 0;
    for (int i = 0; i < n; ++i){
        while (cur && B[cur - 1].second <= B[i].second)
            --cur;
        B[cur++] = B[i];
    }

    push(rect(B[0].second, 0));

    int64 dp;
    for (int i = 0; i < n; ++i){
        dp = eval(B[i].first);
        if (i + 1 < n) push(rect(B[i + 1].second, dp));
    }

    cout << dp << endl;

    return 0;
}
