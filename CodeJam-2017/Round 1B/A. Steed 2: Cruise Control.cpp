#include <iostream>
#include <iomanip>

using namespace std;

long double calcTime(int distance, int initial, int speed) {
    return (distance - initial) / (double)speed;
}

long double calcSpeed(int distance, long double time) {
    return distance / time;
}

int main() {
    int t;

    cin >> t;

    for (int i = 1; i <= t; i++) {
        int d, n;
        cin >> d >> n;

        long double maxTime = -1;
        for (int u = 0; u < n; u++) {
            int initial, speed;
            cin >> initial >> speed;

            long double time = calcTime(d, initial, speed);

            if (time > maxTime) maxTime = time;
        }

        cout  <<fixed<<setprecision(6)<< "Case #" << i << ": " << calcSpeed(d, maxTime) << endl;

    }
    return 0;
}