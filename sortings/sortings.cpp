#include <iostream>
#include <algorithm>
#include <vector>

int mas[9] = { 31, 14, 12, 21, 15, 7, 120, 6, 1 };
int size = 9;

class Sortings  //����� 9, 10 � 12 ����
{
public:
    //#9
    //��������� ���������� - O(n log n)
    //��������� �������� �������� ����
    void heapCreation(int arr[], int n, int i)
    {
        int biggest = i; //������ ��������� ����
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

        //���������, ����� ����� ������� ������� ��� ������
        if (biggest != i) 
        {
            std::swap(arr[i], arr[biggest]);
            heapCreation(arr, n, biggest);  //��������, ������ ����� ���� � ����� �������� �����
        }
    }

    //���� ������������� ���������� (���������� �����)
    void pyramidSort(int arr[], int n)
    {
        for (int i = n / 2 - 1; i >= 0; i--)
        {
            heapCreation(arr, n, i);    //������ ����
        }

        for (int i = n - 1; i >= 0; i--)
        {
            std::swap(arr[0], arr[i]);  //������ ������ � �����
            heapCreation(arr, i, 0);    //� ����� ������ ���� ��������
        }
    }

    ///#10
    //��������� ���������� - O(n log n)

    //������� ��� ������� ���� ��������������� ��������
    void merge(int arr[], int l, int r)
    {
        int m, i, j, k;
        m = (l + r) / 2;
        int n1 = m - l + 1;
        int n2 = r - m;

        //������� ��������� �������
        std::vector<int> left(n1), right(n2);
        
        //�������� ������ �� ��������� �������
        for (i = 0; i < n1; i++)
            left[i] = arr[l + i]; 
        for (j = 0; j < n2; j++)
            right[j] = arr[m + 1 + j];

        //������� ��������� ��������
        i = 0;  //������ ������� ����������
        j = 0;  //������ ������� ����������
        k = l;  //������ ������������� ����������
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
        //����������� ���������� ��������� left[]
        while (i < n1) {
            arr[k] = left[i];
            i++;
            k++;
        }
        //����������� ���������� ��������� right[]
        while (j < n2)
        {
            arr[k] = right[j];
            j++;
            k++;
        }
    }

    //�������� ������� ����������
    void mergeSort(int arr[], int l, int r)
    {
        if (l < r)
        {
            int m = l + (r - l) / 2;    //���������
            //��������� ������ � ������ ��������
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
            //����������
            merge(arr, l, r);
        }
    }

    //#12
    //c�������� ���������� - O(n log n)
    void externalSort(int* arr, int size, int chunkSize)
    {
        int numberOfChunks = (size + chunkSize - 1) / chunkSize;    //�� ������� ������ ����� ������
        int* result = new int[size];    //��������� ������ ��� ��������������� ���������
        int* index = new int[numberOfChunks];   //��������� ������ ��������

        //���������� ������ ����� ��� ������ ���������� ���������� �� ���������� O(n log n)
        for (int i = 0; i < size; i += chunkSize)
        {
            std::sort(arr + i, arr + std::min(i + chunkSize, size));
        }

        //������������� ������ � ������������ � �������
        for (int i = 0; i < numberOfChunks; i++)
        {
            index[i] = i * chunkSize;
        }

        for (int i = 0; i < size; i++)
        {
            int minIndex = -1;
            for (int j = 0; j < numberOfChunks; j++)
            {
                //������� ����� ������ ��� ������� � ��� �������� ������ �������� ������������ ��������
                if (index[j] < (j + 1) * chunkSize && (minIndex == -1 || arr[index[j]] < arr[index[minIndex]]))
                { 
                    minIndex = j;   //����������� ����� �������� ������� �����
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