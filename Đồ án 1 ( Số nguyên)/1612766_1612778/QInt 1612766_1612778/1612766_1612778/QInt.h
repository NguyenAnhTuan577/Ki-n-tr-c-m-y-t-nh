//Khai báo thư viện
#pragma once
#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <bitset>
#include <string.h>
#include "Library.h"
using namespace std;

class QInt
{
private:
	//Mảng gồm hai số kích thước 64 bit lưu trữ số 128 bit
	long long arrBits[2];
public:
	//Constructor
	QInt();
	QInt(long long otherArr[2]);
	QInt(long long number1, long long number2);
	QInt(string str);// Convert dec to QInt
	QInt(string str, char* type);// Convert bin or hex to QInt

	friend istream& operator >> (istream& is, QInt& q);

	void setBit(string &strPosBin, string sign);
	string Div2(string);
	string ConvertPosDecToBin(string &str);//Hàm chuyển số thập phân không âm thành nhị phân
	string Binary();

	string OutputBinary();
	string OutputDecimal();
	string OutputHex();

	//Operator
	QInt operator=(const QInt &);
	bool operator==(const QInt &);
	QInt operator+(const QInt &);
	QInt operator++();
	QInt operator-(const QInt &);
	QInt operator*(const long long &);
	QInt operator*(const QInt &);
	QInt operator/(QInt &);
	QInt operator&(const QInt &);
	QInt operator|(const QInt &);
	QInt operator^(const QInt &);
	QInt operator~();
	QInt operator<<(long long);
	QInt operator >> (long long);
	bool operator>(const QInt &);
	bool operator>=(const QInt &);
	bool operator!=(const QInt &);
};
//Xoay bit
QInt rol(QInt);
QInt ror(QInt);