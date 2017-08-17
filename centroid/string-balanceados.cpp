#include <bits/stdc++.h>

using namespace std;

//#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int n;
char P[maxn];
vi adj[maxn];

bool dead[maxn];

int q[maxn];
int size[maxn];
int mchild[maxn];
int father[maxn];

int centroid(int s){
    int total = 0, pnt = 0;

    q[total++] = s;
    father[s] = -1;
    mchild[s] = 0;
    size[s] = 0;

    while (pnt < total){
        int u = q[pnt++];

        for (auto v : adj[u]){
            if (v == father[u] || dead[v]) continue;
            q[total++] = v;

            father[v] = u;
            mchild[v] = 0;
            size[v] = 0;

//          cout << "queue: " << v << endl;
        }
    }

//  cout << "here: " << s << endl;

    for (int i = total - 1; i >= 0; --i){
        int u = q[i];
        size[u]++;

//      cout << u << " " << mchild[u] << " " << size[u] << endl;
        mchild[u] = max(mchild[u], total - size[u]);

        if (mchild[u] * 2 <= total) return u;

        int f = father[u];
        size[f] += size[u];
        mchild[f] = max(mchild[f], size[u]);
    }

    assert(false);
    return -1;
}

map<int, int64> freq;

int64 dfs1(int s, int f, int open, int closed)
{
    int64 answer = 0;

    if (P[s] == '('){
        open++;
    }
    else{
        if (open) open--;
        else closed++;
    }

    if (open == 0){
        answer = freq[closed];
    }

    for (auto u : adj[s]){
        if (u == f || dead[u])
            continue;

        answer += dfs1(u, s, open, closed);
    }

    return answer;
}


void dfs2(int s, int f, int open, int closed){
    if (P[s] == '('){
        if (closed) closed--;
        else open++;
    }
    else{
        closed++;
    }

    if (closed == 0){
        freq[open]++;
    }

    for (auto u : adj[s]){
        if (u == f || dead[u])
            continue;

        dfs2(u, s, open, closed);
    }
}


int64 calc(int c){
    int total = 0;
    for (auto v : adj[c]){
        if (!dead[v]) q[total++] = v;
    }

    int open = 0, closed = 0;

    (P[c] == '(' ? open : closed) = 1;

    freq.clear();

    int64 answer = 0;

//  cout << "node: " << c << " " << open << " " << closed << endl;

    for (int i = 0; i < total; ++i){
        int u = q[i];
        answer += dfs1(u, c, 0, 0);
        dfs2(u, c, open, closed);
    }

    if (closed){
        answer += freq[0];
    }

    reverse(q, q + total);
    freq.clear();

    if (open)
        freq[1]++;

    for (int i = 0; i < total; ++i){
        int u = q[i];
        answer += dfs1(u, c, 0, 0);
        dfs2(u, c, open, closed);
    }

    return answer;
}

int64 solve(int s){
    int c = centroid(s);
//  cout << "centroid: " << s << " " << c << endl;

    dead[c] = true;
    int64 answer = calc(c);
//  cout << "calculate: " << c << " " << answer << endl;
//  exit(0);

    for (auto u : adj[c]){
        if (!dead[u])
            answer += solve(u);
    }

    return answer;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> P;

    for (int i = 0; i + 1 < n; ++i){
        int u, v; cin >> u >> v;
        u--; v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int64 answer = solve(0);

    cout << answer << endl;

    return 0;
}