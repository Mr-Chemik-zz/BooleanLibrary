#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

class Boolean {
public:
	static std::vector <std::vector<int>> truth_table(const std::string str);
	static std::vector <int> result(const std::string str);
	static std::string simplify(const std::string str);

private:
	#define MATRIX_X sorted_table.size() / 2 + 1
	#define MATRIX_Y pdnf_sorted_table.size() + 1

	static bool checking_expression(std::string str);
	static std::string check_order(std::string str);
	static std::string solving_expression(std::string str);
	static std::string searching_bracket(std::string str, std::vector <int> value);
	static std::vector <std::vector<int>> build_table(std::string str, std::string sorting);

	static std::vector <std::vector<std::string>> build_simply_table(std::string str, std::string sorting);
	static std::vector <std::string> sort_table(std::vector <std::vector<std::string>> table);
	static std::string simplifing(std::vector <std::string> sorted_table, std::string sorting);
};

std::vector <std::vector<int>> Boolean::build_table(std::string str, std::string sorting) {
	// Building a truth table by int
	// Строит таблицу истинности из целочисленных переменных
	int x;
	int y;
	int count;

	x = sorting.length();

	y = pow(2, x);

	std::vector <int> value(x);

	x = x + 1;

	std::vector < std::vector <int>> table(y);

	for (int i = 0; i < y; i++)
		table[i].resize(x);

	for (int i = 0; i < y; i++) {
		count = i;
		for (int j = x - 2; j >= 0; j--) {
			if (count % 2 == 0) {
				table[i][j] = 0;
				value[j] = 0;
			}
			else {
				table[i][j] = 1;
				value[j] = 1;
			}
			count = count / 2;
		}
		// "Sending" the values of the truth table fields for the solution
		// "Отправка" значений полей таблицы истинности для решения
		table[i][x - 1] = atoi(searching_bracket(str, value).c_str());
	}

	return table;
}

std::string Boolean::check_order(std::string str) {
	// Checking an expression for an alphabetical sequence.
	// Проверка выражения на наличие алфавитной последовательности.

	std::string sorting;

	for (int i = 0; i < str.length(); i++) {
		if (str[i] >= 65 && str[i] <= 90) {
			if (sorting.length() == 0) {
				sorting = str[i];
				continue;
			}
			for (int j = 0; j < sorting.length(); j++) {
				if (str[i] == sorting[j])
					break;

				if (j == sorting.length() - 1)
					sorting = sorting + str[i];

			}
		}
	}

	std::sort(sorting.begin(), sorting.end());

	return sorting;
}

std::string Boolean::searching_bracket(std::string str, std::vector <int> value) {
	// Search for parentheses, and solve them.
	// Поиск скобок, и их решение.
	std::string help;
	std::string brackets;
	bool first = true;
	bool brackets_exist = false;
	int end = 0;
	int start = 0;

	for (int i = 0; i < str.length(); i++) {
		if (str[i] >= 65 && str[i] <= 90) {
			help = std::to_string(value[str[i] - 'A']);
			str[i] = help[0];
		}
		if (str[i] == '(')
			brackets_exist = true;
	}

	while (brackets_exist) {
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == '(') {
				if (!first)
					break;

				start = i;
			}
			if (str[i] == ')') {
				if (first) {
					end = i;
					first = false;
				}
			}
		}

		brackets = str[start];

		for (int j = start + 1; j <= end; j++)
			brackets = brackets + str[j];

		help = brackets;

		str.replace(str.find(brackets), brackets.length(), solving_expression(help));


		first = true;

		for (int i = 0; i < str.length(); i++) {
			if (str[i] == ')')
				break;

			if (i == str.length() - 1)
				brackets_exist = false;

		}
	}

	help = str;

	str = solving_expression(help);

	return str;
}

std::string Boolean::solving_expression(std::string str) {
	// Solving An Expression.
	// Решение Выражения.

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(')
			str.erase(i, 1);
		if (str[i] == ')')
			str.erase(i, 1);
	}

	while (str.find("!") != -1) {

		// NOT

		for (int j = 0; j < str.length(); j++) {
			if (str[j] == '!' && str[j + 1] == '0')
				str.replace(str.find("!0"), 2, "1");

			if (str[j] == '!' && str[j + 1] == '1')
				str.replace(str.find("!1"), 2, "0");
		}
	}

	while (str.find("*") != -1) {
		for (int j = 0; j < str.length(); j++) {

			// AND

			if (str[j] == '0' && str[j + 1] == '*' && str[j + 2] == '1')
				str.replace(str.find("0*1"), 3, "0");


			if (str[j] == '1' && str[j + 1] == '*' && str[j + 2] == '0')
				str.replace(str.find("1*0"), 3, "0");


			if (str[j] == '1' && str[j + 1] == '*' && str[j + 2] == '1')
				str.replace(str.find("1*1"), 3, "1");


			if (str[j] == '0' && str[j + 1] == '*' && str[j + 2] == '0')
				str.replace(str.find("0*0"), 3, "0");

		}
	}

	while (str.find("+") != -1) {
		for (int j = 0; j < str.length(); j++) {

			// OR

			if (str[j] == '0' && str[j + 1] == '+' && str[j + 2] == '1')
				str.replace(str.find("0+1"), 3, "1");


			if (str[j] == '1' && str[j + 1] == '+' && str[j + 2] == '0')
				str.replace(str.find("1+0"), 3, "1");


			if (str[j] == '1' && str[j + 1] == '+' && str[j + 2] == '1')
				str.replace(str.find("1+1"), 3, "1");


			if (str[j] == '0' && str[j + 1] == '+' && str[j + 2] == '0')
				str.replace(str.find("0+0"), 3, "0");
		}
	}

	// Logical operations without a certain order.
	// Логические операции без определённой последовательности

	while (str.find("|") != -1 || str.find("^") != -1 || str.find("#") != -1 || str.find(">") != -1 || str.find("=") != -1) {

		for (int j = 0; j < str.length(); j++) {
			// NAND

			if (str[j] == '0' && str[j + 1] == '|' && str[j + 2] == '1') {
				str.replace(str.find("0|1"), 3, "1");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '1' && str[j + 1] == '|' && str[j + 2] == '0') {
				str.replace(str.find("1|0"), 3, "1");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '1' && str[j + 1] == '|' && str[j + 2] == '1') {
				str.replace(str.find("1|1"), 3, "0");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '0' && str[j + 1] == '|' && str[j + 2] == '0') {
				str.replace(str.find("0|0"), 3, "1");
				str = Boolean::solving_expression(str);
			}


			// XOR

			if (str[j] == '0' && str[j + 1] == '^' && str[j + 2] == '1') {
				str.replace(str.find("0^1"), 3, "1");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '1' && str[j + 1] == '^' && str[j + 2] == '0') {
				str.replace(str.find("1^0"), 3, "1");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '1' && str[j + 1] == '^' && str[j + 2] == '1') {
				str.replace(str.find("1^1"), 3, "0");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '0' && str[j + 1] == '^' && str[j + 2] == '0') {
				str.replace(str.find("0^0"), 3, "0");
				str = Boolean::solving_expression(str);
			}

			// NOR

			if (str[j] == '0' && str[j + 1] == '#' && str[j + 2] == '1') {
				str.replace(str.find("0#1"), 3, "0");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '1' && str[j + 1] == '#' && str[j + 2] == '0') {
				str.replace(str.find("1#0"), 3, "0");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '1' && str[j + 1] == '#' && str[j + 2] == '1') {
				str.replace(str.find("1#1"), 3, "0");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '0' && str[j + 1] == '#' && str[j + 2] == '0') {
				str.replace(str.find("0#0"), 3, "1");
				str = Boolean::solving_expression(str);
			}

			// IMPLY

			if (str[j] == '0' && str[j + 1] == '>' && str[j + 2] == '1') {
				str.replace(str.find("0>1"), 3, "1");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '1' && str[j + 1] == '>' && str[j + 2] == '0') {
				str.replace(str.find("1>0"), 3, "0");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '1' && str[j + 1] == '>' && str[j + 2] == '1') {
				str.replace(str.find("1>1"), 3, "1");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '0' && str[j + 1] == '>' && str[j + 2] == '0') {
				str.replace(str.find("0>0"), 3, "1");
				str = Boolean::solving_expression(str);
			}

			// XNOR

			if (str[j] == '0' && str[j + 1] == '=' && str[j + 2] == '1') {
				str.replace(str.find("0=1"), 3, "0");
				str = Boolean::solving_expression(str);
			}

			if (str[j] == '1' && str[j + 1] == '=' && str[j + 2] == '0') {
				str.replace(str.find("1=0"), 3, "0");
				str = Boolean::solving_expression(str);
			}

			if (str[j] == '1' && str[j + 1] == '=' && str[j + 2] == '1') {
				str.replace(str.find("1=1"), 3, "1");
				str = Boolean::solving_expression(str);
			}

			if (str[j] == '0' && str[j + 1] == '=' && str[j + 2] == '0') {
				str.replace(str.find("0=0"), 3, "1");
				str = Boolean::solving_expression(str);
			}
		}
	}

	return str;
}

std::string Boolean::simplifing(std::vector <std::string> sorted_table, std::string sorting) {
	// Simplifying the expression Quine's method.
	// Упрощение выражение методом Куайна

	int end = sorted_table.size();
	int begin = 0;
	int unic = 0;
	int unic_y = 0;
	int last_end = 0;

	std::string first_str = "";
	std::string second_str;
	std::string first_compare;
	std::string second_compare;
	std::string combo = "";

	std::vector <std::string> pdnf_sorted_table;
	std::vector <std::string> simplify_sorted_table = sorted_table;

	if (simplify_sorted_table.size() == 0)
		return "";
	if (simplify_sorted_table.size() == pow(2, sorting.length() + 1))
		return "1";

	// A pairwise comparison of equivalents (terms) in neighboring groups is performed.
	// Проводится попарное сравнение эквивалентов (терминов) в соседних группах.

	for (int i = 0; i < end; i = i + 2) {
		for (int j = begin; j < end; j = j + 2) {
			if (i == j)
				continue;
			combo = "";
			last_end = end;
			first_str = simplify_sorted_table[i];
			second_str = simplify_sorted_table[j];
			first_compare = first_str;
			second_compare = second_str;

			for (int i = 0; i < first_compare.length(); i++) {
				if (first_compare[i] > 96)
					first_compare[i] = first_compare[i] - 32;
			}
			for (int i = 0; i < second_compare.length(); i++) {
				if (second_compare[i] > 96)
					second_compare[i] = second_compare[i] - 32;
			}

			for (int y = 0; y < first_str.length(); y++) {
				if (second_compare != first_compare)
					break;
				for (int x = 0; x < second_str.length(); x++) {
					if (first_str[y] == second_str[x])
						combo = combo + first_str[y];
				}
			}

			if (combo.length() >= first_str.length() - 1 && first_str.length() != 1) {
				simplify_sorted_table[i + 1] = "1";
				simplify_sorted_table[j + 1] = "1";
			}

			for (int n = 0; n < simplify_sorted_table.size(); n++) {
				if (combo == simplify_sorted_table[n])
					combo = "";
			}

			if (combo.length() >= first_str.length() - 1 && first_str.length() != 1) {
				simplify_sorted_table[i + 1] = "1";
				simplify_sorted_table[j + 1] = "1";
				simplify_sorted_table.push_back(combo);
				simplify_sorted_table.push_back("0");
			}
		}
		if (i == end - 2) {
			end = simplify_sorted_table.size();
			begin = last_end;
		}
	}

	// Construction of the implicant matrix
	// Построение импликантной матрицы

	for (int i = 0; i < simplify_sorted_table.size(); i++) {
		if (simplify_sorted_table[i] == "0")
			pdnf_sorted_table.push_back(simplify_sorted_table[i - 1]);
	}

	std::vector <std::vector<std::string>> impl_matrix(MATRIX_Y);

	for (int i = 0; i < MATRIX_Y; i++)
		impl_matrix[i].resize(MATRIX_X);

	for (int i = 0; i < MATRIX_Y; i++) {
		for (int j = 0; j < MATRIX_X; j++)
			impl_matrix[i][j] = "0";
	}

	for (int i = 0; i < MATRIX_Y - 1; i++)
		impl_matrix[i + 1][0] = pdnf_sorted_table[i];

	for (int i = 0; i < MATRIX_X - 1; i++)
		impl_matrix[0][i + 1] = simplify_sorted_table[i * 2];

	for (int i = 1; i < MATRIX_Y; i++) {
		for (int j = 1; j < MATRIX_X; j++) {
			unic = 0;
			first_str = impl_matrix[0][j];
			second_str = impl_matrix[i][0];
			for (int x = 0; x < first_str.length(); x++) {
				for (int y = 0; y < second_str.length(); y++) {
					if (first_str[x] == second_str[y])
						unic++;

					if (unic == second_str.length())
						impl_matrix[i][j] = "1";

				}
			}
		}
	}

	first_str = "";

	// Filling in the implication matrix
	// Заполнение импликантной матрицы

	for (int i = 1; i < MATRIX_X; i++) {
		unic = 0;
		for (int j = 1; j < MATRIX_Y; j++) {
			if (impl_matrix[j][i] == "1") {
				unic_y = j;
				unic++;
			}
			if (unic == 1 && j == MATRIX_Y - 1) {
				if (impl_matrix[unic_y][0] == "NULL")
					break;
				first_str = first_str + impl_matrix[unic_y][0] + "+";
				impl_matrix[unic_y][0] = "NULL";
			}
		}
	}

	// Transformation of expression into a normal form.
	// Трансофрмация выражения в нормальную форму.

	for (int i = 0; i < first_str.length(); i++) {
		if (first_str[i] > 96) {
			combo = (first_str[i] - 32);
			second_str = "!";
			first_str.replace(first_str.find(first_str[i]), 1, second_str + combo);
		}
	}

	// Change "AB" in "A*B"
	// Замена "AB" в "A*B"

	for (int i = 0; i < first_str.length() - 1; i++) {
		if ((first_str[i] >= 65 && first_str[i] <= 90) && (first_str[i + 1] == '!' || (first_str[i + 1] >= 65 && first_str[i + 1] <= 90)))
			first_str.insert(i + 1, "*");
	}

	first_str.erase(first_str.length() - 1);

	return first_str;
}

std::vector <std::vector<std::string>> Boolean::build_simply_table(std::string str, std::string sorting) {
	// Building a truth table from string
	// Построение таблицы истинности из string
	int x;
	int y;
	int count;
	char current_symb;
	std::string exp = "";

	x = sorting.length();

	y = pow(2, x);


	std::vector <int> value(x);

	std::vector < std::vector <std::string>> table(y);

	for (int i = 0; i < y; i++)
		table[i].resize(2);

	for (int i = 0; i < y; i++) {
		count = i;
		for (int j = x - 1; j >= 0; j--) {
			if (count % 2 == 0) {
				current_symb = char('a' + j);
				exp = exp + current_symb;
				value[j] = 0;
			}
			else {
				current_symb = char('A' + j);
				exp = exp + current_symb;
				value[j] = 1;
			}
			count = count / 2;
		}
		std::reverse(exp.begin(), exp.end());
		table[i][0] = exp;
		table[i][1] = Boolean::searching_bracket(str, value);
		exp = "";
	}

	return table;
}

std::vector <std::string> Boolean::sort_table(std::vector <std::vector<std::string>> table) {
	// Sorts a table to get a table from truthful expressions.
	// Сортировка таблицы для получение только верных выражений
	std::vector<std::string> sorted_table(0);

	for (int i = 0; i < table.size(); i++) {
		if (table[i][1] == "1") {
			sorted_table.push_back(table[i][0]);
			sorted_table.push_back("0");
		}
	}

	return sorted_table;
}

bool Boolean::checking_expression(std::string str) {
	// Checking correctness of expression
	// Проверка выражения на корректность

	int count = 0;

	std::string sort_str = Boolean::check_order(str);

	for (int i = 0; i < sort_str.length() - 1; i++) {
		if (sort_str[i] + 1 != sort_str[i + 1])
			return false;
	}

	for (int i = 0; i < str.length(); i++)
		if (str[i] != '+' && str[i] != '*' && str[i] != '#' && str[i] != '|' && str[i] != '>' && str[i] != '^' && str[i] != '=' && str[i] != '!' && str[i] != '(' && str[i] != ')' && !(str[i] >= 65 && str[i] <= 90))
			return false;

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(')
			count++;
		if (str[i] == ')')
			count--;

		if (i == 0 && (str[i] != '(' && str[i] != '!' && !(str[i] >= 65 && str[i] <= 90)))
			return false;
		if (i == str.length() - 1 && (str[i] != ')' && !(str[i] >= 65 && str[i] < 90)))
			return false;
	}


	if (count != 0)
		return false;

	for (int i = 1; i < str.length(); i++) {
		if ((str[i] >= 65 && str[i] <= 90) && (str[i - 1] != '+' && str[i - 1] != '*' && str[i - 1] != '|' && str[i - 1] != '#' && str[i - 1] != '=' && str[i - 1] != '>' && str[i - 1] != '^' && str[i - 1] != '!' && str[i - 1] != '('))
			return false;
		if (str[i] == '(' && ((str[i - 1] >= 65 && str[i - 1] <= 90)))
			return false;
		if ((!(str[i] >= 65 && str[i] <= 90) && str[i] != '(' && str[i] != ')' && str[i] != '!') && (!(str[i - 1] >= 65 && str[i - 1] <= 90) && str[i - 1] != '(' && str[i - 1] != ')' && str[i - 1] != '!'))
			return false;
	}

	for (int i = 0; i < str.length() - 1; i++) {
		if ((str[i] >= 65 && str[i] <= 90) && ((str[i + 1] != '+' && str[i + 1] != '|' && str[i + 1] != '*' && str[i + 1] != '#' && str[i + 1] != '=' && str[i + 1] != '>' && str[i + 1] != '^' && str[i + 1] != ')')))
			return false;
		if (str[i] == '(' && (!(str[i + 1] >= 65 && str[i + 1] <= 90) && str[i + 1] != '!' && str[i + 1] != '('))
			return false;
		if ((!(str[i] >= 65 && str[i] <= 90) && str[i] != '(' && str[i] != ')' && str[i] != '!') && (!(str[i + 1] >= 65 && str[i + 1] <= 90) && str[i + 1] != '(' && str[i + 1] != ')' && str[i + 1] != '!'))
			return false;
	}

	return true;
}

// Visible method.
// Видимые методы.

std::string Boolean::simplify(const std::string str) {
	// Return simplified expression
	// Возврат упрощенного выражения 

	if (!checking_expression(str))
		throw - 1;

	// Error in the expression
	// Ошибка в выражении

	return simplifing(sort_table(build_simply_table(str, check_order(str))), check_order(str));
}

std::vector <std::vector<int>> Boolean::truth_table(const std::string str) {
	// Return the truth table in the vector type
	// Возврат таблицы истинности в типе vector

	if (!checking_expression(str))
		throw - 1;

	// Error in the expression
	// Ошибка в выражении

	return Boolean::build_table(str, Boolean::check_order(str));
}

std::vector <int> Boolean::result(const std::string str) {
	// Return only result of logical expression
	// Возврат только результата логического выражения

	if (!checking_expression(str))
		throw - 1;

	// Error in the expression
	// Ошибка в выражении

	std::vector <std::vector<int>> table = Boolean::truth_table(str);

	std::vector <int> table_result;

	for (int i = 0; i < table.size(); i++)
		table_result.push_back(table[i][table[1].size() - 1]);

	return table_result;
}

