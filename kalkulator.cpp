#include <iostream>
#include <stack>
#include <cmath>
using namespace std;
struct Vid {
	char type;
	double value;
};
int priority(char ch) {
	if ((ch == '+') or (ch == '-')) {
		return 1;
	}
	if ((ch == '*') or (ch == '/')) {
		return 2;
	}
	if (ch == '^') {
		return 3;
	}
	else return 0;
}
bool math(stack <Vid> & stack_n, stack <Vid> & stack_o, Vid & item) {
	double a, b, c;
	a = stack_n.top().value;
	stack_n.pop();
	switch (stack_o.top().type) {
	case '+':
		b = stack_n.top().value;
		stack_n.pop();
		c = a + b;
		item.type = '0';
		item.value = c;
		stack_n.push(item);
		stack_o.pop();
		break;
	case '-':
		b = stack_n.top().value;
		stack_n.pop();
		c = b - a;
		item.type = '0';
		item.value = c;
		stack_n.push(item);
		stack_o.pop();
		break;
	case '*':
		b = stack_n.top().value;
		stack_n.pop();
		c = a * b;
		item.type = '0';
		item.value = c;
		stack_n.push(item);
		stack_o.pop();
		break;
	case '/':
		b = stack_n.top().value;
		stack_n.pop();
		if (a == 0) {
			cout << "\nДеление на 0\n";
			return false;
		}
		if (a != 0) {
			c = b / a;
			item.type = '0';
			item.value = c;
			stack_n.push(item);
			stack_o.pop();
			break;
		}
	case '^':
		b = stack_n.top().value;
		stack_n.pop();
		c = pow(b,a);
		item.type = '0';
		item.value = c;
		stack_n.push(item);
		stack_o.pop();
		break;
	}
}
int main()
{
	setlocale(LC_ALL, "rus");
	char ch;
	bool f = 1;
	double value;
	stack <Vid> stack_n;
	stack <Vid> stack_o;
	Vid item;
	while (1) {
		ch = cin.peek();
		if (ch == '\n') {
			break;
		}
		if ((ch >= '0') and (ch <= '9') or ((ch == '-') and (f == 1))) {
			cin >> value;
			item.type = '0';
			item.value = value;
			stack_n.push(item);
			f = 0;
			continue;
		}
		if ((ch == '+') or ((ch == '-') and (f == 0)) or (ch == '*') or (ch == '/') or (ch == '^')) {
			if (stack_o.size() == 0) {
				item.type = ch;
				item.value = 0;
				stack_o.push(item);
				cin.ignore();
				continue;
			}
			if ((stack_o.size() != 0) and (priority(ch) > priority(stack_o.top().type))) {
				item.type = ch;
				item.value = 0;
				stack_o.push(item);
				cin.ignore();
				continue;
			}
			if ((stack_o.size() != 0) and (priority(ch) <= priority(stack_o.top().type))) {
				if (math(stack_n, stack_o, item) == false) {
					system("pause");
					return 0;
				}
				else continue;
			}
		}
		if (ch == '(') {
			f = 1;
			item.type = ch;
			item.value = 0;
			stack_o.push(item);
			cin.ignore();
			continue;
		}
		if (ch == ')') {
			while (stack_o.top().type != '(') {
				if (math(stack_n, stack_o, item) == false) {
					system("pause");
					return 0;
				}
				else continue;
			}
			stack_o.pop();
			cin.ignore();
		}
	}
	while (stack_o.size() != 0) {
		if (math(stack_n, stack_o, item) == false) {
			system("pause");
			return 0;
		}
		else continue;
	}
	cout << "Ответ: " << stack_n.top().value << endl;
	return 0;
}