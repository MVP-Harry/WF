#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

typedef long long ll;

#ifdef LOCAL
    #include <bits/debug.h>
#else
    #define dbg(...)
#endif

typedef double ftype;
struct Point {
    ftype x, y;
    Point() {}
    Point(ftype _x, ftype _y): x(_x), y(_y) {}
    Point& operator+=(const Point &t) {
        x += t.x;
        y += t.y;
        return *this;
    }
    Point& operator-=(const Point &t) {
        x -= t.x;
        y -= t.y;
        return *this;
    }
    Point& operator *= (ftype t) {
        x *= t;
        y *= t;
        return *this;
    }
    Point& operator/=(ftype t) {
        x /= t;
        y /= t;
        return *this;
    }
    Point operator + (const Point &t) const {
        return Point(*this) += t;
    }
    Point operator - (const Point &t) const {
        return Point(*this) -= t;
    }
    Point operator *(ftype t) const {
        return Point(*this) *= t;
    }
    Point operator / (ftype t) const {
        return Point(*this) /= t;
    }
    bool operator < (const Point& t) const {
        return make_pair(x, y) < make_pair(t.x, t.y);
    }
    bool operator == (const Point& t) const {
        return x == t.x && y == t.y;
    }
    bool operator != (const Point& t) const {
        return x != t.x || y != t.y;
    }
};

Point operator*(ftype a, Point b) {
    return b * a;
}

Point perp(Point p) {
    return {-p.y, p.x};
}

ftype dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

ftype norm(Point a) {
    return dot(a, a);
}

double abs(Point a) {
    return sqrt(norm(a));
}

double proj(Point a, Point b) {
    return dot(a, b) / abs(b);
}

double angle(Point a, Point b) {
    return acos(dot(a, b) / abs(a) / abs(b));
}

ftype cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

// AB x AC > 0 if C is on the left side of AB
// AB x AC = 0 if C is on AB
// AB x AC < 0 if C is on the right side of AB
ftype orient(Point a, Point b, Point c) {
    return cross(b - a, c - a);
}

struct Line {
    Point v;
    ftype c;

    // From direction vector v and offset c
    Line(Point _v, ftype _c) : v(_v), c(_c) {}
    
    // From the equation ax + by = c
    Line(ftype a, ftype b, ftype _c) : v({b, -a}), c(_c) {}

    // From points P and Q
    Line(Point p, Point q) : v(q - p), c(cross(v, p)) {}

    // For a point P = (x, y), find ax + by - c
    ftype side(Point p) {
        return cross(v, p) - c;
    }

    // Distance from a point P to the line
    double dist(Point p) {
        return fabs(side(p)) / abs(v);
    }

    // Find the line perpendicular to the current line passing through P
    Line perp_through(Point p) {
        return {p, p + perp(v)};
    }

    // sort two points P, Q based on the order they appeared on the line
    bool cmp_proj(Point p, Point q) {
        return dot(v, p) < dot(v, q);
    }

    // Translate the line by a vector p
    Line translate(Point p) {
        return {v, cross(v, p) + c};
    }

    // Shifting the line to the left by dist amount
    Line shift_left(double dist) {
        return Line(v, c + dist * abs(v));
    }

    // Find intersection of two lines
    bool inter(Line l1, Line l2, Point &out) {
        ftype d = cross(l1.v, l2.v);
        if (d == 0) {
            return false;
        }
        out = (l2.v * l1.c - l1.v * l2.c) / d;
        return true;
    }

    // Find the projection of P onto a line
    Point proj(Point p) {
        return p - perp(v) * side(p) / norm(v);
    }

    // Find the reflection of P over a line
    Point refl(Point p) {
        return p - 2 * perp(v) * side(p) / norm(v);
    }

    // Find the angle bisector of line 1 and line 2
    Line bisector(Line l1, Line l2, bool interior) {
        assert(cross(l1.v, l2.v) != 0);
        double sign = interior ? 1 : -1;
        return Line(l2.v / abs(l2.v) + l1.v / abs(l1.v) * sign,
                    l2.c / abs(l2.v) + l1.c / abs(l1.v) * sign);
    }
};

// Check if point C lies within the diameter of AB
bool in_disk(Point a, Point b, Point c) {
    return dot(a - c, b - c) <= 0;
}

// Check if point C is on the segment AB
bool on_segment(Point a, Point b, Point c) {
    return in_disk(a, b, c) && orient(a, b, c) == 0;
}

// See if there exists a single non-endpoint interesection between AB and CD
bool proper_inter(Point a, Point b, Point c, Point d, Point& out) {
    double oa = orient(c, d, a);
    double ob = orient(c, d, b);
    double oc = orient(a, b, c);
    double od = orient(a, b, d);

    if (oa * ob < 0 && oc * od < 0) {
        out = (a * ob - b * oa) / (ob - oa);
        return true;
    }
    return false;
}

// Find intersection between AB and CD
set<Point> inters(Point a, Point b, Point c, Point d) {
    Point out;
    if (proper_inter(a, b, c, d, out)) return { out };
    
    set<Point> s;
    if (on_segment(c, d, a)) s.insert(a);
    if (on_segment(c, d, b)) s.insert(b);
    if (on_segment(a, b, c)) s.insert(c);
    if (on_segment(a, b, d)) s.insert(d);

    return s;
}

// Find distance from point P to segment AB
double point_to_seg(Point a, Point b, Point p) {
    if (a != b) {
        Line l(a, b);
        if (l.cmp_proj(a, p) && l.cmp_proj(p, b)) {
            return l.dist(p);
        }
    }
    return min(abs(p - a), abs(p - b));
}

// Find distance between two segments AB and CD
double seg_to_seg(Point a, Point b, Point c, Point d) {
    Point dummy;
    if (proper_inter(a, b, c, d, dummy)) {
        return 0;
    }

    return min({point_to_seg(a, b, c), point_to_seg(a, b, d),
                point_to_seg(c, d, a), point_to_seg(c, d, b)});
}

double polygon_area(vector<Point> pts) {
    double area = 0;
    for (int i = 0, n = pts.size(); i < n; i++) {
        area += cross(pts[i], pts[(i + 1) % n]);
    }
    return abs(area) / 2.0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;

    vector<Point> pts(n), sum(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y;
        sum[i + 1] = sum[i] + pts[i];
    }

    double polygonArea = polygon_area(pts);
    double ans = 0;
    for (int i = 0; i < n; i++) {
        Point p1 = i * pts[i] - sum[i];
        Point p2 = sum[n] - sum[i + 1] - (n - 1 - i) * pts[i];
        ans += cross(p1, p2) / polygonArea / 2;
    }
    cout << fixed << setprecision(9);
    cout << ans << "\n";
    
    return 0;
}
