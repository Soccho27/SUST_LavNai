ll getSign(ll x1,ll y1, ll x2, ll y2, ll x3, ll y3){
    // ll direct = x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2;
    ll direct = (y2 - y1) * (x3 - x2) - (y3 - y2) * (x2 - x1);
    if(x2 == 2)cout<<x1<<SS<<y1<<SS<<x2<<SS<<y2<<SS<<x3<<SS<<y3<<nl;
    if(direct > 0)return 1;     // clockWise
    if(direct < 0)return 2;     // counter - ClockWise
    if(direct == 0)return 0;    // collinear
}

/*
    x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2;
    ei jinis asche triangle area ber korar sutro theke
    search dao triangle area with co-ordinate points
    to etar direction thik kore eta kon dik a jabe, modulo dhorle +, - sign chole jai
    r o valo bujhte cses er plygon area er pepcoding er video dkhte paro
    https://www.youtube.com/watch?v=Zo7Hb-5ePOo&t=1220s
*/


#include <bits/stdc++.h>
using namespace std;

// Function to find orientation of ordered triplet (x1,y1), (x2,y2), (x3,y3)
// Returns: 0 -> collinear, 1 -> clockwise, 2 -> counter-clockwise
int ori(int x1, int y1, int x2, int y2, int x3, int y3) {
    int val = (y2 - y1) * (x3 - x2) - (x2 - x1) * (y3 - y2);
    if (val == 0) return 1;        // clockwise
    else if (val < 0) return 2;    // counter-clockwise
    return 0;                      // collinear
}

// Check if point (x3,y3) lies on segment (x1,y1)-(x2,y2)
bool onSeg(int x1, int y1, int x2, int y2, int x3, int y3) {
    // works only if orientation is zero
    return x3 >= min(x1, x2) && x3 <= max(x1, x2) &&
           y3 >= min(y1, y2) && y3 <= max(y1, y2);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T; cin >> T;
    while (T--) {
        long x1, y1, x2, y2, x3, y3, x4, y4;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

        long o1 = ori(x1, y1, x2, y2, x3, y3);
        long o2 = ori(x1, y1, x2, y2, x4, y4);
        long o3 = ori(x3, y3, x4, y4, x1, y1);
        long o4 = ori(x3, y3, x4, y4, x2, y2);

        if (o1 != o2 && o3 != o4) cout << "YES\n"; // general case
        else if (o1 == 0 && onSeg(x1, y1, x2, y2, x3, y3)) cout << "YES\n";
        else if (o2 == 0 && onSeg(x1, y1, x2, y2, x4, y4)) cout << "YES\n";
        else if (o3 == 0 && onSeg(x3, y3, x4, y4, x1, y1)) cout << "YES\n";
        else if (o4 == 0 && onSeg(x3, y3, x4, y4, x2, y2)) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
 