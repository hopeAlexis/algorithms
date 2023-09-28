#include <iostream>
#include <string>
#include <stack>


int main()
{
	setlocale(LC_ALL, "Russian");

	std::stack <char> stk;
	std::string s = "";
	std::cout << "Введите строку из скобок: ";
	std::cin >> s;
	stk.push(s[0]);

	for (int i = 1; i < s.length(); i++)
	{
		if (s[i] == '(' || s[i] == '[' || s[i] == '{')
		{
			stk.push(s[i]);
		}

		else if (s[i] == ')')
		{
			if (stk.top() == '(')
				stk.pop();
			else
				break;
		}

		else if (s[i] == ']')
		{
			if (stk.top() == '[')
				stk.pop();
			else
				break;
		}

		else if (s[i] == '}')
		{
			if (stk.top() == '{')
				stk.pop();
			else
				break;
		}
		else
			break;	//if entered line has other characters
	}

	if (stk.empty())
		std::cout << "Правильная строка!";
	else
		std::cout << "Неправильная строка!";

	return 0;
}