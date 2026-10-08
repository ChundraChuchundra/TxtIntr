#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Статистический калькулятор (вариант 7)\n"
             << "Использование: " << argv[0] << " -o <операция> <операнд1> ... <операндN>\n"
             << "Операции: mean (среднее), median (медиана)\n"
             << "Количество операндов: от 7 до 9\n";
        return 0;
    }

    string op;
    vector<double> v;

    for (int i = 1; i < argc; ++i) {
        string a = argv[i];
        if (a == "-o" || a == "--operation") {
            if (i + 1 < argc) op = argv[++i];
            else { cerr << "Ошибка: после " << a << " нужна операция\n"; return 1; }
        } else {
            try { v.push_back(stod(a)); }
            catch (...) { cerr << "Ошибка: некорректный операнд '" << a << "'\n"; return 1; }
        }
    }

    if (op.empty()) {
        cerr << "Ошибка: не указана операция (-o mean или -o median)\n";
        return 1;
    }

    if (op != "mean" && op != "median") {
        cerr << "Ошибка: неизвестная операция '" << op << "'. Допустимые: mean, median\n";
        return 1;
    }

    if (v.size() < 7 || v.size() > 9) {
        cerr << "Ошибка: нужно от 7 до 9 операндов (сейчас: " << v.size() << ")\n";
        return 1;
    }
    bool allZeros = true;
    for (double x:v) {
        if (x != 0.0) { allZeros = false; break; }
    }
    if (allZeros) {
        cout << "Я уверен, вы можете лучше :)" << endl;
    }
    double res = 0.0;
    if (op == "mean") {
        for (double x : v) res += x;
        res /= v.size();
        cout << "Среднее арифметическое: " << fixed << setprecision(4) << res << endl;
    } else {
        sort(v.begin(), v.end());
        size_t n = v.size();
        res = (n % 2 == 0) ? (v[n/2 - 1] + v[n/2]) / 2.0 : v[n/2];
        cout << "Медиана: " << fixed << setprecision(4) << res << endl;
    }

    return 0;
}
