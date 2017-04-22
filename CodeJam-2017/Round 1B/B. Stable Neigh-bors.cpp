#include "iostream"

using namespace std;

bool canBeNextTo(int that, int other) {
    if(that == 0) {
        if(other == 1 || other == 0 || other == 5) return false;
    } else if(that == 1) {
        if(other == 0 || other ==2) return false;
    } else if(that == 2) {
        if(other == 1 ||other == 2 || other == 3) return false;
    } else if(that == 3) {
        if(other == 2||other==3||other==4) return false;
    } else if(that == 4) {
        if(other == 3||other==4||other==5) return false;
    } else if(that == 5) {
        if(other == 0 ||other == 4 ||other == 5) return false;
    }
    return true;
}

int getNext(int *colors, int last, int first) {
    int max = -1;
    int maxAmount = -1;

    for (int i = 0; i < 6; i++) {
        if (!canBeNextTo(i, last)) continue;
        if (colors[i] > maxAmount && colors[i] > 0 ||
            colors[i] >= maxAmount && !canBeNextTo(i, first)) {
            max = i;
            maxAmount = colors[i];
        }
    }

    return max;
}

int main() {
    int t;

    cin >> t;

    for (int i = 1; i <= t; i++) {
        int n, colors[6];

        cin >> n >> colors[0] >> colors[1] >> colors[2] >> colors[3] >> colors[4] >> colors[5];

        char *str = new char[n + 1];
        bool possible = true;
        int last = -1, first = -1;
        int strIndex = 0;

        while (possible && strIndex < n) {
            int next = getNext(colors, last, first);
            colors[next]--;
            last = next;
            if (strIndex == 0) first = next;

            switch (next) {
                case 0:
                    str[strIndex++] = 'R';
                    break;
                case 1:
                    str[strIndex++] = 'O';
                    break;
                case 2:
                    str[strIndex++] = 'Y';
                    break;
                case 3:
                    str[strIndex++] = 'G';
                    break;
                case 4:
                    str[strIndex++] = 'B';
                    break;
                case 5:
                    str[strIndex++] = 'V';
                    break;
                default:
                    possible = false;
            }

        }

        if (str[0] == str[n - 1]) possible = false;

        str[n] = '\0';

        cout << "Case #" << i << ": ";

        if (possible) cout << str << endl;
        else cout << "IMPOSSIBLE" << endl;

    }


    return 0;
}

