#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <queue>
#include <chrono>

// Функции сортировки

// Пузырьковая сортировка
void bubbleSort(std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        for (size_t j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Сортировка выбором
void selectionSort(std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        size_t minIdx = i;
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        std::swap(arr[i], arr[minIdx]);
    }
}

// Сортировка вставками
void insertionSort(std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        size_t j = i;
        while (j > 0 && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = key;
    }
}

// Вспомогательная функция для слияния массивов
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int i = 0; i < n2; ++i) R[i] = arr[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Сортировка слиянием
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Вспомогательная функция для разбиения массива
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Быстрая сортировка
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Вспомогательная функция для "просеивания" кучи
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Пирамидальная сортировка (Heap Sort)
void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) heapify(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Сортировка Шелла
void shellSort(std::vector<int>& arr) {
    for (int gap = arr.size() / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < arr.size(); ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Сортировка расчёской
void combSort(std::vector<int>& arr) {
    int gap = arr.size();
    bool swapped = true;
    while (gap != 1 || swapped) {
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;
        swapped = false;
        for (size_t i = 0; i < arr.size() - gap; ++i) {
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

// Сортировка подсчётом
void countingSort(std::vector<int>& arr) {
    int max = *std::max_element(arr.begin(), arr.end());
    int min = *std::min_element(arr.begin(), arr.end());
    int range = max - min + 1;
    std::vector<int> count(range), output(arr.size());
    for (int i = 0; i < arr.size(); ++i) count[arr[i] - min]++;
    for (int i = 1; i < count.size(); ++i) count[i] += count[i - 1];
    for (int i = arr.size() - 1; i >= 0; --i) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }
    for (int i = 0; i < arr.size(); ++i) arr[i] = output[i];
}

// Поразрядная сортировка
void radixSort(std::vector<int>& arr) {
    int max = *std::max_element(arr.begin(), arr.end());
    for (int exp = 1; max / exp > 0; exp *= 10) {
        std::vector<int> output(arr.size());
        int count[10] = { 0 };
        for (int i = 0; i < arr.size(); i++) count[(arr[i] / exp) % 10]++;
        for (int i = 1; i < 10; i++) count[i] += count[i - 1];
        for (int i = arr.size() - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
        for (int i = 0; i < arr.size(); i++) arr[i] = output[i];
    }
}

// Шаблонная функция для измерения времени сортировки и вывода результата
template <typename SortFunc>
void measureAndPrintTime(SortFunc sortFunction, std::vector<int> arr, const std::string& name) {
    auto start = std::chrono::high_resolution_clock::now(); // Начало замера времени
    sortFunction(arr); // Выполнение сортировки
    auto end = std::chrono::high_resolution_clock::now(); // Конец замера времени
    std::chrono::duration<double, std::milli> duration = end - start; // Вычисление длительности
    std::cout << name << ": " << duration.count() << " ms\n"; // Вывод времени выполнения

    // Печать отсортированного массива
    std::cout << name << " Sorted: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl << std::endl;
}

int main() {
    // Создаем генератор случайных чисел с использованием random_device для начальной инициализации
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 1000);

    // Генерируем 10 случайных чисел
    std::vector<int> arr(15);
    for (int& x : arr) {
        x = distrib(gen);
    }

    // Печатаем исходный массив
    std::cout << "Original Array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl << std::endl;

    // Копируем массив для различных методов сортировки
    std::vector<int> arrBubble = arr;
    std::vector<int> arrSelection = arr;
    std::vector<int> arrInsertion = arr;
    std::vector<int> arrMerge = arr;
    std::vector<int> arrQuick = arr;
    std::vector<int> arrHeap = arr;
    std::vector<int> arrShell = arr;
    std::vector<int> arrComb = arr;
    std::vector<int> arrCounting = arr;
    std::vector<int> arrRadix = arr;

    // Измеряем и выводим время выполнения для различных методов сортировки
    measureAndPrintTime(bubbleSort, arrBubble, "Bubble Sort");
    measureAndPrintTime(selectionSort, arrSelection, "Selection Sort");
    measureAndPrintTime(insertionSort, arrInsertion, "Insertion Sort");
    measureAndPrintTime([&](std::vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }, arrMerge, "Merge Sort");
    measureAndPrintTime([&](std::vector<int>& arr) { quickSort(arr, 0, arr.size() - 1); }, arrQuick, "Quick Sort");
    measureAndPrintTime(heapSort, arrHeap, "Heap Sort");
    measureAndPrintTime(shellSort, arrShell, "Shell Sort");
    measureAndPrintTime(combSort, arrComb, "Comb Sort");
    measureAndPrintTime(countingSort, arrCounting, "Counting Sort");
    measureAndPrintTime(radixSort, arrRadix, "Radix Sort");

    return 0;
}
