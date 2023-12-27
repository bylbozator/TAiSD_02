#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>
#include <algorithm>
#include <windows.h>
using namespace std;

bool hasDigits(const string& str) {
    return any_of(str.begin(), str.end(), ::isdigit);
}
// Функция для удаления первого и последнего слова в строке

string removeFirstAndLastWord(const string& str)
{
    string result = str;

    if (hasDigits(str)) {
        return("Входная строка содержит цифры. Инициализируется выход.");
    }
    // Проверка на количество слов
    size_t spaceCount = count(str.begin(), str.end(), ' ');
    if (spaceCount < 2) {
        return "Ошибка: введено меньше трёх слов. Инициализируется выход.";
    }
    // Удаление первого слова 
    size_t firstSpace = result.find(" ");
    size_t punctuation = result.find_first_of(".,;:!?");
    if (firstSpace != string::npos && (punctuation == string::npos || firstSpace < punctuation))
    {
        result = result.substr(firstSpace + 1);
    }

    // Удаление последнего слова 
    size_t lastSpace = result.find_last_of(" ");
    size_t lastPunctuation = result.find_last_of(".!?");
    if (lastSpace != string::npos && (lastPunctuation == string::npos || lastSpace > lastPunctuation))
    {
        result = result.substr(0, lastSpace);
    }

    return result;
}

// Функция для генерации случайного числа
int generateRandomNumber() {
    return rand() % 100; // Генерируем числа от 0 до 99
}

    // Функция для заполнения массива вручную
void fillArrayManually(char** arr, int rows, int* lengths) {
    for (int i = 0; i < rows; i++) {
        char temp[100];
        cout << "Введите строку " << i + 1 << ": ";
        cin.ignore(); // Очищаем буфер ввода, чтобы getline корректно работал
        cin.getline(temp, 100); // Вводим строку во временный массив
        lengths[i] = strlen(temp); // Запоминаем длину строки
        arr[i] = new char[lengths[i] + 1]; // Выделяем достаточно памяти под строку
        strcpy_s(arr[i], lengths[i] + 1, temp); // Копируем строку в массив arr
    }
}


        // Функция для заполнения массива с помощью ДСЧ
void fillArrayWithRandom(char** arr, int rows, int* lengths) {
    srand(static_cast<unsigned int>(std::time(nullptr))); // Инициализируем генератор случайных чисел  
    for (int i = 0; i < rows; i++) {
        // Генерируем несколько случайных чисел и объединяем их в строку, разделенную пробелами
        std::string str;
        int count = rand() % 5 + 1; // Генерируем от 1 до 5 чисел в строке
        for (int j = 0; j < count; j++) {
            int num = rand() % 100; // Случайное число от 0 до 99
            str += std::to_string(num) + " "; // Преобразуем число в строку и добавляем пробел
        }
        str.pop_back(); // Удаляем последний пробел

        lengths[i] = str.length(); // Запоминаем длину строки  
        arr[i] = new char[lengths[i] + 1]; // Выделяем память под строку  
        strcpy_s(arr[i], lengths[i] + 1, str.c_str()); // Копируем строку в массив arr  
    }
}



// Функция для вывода массива на печать
void printArray(char** arr, int rows, int* lengths) {
    for (int i = 0; i < rows; i++) {
        cout << "Строка " << i + 1 << ": " << arr[i] << endl;
    }
}

// Функция для сортировки строк массива по убыванию кодов символов
void sortArray(char** arr, int rows, int* lengths) {
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < rows - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) < 0) { // Сравниваем строки
                // Меняем строки местами
                char* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                // Меняем длины строк местами
                int len = lengths[j];
                lengths[j] = lengths[j + 1];
                lengths[j + 1] = len;
            }
        }
    }
}

int main() {
    setlocale(0, "");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand(time(0)); // Для инициализации генератора случайных чисел
    
        int choice;
        cout << "Выберите действие (0 - удалить первое и последнее слово из строки, 1 - заполнить и отсортировать массив строк): ";
        cin >> choice;

        if (choice == 0) {
            string str;
            cout << "Введите строку: ";
            cin.ignore();
            getline(cin, str);
            cout << removeFirstAndLastWord(str) << endl;
        }
        else if (choice == 1) {
            int rows;
            cout << "Введите количество строк: ";
            cin >> rows;
            char** arr = new char* [rows];
            int* lengths = new int[rows];

            cout << "Выберите способ заполнения массива:" << endl;
            cout << "1. Вручную" << endl;
            cout << "2. Случайным образом" << endl;
            cin >> choice;

            if (choice == 1) {
                fillArrayManually(arr, rows, lengths);

            }
            else if (choice == 2) {
                fillArrayWithRandom(arr, rows, lengths);

                printArray(arr, rows, lengths);
            }
            cout << "Отсортированнный массив: " << endl;
            sortArray(arr, rows, lengths);
            printArray(arr, rows, lengths);

            for (int i = 0; i < rows; i++) {
                delete[] arr[i]; // Освобождаем память для каждой строки
            }

            delete[] arr; // Освобождаем память для массива указателей на строки
            delete[] lengths; // Освобождаем память для массива длин строк
        }
        else cout<< "Ошибка ввода. Выход." << endl;
       
        return 1;
    }
        

    

