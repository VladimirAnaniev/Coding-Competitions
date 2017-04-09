#include <iostream>
#include <cstring>

int getToFlip(char *s) {
    int len = (int) strlen(s);
    int count = 0;

    for (int i = 0; i < len; i++) {
        if (s[i] == '-') count++;
    }

    return count;
}

int getResult(char *s, int k) {
    int flips = 0;
    int len = (int) strlen(s);

    for (int i = 0; i <= len - k; i++) {
        if (s[i] == '-') {
            for (int u = 0; u < k; u++) {
                if (s[i + u] == '-') s[i + u] = '+';
                else s[i + u] = '-';
            }
            flips++;
        }
    }

    int toFlip = getToFlip(s);
    if (toFlip == 0) return flips;
    else return -1;


}

int parseInt(char*num) {
    return atoi(num);
}

int main() {
    int t, k;
    char s[1010];

    std::cin >> t;
    std::cin.getline(s, 10);

    for (int i = 1; i <= t; i++) {
        std::cin.getline(s, 1010);

        int splitIndex = 0;

        for (int z = 0; z < strlen(s); z++) {
            if(s[z] ==' ') {
                s[z]='\0';
                splitIndex = z;
                break;
            }
        }

        k = parseInt(s+splitIndex+1);

        int result = getResult(s, k);

        std::cout << "Case #" << i << ": ";
        if (result >= 0) std::cout << result;
        else std::cout << "IMPOSSIBLE";
        std::cout << std::endl;
    }

    return 0;
}
