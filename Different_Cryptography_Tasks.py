#!/usr/bin/env python
#-*- coding: utf-8 -*-
from __future__ import unicode_literals
from operator import itemgetter
from collections import OrderedDict
from collections import Counter
from itertools import cycle

def ifIsOpenText1(lines, special_letters): #Метод для проверки на открытый текст
	simple = 1							   #С использованием запретных комбинаций
	for i in range(len(lines)):			   #Количество комбинаций может быть увеличено
		if lines[i] in special_letters:
			#print(special_letters.index(lines[i]))
			if i == 0:
				if lines[i+1] in special_letters:
					print ("Это не текст")
					simple = 0
					break
			elif i == len(lines):
				if lines[i-1] in special_letters:
					print ("Это не текст")
					simple = 0
					break
			else:
				if lines[i-1] or lines[i+1] in special_letters:
					print ("Это не текст")
					simple = 0
					break
	if (simple):
		print("Это простой текст")



def transpose(array): #Метод для транспонирования матрицы
  return [[ array[row][col] for row in range (0,len(array)) ] for col in range (0, len(array)) ]

def ifIsOpenText2(lines): #Метод для проверки на открытый текст с помощью частотности
	letters_frequency = {'а':0,'б':0,'в':0,'г':0,'д':0,'е':0,'ё':0,'ж':0,'з':0,'и':0,'й':0,'к':0,'л':0,'м':0,'н':0,'о':0,'п':0,'р':0,'с':0,'т':0,'у':0,'ф':0,'х':0,'ц':0,'ч':0,'ш':0,'щ':0,'ъ':0,'ы':0,'ь':0,'э':0,'ю':0,'я':0 }
	for i in range(len(lines)): #Создаём словарь в который записываем частотность для каждой буквы
		if lines[i] in letters_frequency:
			letters_frequency[lines[i]] = letters_frequency[lines[i]] + 1
	print(letters_frequency)
	letters_frequency['е'] = letters_frequency['е'] / len(lines)
	letters_frequency['о'] = letters_frequency['о'] / len(lines)
	letters_frequency['а'] = letters_frequency['а'] / len(lines)
	print(letters_frequency) #Потом проверяем частоту для букв 'а', 'о' и 'е' 
	if letters_frequency['е'] and letters_frequency['о'] and letters_frequency['а'] > 0.05 and letters_frequency['е'] and letters_frequency['о'] and letters_frequency['а'] < 0.15 :
		print("Это простой текст") #Имеет смысл проверять только для распространённых букв, так как частота
	else:							#с которой встречаются остальные буквы очень зависит от тематики текста
		print("Это не текст")
	

def fromFileNums(file_name): 
 with open(file_name, 'r', encoding='UTF-8') as fin:
  matrix = [list(row.split()) for row in fin.readlines()]
 return matrix
def fromFileText(file_name):
	file = open(file_name, encoding='UTF-8')
	lines = file.read()
	file.close()
	return lines



def swap_lines(matrix, first, second): 
  matrix[first], matrix[second] = matrix [second], matrix[first]
  return matrix

def swap_cols(matrix, first, second):
	for i in range(len(matrix)):
		matrix[i][first], matrix[i][second] = matrix [i][second], matrix [i][first]

def decrypt_lines_cols(matrix):
	#matrix_count = 0
	for first in range (len(matrix)):
		for second in range(len(matrix)):
			swap_cols(matrix, first, second)
			transpose(matrix)
			swap_lines(matrix, first, second)
			for line in matrix:
				print(line)
			#matrix_count = matrix_count + 1
			print ("---------------")
			#print (matrix_count)

def encryption(cypher):
 letters_rank = {'а':3,'б':21,'в':9,'г':19,'д':13,'е':2,'ё':33,'ж':25,'з':20,'и':4,'й':23,'к':11,'л':10,'м':12,'н':5,'о':1,'п':14,'р':8,'с':7,'т':6,'у':15,'ф':31,'х':24,'ц':28,'ч':22,'ш':26,'щ':29,'ъ':32,'ы':17,'ь':18,'э':30,'ю':27,'я':16 }
 letters_ranking = ['о','е','а','и','н','т','с','р','в','л','к','м','д','п','у','я','ы','ь','г','з','б','ч','й','х','ж','ш','ю','ц','щ','э','ф','Ъ','ё',',',':','.']
 cypher_frequency = {}
 cypher_elements = []
 for i in range(len(cypher)):
  #print(cypher[i], "- element")
  if cypher[i] in cypher_frequency: #Вычисляем как часто встречаются "буквы" в тексте
   cypher_frequency[cypher[i]] = cypher_frequency[cypher[i]] + 1
  else:
   cypher_frequency[cypher[i]] = 1
   cypher_elements.append(cypher[i])
 cypher_rank = {}
 list_d = list(cypher_frequency.items())
 list_d.sort(key=lambda i: i[1]) #Создаём список и сортируем его по частоте (словари нельзя сортировать)
 list_d.reverse()
 delete_list =[]
 print(list_d)
 for i in range(len(list_d)): #Удаляем из списка всё, что не является буквами
  if list_d[i][0] == ',' or list_d[i][0] == '.' or list_d[i][0] == ':' or list_d[i][0] == '-' or list_d[i][0] == '_':
   delete_list.append(i)
 print(delete_list)
 for i in range(len(delete_list)):
  list_d.remove(list_d[delete_list[i] - i])
 print(list_d)
 for i in range(len(list_d)): #Создаём словарь с рангами букв входного текста
  cypher_rank[list_d[i][0]] = i+1
 print(len(cypher_rank))
 print(len(letters_ranking))
 for i in range(len(cypher)): #По сформированному словарю восстанавлиаем исходный текст и печатаем его в файл
  if cypher[i] == ',' or cypher[i] == '.' or  cypher[i] == ':' or  cypher[i] == '-' or cypher[i] == '_':
   print(" ")
  else:
   cypher[i] = letters_ranking[cypher_rank[cypher[i]]]
 print("\n")
 f = open('text.txt', 'w')
 for lines in cypher:
  f.write(lines)

def encode_vijn(text, keytext):
    f = lambda arg: alp[(alp.index(arg[0])+alp.index(arg[1])%26)%26]
    return ''.join(map(f, zip(text, cycle(keytext))))


def decode_vijn(coded_text, keytext):
    f = lambda arg: alp[alp.index(arg[0])-alp.index(arg[1])%26]
    return ''.join(map(f, zip(coded_text, cycle(keytext)))) 


def main():
 mode = int(input("Введите номер задания:"))
 if mode == 1:
  lines = fromFileText("input.txt")
  special_letters = ['ь','ы','ъ']
  split_lines = lines.split()
  #print(lines)
  ifIsOpenText1(lines, special_letters)
  ifIsOpenText2(lines)
 if mode == 2:
  matrix = fromFileNums("input3.txt")
  #matrix = matrix.split()
  for lines in matrix:
   print(lines)
  decrypt_lines_cols(matrix)
 if mode == 3:
  cypher = fromFileText("cyphertext.txt")
  cypher = cypher.split()
  #print(cypher)
  encryption(cypher)
 if mode == 4:
  visiner = fromFileText("visiner.txt")
  #print(visiner)
  decode_vijn(visiner,keytext)





if __name__ == "__main__":
	main()

