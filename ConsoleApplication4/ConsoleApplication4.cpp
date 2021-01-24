#include <iostream>
#include<string>
#include <fstream>
#include <thread>
#include <mutex>
using namespace std;
void Potok_One()
{
	while (true) {
		cout << "Введите строку чисел" << endl;
		string str;
		getline(cin, str);
		int i = 0;
		while (i != str.length() - 1) //Проверка на кол-во символов и на наличие букв
		{

			if (str.length() >= 64) // Если кол-во символов больше 64, то укорачивается до 64
			{
				str.erase(64, str.length());
			}


			if (isdigit(str[i]) == 0)
			{
				cout << "В строке есть буквы, введите строку занова" << endl;
				str = "";
				getline(cin, str);
				i = -1;


			}
			i++;

		}

		for (int i = 0; i < str.length() - 1; i++) //сортировка по убыванию
		{
			for (int t = 0; t < str.length() - 1; t++)
			{
				if (str[t + 1] > str[t])
				{
					swap(str[t + 1], str[t]);

				}

			}
		}
		string str2 = str;
		str = "";
		for (int i = 0; i < str2.length(); i++) // Заменяем все четные элементы на "KB"
		{
			int q = str2[i] - '0';
			if (q % 2 == 0)
			{
				str += "KB";
			}
			else
			{
				str += str2[i];
			}
		}

		cout << endl;
		ofstream bey;
		bey.open("C:\\Users\\артем\\Desktop\\txt.txt");
		if (bey.is_open()) {
			cout << "Файл открыт. Запись запущена." << endl;
			bey << str;
			bey.close();
		}
		else
			cout << "Файл не открыт" << endl;
	}
}


void Potok_Two()
{
	while (true) {



		string str1;

		ifstream bey;
		bey.open("C:\\Users\\артем\\Desktop\\txt.txt");
		if (bey.is_open())
		{
			cout << "Файл открыт. Считывание файла" << endl;
			bey >> str1;
			bey.close();

		}
		else
			cout << "Файл считывания не открыт" << endl;

		int a = 0;

		cout << str1 << endl;
		for (int i = 0; i < str1.length(); i++)
		{
			if (isdigit(str1[i] != 0))
			{
				int q = str1[i] - '0';
				a += q;
			}
		}
		cout << a;
	}
}

int main()
{

	setlocale(LC_ALL, "rus");
	thread th(Potok_Two);
	Potok_One();
}
