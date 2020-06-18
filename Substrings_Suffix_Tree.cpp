// Algorytmi_Laba_6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#define MAX_CHAR 26 
using namespace std;

// Узел суффиксного дерева
class SuffixTrieNode
{
public:
	SuffixTrieNode *children[MAX_CHAR];
	SuffixTrieNode() // Конструктор
	{
		// Инициализируем всех детей как NULL
		for (int i = 0; i < MAX_CHAR; i++)
			children[i] = NULL;
	}
	// Рекурсивная функция для вставки суффикса 
	// в поддерево, корнем которого является данный узел
	void insertSuffix(string suffix);
};

// Дерево всех суффиксов
class SuffixTrie
{
	SuffixTrieNode *root;
	int _countNodesInTrie(SuffixTrieNode *);
public:
	// Конструктор (Строит дерево всех суффиксов в заданном тексте)
	SuffixTrie(string s)
	{
		root = new SuffixTrieNode();
		// Рассмотрим все суффиксы заданной строки 
		// и вставим их в суффиксное деревое с помощью рекурсивной функции
		// insertSuffix() в классе SuffixTrieNode
		for (int i = 0; i < s.length(); i++)
			root->insertSuffix(s.substr(i));
	}
	// метод для подсчёта числа узлов в суффиксном дереве
	int countNodesInTrie() { return _countNodesInTrie(root); }
};
// Рекурсивная функция для вставки суффикса строки 
// в поддерево, корнем которого является данный узел
void SuffixTrieNode::insertSuffix(string s)
{
	// Если у строки есть ещё символы
	if (s.length() > 0)
	{
		// Находим первый символ
		// и конвертируем его в в код от 0 до 25
		char cIndex = s.at(0) - 'a';
		// Если нет ребра для этого знака
		// добавляем новое ребро
		if (children[cIndex] == NULL)
			children[cIndex] = new SuffixTrieNode();
		// Вовзвращаемся к следующему суффиксу
		children[cIndex]->insertSuffix(s.substr(1));
	}
}

// Рекурсивная функция для подсчёта числа узлов в дереве
int SuffixTrie::_countNodesInTrie(SuffixTrieNode* node)
{
	// Если все символы были обработаны
	if (node == NULL)
		return 0;
	int count = 0;
	for (int i = 0; i < MAX_CHAR; i++)
	{
		// Если дети не равны NULL
		// то найдём число узлов в данном поддереве
		if (node->children[i] != NULL)
			count += _countNodesInTrie(node->children[i]);
			//cout << node->children[i];
	}
	// возвращаем число узлов поддерева
	// прибавив к нему единицу, т.е. сам корень 
	return (1 + count);
}

// Возвращает количество различных подстрок в строке
int countDistinctSubstring(string str)
{
	// Строим дерево всех суффиксов
	SuffixTrie sTrie(str);
	// Возвращаем числовсех узлов в суффиксном дереве
	return sTrie.countNodesInTrie();
}


int main()
{
	ifstream input_file("input.txt");
	string txt = "";
	input_file >> txt;
	srand(time(0));
	cout << "Count of distinct substrings is " << countDistinctSubstring(txt) << endl;
	cout << "runtime = " << clock() / 1000.0 << endl;
	return 0;
}
