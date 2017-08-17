#include <algorithm>
#include <cstdio>
#include <vector>
#include <complex>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int64,int64> pii;
typedef vector<int> vi;

typedef complex<int64> point;
typedef vector<point> hull;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100010;

int64 cross(point a, point b){ return imag(conj(a) * b); }
int64 dot(point a, point b){ return real(conj(a) * b); }

void add(point a, hull &ch){
    for (int n = (int)ch.size(); n > 1 && cross(ch[n - 1] - ch[n -2], a - ch[n - 2]) >= 0; n--)
        ch.pop_back();
    ch.push_back(a);
}

int64 eval(point a, hull &ch){
    int lo = 0, hi = (int)ch.size() - 1;
    while (lo < hi){
        int m = (lo + hi) / 2;

        if (dot(ch[m], a) >= dot(ch[m + 1], a))
            hi = m;
        else
            lo = m + 1;
    }
    return dot(ch[lo], a);
}

hull merge(const hull &a, const hull &b){
    int n = (int)a.size(), m = (int)b.size();
    int x = 0, y = 0;
    hull c;

    while (x < n && y < m){
        if (real(a[x]) <= real(b[y])) add(a[x++], c);
        else add(b[y++], c);
    }

    while (x < n) add(a[x++], c);
    while (y < m) add(b[y++], c);

    return c;
}

struct dyn{
    vector<hull> H;

    void add(point p){
        hull h;
        h.push_back(p);

        for (int i = 0; i < (int)H.size(); ++i){
            hull &ch = H[i];

            if (ch.empty()){
                ch = h;
                return;
            }

            h = merge(h, ch);
            ch.clear();
        }

        if (!h.empty()) H.push_back(h);
    }

    int64 query(point p){
        bool f = false;
        int64 answer = 0;

        for (int i = 0; i < (int)H.size(); ++i){
            hull &ch = H[i];

            if (ch.empty()) continue;
            int64 val = eval(p, ch);

            if (!f){
                f = true;
                answer = val;
            }

            answer = max(answer, val);
        }

        return answer;
    }
} C;

int64 L[maxn], R[maxn];
pii grades[maxn];
int64 A[maxn], B[maxn];

bool compare(pii a, pii b){
    return a.first * b.second > a.second * b.first;
}

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        int64 a, b;
        scanf("%lld%lld", &a, &b);
        grades[i] = pii(a, b);
    }

    sort(grades, grades + n, compare);

    for (int i = 1; i <= n; ++i){
        A[i] = A[i - 1] + grades[i - 1].first;
        B[i] = B[i - 1] + grades[i - 1].second;
    }

    for (int i = 1; i < n; ++i){
        C.add(point(-grades[i - 1].first, grades[i - 1].second));
        int64 p = A[i], q = B[i];

        L[i] = -C.query(point(q, p));
    }

    C = dyn();

    for (int i = n; i > 1; --i){
        C.add(point(grades[i - 1].first, -grades[i - 1].second));
        int64 p = A[i - 1], q = B[i - 1];

        R[i] = C.query(point(q, p));
    }

    vector<int> ans;

    for (int i = 1; i < n; ++i){
        if (L[i] < R[i + 1]){
            ans.push_back(i);
        }
    }

    printf("%d\n", (int)ans.size());
    reverse(ans.begin(), ans.end());

    for (int i = 0; i < (int)ans.size(); ++i){
        printf("%d\n", n - ans[i]);
    }

    return 0;
}

