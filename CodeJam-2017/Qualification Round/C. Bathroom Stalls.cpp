#include <iostream>
#include <cstring>

int distanceToTheLeft(char *stalls, int index) {
    int result = 0;
    for (int i = index - 1; i >= 0; i--) {
        if (stalls[i] == '.') result++;
        else break;
    }
    return result;
}

int distanceToTheRight(char *stalls, int index) {
    int len = (int) strlen(stalls);
    int result = 0;
    for (int i = index + 1; i < len; i++) {
        if (stalls[i] == '.') result++;
        else break;
    }
    return result;
}

void getResult(int n, int k, int *result) {
    char *stalls = new char[n + 3];
    stalls[0] = stalls[n + 1] = '0';
    stalls[n + 2] = '\0';
    for (int i = 1; i < n + 1; i++) {
        stalls[i] = '.';
    }

    for (int u = 0; u < k; u++) {
        int optimal[3] = {-100, -100, -1};

        for (int i = 1; i < n + 1; i++) {
            if (stalls[i] == '.') {
                int left = distanceToTheLeft(stalls, i);
                int right = distanceToTheRight(stalls, i);


                int min = std::min(left, right);
                int max = std::max(left, right);

                if (min > optimal[0] || (min == optimal[0] && max > optimal[1])) {
                    optimal[0] = min;
                    optimal[1] = max;
                    optimal[2] = i;
                }
            }
        }

        stalls[optimal[2]] = '0';

        if (u == k - 1) {
            result[0] = optimal[0];
            result[1] = optimal[1];
        }
    }

    delete[] stalls;

}

int main() {
    int t, n, k;

    std::cin >> t;

    for (int i = 1; i <= t; i++) {
        std::cin >> n >> k;

        int result[2];

        getResult(n, k, result);

        std::cout << "Case #" << i << ": " << result[1] << " " << result[0] << std::endl;
    }
    return 0;
}
