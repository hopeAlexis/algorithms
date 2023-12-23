#include <iostream>
#include <algorithm>
#include <vector>

int mas[9] = { 31, 14, 12, 21, 15, 7, 120, 6, 1 };
int size = 9;

class Sortings  //здесь 9, 10 и 12 лабы
{
public:
    //#9
    //сложность сортировки - O(n log n)
    //процедура создани€ двоичной кучи
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

        //провер€ем, чтобы самый большой элемент был корнем
        if (biggest != i) 
        {
            std::swap(arr[i], arr[biggest]);
            heapCreation(arr, n, biggest);  //рекурси€, создаЄм новую кучу с новым корневым узлом
        }
    }

    //сама пирамидальна€ сортировка (сортировка кучей)
    void pyramidSort(int arr[], int n)
    {
        for (int i = n / 2 - 1; i >= 0; i--)
        {
            heapCreation(arr, n, i);    //создаЄм кучу
        }

        for (int i = n - 1; i >= 0; i--)
        {
            std::swap(arr[0], arr[i]);  //ставим корень в конец
            heapCreation(arr, i, 0);    //и тогда создаЄм кучу поменьше
        }
    }

    ///#10
    //сложность сортировки - O(n log n)

    //функци€ дл€ сли€ни€ двух отсортированных массивов
    void merge(int arr[], int l, int r)
    {
        int m, i, j, k;
        m = (l + r) / 2;
        int n1 = m - l + 1;
        int n2 = r - m;

        //создаем временные массивы
        std::vector<int> left(n1), right(n2);
        
        //копируем данные во временные массивы
        for (i = 0; i < n1; i++)
            left[i] = arr[l + i]; 
        for (j = 0; j < n2; j++)
            right[j] = arr[m + 1 + j];

        //сли€ние временных массивов
        i = 0;  //индекс первого подмассива
        j = 0;  //индекс второго подмассива
        k = l;  //индекс объединенного подмассива
        while (i < n1 && j < n2)
        {
            if (left[i] <= right[j])
            {
                arr[k] = left[i];
                i++;
            }
            else
            {
                arr[k] = right[j];
                j++;
            }
            k++;
        }
        //копирование оставшихс€ элементов left[]
        while (i < n1) {
            arr[k] = left[i];
            i++;
            k++;
        }
        //копирование оставшихс€ элементов right[]
        while (j < n2)
        {
            arr[k] = right[j];
            j++;
            k++;
        }
    }

    //основна€ функци€ сортировки
    void mergeSort(int arr[], int l, int r)
    {
        if (l < r)
        {
            int m = l + (r - l) / 2;    //серединка
            //сортируем первую и вторую половины
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
            //объедин€ем
            merge(arr, l, r);
        }
    }

    //#12
    //cложность сортировки - O(n log n)
    void externalSort(int* arr, int size, int chunkSize)
    {
        int numberOfChunks = (size + chunkSize - 1) / chunkSize;    //на сколько частей делим массив
        int* result = new int[size];    //временный массив дл€ отсортированных элементов
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
                //элемент чанка меньше его границы и его значение меньше значени€ минимального элемента
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
    test.pyramidSort(mas, size);
    //test.mergeSort(mas, 0, 8);
    //test.externalSort(mas, size, 2);

    std::cout << "Sorted array: \n";
    for (int i = 0; i < size; i++)
    {
        std::cout << mas[i] << " ";
    }

    return 0;
}