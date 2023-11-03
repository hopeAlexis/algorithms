#include <iostream>

class Sortings
{
public:
    void bubbleSort(int arr[], int n) //#4
    {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (arr[j] > arr[j + 1]) 
                {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    void insertSort(int arr[], int n) //#5
    {
        for (int i = 1; i < n; i++)
        {
            int check = arr[i];
            int j = i - 1; //index of the element to the left
            while (j >= 0 && arr[j] > check) //as long as left element is bigger
            {
                arr[j + 1] = arr[j]; //shifting elements to the right
                j--;
            }
            arr[j + 1] = check;
        }
    }

    void selectSort(int arr[], int n) //#6
    {
        for (int i = 0; i < n - 1; i++)
        {
            int minIndex = i;
            for (int j = i + 1; j < n; j++)
            {
                if (arr[j] < arr[minIndex])
                {
                    minIndex = j;
                }
            }
            std::swap(arr[i], arr[minIndex]); //position the smallest found element where we began the check
        }
    }

    void shellaSort(int arr[], int n) //#7
    {
        for (int step = n / 2; step > 0; step /= 2) // Выбираем шаг
        {
            for (int i = step; i < n; i++) // Применяем сортировку вставками для каждого сегмента
            {
                int check = arr[i];
                int j;
                for (j = i; j >= step && arr[j - step] > check; j -= step) // Сравнивем, меняем
                {
                    arr[j] = arr[j - step];
                }
                arr[j] = check;
            }
        }
    }

    void quickSort(int arr[], int low, int high) //#11
    {
        int i = low;
        int j = high;
        int pivot = arr[(i + j) / 2];
        int temp;

        while (i <= j)
        {
            while (arr[i] < pivot)
                i++;
            while (arr[j] > pivot)
                j--;
            if (i <= j)
            {
                std::swap(arr[i], arr[j]);
                i++;
                j--;
            }
        }
        if (j > low)
            quickSort(arr, low, j);
        if (i < high)
            quickSort(arr, i, high);
    }
};


int main()
{
    int const size = 6;
    int mas[size] = { 31, 14, 12, 21, 15 };

    Sortings test;

    //test.bubbleSort(mas, size);
    //test.insertSort(mas, size);
    //test.selectSort(mas, size);
    test.shellaSort(mas, size);
    //test.selectSort(mas, 0, n-1);

    std::cout << "Sorted array: \n";
    for (int i = 0; i < size; i++)
    {
        std::cout << mas[i] << " ";
    }

    return 0;
}