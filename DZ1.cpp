// DZ1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>
#include <locale>
#include "Payment.h"
#include <iomanip>

auto randInt = []()
{
	return std::rand() % 101 - 50;
};

void CreateData_1()
{
	std::ofstream file("Numbers1.txt");
	if(file.is_open())
	{
		for (int i = 0; i < 100; ++i)
			file << randInt() << " ";
		file << std::endl;
	}
	else std::cout << "File not found" << std::endl;
	
}

void CreateData_2()
{
	std::ofstream file("Numbers2.txt");
	if (file.is_open())
	{
		std::vector<int> p_Vec(100);
		std::generate(p_Vec.begin(), p_Vec.end(), randInt);
		std::copy(p_Vec.begin(), p_Vec.end(), std::ostream_iterator<int>(file, " "));
	}
	else std::cout << "File not found" << std::endl;
}

template<class __T>
std::vector<__T> LoadData_1(const char fileName[]) {
	std::ifstream file(fileName);
	if (file.is_open())
	{
		std::vector<__T> p_Vec;
		__T p_Temp;
		while (!file.eof()) {
			file >> p_Temp;
			p_Vec.push_back(p_Temp);
		}
		return p_Vec;
	}
	else std::cout << "File not found" << std::endl;
}

template<class __T>
std::vector<__T> LoadData_2(const char fileName[]) {
	std::ifstream file(fileName);
	if (file.is_open())
	{
		std::vector<__T> p_Vec;
		std::copy(std::istream_iterator<__T>(file), std::istream_iterator<__T>(), std::back_inserter(p_Vec));
		return p_Vec;
	}
	else std::cout << "File not found" << std::endl;
}

void Modify1(std::vector<int>& p_Data)
{
	int Max = *(std::max_element(p_Data.begin(), p_Data.end()));
	for(auto It = p_Data.begin(); It < p_Data.end(); ++It)
		if (*It > 0) *It = Max;
}

void Modify2(std::vector<int>::iterator Beg, std::vector<int>::iterator End)
{
	int Max = *(std::max_element(Beg, End));
	for (auto It = Beg; It < End; ++It)
		if (*It > 0) *It = Max;
}

void Modify3(std::vector<int>& p_Data)
{
	int Max = *(std::max_element(p_Data.begin(), p_Data.end()));
	std::for_each(p_Data.begin(), p_Data.end(), [&](int &A) {if(A>0) A = Max; });
}

void Modify4(std::vector<int>& p_Data)
{
	std::ofstream file("Modife.txt");
	if (file.is_open())
	{
		int Max = *(std::max_element(p_Data.begin(), p_Data.end()));
		std::transform(p_Data.begin(), p_Data.end(), std::ostream_iterator<int>(file, " "), [&](int &A) {if (A > 0) A = Max; return A; });
	}
	else std::cout << "File not found" << std::endl;
}

void OutputResult_1(std::vector<int>& p_Data)
{
	std::ofstream file("Result1.txt");
	if (file.is_open())
	{
		std::copy(p_Data.begin(), p_Data.end(), std::ostream_iterator<int>(file, "\n"));
	}
	else std::cout << "File not found" << std::endl;
}

void OutputResult_2(std::vector<int>& p_Data)
{
	std::ofstream file("Result2.txt");
	if (file.is_open())
	{
		auto It = p_Data.begin();
		auto End = p_Data.end();
		while (It != End)
			file << *(It++) << "\n";
	}
	else std::cout << "File not found" << std::endl;
}

void nodeAdd(const char fileName[], const Payment& p_Pay) {

	std::ofstream file(fileName, std::ios::app | std::ios::binary);
	if (file.is_open())
	{
		if (file.is_open()) {
			file.write((char *)&p_Pay, sizeof(p_Pay));
		}
		else std::cout << "File not found";
	}
	else std::cout << "File not found" << std::endl;
}

void nodeDelete(const char fileName[], const char p_NameCompany[], const char p_KindOfWork[], const char p_Date[]) {
	std::ofstream fileBuff("BUFFERDelete", std::ios::out | std::ios_base::binary);
	std::ifstream file(fileName, std::ios_base::binary);
	if (file.is_open()) {
		Payment p_Pay;
		while (!file.eof()) {
			file.read((char*)&p_Pay, sizeof(p_Pay));
			if ((strcmp(p_Pay.m_NameCompany, p_NameCompany) != 0) || (strcmp(p_Pay.m_KindOfWork, p_KindOfWork) != 0) || (strcmp(p_Pay.m_Date, p_Date) != 0))
				fileBuff.write((char *)&p_Pay, sizeof(p_Pay));
		}
		/*remove("Payment");
		rename("BUFFER", "newname");*/
	}
	else std::cout << "File not found" << std::endl;
	file.close();
	fileBuff.close();
}

void nodeChange(const char fileName[], const char p_NameCompany[], const char p_KindOfWork[], const char p_Date[], const Payment& p_Pay = Payment()) {
	std::ofstream fileBuff("BUFFERChange", std::ios::out | std::ios_base::binary);
	std::ifstream file(fileName, std::ios_base::binary);
	Payment Pay;
	if (file.is_open()) {
		while (!file.eof()) {
			file.read((char*)&Pay, sizeof(Pay));
			if ((strcmp(Pay.m_NameCompany, p_NameCompany) != 0) || (strcmp(Pay.m_KindOfWork, p_KindOfWork) != 0) || (strcmp(Pay.m_Date, p_Date) != 0))
				fileBuff.write((char *)&Pay, sizeof(Pay));
			else
				fileBuff.write((char *)&p_Pay, sizeof(p_Pay));
		}
		/*remove("Payment");
		rename("BUFFER", "newname");*/
	}
	else std::cout << "File not found" << std::endl;
	file.close();
	fileBuff.close();
}

void nodeFind(const char fileName[], const char p_NameCompany[], const char p_KindOfWork[], const char p_Date[]){
	std::ofstream fileBuff("FindedNodes", std::ios::out | std::ios_base::binary);
	std::ifstream file(fileName, std::ios_base::binary);
	if (file.is_open()) {
		Payment p_Pay;
		while (!file.eof()) {
			file.read((char*)&p_Pay, sizeof(p_Pay));
			if ((strcmp(p_Pay.m_NameCompany, p_NameCompany) == 0) && (strcmp(p_Pay.m_KindOfWork, p_KindOfWork) == 0) && (strcmp(p_Pay.m_Date, p_Date) == 0))
				fileBuff.write((char*)&p_Pay, sizeof(p_Pay));
		}
		std::cout << "Найденный счета выведены в файле FindedNodes" << std::endl;
	}
	else std::cout << "File not found" << std::endl;
}

void toText(const char fileName[]){
	Payment p_Pay;
	std::ifstream file(fileName, std::ios_base::binary);
	std::ofstream fileText(fileName+std::string("_TEXT.txt"));
	if (file.is_open()) {
		fileText.width(92);
		fileText.fill('-');
		fileText << "\n";
		fileText.fill(' ');
		fileText << std::setw(15) << std::left << "NameCompany";
		fileText << "|";
		fileText << std::setw(15) << std::left << "KindOfWork";
		fileText << "|";
		fileText << std::setw(20) << std::left << "UnitOfMeasurement";
		fileText << "|";
		fileText << std::setw(10) << std::left << "Cost";
		fileText << "|";
		fileText << std::setw(15) << std::left << "Date";
		fileText << "|";
		fileText << std::setw(10) << std::left << "Workload";
		fileText << "|";
		fileText << std::right << "\n";
		fileText.width(92);
		fileText.fill('-');
		fileText << std::right << "\n";
		while (!file.eof()) {
			file.read((char*)&p_Pay, sizeof(p_Pay));
			fileText.fill(' ');
			fileText << std::setw(15) << std::left << p_Pay.m_NameCompany;
			fileText << "|";
			fileText << std::setw(15) << std::left << p_Pay.m_KindOfWork;
			fileText << "|";
			fileText << std::setw(20) << std::left << p_Pay.m_UnitOfMeasurement;
			fileText << "|";
			fileText << std::setw(10) << std::left << p_Pay.m_Cost;
			fileText << "|";
			fileText << std::setw(15) << std::left << p_Pay.m_Date;
			fileText << "|";
			fileText << std::setw(10) << std::left << p_Pay.m_Workload;
			fileText << "|";
			fileText << std::setw(10) << std::endl;
		}
		fileText.width(92);
		fileText.fill('-');
		fileText << std::right << "\n";
		fileText.close();
	}
	else std::cout << "File not found" << std::endl;
}

void toConsole(const char fileName[]) {
	Payment p_Pay;
	std::ifstream file(fileName, std::ios_base::binary);
	std::cout.width(92);
	std::cout.fill('-');
	std::cout << "\n";
	std::cout.fill(' ');
	std::cout << std::setw(15) << std::left << "NameCompany";
	std::cout << "|";
	std::cout << std::setw(15) << std::left << "KindOfWork";
	std::cout << "|";
	std::cout << std::setw(20) << std::left << "UnitOfMeasurement";
	std::cout << "|";
	std::cout << std::setw(10) << std::left << "Cost";
	std::cout << "|";
	std::cout << std::setw(15) << std::left << "Date";
	std::cout << "|";
	std::cout << std::setw(10) << std::left << "Workload";
	std::cout << "|";
	std::cout << "\n";
	std::cout.width(92);
	std::cout.fill('-');
	std::cout << std::right << "\n";
	while (!file.eof()) {
		file.read((char*)&p_Pay, sizeof(p_Pay));
		std::cout.fill(' ');
		std::cout << std::setw(15) << std::left << p_Pay.m_NameCompany;
		std::cout << "|";
		std::cout << std::setw(15) << std::left << p_Pay.m_KindOfWork;
		std::cout << "|";
		std::cout << std::setw(20) << std::left << p_Pay.m_UnitOfMeasurement;
		std::cout << "|";
		std::cout << std::setw(10) << std::left << p_Pay.m_Cost;
		std::cout << "|";
		std::cout << std::setw(15) << std::left << p_Pay.m_Date;
		std::cout << "|";
		std::cout << std::setw(10) << std::left << p_Pay.m_Workload;
		std::cout << "|";
		std::cout << std::setw(10) << std::endl;
	}
	std::cout.width(92);
	std::cout.fill('-');
	std::cout << std::right << "\n";
	file.close();
}

int main()
{
	setlocale(0, "RUSSIAN");
	int choose = 0;
	while (choose != 0)
	{
		std::cout << "1.CreateData() создать текстовый файл с данными в виде 100 случайно сгенерированных целых чисел от -50 до 50" << std::endl;
		std::cout << "2.LoadData() - загрузить данные в последовательный контейнер данного типа" << std::endl;
		std::cout << "3.Modify() - заменить все положительные числа на максимум" << std::endl;
		std::cout << "4.OutputResult() - вывод контейнера - результата" << std::endl;
		std::cout << "0.Выход" << std::endl;
		std::cin >> choose;
		system("cls");
		std::vector<int> Vec;
		switch (choose)
		{
		case 1:
			std::cout << "1. Функция, выгружающая данные с использованием файловых потоков" << std::endl;
			std::cout << "2. Функция, использующая алгоритм generate" << std::endl;
			std::cout << "0.Выход" << std::endl;
			std::cin >> choose;
			switch (choose) {
			case 1: CreateData_1();  break;
			case 2: CreateData_2();  break;
			}
			break;
		case 2:
			std::cout << "1. Функция, загружающая данные с использованием файловых потоков" << std::endl;
			std::cout << "2. Функция, загружающая данные с использованием потоковых итераторов и алгоритма copy" << std::endl;
			std::cout << "3.Выход" << std::endl;
			std::cin >> choose;
			switch (choose) {
			case 1: Vec = LoadData_1<int>("Numbers1.txt"); break;
			case 2: Vec = LoadData_2<int>("Numbers1.txt"); break;
			default:
				break;
			}
			std::copy(Vec.begin(), Vec.end(), std::ostream_iterator<int>(std::cout, "\n"));
			break;
		case 3:
			std::cout << "1. Как шаблонная функция, принимающая последовательный контейнер данного типа" << std::endl;
			std::cout << "2. Как функция, принимающая аргументы-итераторы" << std::endl;
			std::cout << "3. Как функция, использующая алгоритм for_each()" << std::endl;
			std::cout << "4. Как функция, использующая алгоритм transform() и потоковые итератор" << std::endl;
			std::cout << "5.Выход" << std::endl;
			std::cin >> choose;
			switch (choose) {
			case 1: Vec = LoadData_2<int>("Numbers1.txt"); Modify1(Vec); break;
			case 2: Vec = LoadData_2<int>("Numbers1.txt"); Modify2(Vec.begin(), Vec.end()); break;
			case 3: Vec = LoadData_2<int>("Numbers1.txt"); Modify3(Vec); break;
			case 4: Vec = LoadData_2<int>("Numbers1.txt"); Modify4(Vec); break;
			default:
				break;
			}
			std::copy(Vec.begin(), Vec.end(), std::ostream_iterator<int>(std::cout, "\n"));
			break;
		case 4:
			std::cout << "1. Функция, выгружающая данные с использованием файловых потоков" << std::endl;
			std::cout << "2. Функция, использующая алгоритм copy для вывода контейнера в файл с использованием потоковых итераторов" << std::endl;
			std::cout << "3.Выход" << std::endl;
			std::cin >> choose;
			switch (choose) {
			case 1: Vec = LoadData_2<int>("Numbers1.txt"); OutputResult_1(Vec); break;

			case 2: Vec = LoadData_2<int>("Numbers1.txt"); OutputResult_2(Vec); break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		system("pause");
		system("cls");
	}
	choose = 1;
	while (choose != 0)
	{
		std::cout << "1.Добавить запись" << std::endl;
		std::cout << "2.Удалить запись" << std::endl;
		std::cout << "3.Заменить запись" << std::endl;
		std::cout << "4.Поиск записи" << std::endl;
		std::cout << "5.Запись/дозапись" << std::endl;
		std::cout << "6.Преобразовать в текстовый файл" << std::endl;
		std::cout << "7.Показать записи" << std::endl;
		std::cout << "0.Выход" << std::endl;
		std::cin >> choose;
		system("cls");
		std::vector<int> Vec;
		Payment Pay;
		char NameCompany[10];
		char KindOfWork[10];
		char Date[10];
		switch (choose)
		{
		case 1: 
			std::cout << "Введите счет" << std::endl;
			std::cin >> Pay;
			nodeAdd("Payment", Pay);
			break;
		case 2:
			
			std::cout << "Введите удаляемый счет" << std::endl;
			std::cout << "Имя компании: " << std::endl;
			std::cin >> NameCompany;
			std::cout << "Вид работы: " << std::endl;
			std::cin >> KindOfWork;
			std::cout << "Дата: " << std::endl;
			std::cin >> Date;
			nodeDelete("Payment", NameCompany, KindOfWork, Date);
			toText("BUFFERDelete");
			break;
		case 3: 
			std::cout << "Введите заменяемый счет" << std::endl;
			std::cout << "Имя компании: " << std::endl;
			std::cin >> NameCompany;
			std::cout << "Вид работы: " << std::endl;
			std::cin >> KindOfWork;
			std::cout << "Дата: " << std::endl;
			std::cin >> Date;
			std::cout << "Введите новый счет" << std::endl;
			std::cin >> Pay;
			nodeChange("Payment", NameCompany, KindOfWork, Date, Pay);
			toText("BUFFERChange");
			break;
		case 4:
			std::cout << "Введите нужный счет" << std::endl;
			std::cout << "Имя компании: " << std::endl;
			std::cin >> NameCompany;
			std::cout << "Вид работы: " << std::endl;
			std::cin >> KindOfWork;
			std::cout << "Дата: " << std::endl;
			std::cin >> Date;
			nodeFind("Payment", NameCompany, KindOfWork, Date);
			toText("FindedNodes");
			break;
		case 5:
			int N;
			std::cout << "Введите кол-во добавляемых счетов" << std::endl;
			std::cin >> N;
			for (int i = 0; i < N; ++i)
			{
				std::cout << "Введите счет" << std::endl;
				std::cin >> Pay;
				nodeAdd("Payment", Pay);
			}
			break;
		case 6:
			toText("Payment");
			break;
		case 7:
			std::cout << "1.Исходные записи" << std::endl;
			std::cout << "2.Записи после удаления" << std::endl;
			std::cout << "3.Записи после замены" << std::endl;
			std::cout << "0.Выход" << std::endl;
			std::cin >> choose;
			switch (choose) {
			case 1: toConsole("Payment"); break;
			case 2: toConsole("BUFFERDelete"); break;
			case 3: toConsole("BUFFERChange"); break;
			}
			system("pause");
			break;
		default:
			break;
		}
		system("cls");
	}
	/*Payment Pay;
	std::ofstream file;
	file.open("Payment", std::ios::out);
	file.close(); 
	strcpy_s(Pay.m_NameCompany, "Nike");
	strcpy_s(Pay.m_KindOfWork, "Prodavec");
	strcpy_s(Pay.m_Date, "September");
	Pay.m_Cost = 10;
	strcpy_s(Pay.m_UnitOfMeasurement, "DAY");
	strcpy_s(Pay.m_Workload, "3");
	nodeAdd("Payment", Pay);
	strcpy_s(Pay.m_NameCompany, "Adidas");
	strcpy_s(Pay.m_KindOfWork, "Prodavec");
	strcpy_s(Pay.m_Date, "October     ");
	Pay.m_Cost = 3;
	strcpy_s(Pay.m_UnitOfMeasurement, "DAY");
	strcpy_s(Pay.m_Workload, "4");
	nodeAdd("Payment", Pay);
	strcpy_s(Pay.m_NameCompany, "Reebok");
	strcpy_s(Pay.m_KindOfWork, "Prodavec");
	strcpy_s(Pay.m_Date, "September");
	Pay.m_Cost = 3;
	strcpy_s(Pay.m_UnitOfMeasurement, "DAY");
	strcpy_s(Pay.m_Workload, "4");
	nodeAdd("Payment", Pay);
	strcpy_s(Pay.m_NameCompany, "Puma");
	strcpy_s(Pay.m_KindOfWork, "Prodavec");
	strcpy_s(Pay.m_Date, "November ");
	Pay.m_Cost = 1;
	strcpy_s(Pay.m_UnitOfMeasurement, "DAY");
	strcpy_s(Pay.m_Workload, "3");
	nodeAdd("Payment", Pay);
	nodeDelete("Payment", "Nike", "Prodavec", "September");
	toText("BUFFER");*/
    return 0;
}