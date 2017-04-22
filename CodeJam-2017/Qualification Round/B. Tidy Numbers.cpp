#include <iostream>
#include <cstring>

/** 
 *Small Data Set Solution 
 **/
bool isTidySmall(int num) {
    int last = num % 10, next;
    num /= 10;
    while (num) {
        next = num % 10;
        if (last < next) return false;
        num /= 10;
        last = next;
    }

    return true;
}

int getLastTidySmall(int num) {
    int n = num;

    while (!isTidySmall(n)) n--;

    return n;
}

void smallDataset() {
    int n, num;

    std::cin >> n;

    for (int i = 1; i <= n; i++) {
        std::cin >> num;
        std::cout << "Case #" << i << ": " << getLastTidySmall(num) << std::endl;
    }
}

/** 
 * Big Data Set Solution 
 **/
bool isTidyBig(char *num) {
    char last = num[0];
    char next;

    int len = (int) strlen(num);

    for (int i = 1; i < len; i++) {
        next = num[i];
        if (last > next) return false;
        last = next;
    }
    return true;
}

void makeSmaller(char *num) {
    int len = (int) strlen(num);
    num[0]--;
    for (int i = 1; i < len; i++) {
        num[i] = '9';
    }
}

void print(char *num) {
    int len = (int) strlen(num);
    bool hasStarted = false;

    if(num[0] == '0' && len == 1) {
        std::cout<<"0";
        return;
    }

    for (int i = 0; i < len; i++) {
        if (hasStarted) std::cout << num[i];
        else if (num[i] != '0') {
            std::cout << num[i];
            hasStarted = true;
        }
    }
}

void getLastTidyBig(char *num) {
    int len = (int) strlen(num);

    while (!isTidyBig(num)) {
        int last = 0;

        for (int i = 1; i < len; i++) {
            if (num[last] > num[i]) {
                makeSmaller(num + last);
                break;
            }
            last = i;
        }
    }
}

void bigDataset() {
    int n;
    char num[20];

    std::cin >> n;
    std::cin.getline(num, 20);

    for (int i = 1; i <= n; i++) {
        std::cin.getline(num, 20);
        getLastTidyBig(num);
        std::cout << "Case #" << i << ": ";
        print(num);
        std::cout << std::endl;
    }


}

int main() {
    //smallDataset();
    bigDataset();
    return 0;
}
