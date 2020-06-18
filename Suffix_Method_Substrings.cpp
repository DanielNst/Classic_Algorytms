// Algorytmi_Laba_4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
void computeLPSArray(string pat, int M, int* lps);

void KMPSearch(string pat, string txt)
{
	int M = pat.length();
	int N = txt.length();
	// в lps - самый длинный суффикс
	int *lps = new int [M];
	computeLPSArray(pat, M, lps);
	for (int k = 0; k < M; k++)
	{
		cout << lps[k] << " ";
	}
	int i = 0; 
	int j = 0; 
	while (i < N) {
		if (pat[j] == txt[i]) {
			j++;
			i++;
		}

		if (j == M) {
			cout << "Found pattern at index: " << i - j;
			j = lps[j - 1];
		}
		else if (i < N && pat[j] != txt[i]) {
			if (j != 0)
				j = lps[j - 1];
			else
				i = i + 1;
		}
	}
}

void computeLPSArray(string pat, int M, int* lps)
{
	// длина предыдущего самого длинного суффикса
	int len = 0;

	lps[0] = 0; 

	int i = 1;
	while (i < M) {
		if (pat[i] == pat[len]) {
			len++;
			lps[i] = len;
			i++;
		}
		else 
		{
			if (len != 0) {
				len = lps[len - 1];
			}
			else 
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}
int main()
{
	ifstream input_file("input.txt");
	string txt = "";
	string pat = "";
	input_file >> txt;
	input_file >> pat;
	KMPSearch(pat, txt);
	return 0;
}
