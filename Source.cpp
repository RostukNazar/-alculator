#include<stack>
#include <iostream>
using namespace std;

struct Dija
{
	char type;
	double value;
};
bool mat(stack<Dija>& Stack_n, stack<Dija>& Stack_o,Dija& x1)
{
	double a,b,c;
	a=Stack_n.top().value;
	Stack_n.pop();
	switch (Stack_o.top().type)
	{
	case'+':
		b = Stack_n.top().value;
		Stack_n.pop();
		c = a + b;
		x1.type = '0';
		x1.value = c;
		Stack_n.push(x1);
		Stack_o.pop();
		break;

	case'-':
		b = Stack_n.top().value;
		Stack_n.pop();
		c = b - a;
		x1.type = '0';
		x1.value = c;
		Stack_n.push(x1);
		Stack_o.pop();
		break;

	case'*':
		b = Stack_n.top().value;
		Stack_n.pop();
		c = a * b;
		x1.type = '0';
		x1.value = c;
		Stack_n.push(x1);
		Stack_o.pop();
		break;

	case'/':
		b = Stack_n.top().value;
		if (a == 0)
		{
			cerr << "\nНа ноль ділити неможна\n" << endl;
			return false;
		}
		else
		{
			Stack_n.pop();
			c = b / a;
			x1.type = '0';
			x1.value = c;
			Stack_n.push(x1);
			Stack_o.pop();
			break;
		}
	default:
		cerr << "\nПомилка\n" << endl;
		return false;
		break;
	}
	return true;
}
int getnamber(char ch)
{
	if (ch == '+' || ch == '-')
	{
		return 1;
	}
	if (ch == '*' || ch == '/')
	{
		return 2;
	}
	return 0;
}
int main()
{
	setlocale(LC_ALL, "Ukraine");
	cout << "  Привіт це програма калькулятор \n  Ведіть вираз" << endl;
	char ch;
	double value;
	bool flag = 1;
	stack <Dija> Stack_n;
	stack <Dija> Stack_o;
	Dija x1;
	while (1)
	{
		ch = cin.peek();
		if (ch == '\n')break;
		if (ch==' ')
		{
			cin.ignore();
			continue;
		}
		if (ch >= '0' && ch <= '9' || ch=='-'&& flag == 1)
		{
			cin >> value;
			x1.type = '0';
			x1.value = value;
			Stack_n.push(x1);
			flag = 0;
			continue;
		}
		if (ch == '+' || ch == '-' && flag==0 || ch == '/' || ch == '*')
		{
			if (Stack_o.size() == 0)
			{
				x1.type = ch;
				x1.value = 0;
				Stack_o.push(x1);
				cin.ignore();
				continue;
			}
			if (Stack_o.size() != 0 && getnamber(ch)>getnamber(Stack_o.top().type))
			{
				x1.type = ch;
				x1.value = 0;
				Stack_o.push(x1);
				cin.ignore();
				continue;
			}
			if (Stack_o.size() != 0 && getnamber(ch) <= getnamber(Stack_o.top().type))
				if (mat(Stack_n, Stack_o, x1) == false)
				{
					system("pause");
					return 0;
				}
			continue;
		}
		if (ch=='(')
		{
			x1.type = ch;
			x1.value = 0;
			Stack_o.push(x1);
			cin.ignore();
			continue;
		}
		if (ch==')')
		{
			while (Stack_o.top().type != '(')
			{
				if (mat(Stack_n, Stack_o, x1) == false)
				{
					system("pause");
					return 0;
				}
				else
				{
					continue;
				}
			}
			Stack_o.pop();
			cin.ignore();
			continue;

		}
		else
		{
			cout << "Невірно ведений вираз" << endl;
			system("pause");
			return 0;
		}
	}

	while (Stack_o.size() != 0)
	{
		if (mat(Stack_n, Stack_o, x1) == false)
		{
			system("pause");
			return 0;
		}
		else
		{
			continue;
		}
	}
	cout << "Otvet:  " << Stack_n.top().value << endl;
          return 0;
}
