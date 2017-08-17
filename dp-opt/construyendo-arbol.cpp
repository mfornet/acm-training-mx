#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int64,int64> pii;
typedef vector<int> vi;

const int64 oo = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-9;
const int maxn = 1000 + 10;

pii pos[maxn];
int64 X[maxn];
int64 Y[maxn];

int64 dp[maxn][maxn];
int opt[maxn][maxn];

int64 calc(int b, int e){
    int64 size = e - b + 1;
    int64 xx = Y[e] - Y[b - 1] - pos[e].second * size;
    int64 yy = pos[e].first - pos[b].first;

    return xx + yy;
}

int64 comp(int b, int k, int e){
    if (k == e) return oo;
    int64 ans = dp[b][k] + dp[k + 1][e] + pos[k + 1].first - pos[b].first + pos[k].second - pos[e].second;
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    for (int i = 1; i <= n; ++i){
        cin >> pos[i].first >> pos[i].second;
    }

    sort(pos + 1, pos + n + 1);

    for (int i = 1; i <= n; ++i){
        X[i] = X[i - 1] + pos[i].first;
        Y[i] = Y[i - 1] + pos[i].second;
        opt[i][i] = i;
    }

    for (int sz = 2; sz <= n; ++sz){
        for (int b = 1; b + sz <= n + 1; ++b){
            int e = b + sz - 1;

            dp[b][e] = calc(b, e);
            opt[b][e] = opt[b][e - 1];

            for (int k = opt[b][e - 1]; k <= opt[b + 1][e]; ++k){
                int64 v = comp(b, k, e);
                if (v < dp[b][e]){
                    opt[b][e] = k;
                    dp[b][e] = v;
                }
            }
        }
    }

    cout << dp[1][n] << endl;

    return 0;
}
