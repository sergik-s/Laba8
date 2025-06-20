#include "header.h"

void processArrayOperations() {
    double* arr = nullptr;
    int32_t size = 0;
    int32_t choice;
    
    std::cout << "Выберите источник данных:\n";
    std::cout << "1 - Файл (вывод на консоль)\n";
    std::cout << "2 - Консоль (запись в файл)\n";
    std::cout << "3 - Файл (обработка и запись в файл)\n";
    
    if (!(std::cin >> choice) || choice < 1 || choice > 3) {
        throw std::invalid_argument("Неверный выбор источника данных");
    }
    
    char filename[256];
    switch(choice) {
        case 1: {
            std::cout << "Введите имя файла: ";
            std::cin >> filename;
            arr = readArrayFromFile(filename, &size);
            std::cout << "Исходный массив:\n";
            printArray(arr, size);
            sortArray(arr, size);
            std::cout << "Отсортированный массив:\n";
            printArray(arr, size);
            break;
        }
        case 2: {
            arr = readArrayFromConsole(&size);
            std::cout << "Введите имя файла для записи: ";
            std::cin >> filename;
            sortArray(arr, size);
            writeArrayToFile(filename, arr, size);
            std::cout << "Массив отсортирован и записан в файл.\n";
            break;
        }
        case 3: {
            std::cout << "Введите имя исходного файла: ";
            char inputFile[256];
            std::cin >> inputFile;
            arr = readArrayFromFile(inputFile, &size);
            std::cout << "Введите имя файла для записи: ";
            std::cin >> filename;
            sortArray(arr, size);
            writeArrayToFile(filename, arr, size);
            std::cout << "Массив обработан и записан в файл.\n";
            break;
        }
    }
    
    freeArray(arr);
}

void processStudentOperations() {
    int32_t studentCount = 0;
    Student* students = readStudentsFromConsole(&studentCount);
    
    calculateAverages(students, studentCount);
    sortStudentsByAverage(students, studentCount);
    
    std::cout << "\nОтсортированный список студентов:\n";
    printStudents(students, studentCount);
    
    freeStudents(students);
}

int main() {
    try {
        int32_t choice;
        std::cout << "Выберите программу:\n";
        std::cout << "1 - Сортировка массива\n";
        std::cout << "2 - Сортировка студентов\n";
        
        if (!(std::cin >> choice)) {
            throw std::runtime_error("Некорректный ввод выбора программы");
        }

        std::cin.ignore();

        if (choice == 1) {
            processArrayOperations();
        }
        else if (choice == 2) {
            processStudentOperations();
        }
        else {
            throw std::invalid_argument("Неверный выбор программы");
        }
    }
    catch(const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
        return 1;
    }
    catch(...) {
        std::cerr << "Неизвестная ошибка\n";
        return 1;
    }

    return 0;
}
