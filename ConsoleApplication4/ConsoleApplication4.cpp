#include <iostream>
#include<string>
#include <fstream>
#include <thread>
#include <mutex>
#include <winsock2.h>


#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable: 4996)

using namespace std;



void Potok_One(int &rey)
{// ладноЩас увидишь все дпраодуманно	
	// жду>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>пиши сюда

	while (true) {
		
		char buffer[BUFSIZ];// объявление буфера
		Sleep(1);
		cout << "Введите строку чисел" << endl;
		string str;
		getline(cin, str);
		int i = 0;
		

		//
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
		if (rey == 0)
		{
			ofstream bey("txt.txt");
			bey.open("txt.txt");
			if (bey.is_open()) {
				cout << "Файл открыт. Запись запущена." << endl;
				bey << str;
				bey.close();//  я пытался так, но по идее, поток каждый раз проверяет 1 поток, точнее его переменную, ЕСЛИ Я ПРАВИЛЬНО ДУМАЮ

				rey = 1; // "Оповещает буфер о наличии данных"
			}
			else
				cout << "Файл не открыт" << endl;
			

			FILE* ptrFile1; // готово. Тестиб :всё норм ?
			setbuf(ptrFile1, buffer);
			fputs("str", ptrFile1);// есть идеи ? Я ЕБЛАН

		}
	}
	
}

int Socket()
{

WSAData wsaData;
WORD DLLVersions= MAKEWORD(2,1);
if(WSAStartup(DLLVersions, &wsaData) !=0)
{
	cout << "Error" << endl;
	exit(1);

}

SOCKADDR_IN addr;
int sizeofaddr= sizeof(addr);
addr.sin_addr.s_addr= inet_addr("127.0.0.1");
addr.sin_port = htons(1111);
addr.sin_family = AF_INET;
SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
listen(sListen, SOMAXCONN);


SOCKET ServConnections;
ServConnnections = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
if(ServConnections ==0)
{
	cout << "ERROR!" << endl;
	return 1;

}
else{
	cout << "CONNECTION" << endl;
	send(ServConnections, msg, sizeof(int),  NULL);

}


}


void Potok_Two(int &rey)
{
	
	
	while (true) {



		string str1;
		while(rey!=1) // Цикл, который не дает опросить буфер, пока в него не подадутся данные
		{

		}
		ifstream bey;
		bey.open("txt.txt");
		if (bey.is_open())
		{
			cout << "Файл открыт. Считывание файла" << endl;
			bey >> str1;
			bey.close();
			rey = 0; //  Возвращаю ноль, что бы все бесконечно шло по кругу

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
	int rey = 0;
	Potok_One(rey);
	thread th(Potok_Two, ref(rey));
	
}
