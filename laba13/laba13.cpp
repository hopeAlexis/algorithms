#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>    //библиотека для хеш-таблиц

int hashFunction(const std::string& key, int n) //функция, которая создаёт ключи для хеш-таблицы
{
    int sum = 0;
    for (int i = 0; i < key.length(); i++)
    {
        sum += key[i];
    }
    return sum % n;
}

int countLines(const std::string& key)
{
    std::ifstream F(key, std::ios::in); //экземлпяр класса ifstream
    int count = 0;
    char temp[10000];

    while (!F.eof())
    {
        count++;
        F.getline(temp, 10000);
    }

    F.close();
    return count;
}

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    if (!fin)
    {
        std::cout << "File is not open.";
        return 1;   //завершаем программу
    }

    std::unordered_map<int, std::string> hashTable;
    int n = countLines("input.txt");

    std::string line;

    while (std::getline(fin, line)) //getline позволяет нам считать строку с пробелами
    {
        int key = hashFunction(line, n);
        bool fl = true;
        while (fl)
        {
            if (hashTable[key].empty()) //ищем "свободную" позицию в таблице
            {
                hashTable[key] = line;
                fl = false;
            }
            else   //если позиция уже занята
            {
                if (key < (n - 1))  //проверяем следующую позицию
                    key += 1;
                else
                    key = 0;    //но не выходим за пределы возможных ключей
            }
        }
    }

    for (const auto& entry : hashTable)
    {
        fout << entry.first << ": " << entry.second << "\n";
    }
    std::cout << "Hash table is now written in output.txt";

    fin.close();
    fout.close();
    return 0;
}
