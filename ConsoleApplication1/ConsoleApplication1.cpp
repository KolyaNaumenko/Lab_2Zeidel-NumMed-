// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void printMatrix(vector<vector<double>>& A) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

void generateRandomDiagonallyDominantMatrix(vector<vector<double>>& A, int n, int minValue, int maxValue) {
    A = vector<vector<double>>(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        double diagonalSum = 0.0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                A[i][j] = static_cast<double>(rand() % (maxValue - minValue + 1) + minValue);
                diagonalSum += abs(A[i][j]);
            }
        }

        A[i][i] = diagonalSum + 1.0;
    }
}

void computeVectorB(const vector<vector<double>>& A, vector<double>& b) {
    int n = A.size();
    b = vector<double>(n, 0.0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[i] += A[i][j];
        }
    }
}

vector<double> gaussSeidelMethod(const vector<vector<double>>& A, const vector<double>& b, int maxIterations, double tolerance) {
    int n = A.size();
    vector<double> x(n, 0.0);

    for (int iteration = 0; iteration < maxIterations; iteration++) {
        for (int i = 0; i < n; i++) {
            double sigma1 = 0.0;
            for (int j = 0; j < i; j++) {
                sigma1 += A[i][j] * x[j];
            }

            double sigma2 = 0.0;
            for (int j = i + 1; j < n; j++) {
                sigma2 += A[i][j] * x[j];
            }

            x[i] = (b[i] - sigma1 - sigma2) / A[i][i];
        }

        // Check for convergence
        double maxDiff = 0.0;
        for (int i = 0; i < n; i++) {
            maxDiff = max(maxDiff, abs(x[i]));
        }

        if (maxDiff < tolerance) {
            cout << "Converged after " << iteration + 1 << " iterations." << endl;
            break;
        }
    }

    return x;
}

int main() {
    int n;
    cout << "Enter the matrix dimension: ";
    cin >> n;

    vector<vector<double>> A;
    vector<double> b;

    srand(time(0));

    int minValue, maxValue;
    cout << "Enter the minimum and maximum values for random matrix elements: ";
    cin >> minValue >> maxValue;
    generateRandomDiagonallyDominantMatrix(A, n, minValue, maxValue);

    computeVectorB(A, b);

    cout << "Vector b:" << endl;
    for (int i = 0; i < n; i++) {
        cout << b[i] << " ";
    }
    cout << endl;

    int maxIterations;
    double tolerance;
    cout << "Enter the maximum number of iterations: ";
    cin >> maxIterations;
    cout << "Enter the tolerance (e.g., 1e-6): ";
    cin >> tolerance;

    vector<double> solution = gaussSeidelMethod(A, b, maxIterations, tolerance);

    cout << "Solution:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "] = " << solution[i] << endl;
    }

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
