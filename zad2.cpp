#include <bits/stdc++.h>

using namespace std;

struct Point {
    double x, y;

    Point() {}
    Point(double X, double Y) : x(X), y(Y) {}

    double operator*(const Point& o) const {
        return o.x*y-x*o.y;
    }
    Point operator-(const Point& o) const {
        return {x-o.x, y-o.y};
    }
    bool operator<(const Point& o) const {
        if (x == o.x) return y < o.y;
        return x < o.x;
    }
};

struct Geo {
    vector<Point> points;

    Geo() {}
    Geo(vector<Point> Points) : points(Points) {}

    void add_point(Point p) {
        points.push_back(p);
    }
    void add_point(double x, double y) {
        add_point({x,y});
    }

    vector<Point> convex_hull() {
        vector<Point> result;

        if (points.size() == 1) {
            result = points;
        }
        if (points.size() > 1) {
            sort(points.begin(), points.end());

            for (int it = 2; it > 0; it--) {
                result.push_back(points[0]);
                result.push_back(points[1]);

                for (int i = 2; i < points.size(); i++) {

                    while ( (result[result.size()-1] - result[result.size()-2]) * (points[i] - result[result.size()-2]) >= 0) {
                        result.pop_back();
                    }

                    result.push_back(points[i]);
                }
                result.pop_back();

                if (it > 1) reverse(points.begin(), points.end());
            }


        }
        return result;
    }
};

Geo geo;

bool read_file() {
    try {
        string file_name;
        cin >> file_name;

        ifstream cin(file_name);
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            double x, y;
            cin >> x >> y;
            geo.add_point(x,y);
        }
        return true;
    } catch (...) {
        return false;
    }
}

void write_output(const vector<Point>& result) {
    cout << "[";
    for (int i = 0; i < result.size(); i++) {
        auto p = result[i];
        cout << "(" << p.x << ", " << p.y << ")";
        if (i < result.size()-1) 
            cout << ", ";
    }

    cout << "]\n";
}

int main () {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);

    if (read_file()) {
        vector<Point> convex_hull = geo.convex_hull();
        write_output(convex_hull);
    }
}