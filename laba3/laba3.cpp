#include <iostream>
#include <vector>

int main()
{
    int x=15;
    std::vector<int> check = { 1 };
    int j;

    for (int i = 3; i <= x; i += 2)
    {
        j = i;
        while (j % 3 == 0)
        {
            j = j / 3;
        }
        while (j % 5 == 0)
        {
            j = j / 5;
        }
        while (j % 7 == 0)
        {
            j = j / 7;
        }
        if (j == 1)
            check.push_back(i);
    }

    for (int i = 0; i < check.size(); i++)
    {
        std::cout << check[i] << "\n";
    }
    check.clear();
    check.shrink_to_fit();
    return 0;
}