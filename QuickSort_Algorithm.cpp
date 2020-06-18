// Algorytmi_Laba_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stdlib.h>
#define MAXSIZE 500
using namespace std;
class Record
{
	public:
		string note[5];
		string generateString() // Генерация случайной строки
			{
			string generate = "";
			for (int i = 0; i < 3; i++)
				{
					const char ch = randomRange('a', 'c');
					generate += ch;
				}
			return generate;
			}
		int randomRange(int low, int high) // Генерация случайного числа
			{
			return rand() % (high - low + 1) + low;
			}
		void generateRecords() // Генерация основного файла с записями для сортировки			
		{
						int tmp;
						note[0] = generateString();
						note[1] = generateString();
						tmp = randomRange(100, 150);
						note[2] = to_string(tmp);
						tmp = randomRange(100, 150);
						note[3] = to_string(tmp);
						tmp = randomRange(100, 150);
						note[4] = to_string(tmp);
		}
};
void ThirdQuickSort(Record *arr, int left, int right, int first_index, int second_index, int third_index) {
	int i = left, j = right;
	string tmp;
	string pivot = arr[(left + right) / 2].note[third_index];
	/* partition */
	if (third_index == 0 || third_index == 1) 
	{ 
		while (i <= j) {
			while (arr[i].note[third_index] < pivot)
				i++;
			while (arr[j].note[third_index] > pivot)
				j--;
			if (i <= j) {
				//cout << i << "||<=||" << j << endl;
				tmp = arr[i].note[third_index];
				arr[i].note[third_index] = arr[j].note[third_index];
				arr[j].note[third_index] = tmp;
				i++;
				j--;
			}
		}
	}
	else
	{
		while (i <= j) {
			while (stoi(arr[i].note[third_index]) < stoi(pivot))
				i++;
			while (stoi(arr[j].note[third_index]) > stoi(pivot))
				j--;
			if (i <= j) {
				//cout << i << "||<=||" << j << endl;
				tmp = arr[i].note[third_index];
				arr[i].note[third_index] = arr[j].note[third_index];
				arr[j].note[third_index] = tmp;
				i++;
				j--;
			}
		}
	}
	/* recursion */
	if (left < j)
		ThirdQuickSort(arr, left, j, first_index, second_index, third_index);
	if (i < right)
		ThirdQuickSort(arr, i, right, first_index, second_index, third_index);
}

void SecondQuickSort(Record *arr, int left, int right, int first_index, int second_index, int third_index) {
	int i = left, j = right;
	string tmp;
	string pivot = arr[(left + right) / 2].note[second_index];
	//cout << "Pivot is " << pivot << endl;
	if (second_index == 0 || second_index == 1)
	{
		while (i <= j) {
			while (arr[i].note[second_index] < pivot)
			{
				//cout << "first_index i is now:" << i << " ;";
				i++;
			}
			while (arr[j].note[second_index] > pivot)
			{
				//cout << "first_index j is now:" << j << " ;";
				j--;
			}
			if (arr[i].note[second_index] == arr[j].note[second_index])
			{
				//cout << "Elements are equal" << endl;
				int right_element = j;
				int tmp_j = j;
				while (arr[i].note[second_index] != arr[j].note[second_index])
				{
					right_element = j;
					j++;
				}
				ThirdQuickSort(arr, i, right_element, first_index, second_index, third_index);
				j = tmp_j;
			}
			if (i <= j)
			{
				//cout << i << "||<=||" << j << endl;
				tmp = arr[i].note[second_index];
				arr[i].note[second_index] = arr[j].note[second_index];
				arr[j].note[second_index] = tmp;
				i++;
				j--;
			}
		};
	}
	else {
	while (i <= j) {
		while (stoi(arr[i].note[second_index]) < stoi(pivot))
		{
			//cout << "first_index i is now:" << i << " ;";
			i++;
		}
		while (stoi(arr[j].note[second_index]) > stoi(pivot))
		{
			//cout << "first_index j is now:" << j << " ;";
			j--;
		}
		if (arr[i].note[second_index] == arr[j].note[second_index])
		{
			//cout << "Elements are equal" << endl;
			int right_element = j;
			int tmp_j = j;
			while (arr[i].note[second_index] != arr[j].note[second_index])
			{
				right_element = j;
				j++;
			}
			ThirdQuickSort(arr, i, right_element, first_index, second_index, third_index);
			j = tmp_j;
		}
		if (i <= j)
		{
			//cout << i << "||<=||" << j << endl;
			tmp = arr[i].note[second_index];
			arr[i].note[second_index] = arr[j].note[second_index];
			arr[j].note[second_index] = tmp;
			i++;
			j--;
		}
	};
}
	if (left < j)
		SecondQuickSort(arr, left, j, first_index, second_index, third_index);
	if (i < right)
		SecondQuickSort(arr, i, right, first_index, second_index, third_index);
}
void FirstQuickSort(Record *arr, int left, int right, int first_index, int second_index, int third_index) {
	int i = left, j = right;
	string tmp;
	string pivot = arr[(left + right) / 2].note[first_index];
	//cout << "Pivot is " << pivot << endl;
	if (first_index == 0 || first_index == 1)
	{
		while (i <= j) {
			while (arr[i].note[first_index] < pivot)
			{
				//cout << "first_index i is now:" << i << " ;";
				i++;
			}
			while (arr[j].note[first_index] > pivot)
			{
				//cout << "first_index j is now:" << j << " ;";
				j--;
			}
			if (arr[i].note[first_index] == arr[j].note[first_index])
			{
				//cout << "Elements are equal" << endl;
				int right_element = j;
				int tmp_j = j;
				while (arr[i].note[first_index] != arr[j].note[first_index])
				{
					right_element = j;
					j++;
				}
				//cout << "Left element is " << i << "Right element is " << right_element << endl;
				SecondQuickSort(arr, i, right_element, first_index, second_index, third_index);
				j = tmp_j;
			}
			if (i <= j)
			{
				//cout << i << "<=" << j << endl;
				tmp = arr[i].note[first_index];
				arr[i].note[first_index] = arr[j].note[first_index];
				arr[j].note[first_index] = tmp;
				i++;
				j--;
			}
		};
}
	else {
		while (i <= j) {
			while (stoi(arr[i].note[first_index]) < stoi(pivot))
			{
				//cout << "first_index i is now:" << i << " ;";
				i++;
			}
			while (stoi(arr[j].note[first_index]) > stoi(pivot))
			{
				//cout << "first_index j is now:" << j << " ;";
				j--;
			}
			if (arr[i].note[first_index] == arr[j].note[first_index])
			{
				//cout << "Elements are equal" << endl;
				int right_element = j;
				int tmp_j = j;
				while (arr[i].note[first_index] != arr[j].note[first_index])
				{
					right_element = j;
					j++;
				}
				//cout << "Left element is " << i << "Right element is " << right_element << endl;
				SecondQuickSort(arr, i, right_element, first_index, second_index, third_index);
				j = tmp_j;
			}
			if (i <= j)
			{
				//cout << i << "<=" << j << endl;
				tmp = arr[i].note[first_index];
				arr[i].note[first_index] = arr[j].note[first_index];
				arr[j].note[first_index] = tmp;
				i++;
				j--;
			}
		};
	}
	if (left < j)
		FirstQuickSort(arr, left, j, first_index,second_index, third_index);
	if (i < right)
		FirstQuickSort(arr, i, right, first_index, second_index, third_index);
}

void generateArray(Record *arr)
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		arr[i].generateRecords();
	}
	cout << "Array succesfully generated" << endl;
}
void printArray(Record *arr)
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		cout << arr[i].note[0] << " ";
		cout << arr[i].note[1] << " ";
		cout << arr[i].note[2] << " ";
		cout << arr[i].note[3] << " ";
		cout << arr[i].note[4] << endl;
	}
}
int main()
{	
    Record array[MAXSIZE];
	srand(time(NULL));
	int first_index,second_index,third_index;
	generateArray(array);
	printArray(array);
	cout << "Input the first number of field" << endl;
	cin >> first_index;
	first_index--;
	if (first_index < 0 || first_index > 4)
		{
			cout << "Error, incorrect number of field" << endl;
			return 1;
		}
	cout << "Input the second number of field" << endl;
	cin >> second_index;
	second_index--;
	if (second_index < 0 || second_index > 4)
	{
		cout << "Error, incorrect number of field" << endl;
		return 1;
	}
	cout << "Input the third number of field" << endl;
	cin >> third_index;
	third_index--;
	if (third_index < 0 || third_index > 4)
	{
		cout << "Error, incorrect number of field" << endl;
		return 1;
	}
	FirstQuickSort(array, 0, MAXSIZE - 1, first_index, second_index, third_index);
	FirstQuickSort(array, 0, MAXSIZE - 1, first_index, second_index, third_index);
	FirstQuickSort(array, 0, MAXSIZE - 1, first_index, second_index, third_index);
	printArray(array);
	cout << "Array succesfully sorted" << endl;
	return 0;                                           
}
