#include <iostream>
#include <fstream>

using namespace std;

int rows, cols, minimum, maximum, tomatoes = 0, mushrooms = 0, piecesCount = 0;
char **pizza;
int **points, **possibilities;

bool isPieceValid(int top, int left, int bottom, int right) {
    int tomatoesCount = 0, mushroomsCount = 0;

    for (int r = top; r < bottom; r++) {
        for (int c = left; c < right; c++) {
            if (pizza[r][c] == 'X') return false;
            else if (pizza[r][c] == 'T') tomatoesCount++;
            else if (pizza[r][c] == 'M') mushroomsCount++;
        }
    }

    return tomatoesCount >= minimum && mushroomsCount >= minimum;
}

void fillWithX(int *coordinates) {
    for (int r = coordinates[0]; r <= coordinates[2]; r++) {
        for (int c = coordinates[1]; c <= coordinates[3]; c++) {
            if (pizza[r][c] == 'T') tomatoes--;
            else if (pizza[r][c] == 'M') mushrooms--;
            pizza[r][c] = 'X';
        }
    }
}

int getMaximumRemainingPieces(int top, int left, int bottom, int right) {
    int tomatoesInside = 0, mushroomsInside = 0;

    for (int r = top; r < bottom; r++) {
        for (int c = left; c < right; c++) {
            if (pizza[r][c] == 'X') return false;
            else if (pizza[r][c] == 'T') tomatoesInside++;
            else if (pizza[r][c] == 'M') mushroomsInside++;
        }
    }

    return min(tomatoes - tomatoesInside, mushrooms - mushroomsInside) / minimum;
}

bool getValidPiece(int row, int col, int size, int count) {
    if (size < minimum * 2) {
        if (count > 0) {
            int optimalIndex = 0;
            int maxRemaining = -1;
            for (int i = 0; i < count; i++) {
                if (possibilities[i][4] > maxRemaining) {
                    maxRemaining = possibilities[i][4];
                    optimalIndex = i;
                }
            }

            points[piecesCount] = possibilities[optimalIndex];
            fillWithX(possibilities[optimalIndex]);

            return true;
        } else return false;
    }

    for (int i = 1; i <= size; i++) {
        if (size % i == 0) {
            int bottom = row + i;
            int right = col + size / i;

            if (bottom <= rows && right <= cols && isPieceValid(row, col, bottom, right)) {
                int remaining = getMaximumRemainingPieces(row, col, bottom, right);
                possibilities[count++] = new int[5]{row, col, bottom - 1, right - 1, remaining+size};
            }
        }
    }

    return getValidPiece(row, col, size - 1, count);
}

void getPieces() {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (pizza[r][c] != 'X') {
                if (getValidPiece(r, c, maximum, 0)) piecesCount++;
            }
        }
    }
}

void deleteArrays() {
    for (int i = 0; i < rows; i++) {
        delete[] pizza[i];
    }
    for (int i = 0; i < piecesCount; i++) {
        delete[] points[i];
    }

    delete[] pizza;
    delete[] points;
}

void cutPizza() {
    int maxPossiblePieces = min(tomatoes, mushrooms) / minimum;

    points = new int *[maxPossiblePieces];
    possibilities = new int *[maxPossiblePieces];

    getPieces();

    ofstream output("output.txt");

    output << piecesCount << endl;

    for (int i = 0; i < piecesCount; i++) {
        output << points[i][0] << ' ' << points[i][1] << ' ' << points[i][2] << ' ' << points[i][3] << endl;
    }

    output.close();

    deleteArrays();
}

int main() {
    cin >> rows >> cols >> minimum >> maximum;

    pizza = new char *[rows];

    for (int r = 0; r < rows; r++) {
        char *row = new char[cols];
        for (int c = 0; c < cols; c++) {
            cin >> row[c];
            if (row[c] == 'T') tomatoes++;
            else mushrooms++;
        }
        pizza[r] = row;
    }

    cutPizza();

    return 0;
}