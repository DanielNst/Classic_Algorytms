// Algorytmi_Laba_5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <cstring> 
#include <algorithm> 
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Структура с данными о суффиксе
struct suffix
{
	int index;  // Оригинальный индекс
	int rank[2]; // Для хранения рангов 
				 // и следующей пары рангов 
};

// A comparison function used by sort() to compare 
// two suffixes. Compares two pairs, returns 1 if 
// first pair is smaller 
// Сравниваем с помощью sort() два суффикса, сравниваем две пары и возвращаем 1, если первая пара меньше
int cmp(struct suffix a, struct suffix b)
{
	return (a.rank[0] == b.rank[0]) ?
		(a.rank[1] < b.rank[1] ? 1 : 0) :
		(a.rank[0] < b.rank[0] ? 1 : 0);
}

// Функция строит суффиксный массив для строки txt длины n
vector<int> buildSuffixArray(string txt, int n)
{
	suffix *suffixes = new suffix[n];

	// Сохраняем суффиксы и их индексы в массив структур, 
	//структура нужна для сртировки суффиксов в алфавитном порядке 
	//и чтобы сохранять старые индексы при сортировке
	for (int i = 0; i < n; i++)
	{
		suffixes[i].index = i;
		suffixes[i].rank[0] = txt[i] - 'a';
		suffixes[i].rank[1] = ((i + 1) < n) ?
			(txt[i + 1] - 'a') : -1;
	}
	// сортируем суффиксы с помощью sort 
	sort(suffixes, suffixes + n, cmp);
	// Сортируем сначала по первым двум, потом по первым четырём и т.д.
	int *ind = new int[n];  // Этот массив нужен чтобы хранить старые суффиксы
	for (int k = 4; k < 2 * n; k = k * 2)
	{
		// Присваиваем ранг и индекс первому суффиксу
		int rank = 0;
		int prev_rank = suffixes[0].rank[0];
		suffixes[0].rank[0] = rank;
		ind[suffixes[0].index] = 0;

		// Присваиваем ранги суффиксам
		for (int i = 1; i < n; i++)
		{
			// Если первый ранг и следующий ранг
			// одинаковые с предыдущим суффиксом в массиве
			// присваиваем новый ранг этому суффиксу
			if (suffixes[i].rank[0] == prev_rank &&
				suffixes[i].rank[1] == suffixes[i - 1].rank[1])
			{
				prev_rank = suffixes[i].rank[0];
				suffixes[i].rank[0] = rank;
			}

			else // В другом случае увеличиваем ранг и присваиваем
			{
				prev_rank = suffixes[i].rank[0];
				suffixes[i].rank[0] = ++rank;
			}
			ind[suffixes[i].index] = i;
		}

		// Присваиваем следующий ранг каждому суффиксу
		for (int i = 0; i < n; i++)
		{
			int nextindex = suffixes[i].index + k / 2;
			suffixes[i].rank[1] = (nextindex < n) ?
				suffixes[ind[nextindex]].rank[0] : -1;
		}

		// Сортируем суффиксы по первым k символам
		sort(suffixes, suffixes + n, cmp);
	}
	// Сохраняем индексы всех отсортированных суффиксов в массиве суффиксов
	vector<int>suffixArr;
	for (int i = 0; i < n; i++)
		suffixArr.push_back(suffixes[i].index);
	cout << "The input string: " << endl << txt << endl;
	//Выводим суффиксный массив
	cout << "Suffix array (indexes): " << endl;
	for (int i = 0; i < n; i++)
		cout << suffixArr.at(i) << "  ";
	cout << endl;
	cout << "Suffix array (suffixes): " << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = suffixArr.at(i); j <= n; j++)
			cout << txt[j];
		cout << endl;
	}
	// Возвращает суффиксный массив
	return  suffixArr;
}

/*  Строим массив LCP */
vector<int> kasai(string txt, vector<int> suffixArr)
{
	int n = suffixArr.size();

	vector<int> lcp(n, 0);

	// Вспомогательный массив для хранения элементов инвертированного суффиксного массива 
	// Например если значение suffixArr[0] 5, то
	// в invSuff[5] будет значение 0. Это используется для получения следующей
	// суффиксной строки из масссива суффиксов. 
	vector<int> invSuff(n, 0);

	// Заполняем массив invSuff[] 
	for (int i = 0; i < n; i++)
		invSuff[suffixArr[i]] = i;
	int k = 0;

	// Обработаем последовательно все суффиксы
	// начиная с первого суффикса в txt[] 
	for (int i = 0; i < n; i++)
	{
		/*Если текущий суффикс на n-1, тогда 
		   у нас нет следующей подстроки для подтверждения. Значит LCP не определён для этой подстроки
		   и мы присваиваем ему нулевое значение. */
		if (invSuff[i] == n - 1)
		{
			k = 0;
			continue;
		}

		/* j содержит индекс следующей подстроки
		   рассматриваемой для сравнения с текущей подстрокой
		   т.е. следующей строкой в суффиксном массиве */
		int j = suffixArr[invSuff[i] + 1];

		// Напрямую начинает сравнивать с k-ого индекса
		//  совпадут минимум k-1 символов 
		while (i + k < n && j + k < n && txt[i + k] == txt[j + k])
			k++;

		lcp[invSuff[i]] = k; // LCP для текущего суффикса 

		// Удаляем первый элемент строки
		if (k > 0)
			k--;
	}

	// возвращаем LCP массив
	return lcp;
}
//  метод для подсчёта числа различных подстрок
int countDistinctSubstring(string txt)
{
	//srand(time(0));
	int n = txt.length();
	// строим LCP - массив и суффиксный массив
	vector<int> suffixArr = buildSuffixArray(txt, n);
	vector<int> lcp = kasai(txt, suffixArr);

	// n - suffixArr[i] это длина суффикса
	// инициализируется с i-той позиции в суффиксном массиве 
	// считаем длину от первого суффикса в сортированном массиве 
	int result = n - suffixArr[0];

	for (int i = 1; i < lcp.size(); i++)

		// Вычитаем LCP от длины суффикса
		result += (n - suffixArr[i]) - lcp[i - 1];

	result++;  // Для пустой строки
	//cout << "runtime = " << clock() / 1000.0 << endl;
	return result;
}
int newString(string *substrings, string new_string, int substring_numbers)
{
	for (int i = 0; i < substring_numbers; i++)
	{
		if (substrings[i] == new_string)
		{
			return 0;
		}
	}
	return 1;
}
void subString(string txt, int n)
{
	srand(time(0));
	int result_number = 0;
	int substring_numbers = 0;
	string substrings[1000];
	// Pick starting point 
	for (int len = 1; len <= n; len++)
	{
		// Pick ending point 
		for (int i = 0; i <= n - len; i++)
		{
			//  Print characters from current 
			// starting point to current ending 
			// point.   
			int j = i + len - 1;
			string substring_test = "";
			for (int k = i; k <= j; k++)
				substring_test += txt[k];
			if (newString(substrings, substring_test, substring_numbers) == 1)
			{
				result_number++;
				substrings[substring_numbers] = substring_test;
			}
			//cout << substrings[substring_numbers] << endl;
			substring_numbers++;
			//cout << result_number << endl;
			//cout << endl;
		}
	}
	result_number++;
	cout << result_number << endl;
	cout << "runtime = " << clock() / 1000.0 << endl;
}










int main()
{
	ifstream input_file("input.txt");
	string txt = "";
	input_file >> txt;
	srand(time(0));
	//string test_txt = "ababababa"; // Тестовая строка для сравнения скорости работы
	//string txt = "ababababababababababababababababababababababababababababababababababababababababababababababababababababababababa";
	//subString(test_txt, test_txt.length());
	cout << "Number of substrings: " << countDistinctSubstring(txt) << endl;
	cout << "runtime = " << clock() / 1000.0 << endl;
	return 0;
}