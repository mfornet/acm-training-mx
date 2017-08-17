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
map<int,int> dist[maxn];

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

int par[maxn];

void generate_dist(int c, int p, int s){
    for (auto u : adj[c]){
        if (u == p || mk[u]) continue;
        dist[u][s] = dist[c][s] + 1;
        generate_dist(u, c, s);
    }
}

void build(int s){
    generate_dist(s, -1, s);
    mk[s] = true;

    for (auto u : adj[s]){
        if (mk[u]) continue;

        int c = centroid(u);
        par[c] = s;

        build(c);
    }
}

int V1[maxn];
int V2[maxn];
set<pii> DP[maxn];

void update(int u, int a, int d){
    int v = u;

    while (v != -1){
        int cd = dist[u][v];

        DP[v].erase({d - cd, -u});
        DP[v].insert({a - cd, -u});

        v = par[v];
    }
}

pii query(int u){
    pii ans(-oo, 1);
    int v = u;

    while (v != -1){
        int d = dist[u][v];
        pii cur = *DP[v].rbegin(); cur.first -= d;
        ans = max(ans, cur);
        v = par[v];
    }

    return ans;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;

    cin >> n;

    for (int i = 1; i < n; ++i){
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int c = centroid(0);
    par[c] = -1;

    build(c);

    for (int i = 0; i < n; ++i)
        cin >> V1[i];

    for (int i = 0; i < n; ++i){
        cin >> V2[i];
        update(i, V2[i], -1);
    }

    int q; cin >> q;

    while (q--){
        int t; cin >> t;

        if (t == 0){
            int u, x;
            cin >> u >> x;
            u--;
            V1[u] = x;
        }
        else if (t == 1){
            int u, x;
            cin >> u >> x;
            u--;
            update(u, x, V2[u]);
            V2[u] = x;
        }
        else{
            int u; cin >> u; u--;
            pii ans = query(u); ans.first += V1[u];
            cout << -ans.second + 1 << " " << ans.first << endl;
        }
    }

    return 0;
}
