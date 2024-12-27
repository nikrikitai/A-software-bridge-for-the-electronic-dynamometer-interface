#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include "xserial.hpp"
using namespace std;



class Data
{
public:

	Data(std::string num, std::time_t t);
	~Data();


	void Write_into_file(std::string date_now) {

		std::ofstream out;  // поток для записи
		out.open(date_now, ios::app);  // открываем файл для записи
		if (out.is_open()) {
			out << time_when_write <<","<< std::stof(number_from_comport) << std::endl;
		}
		out.close();

	}


private:

	std::string number_from_comport;
	std::time_t time_when_write;

};

Data::Data(std::string num, std::time_t t)
{
	number_from_comport = num;
	time_when_write = t;

}


Data::~Data()
{
}


int main()
{
	xserial::ComPort com;
	std::time_t time_from_start; //время получения данных из компорта
	std::string data_from_comport; // данные из компорта
	int numer_of_comport;

	std::time_t time_now = std::time(0);
	std::tm tm; // Создаем структуру tm

	// Используем localtime_s для безопасного получения локального времени
	localtime_s(&tm, &time_now); // Передаем указатели на tm и time_now

	char date[20];
	strftime(date, sizeof(date), "%Y-%m-%d", &tm); // Форматируем дату
	
	std::string str_date = date;
	str_date += ".txt";
	std::cout << str_date << "\n";
	// Функция печатает в терминале список доступых портов.
	com.printListSerialPorts();
	//  Функция возарщает список доступых портов.
	std::vector<std::string> listSerials;
	com.getListSerialPorts(listSerials);

	

	cout << "Enter number of comport:";
	cin >> numer_of_comport;



	com.open(numer_of_comport);
	do
	{
		if (com.getStateComPort()) {
			bool flag = false;
			std::string data_for_write;
			data_from_comport = com.getLine();
			data_for_write = data_from_comport.substr(5, 8);
			
			time_from_start = clock();
			Data data(data_for_write, time_from_start);
			cout << data_from_comport << " " << time_from_start << "\n";
			data.Write_into_file(str_date);
			
		}
		else
		{
			cout << "Comport no open" << "\n";
		}

	} while (true);

}


