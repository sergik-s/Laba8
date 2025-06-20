#include "header.h"

void quickSort(double* arr, int32_t left, int32_t right, bool ascending) {
    if (left >= right) return;
    
    double pivot = arr[(left + right) / 2];
    int32_t i = left, j = right;
    
    while (i <= j) {
        if (ascending) {
            while (arr[i] < pivot) i++;
            while (arr[j] > pivot) j--;
        } else {
            while (arr[i] > pivot) i++;
            while (arr[j] < pivot) j--;
        }
        
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    
    quickSort(arr, left, j, ascending);
    quickSort(arr, i, right, ascending);
}

void insertionSort(double* arr, int32_t size, bool ascending) {
    for (int32_t i = 1; i < size; i++) {
        double key = arr[i];
        int32_t j = i - 1;
        
        if (ascending) {
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
        } else {
            while (j >= 0 && arr[j] < key) {
                arr[j + 1] = arr[j];
                j--;
            }
        }
        
        arr[j + 1] = key;
    }
}

void selectionSort(double* arr, int32_t size, bool ascending) {
    for (int32_t i = 0; i < size - 1; i++) {
        int32_t extremaIndex = i;
        for (int32_t j = i + 1; j < size; j++) {
            if (ascending ? (arr[j] < arr[extremaIndex]) : (arr[j] > arr[extremaIndex])) {
                extremaIndex = j;
            }
        }
        std::swap(arr[i], arr[extremaIndex]);
    }
}

void merge(double* arr, int32_t left, int32_t mid, int32_t right, bool ascending) {
    int32_t n1 = mid - left + 1;
    int32_t n2 = right - mid;

    double* L = new double[n1];
    double* R = new double[n2];

    for (int32_t i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int32_t j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int32_t i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (ascending ? (L[i] <= R[j]) : (L[i] >= R[j])) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(double* arr, int32_t left, int32_t right, bool ascending) {
    if (left >= right) return;

    int32_t mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, ascending);
    mergeSort(arr, mid + 1, right, ascending);
    merge(arr, left, mid, right, ascending);
}

void improvedBubbleSort(double* arr, int32_t size, bool ascending) {
    bool swapped;
    for (int32_t i = 0; i < size - 1; i++) {
        swapped = false;
        for (int32_t j = 0; j < size - i - 1; j++) {
            if (ascending ? (arr[j] > arr[j + 1]) : (arr[j] < arr[j + 1])) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

int32_t countFractionalDigits(double num) {
    const double eps = 1e-9;
    if (fabs(num - round(num)) < eps) return 0;
    
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%.15f", num);
    
    char* dot = strchr(buffer, '.');
    if (!dot) return 0;
    
    char* end = buffer + strlen(buffer) - 1;
    while (end > dot && *end == '0') end--;
    
    return end - dot;
}

void qsortByFractionalDigits(double* arr, int32_t size) {
    struct Pair { double num; int32_t digits; };
    Pair* pairs = new Pair[size];
    
    for (int32_t i = 0; i < size; i++) {
        pairs[i].num = arr[i];
        pairs[i].digits = countFractionalDigits(arr[i]);
    }
    
    for (int32_t i = 0; i < size - 1; i++) {
        for (int32_t j = 0; j < size - i - 1; j++) {
            if (pairs[j].digits < pairs[j + 1].digits) {
                std::swap(pairs[j], pairs[j + 1]);
            }
        }
    }
    
    for (int32_t i = 0; i < size; i++) {
        arr[i] = pairs[i].num;
    }
    
    delete[] pairs;
}

double* readArrayFromFile(const char* filename, int32_t* outSize) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл " + std::string(filename));
    }

    int32_t count = 0;
    double temp;
    while (file >> temp) {
        count++;
    }

    if (count == 0) {
        throw std::runtime_error("Файл пуст или содержит некорректные данные");
    }

    file.clear();
    file.seekg(0);

    double* arr = new double[count];
    for (int32_t i = 0; i < count; i++) {
        if (!(file >> arr[i])) {
            delete[] arr;
            throw std::runtime_error("Ошибка чтения данных из файла");
        }
    }

    *outSize = count;
    file.close();
    return arr;
}

void writeArrayToFile(const char* filename, double* arr, int32_t size) {
    if (size <= 0) {
        throw std::invalid_argument("Размер массива должен быть положительным");
    }

    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Не удалось создать файл " + std::string(filename));
    }

    for (int32_t i = 0; i < size; i++) {
        if (!(file << arr[i] << " ")) {
            throw std::runtime_error("Ошибка записи в файл");
        }
    }

    file.close();
}

double* readArrayFromConsole(int32_t* outSize) {
    std::cout << "Введите количество элементов: ";
    if (!(std::cin >> *outSize) || *outSize <= 0) {
        throw std::invalid_argument("Некорректное количество элементов");
    }

    double* arr = new double[*outSize];
    std::cout << "Введите элементы массива:\n";
    for (int32_t i = 0; i < *outSize; i++) {
        if (!(std::cin >> arr[i])) {
            delete[] arr;
            throw std::invalid_argument("Некорректный ввод элемента массива");
        }
    }

    return arr;
}

void printArray(double* arr, int32_t size) {
    for (int32_t i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

void sortArray(double* arr, int32_t size) {
    int32_t sortType, order;
    
    std::cout << "Выберите тип сортировки:\n";
    std::cout << "1 - Быстрая сортировка\n";
    std::cout << "2 - Сортировка вставками\n";
    std::cout << "3 - Сортировка выбором\n";
    std::cout << "4 - Сортировка слиянием\n";
    std::cout << "5 - Улучшенная сортировка пузырьком\n";
    std::cout << "6 - QSort по убыванию количества цифр в дробной части\n";
    if (!(std::cin >> sortType) || sortType < 1 || sortType > 6) {
        throw std::invalid_argument("Некорректный выбор сортировки");
    }
    
    if (sortType != 6) {
        std::cout << "Выберите порядок сортировки:\n";
        std::cout << "1 - По возрастанию\n";
        std::cout << "2 - По убыванию\n";
        if (!(std::cin >> order) || (order != 1 && order != 2)) {
            throw std::invalid_argument("Некорректный порядок сортировки");
        }
    }
    
    bool ascending = (sortType == 6) ? false : (order == 1);
    
    switch(sortType) {
        case 1: quickSort(arr, 0, size - 1, ascending); break;
        case 2: insertionSort(arr, size, ascending); break;
        case 3: selectionSort(arr, size, ascending); break;
        case 4: mergeSort(arr, 0, size - 1, ascending); break;
        case 5: improvedBubbleSort(arr, size, ascending); break;
        case 6: qsortByFractionalDigits(arr, size); break;
    }
}

void freeArray(double* arr) {
    delete[] arr;
}

Student* readStudentsFromConsole(int32_t* count) {
    std::cout << "Введите количество студентов: ";
    if (!(std::cin >> *count) || *count <= 0) {
        throw std::invalid_argument("Некорректное количество студентов");
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    Student* students = new Student[*count];
    
    for (int32_t i = 0; i < *count; i++) {
        std::cout << "\nСтудент #" << i + 1 << ":\n";
        
        std::cout << "Имя: ";
        std::cin.getline(students[i].firstName, 50);
        
        std::cout << "Фамилия: ";
        std::cin.getline(students[i].lastName, 50);
        
        std::cout << "Курс: ";
        if (!(std::cin >> students[i].course) || students[i].course <= 0) {
            delete[] students;
            throw std::invalid_argument("Некорректный номер курса");
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "Группа: ";
        std::cin.getline(students[i].group, 20);
        
        std::cout << "5 оценок: ";
        for (int32_t j = 0; j < 5; j++) {
            if (!(std::cin >> students[i].grades[j]) || students[i].grades[j] < 1 || students[i].grades[j] > 5) {
                delete[] students;
                throw std::invalid_argument("Некорректная оценка");
            }
        }
        std::cin.ignore();
    }
    
    return students;
}

void calculateAverages(Student* students, int32_t count) {
    for (int32_t i = 0; i < count; i++) {
        double sum = 0;
        for (int32_t j = 0; j < 5; j++) {
            sum += students[i].grades[j];
        }
        students[i].average = sum / 5;
    }
}

void sortStudentsByAverage(Student* students, int32_t count) {
    for (int32_t i = 0; i < count - 1; i++) {
        for (int32_t j = 0; j < count - i - 1; j++) {
            if (students[j].average < students[j + 1].average) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

void printStudents(Student* students, int32_t count) {
    for (int32_t i = 0; i < count; i++) {
        std::cout << students[i].lastName << " " << students[i].firstName 
                  << ", курс " << students[i].course << ", группа " << students[i].group
                  << ", средний балл: " << students[i].average << "\n";
    }
}

void freeStudents(Student* students) {
    delete[] students;
}
