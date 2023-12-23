#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>    //áèáëèîòåêà äëÿ õåø-òàáëèö 

int hashFunction(const std::string& key, int n) //ôóíêöèÿ, êîòîðàÿ ñîçäà¸ò "ðàíäîìíûå" êëþ÷è äëÿ õåø-òàáëèöû
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
    std::ifstream F(key, std::ios::in); //ýêçåìëïÿð êëàññà ifstream
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
        return 1;   //çàâåðøàåì ïðîãðàììó
    }

    std::unordered_map<int, std::string> hashTable;
    int n = countLines("input.txt");

    std::string line;

    while (std::getline(fin, line)) //getline ïîçâîëÿåò íàì ñ÷èòàòü ñòðîêó ñ ïðîáåëàìè
    {
        int key = hashFunction(line, n);
        bool fl = true;
        while (fl)
        {
            if (hashTable[key].empty()) //èùåì "ñâîáîäíóþ" ïîçèöèþ â òàáëèöå
            {
                hashTable[key] = line;
                fl = false;
            }
            else   //åñëè ïîçèöèÿ óæå çàíÿòà
            {
                if (key < (n - 1))  //ïðîâåðÿåì ñëåäóþùóþ ïîçèöèþ
                    key += 1;
                else
                    key = 0;    //íî íå âûõîäèì çà ïðåäåëû âîçìîæíûõ êëþ÷åé
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
