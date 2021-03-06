#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

vi adj[maxn];
bool mk[maxn];
int q[maxn], p[maxn], sz[maxn], mc[maxn];

int centroid(int c){
    int b = 0, e = 0;
    q[e++] = c, p[c] = -1, sz[c] = 1, mc[c] = 0;

    while (b < e){
        int u = q[b++];
        for (auto v : adj[u]) if (v != p[u] && !mk[v])
                p[v] = u, sz[v] = 1, mc[v] = 0, q[e++] = v;
    }

    for (int i = e - 1; ~i; --i){
        int u = q[i];
        int bc = max(e - sz[u], mc[u]);
        if (2 * bc <= e) return u;
        sz[p[u]] += sz[u], mc[p[u]] = max(mc[p[u]], sz[u]);
    }

    assert(false);
    return -1;
}

int ans[maxn];

void build(int s, int p){
    int c = centroid(s);

    mk[c] = true;
    ans[c] = p;

    for (auto u : adj[c]){
        if (mk[u]) continue;
        build(u, p + 1);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    for (int i = 0; i + 1 < n; ++i){
        int u, v; cin >> u >> v;
        u--; v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    build(0, 0);

    for (int i = 0; i < n; ++i)
        cout << (char)(ans[i] + 'A') << " ";

    cout << endl;

    return 0;
}