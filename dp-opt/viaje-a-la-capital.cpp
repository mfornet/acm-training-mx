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
int END = 0;

bool bad(rect r2, rect r1, rect r){
    return 1.0 *(r.n - r2.n) / (r2.m - r.m) < 1.0 * (r1.n - r2.n) / (r2.m - r1.m)  ;
}

int getPos(rect r){
    if (END <= 1) return END;

    int lo = 1, hi = END;
    while (lo + 1 < hi){
        int mid = (lo + hi) >> 1;

        if (bad(STK[mid - 1], STK[mid], r))
            hi = mid;
        else
            lo = mid;
    }

    return hi;
}

int64 eval(int64 x){
    if (END == 1) return STK[0].eval(x);

    int lo = -1, hi = END - 1;

    while (lo + 1 < hi){
        int mid = (lo + hi) >> 1;
        if (1.0 * x < 1.0 * (STK[mid].n - STK[mid + 1].n) / (STK[mid + 1].m - STK[mid].m))
            hi = mid;
        else
            lo = mid;
    }

    return STK[hi].eval(x);
}

vector<pair<int,int64>> ady[MAXN];
int64 dp[MAXN], p[MAXN], v[MAXN], dist[MAXN];
bool mk[MAXN];

void dfs(int s){
    mk[s] = true;
    dp[s] = eval(v[s]) + p[s] + v[s] * dist[s];

    rect r = rect(-dist[s], dp[s]);

    int pos = getPos(r);
    rect tmp = STK[pos];
    STK[pos] = r;
    int __END = END;
    END = pos + 1;

    for (auto nxt: ady[s]){
        int child = nxt.first, d = nxt.second;
        if (mk[child]) continue;
        dist[child] = dist[s] + d;
        dfs(child);
    }

    STK[pos] = tmp;
    END = __END;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    for (int i = 1; i < n; ++i){
        int u, v;
        int64 d;
        cin >> u >> v >> d;
        ady[u].push_back(MP(v, d));
        ady[v].push_back(MP(u, d));
    }

    for (int i = 2; i <= n; ++i)
        cin >> p[i] >> v[i];

    STK[END++] = rect(0, 0);
    dfs(1);

    for (int i = 2; i <= n; ++i)
        cout << dp[i] << " ";
    cout << endl;

    return 0;
}
