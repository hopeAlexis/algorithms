#include <iostream>
#include <algorithm>
#include <vector>

int mas[9] = { 31, 14, 12, 21, 15, 7, 120, 6, 1 };
int size = 9;

class Sortings  //здесь 9, 10 и 12 лабы
{
public:
    //#9
    //процедура создания двоичной кучи
    void heapCreation(int arr[], int n, int i)
    {
        int biggest = i; //индекс корневого узла
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[biggest]) 
        {
            biggest = left;
        }

        if (right < n && arr[right] > arr[biggest]) 
        {
            biggest = right;
        }

        //проверяем, чтобы самый большой элемент был корнем
        if (biggest != i) 
        {
            std::swap(arr[i], arr[biggest]);
            heapCreation(arr, n, biggest);  //рекурсия, создаём новую кучу с новым корневым узлом
        }
    }

    //сама пирамидальная сортировка (сортировка кучей)
    void pyramidSort(int arr[], int n)
    {
        for (int i = n / 2 - 1; i >= 0; i--)
        {
            heapCreation(arr, n, i);    //создаём кучу
        }

        for (int i = n - 1; i >= 0; i--)
        {
            std::swap(arr[0], arr[i]);  //ставим корень в конец
            heapCreation(arr, i, 0);    //и тогда создаём кучу поменьше
        }
    }

    ///#10
    //Cортировка слиянием делит большой массив на два меньших подмассива, а затем рекурсивно сортирует подмассивы.
    //Суть работы алгоритма заключается в том, что он разбивает список на две половины,
    //сортирует каждую половину отдельно, а затем объединяет их вместе в отсортированный список.
    //Этот процесс повторяется для каждой половины до тех пор, пока не будет достигнута базовая единица - список из одного элемента.
    //сложность сортировки O(n log n)

    //Функция для слияния двух отсортированных массивов
    void merge(int arr[], int l, int r)
    {
        int m, i, j, k;
        m = (l + r) / 2;
        int n1 = m - l + 1;
        int n2 = r - m;

        // Создаем временные массивы
        std::vector<int> L(n1), R(n2);
        
        // Копируем данные во временные массивы
        for (i = 0; i < n1; i++)
            L[i] = arr[l + i];  //здесь ошибка
        for (j = 0; j < n2; j++)
            R[j] = arr[m + 1 + j];

        // Слияние временных массивов обратно в arr[l..r]
        i = 0; // Индекс первого подмассива
        j = 0; // Индекс второго подмассива
        k = l; // Индекс объединенного подмассива
        while (i < n1 && j < n2)
        {
            if (L[i] <= R[j])
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        // Копирование оставшихся элементов L[], если они есть
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }
        // Копирование оставшихся элементов R[], если они есть
        while (j < n2)
        {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
    // Основная функция, которая сортирует arr[l..r] с использованием merge()
    void mergeSort(int arr[], int l, int r)
    {
        if (l < r)
        {
            // Найдем среднюю точку
            int m = l + (r - l) / 2;
            // Сортируем первую и вторую половины
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
            // Объединяем отсортированные половины
            merge(arr, l, r);
        }
    }

    //#12
    //cложность сортировки - O(n log n)
    void externalSort(int* arr, int size, int chunkSize)
    {
        int numberOfChunks = (size + chunkSize - 1) / chunkSize;    //на сколько частей делим массив
        int* result = new int[size];    //временный массив для отсортированных элементов
        int* index = new int[numberOfChunks];   //временный массив индексов

        //сортировка каждой части при помощи встроенной сортировки со сложностью O(n log n)
        for (int i = 0; i < size; i += chunkSize)
        {
            std::sort(arr + i, arr + std::min(i + chunkSize, size));
        }

        //устанавливаем индекс в соответствии с чанками
        for (int i = 0; i < numberOfChunks; i++)
        {
            index[i] = i * chunkSize;
        }

        for (int i = 0; i < size; i++)
        {
            int minIndex = -1;
            for (int j = 0; j < numberOfChunks; j++)
            {
                //элемент чанка меньше его границы и его значение меньше значения минимального элемента
                if (index[j] < (j + 1) * chunkSize && (minIndex == -1 || arr[index[j]] < arr[index[minIndex]]))
                { 
                    minIndex = j;   //присваиваем новое значение индексу чанка
                }
            }
            result[i] = arr[index[minIndex]];
            index[minIndex]++;
        }

        for (int i = 0; i < size; i++)
        {
            arr[i] = result[i];
        }
    }
};


int main()
{
    Sortings test;
    //test.pyramidSort(mas, size);
    test.mergeSort(mas, 0, 8);
    //test.externalSort(mas, size, 2);

    std::cout << "Sorted array: \n";
    for (int i = 0; i < size; i++)
    {
        std::cout << mas[i] << " ";
    }

    return 0;
}