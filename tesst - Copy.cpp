/// https://vnoi.info/wiki/algo/search/Local-Search.md#local-search

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    Point operator - (Point a) { return Point(x-a.x, y-a.y); }
    double len() { return sqrt(x*x + y*y); }
} a[MAXN];

int n;
bool used[MAXN];  // Đánh dấu điểm đã được đi qua.
int id[MAXN];  // Lưu chỉ số của các điểm trong kết quả tìm được.


void optimize() {
    iota(id + 1, id + n + 1, 1);
    id[n + 1] = 1;
    while (true) {
        bool stop = true;
        for(int u = 2; u <= n + 1; ++u) {
            for(int v = n; v > u; --v) {
                // t1 = (cạnh (u-1) --> u) + (cạnh (v --> (v+1))
                double t1 = (a[id[u-1]] - a[id[u]]).len()
                        + (a[id[v]] - a[id[v+1]]).len();
                // t2 = (cạnh (u-1) --> v) + (cạnh (u --> (v+1))
                double t2 = (a[id[u-1]] - a[id[v]]).len()
                        + (a[id[u]] - a[id[v+1]]).len();
                if (t1 > t2) {  // Nếu đổi chu trình cho kết quả tốt hơn
                    for(int i = u, j = v; i <= j; ++i, --j) {
                        swap(id[i], id[j]);
                    }
                    stop = false;
                }
            }
        }
        if (stop) break;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    optimize();
    double ans = 0;
    for (int i = 1; i <= n; i++) {
        int nxt = i + 1 > n ? 1 : i + 1;
        ans += (a[id[i]] - a[id[nxt]]).len();
    }
    cout << setprecision(4) << fixed << ans << endl;
    for (int i = 1; i <= n; i++) {
        cout << id[i] << " ";
    }
    
    return 0;
}
