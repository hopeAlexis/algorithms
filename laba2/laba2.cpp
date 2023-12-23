#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool parenthesis(std::string str) // проверка на скобки через стек (см. 1 лабу)
{
    stack<char> stk;
    for (char elem : str)
    {
        if (elem == '(' || elem == '{' || elem == '[')
        {
            stk.push(elem);
        }
        else if (elem == ')' || elem == '}' || elem == ']')
        {
            if (stk.empty())
            {
                return false;
            }
            else if ((elem == ')' && stk.top() != '(') ||
                (elem == '}' && stk.top() != '{') ||
                (elem == ']' && stk.top() != '['))
            {
                return false;
            }
            stk.pop();
        }
    }
    return stk.empty();
}

std::string length(std::string str, int& j)    //длина выражения
{
    std::string len;
    for (int i = j; (str[i] >= '0') && (str[i] <= '9'); i++)
    {
        len += str[i];
        j++;
    }
    j--;
    return len;
}

bool equals(std::string str)    //проверка на присутствие знака равно
{
    if (str[str.size() - 1] == '=')
        return 1;
    else
        return 0;
}

int count(std::string str)     //калькулятируем)
{
    std::stack <std::string> numbers;   //здесь будут цифры
    std::stack <char> operators; //здесь буду операторы
    double a = 0;
    double b = 0;
    str += '=';
    for (int i = 0; str[i] != '='; i++)
    {
        if (str[i] != '+' && str[i] != '-' && str[i] != '/' && str[i] != '*' && str[i] != '(' && str[i] != ')' && str[i] != '{' && str[i] != '}' && str[i] != '[' && str[i] != ']') //проверяем кучу всего
        {
            numbers.push(length(str, i));
        }

        if (str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*')
        {
            if (!operators.empty())
            {
                if ((str[i] == '*' || str[i] == '/') && (operators.top() == '*' || operators.top() == '/') && numbers.size() >= 2)
                {
                    b = stoi(numbers.top());    //std::stoi интерпретирует инт в стринг
                    numbers.pop();
                    a = stoi(numbers.top());
                    numbers.pop();
                    if (b == '0' && operators.top() == '/')
                    {
                        std::cout << "Dividing by zero is undefined.";
                        return 0;
                    }
                    if (operators.top() == '/') { numbers.push(std::to_string(a / b)); }
                    if (operators.top() == '*') { numbers.push(std::to_string(a * b)); }
                    operators.pop();
                }
            }
            if (!operators.empty())
            {
                if ((str[i] == '+' || str[i] == '-') && (operators.top() == '+' || operators.top() == '-') && numbers.size() >= 2)
                {
                    b = stoi(numbers.top());
                    numbers.pop();
                    a = stoi(numbers.top());
                    numbers.pop();
                    if (operators.top() == '+') { numbers.push(std::to_string(a + b)); }
                    if (operators.top() == '-') { numbers.push(std::to_string(a - b)); }
                }
            }
        }
        if (str[i] == '(')
        {
            std::string str2;
            int leftBorder = 1;
            int rightBorder = 0;
            for (int j = i + 1; leftBorder != rightBorder; j++)
            {
                str2 += str[j];
                if (str[j] == '(')
                    leftBorder += 1;
                if (str[j] == ')')
                    rightBorder += 1;
                i++;
            }
            str2.pop_back();
            numbers.push(std::to_string(count(str2)));
        }
        if (str[i] == '{')
        {
            std::string str2;
            int left_boarder = 1;
            int right_boarder = 0;
            for (int j = i + 1; left_boarder != right_boarder; j++)
            {
                str2 += str[j];
                if (str[j] == '{')
                    left_boarder += 1;
                if (str[j] == '}')
                    right_boarder += 1;
                i++;
            }
            if (str[i] == '[')
            {
                std::string str2;

                int left_boarder = 1;
                int right_boarder = 0;
                for (int j = i + 1; left_boarder != right_boarder; j++)
                {
                    str2 += str[j];
                    if (str[j] == '[')
                        left_boarder += 1;
                    if (str[j] == ']')
                        right_boarder += 1;
                    i++;
                }
                str2.pop_back();
                numbers.push(std::to_string(count(str2)));
            }
            str2.pop_back();
            numbers.push(std::to_string(count(str2)));
        }
        if (!operators.empty())
        {
            if ((str[i] == '/' || str[i] == '*') && (operators.top() == '/' || operators.top() == '*'))
            {
                b = stoi(numbers.top());
                numbers.pop();
                a = stoi(numbers.top());
                numbers.pop();
                
                if (b == '0' && operators.top() == '/')
                {
                    std::cout << "Dividing by zero is undefined.";
                    return 0;
                }
                if (operators.top() == '/' && b != '0') { numbers.push(std::to_string(a / b)); }
                if (operators.top() == '*') { numbers.push(std::to_string(a * b)); }
                operators.pop();
                operators.push(str[i]);
            }
            if ((str[i] == '/' || str[i] == '*') && (operators.top() == '+' || operators.top() == '-')) { operators.push(str[i]); }
            if ((str[i] == '+' || str[i] == '-') && (operators.top() != '/' && operators.top() != '*')) { operators.push(str[i]); }
        }
        if ((operators.empty() && (str[i] < '0' || str[i]>'9')) && str[i] != ')' && str[i] != '}' && str[i] != ']') { operators.push(str[i]); }
    }
    while (!operators.empty() && numbers.size() >= 2)
    {
        b = stoi(numbers.top());
        numbers.pop();
        a = stoi(numbers.top());
        numbers.pop();
        if (b == 0 && operators.top() == '/')
        {
            std::cout << "Dividing by zero is undefined.";
            return 0;
        }
        if (operators.top() == '/' && b != '0') { numbers.push(std::to_string(a / b)); }
        if (operators.top() == '*') { numbers.push(std::to_string(a * b)); }
        if (operators.top() == '+') { numbers.push(std::to_string(a + b)); }
        if (operators.top() == '-') { numbers.push(std::to_string(a - b)); }
        operators.pop();
    }
    return stoi(numbers.top());
}
int main()
{
    std::cout << "Enter your equation: \n";
    std::string equation;
    std::cin >> equation;
    if (equals(equation) && parenthesis(equation))
        std::cout << "Result = " << count(equation);
    else
        std::cout << "Something went wrong. Please make sure to type '=' at the end.";
    return 0;
}