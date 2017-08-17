#include <iostream>

using namespace std;

typedef long long int64;

const int N = 1001;


int64 sm[N], v[N];
int64 dp[N][N];
int opt[N][N];

int main(){
    int n; cin >> n;

    for (int i = 1; i <= n; ++i){
        cin >> v[i-1];

        sm[i] = sm[i - 1] + v[i-1];
        opt[i - 1][i] = i - 1;
    }

    for (int sz = 2; sz <= n; ++sz){
        for (int x = 0; x + sz <= n; ++x){
            int y = x + sz;

            opt[x][y] = opt[x][y - 1];
            dp[x][y] = dp[x][opt[x][y]] + dp[opt[x][y]+1][y] - v[opt[x][y]];

            for (int k = opt[x][y - 1] + 1; k <= opt[x+1][y]; ++k){
                int64 val = dp[x][k] + dp[k + 1][y] - v[k];

                if (val <= dp[x][y]){
                    dp[x][y] = val;
                    opt[x][y] = k;
                }
            }

            dp[x][y] += sm[y] - sm[x];
        }
    }

    cout << dp[0][n] << endl;
}
