#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

struct disjoint_set{
    vector<int> ds;
    disjoint_set(int n) : ds(n, -1) {}

    int root(int a){
        return ds[a] < 0 ? a : ds[a] = root(ds[a]);
    }

    bool join(int a, int b){
        a = root(a), b = root(b);
        if (a == b) return false;
        if (rand() & 1) swap(a, b);
        ds[a] = b;
        return true;
    }
};

vector<pii> edges;

int X(int n){
    random_shuffle(edges.begin(), edges.end());
    disjoint_set d(n);
    int c = n, i;

    for (i = 0; c > 1; ++i)
        if (d.join(edges[i].first, edges[i].second))
            c--;

    return i;
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            edges.push_back(pii(i,j));

    long long mc = 0;
    int tm = 0;

    for(int i = 0; 1. * clock() / CLOCKS_PER_SEC < 1.9; ++i){
        mc += X(n);
        tm++;
    }

    cout << mc / tm << endl;
    return 0;
}
