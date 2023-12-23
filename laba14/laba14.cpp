#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>

const int n = 20;

class HashTable
{
private:
    int hashFunction(const std::string& word)
    {
        int sum = 0;
        for (char ch : word)
        {
            sum += ch;
        }
        return sum % n;
    }

    std::vector<std::list<std::string>> table;  //������ ������ �� �����

public:
    HashTable() : table(n) {}
    //��������� ������ (�����) � ���-�������.
    void insert(const std::string& word)
    {
        int index = hashFunction(word);
        table[index].push_back(word);
    }

    void writeToFile(const std::string& filename)
    {
        std::ofstream outputFile(filename);
        if (!outputFile.is_open())
        {
            std::cerr << "File is not open.";
            return;
        }
        for (int i = 0; i < n; ++i)
        {
            for (const auto& word : table[i])
            {
                outputFile << i << ": " << word << std::endl;
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
    if (!inputFile.is_open()) {
        std::cerr << "File is not open.";
        return 1;
    }
    std::string word;
    while (inputFile >> word)
    {
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end()); //������� ����� ���������� �� �����
        hashTable.insert(word);
    }
    inputFile.close();
    // ������ � ����
    hashTable.writeToFile(outputFileName);
    std::cout << "Hash-table is now in " << outputFileName;
    return 0;
}