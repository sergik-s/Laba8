#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <stdexcept>


void quickSort(double* arr, int32_t left, int32_t right, bool ascending);
void insertionSort(double* arr, int32_t size, bool ascending);
void selectionSort(double* arr, int32_t size, bool ascending);
void mergeSort(double* arr, int32_t left, int32_t right, bool ascending);
void merge(double* arr, int32_t left, int32_t mid, int32_t right, bool ascending);
void improvedBubbleSort(double* arr, int32_t size, bool ascending);
void qsortByFractionalDigits(double* arr, int32_t size);
int32_t countFractionalDigits(double num);
double* readArrayFromFile(const char* filename, int32_t* outSize);
void writeArrayToFile(const char* filename, double* arr, int32_t size);
double* readArrayFromConsole(int32_t* outSize);
void printArray(double* arr, int32_t size);
void sortArray(double* arr, int32_t size);
void freeArray(double* arr);

struct Student {
    char firstName[50];
    char lastName[50];
    int32_t course;
    char group[20];
    int32_t grades[5];
    double average;
};

Student* readStudentsFromConsole(int32_t* count);
void calculateAverages(Student* students, int32_t count);
void sortStudentsByAverage(Student* students, int32_t count);
void printStudents(Student* students, int32_t count);
void freeStudents(Student* students);

#endif
