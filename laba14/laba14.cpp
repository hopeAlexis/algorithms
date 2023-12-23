#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>

const int n = 5;

class HashTable
{
private:
    int hashFunction(const std::string& line)
    {
        int sum = 0;
        for (char ch : line)
        {
            sum += ch;
        }
        return sum % n;
    }

    std::vector<std::list<std::string>> table;  //вектор листов из строк

public:
    HashTable() : table(n) {}

    void insert(const std::string& line)
    {
        int key = hashFunction(line);
        bool fl = true;
        while (fl)
        {
            if (table[key].empty()) //ищем "свободную" позицию в таблице
            {
                table[key].push_back(line);
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

    void writeOut(const std::string& filename)
    {
        std::ofstream outputFile(filename);
        if (!outputFile.is_open())
        {
            std::cerr << "File is not open.";
            return;
        }

        for (int i = 0; i < n; ++i)
        {
            for (const auto& line : table[i])
            {
                outputFile << i << ": " << line << "\n";
            }
        }
        outputFile.close();
    }
};

int main()
{
    std::string inputFileName = "input.txt";
    std::string outputFileName = "output.txt";
    HashTable hashTable;
    std::ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) 
    {
        std::cerr << "File is not open.";
        return 1;
    }

    std::string line;
    while (inputFile >> line)
    {
        hashTable.insert(line);
    }
    inputFile.close();

    hashTable.writeOut(outputFileName);
    std::cout << "Hash-table is now in " << outputFileName;
    return 0;
}