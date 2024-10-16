
#include <iostream>
#include <vector>
#include <iterator>
#include <list>
#include <set>
#include <fstream>
#include <algorithm>
#include <string>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <map>
using namespace std;

int safeInput() {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cerr << "Ошибка: введите целое число.\n";
        } else {
            return value;
        }
    }
}

int safeInputK() {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cin.clear();  // Сбрасываем флаг ошибки
            cin.ignore();  // Очищаем буфер
            cerr << "Ошибка: введите целое число больше 0.\n";
        } else if (value <= 0) {
            cerr << "Ошибка: K должно быть больше 0.\n";
        } else {
            return value;
        }
    }
}

void task1() {
    vector<int> V;
    int n;

    cout << "Введите количество элементов (должно быть четным): ";
    n = safeInput();

    if (n % 2 != 0) {
        cerr << "Ошибка: количество элементов должно быть четным.\n";
        return;
    }

    cout << "Введите " << n << " целых чисел:\n";

    for (int i = 0; i < n; ++i) {
        cout << "Элемент " << i + 1 << ": ";
        int value = safeInput();
        V.push_back(value);
    }

    auto half = V.size() / 2;

    cout << "Вторая половина элементов:\n";
    copy(V.begin() + half, V.end(), ostream_iterator<int>(cout, " "));
    cout << "\nПервая половина элементов:\n";
    copy(V.begin(), V.begin() + half, ostream_iterator<int>(cout, " "));
    cout << endl;
}

void task2() {
        vector<int> V;
        list<int> L;

        cout << "Введите количество элементов для вектора (не менее 5): ";
        int vectorSize = safeInput();
        while (vectorSize < 5) {
            cerr << "Ошибка: количество элементов должно быть не менее 5.\nВведите количество элементов для вектора (не менее 5): ";
            vectorSize = safeInput();
        }

        cout << "Введите " << vectorSize << " целых чисел для вектора:\n";
        for (int i = 0; i < vectorSize; ++i) {
            cout << "Элемент вектора " << i + 1 << ": ";
            V.push_back(safeInput());
        }

        cout << "Введите количество элементов для списка (не менее 5): ";
        int listSize = safeInput();
        while (listSize < 5) {
            cerr << "Ошибка: количество элементов должно быть не менее 5.\nВведите количество элементов для списка (не менее 5): ";
            listSize = safeInput();
        }

        cout << "Введите " << listSize << " целых чисел для списка:\n";
        for (int i = 0; i < listSize; ++i) {
            cout << "Элемент списка " << i + 1 << ": ";
            L.push_back(safeInput());
        }

        // Вставляем в список первые 5 элементов вектора в обратном порядке
        auto it = L.begin();
        advance(it, 5);  // Перемещаем итератор на 5-й элемент

        // Вставка первых 5 элементов вектора в обратном порядке
        for (int i = 4; i >= 0; --i) {
            L.insert(it, V[i]); // Вставка элементов в обратном порядке
        }

        // Выводим итоговый список
        cout << "Итоговый список:\n";
        for (const auto& elem : L) {
            cout << elem << " ";
        }
        cout << endl;
    }

void task3() {
    list<int> L1, L2;

    cout << "Введите количество элементов для списков (четное число): ";
    int size = safeInput();
    while (size % 2 != 0) {
        cerr << "Ошибка: количество элементов должно быть четным.\nВведите количество элементов для списков (четное число): ";
        size = safeInput();
    }

    cout << "Введите " << size << " целых чисел для первого списка (L1):\n";
    for (int i = 0; i < size; ++i) {
        cout << "Элемент списка L1 " << i + 1 << ": ";
        L1.push_back(safeInput());
    }

    cout << "Введите " << size << " целых чисел для второго списка (L2):\n";
    for (int i = 0; i < size; ++i) {
        cout << "Элемент списка L2 " << i + 1 << ": ";
        L2.push_back(safeInput());
    }

    // Определяем итераторы для первой и второй половин списков
    auto mid1 = L1.begin();
    advance(mid1, size / 2);  // Перемещаем на середину L1

    auto mid2 = L2.begin();
    advance(mid2, size / 2);  // Перемещаем на середину L2

    // Меняем местами первую половину L1 и вторую половину L2
    list<int> temp1(mid1, L1.end());  // Временный список для первой половины L1
    list<int> temp2(mid2, L2.end());  // Временный список для второй половины L2

    L1.erase(mid1, L1.end());  // Удаляем вторую половину L1
    L2.erase(mid2, L2.end());  // Удаляем первую половину L2

    L1.splice(L1.end(), temp2); // Добавляем вторую половину L2 в конец L1
    L2.splice(L2.end(), temp1); // Добавляем первую половину L1 в конец L2

    // Выводим итоговые списки
    cout << "Итоговый список L1:\n";
    for (const auto& elem : L1) {
        cout << elem << " ";
    }
    cout << endl;

    cout << "Итоговый список L2:\n";
    for (const auto& elem : L2) {
        cout << elem << " ";
    }
    cout << endl;
}

void task4(int K, const string& inputFile, const string& outputFile) {
    ifstream infile(inputFile);
    if (!infile) {
        cerr << "Ошибка: не удалось открыть файл " << inputFile << endl;
        return;
    }

    ofstream outfile(outputFile);
    if (!outfile) {
        cerr << "Ошибка: не удалось открыть файл " << outputFile << endl;
        return;
    }

    // Чтение слов и запись в выходной файл с фильтрацией
    istream_iterator<string> start(infile), end;  // Итераторы для чтения слов
    ostream_iterator<string> output_it(outfile, "\n");  // Итератор для записи слов

    remove_copy_if(start, end, output_it, [K](const string& word) {
        return word.length() > K;  // Условие фильтрации
    });
}

void task5(deque<int>& D) {
    // Используем обратный итератор для поиска последнего нуля
    auto it = find(D.rbegin(), D.rend(), 0);

    // Проверяем, найден ли нулевой элемент
    if (it != D.rend()) {
        // Удаляем элемент, преобразовав обратно в обычный итератор
        D.erase(--it.base()); // Удаляем элемент, предшествующий base() итератора
    }
}

deque<int> generateDeque(int size) {
    deque<int> D;
    D.push_back(0); // Обязательно добавляем 0 в начало

    // Генерируем случайные числа от 0 до 10
    for (int i = 1; i < size; ++i) {
        D.push_back(rand() % 11); // Случайное число от 0 до 10
    }

    return D;
}

void task6(vector<int>& V1, vector<int>& V2, int A, int B) {
    // Заполнение V1 с использованием fill_n и inserter/back_inserter
    fill_n(inserter(V1, V1.begin()), 5, A); // Вставляем A в начало
    fill_n(back_inserter(V1), 5, B); // Вставляем B в конец

    // Заполнение V2 с использованием функции-члена insert
    V2.insert(V2.begin(), 5, A); // Вставляем A в начало
    V2.insert(V2.end(), 5, B);}

vector<int> generateSortedVector(int size) {
    vector<int> V(size);
    // Заполняем первую половину отсортированными числами
    for (int i = 0; i < size / 2; ++i) {
        V[i] = i; // Пример: 0, 1, 2, ..., size/2 - 1
    }
    // Заполняем вторую половину случайными числами
    for (int i = size / 2; i < size; ++i) {
        V[i] = rand() % 100; // Случайные числа от 0 до 99
    }
    return V;}

void task7(vector<int>& V) {
    // Сортируем вторую половину
    sort(V.begin() + V.size() / 2, V.end());
    cout << "Вектор после сортировки второй половины: ";
    for (const auto& num : V) {
        cout << num << " ";
    }
    cout << endl;

    // Сливаем обе половины
    inplace_merge(V.begin(), V.begin() + V.size() / 2, V.end());
    cout << "Вектор после слияния: ";
    for (const auto& num : V) {
        cout << num << " ";
    }
    cout << endl;
}

void task8(int numElements, double minValue, double maxValue) {
    // Создаем список L и заполняем его случайными числами
    list<double> L;
    for (int i = 0; i < numElements; ++i) {
        double randomValue = minValue + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (maxValue - minValue)));
        L.push_back(randomValue);
    }

    // Вектор V для хранения средних значений
    vector<double> V;

    // Используем adjacent_difference для вычисления разностей
    adjacent_difference(L.begin(), L.end(), back_inserter(V), [](double a, double b) {
        return (a + b) / 2; // Функциональный объект для среднего арифметического
    });
    V.erase(V.begin());

    // Выводим исходный список
    cout << "Исходный список L: ";
    for (const auto& num : L) {
        cout << num << " ";
    }
    cout << endl;

    // Выводим полученные средние значения
    cout << "Полученный вектор средних значений: ";
    for (const auto& num : V) {
        cout << num << " ";
    }
    cout << endl;
}

void task9() {
    srand(static_cast<unsigned>(time(0)));

    int N;
    cout << "Введите количество векторов (N > 0): ";
    cin >> N;

    if (N <= 0) {
        cerr << "Количество векторов должно быть больше 0." << endl;
        return;
    }

    int sizeV0;
    cout << "Введите размер вектора V0: ";
    cin >> sizeV0;

    if (sizeV0 <= 0) {
        cerr << "Размер вектора V0 должен быть больше 0." << endl;
        return;
    }

    // Создаем и заполняем вектор V0 случайными числами
    vector<int> V0(sizeV0);
    for (int& num : V0) {
        num = rand() % 10 + 1; // Случайные числа от 1 до 10
    }

    // Создаем векторы V1, ..., VN
    vector<vector<int>> vectors(N);
    for (int i = 0; i < N; ++i) {
        // Генерируем случайный размер вектора от sizeV0 до 100
        int sizeVi = rand() % (100 - sizeV0 + 1) + sizeV0; // Случайный размер от sizeV0 до 100
        vectors[i].resize(sizeVi);

        // Заполняем текущий вектор случайными числами
        for (int& num : vectors[i]) {
            num = rand() % 10 + 1; // Случайные числа от 1 до 10
        }
    }

    // Выводим вектор V0
    cout << "Вектор V0: ";
    for (const auto& num : V0) {
        cout << num << " ";
    }
    cout << endl;

    // Выводим векторы V1, ..., VN
    for (int i = 0; i < N; ++i) {
        cout << "Вектор V" << (i + 1) << ": ";
        for (const auto& num : vectors[i]) {
            cout << num << " ";
        }
        cout << endl;
    }

    // Создаем множество уникальных элементов из V0
    set<int> uniqueV0(V0.begin(), V0.end());

    int count = 0; // Счетчик векторов, содержащих все элементы из V0

    // Проверяем каждый вектор
    for (const auto& v : vectors) {
        set<int> uniqueVi(v.begin(), v.end()); // Уникальные элементы текущего вектора
        // Проверяем, содержит ли текущий вектор все элементы из uniqueV0
        if (includes(uniqueVi.begin(), uniqueVi.end(), uniqueV0.begin(), uniqueV0.end())) {
            count++;
        }
    }

    // Выводим результат
    cout << "Количество векторов, содержащих все элементы из V0: " << count << endl;
}

void task10() {
    // Заполнение вектора V названиями алкогольных напитков
    vector<string> V = {
        "VODKA", "VERMOUTH", "WHISKEY", "WINE",
        "RUM", "RUM", "GIN", "GIN",
        "TEQUILA", "BRANDY", "CIDER", "COGNAC",
        "BEER", "ALE", "MEAD", "SPIRITS"
    };

    // Отображение для хранения суммарной длины слов по первой букве
    map<char, int> M;
    cout << "Список совершенно случайных английских слов:" << endl;
    for (const auto& drink : V) {
        cout << drink << endl; // Выводим каждый напиток
    }
    cout << endl;
    // Заполнение отображения M
    for (auto it = V.begin(); it != V.end(); ++it) {
        M[(*it)[0]] += it->size(); // Суммируем длины слов по первой букве
    }

    // Сортировка ключей отображения M и вывод результата
    for (auto it = M.begin(); it != M.end(); ++it) {
        cout << it->first << ": " << it->second << endl; // Выводим буквы и их суммарные длины
    }
}

int main(){

    system("chcp 65001");
    int tasknum;
    int k;
    string inputFile, outputFile;
    srand(static_cast<unsigned>(time(0)));
    int size;
    deque<int> D;
    int A, B;
    vector<int> V1;
    vector<int> V2;
    vector<int> V;
    int numElements;
    double minValue, maxValue;


    cout << "Введите номер задания. Для окончание работы программы введите 0." << endl;
    cin >> tasknum;
    while (tasknum != 0) {
        switch (tasknum) {
            case 1:
                task1();
                break;
            case 2:
                task2();
                break;
            case 3:
                task3();
                break;
            case 4:
                cout << "Введите значение K (> 0): ";
                k = safeInputK();

                cout << "Введите имя входного файла (name1): ";
                cin >> inputFile;
                cout << "Введите имя выходного файла (name2): ";
                cin >> outputFile;
                task4(k, inputFile, outputFile);
                break;
            case 5:
                cout << "Введите размер дека (больше 1): ";
                cin >> size;

            // Проверка на допустимый размер
                if (size <= 1) {
                    cerr << "Размер дека должен быть больше 1." << endl;
                    return 1;}

            D = generateDeque(size);
            cout << "Дек до удаления последнего нулевого элемента: ";
            for (const auto& num : D) {
                cout << num << " ";
            }
            cout << endl;

            task5(D);

            cout << "Дек после удаления последнего нулевого элемента: ";
            for (const auto& num : D) {
                cout << num << " ";
            }
            cout << endl;
                break;
            case 6:
                cout << "Введите значение A: ";
            cin >> A;

            cout << "Введите значение B: ";
            cin >> B;
            task6(V1, V2, A, B);
            cout << "Вектор V1: ";
            for (const auto& num : V1) {
                cout << num << " ";
            }
            cout << endl;

            cout << "Вектор V2: ";
            for (const auto& num : V2) {
                cout << num << " ";
            }
            cout << endl;

                break;
            case 7:
                cout << "Введите четное число для размера вектора: ";
            cin >> size;
            if (size % 2 != 0 || size <= 0) {
                cerr << "Размер вектора должен быть четным и больше 0." << endl;
                return 1;
            }
            V = generateSortedVector(size);
            cout << "Исходный вектор: ";
            for (const auto& num : V) {
                cout << num << " ";
            }
            cout << endl;
            task7(V);
                break;
            case 8:
                cout << "Введите количество элементов в списке: ";
            cin >> numElements;

            // Проверка на положительное количество элементов
            if (numElements <= 1) {
                cerr << "Количество элементов должно быть больше 1." << endl;
                return 1;
            }
            cout << "Введите минимальное значение: ";
            cin >> minValue;
            cout << "Введите максимальное значение: ";
            cin >> maxValue;
            task8(numElements, minValue, maxValue);
                break;
            case 9:
                task9();
                break;
            case 10:
                task10();
                break;
            default:
                break;
        }
        cout << "Введите номер следующего задания. Для окончание работы программы введите 0." << endl;
        cin >> tasknum;
    }
    return 0;
}