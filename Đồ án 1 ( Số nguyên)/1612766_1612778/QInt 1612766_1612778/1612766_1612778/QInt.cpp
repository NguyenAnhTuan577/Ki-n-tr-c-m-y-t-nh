 #include "QInt.h"
#include "Library.h"

//Constructor
QInt::QInt()
{
	arrBits[0] = arrBits[1] = 0;
}

QInt::QInt(long long otherArr[2])
{
	arrBits[0] = otherArr[0];
	arrBits[1] = otherArr[1];
}

QInt::QInt(long long number1, long long number2)
{
	arrBits[0] = number1;
	arrBits[1] = number2;
}

QInt::QInt(string str)
{
	arrBits[0] = arrBits[1] = 0;
	string temp = AbsoluteValue(str);
	setBit(ConvertPosDecToBin(temp), str);
}

QInt::QInt(string str, char* type)
{
	string tp = type;
	if (tp == "bin")
	{
		string sign="+";
		if (str.length() == 128 && str[0] == 1)
			sign = "-";
		setBit(str, sign);
	}
	else if (tp == "hex")
	{
		string sign = "+";
		string temp = ConvertHexToBin(str);
		if (temp.length() == 128 && temp[0] == 1)
			sign = "-";
		setBit(temp, sign);
	}
}

istream& operator >> (istream& is, QInt& q)
{
	string temp;
	is >> temp;
	string abValue = AbsoluteValue(temp);
	q.setBit(q.ConvertPosDecToBin(abValue), temp);
	return is;
}

//Hàm trả về kết quả sau khi chia một chuỗi cho 2
string QInt::Div2(string str)
{
	string result = "";
	int d = 0; //Số dư

			   //Xác định vị trí đầu tiên của chuỗi có giá trị khác 0
	int i = 0;
	while (str[i] == '0')
	{
		i++;
	}
	int c;
	if (str[i] == '1')
	{
		c = (str[i] - '0') * 10 + str[i + 1] - '0';
		d = c % 2;
		result.push_back('0' + c / 2);
		i += 2;
	}
	for (i; i < str.length(); i++)
	{
		c = str[i] - '0' + 10 * d;
		d = c % 2;
		result.push_back('0' + c / 2);

	}
	return result;
}

//Hàm chuyển số thập phân không âm thành nhị phân
string QInt::ConvertPosDecToBin(string &str)
{
	string temp = str;
	//Tạo string toàn số 0 chứa kết quả
	string strBinary = "";
	for (int i = 0; i < 128; i++)
	{
		strBinary.push_back('0');
	}
	int bit;
	int i = strBinary.length() - 1;

	while (true)
	{
		int number0 = 0;
		int k = 0;
		while (temp[k++] != NULL)
		{
			if (temp[k] == '0')
			{
				number0++;
			}
		}
		if (number0 == temp.length())
			break;
		else
		{
			bit = (temp[temp.length() - 1] - '0') % 2;
			strBinary[i] = bit + '0';
			temp = Div2(temp);
			i--;
		}
	}
	return strBinary;
}


//Hàm lưu số cần lưu vào QInt dựa trên mảng nhị phân của giá trị tuyệt đối đã tính được
/*void QInt::setBit(string &strPosBin, string sign)
{
	arrBits[0] = arrBits[1] = 0;
	string temp = "";
	if (strPosBin.length() != 128)
	{
		for (int i = 0; i < (128 - strPosBin.length()); i++)
			temp.push_back('0');
		temp = temp + strPosBin;
	}
	else
	{
		temp = strPosBin;
	}

	for (int i = 0; i < 64; i++)
	{
		if (temp[i] == '1')
		{
			arrBits[0] = ((long long)1 << (63 - i) | arrBits[0]);
		}
	}
	for (int i = 64; i < 128; i++)
	{
		if (temp[i] == '1')
		{
			arrBits[1] = ((long long)1 << (127 - i) | arrBits[1]);
		}
	}
	if (sign[0] == '-')
	{
		long long temp1 = ~arrBits[0];
		long long temp2 = ~arrBits[1];
		*this = QInt(temp1, temp2);
		*this = *this + QInt(0, 1);
	}
}
*/
void QInt::setBit(string &strPosBin, string sign)
{
	arrBits[0] = arrBits[1] = 0;
	string temp = "";
	if (strPosBin.length() != 128)
	{
		for (int i = 0; i < (128 - strPosBin.length()); i++)
			temp.push_back('0');
		temp = temp + strPosBin;
	}
	else
	{
		temp = strPosBin;
	}

	for (int i = 0; i < 64; i++)
	{
		if (temp[i] == '1')
		{
			arrBits[0] = ((long long)1 << (63 - i) | arrBits[0]);
		}
	}
	for (int i = 64; i < 128; i++)
	{
		if (temp[i] == '1')
		{
			arrBits[1] = ((long long)1 << (127 - i) | arrBits[1]);
		}
	}
	if (sign[0] == '-')
	{
		*this = ~(*this);
	}
}

//Hàm xuất ra nhị phân của số 64 bit

string QInt::Binary()
{
	bitset<64> x(arrBits[0]);
	bitset<64> y(arrBits[1]);
	string temp1 = x.to_string();
	string temp2 = y.to_string();
	if (arrBits[0] == 0)
		return SimplifyNumber(temp2);
	else
		return SimplifyNumber(temp1) + temp2;
}

//Operator
QInt QInt:: operator=(const QInt &otherQInt)
{
	arrBits[0] = otherQInt.arrBits[0];
	arrBits[1] = otherQInt.arrBits[1];
	return *this;
}

/*Ý tưởng thực hiện toán tử +,-:
Cộng từng cặp tương đương
Nếu cặp arrBit[1] cộng lại bị tràn số, cộng thêm bit 1 vào phép cộng cặp arrBits[0]
*/
QInt QInt::operator+(const QInt &otherQInt)
{
	int carry = 0;
	long long temp1 = arrBits[0] + otherQInt.arrBits[0];
	long long temp2 = arrBits[1] + otherQInt.arrBits[1];
	if (arrBits[1] > 0 && otherQInt.arrBits[1] > 0 && arrBits[1] + otherQInt.arrBits[1] < arrBits[1])
		carry = 1;
	if (arrBits[1] < 0 && otherQInt.arrBits[1] < 0 && arrBits[1] + otherQInt.arrBits[1] > arrBits[1])
		carry = 1;
	temp1 += carry;
	return QInt(temp1, temp2);
}

QInt QInt::operator-(const QInt &otherQInt)
{
	int remainder = 0;
	long long temp1 = arrBits[0] - otherQInt.arrBits[0];
	long long temp2 = arrBits[1] - otherQInt.arrBits[1];
	if (arrBits[1] > 0 && otherQInt.arrBits[1] < 0 && arrBits[1] - otherQInt.arrBits[1] < arrBits[1])
		remainder = 1;
	if (arrBits[1] < 0 && otherQInt.arrBits[1] > 0 && arrBits[1] + otherQInt.arrBits[1] > arrBits[1])
		remainder = 1;
	temp1 += remainder;
	return QInt(temp1, temp2);
}

/*Ý tưởng thực hiện toán tử *:
Chia số nguyên 128 bit thành 4 phần, mỗi phần chứa 32 bit
Số đầu tiên chia thành 4 phần, ký hiệu abcd
Số thứ hai gồm bốn phần xyzt

abcd
*
xyzt
------------
ta tb tc td
zb zc zd
yd yc
td
-----------
Kết quả(Cộng 4 số nguyên 128 bit)

Cách nhân một số 128bit với số 32bit
t
*
abcd
------
dt
ct
bt
at
--------
Kết quả
*/

//Toán tử nhân số 32 bit với số 128 bit
QInt QInt:: operator*(const long long &rhs)
{
	//Chia số 128 bit thành bốn phần
	long long top[4] = { arrBits[0] >> 32, arrBits[0] & 0xffffffff, arrBits[1] >> 32, arrBits[1] & 0xffffffff };

	//Hàng thứ nhất
	QInt firstRow = QInt(0, long long(rhs*top[3]));

	//Hàng thứ hai
	QInt secondRow = QInt(0, long long(rhs*top[2])) << 32;

	//Hàng thứ ba
	QInt thirdRow = QInt(0, long long(rhs*top[1])) << 64;

	//Hàng thứ tư
	QInt fourthRow = QInt(0, long long(rhs*top[2])) << 96;

	return firstRow + secondRow + thirdRow + fourthRow;
}

//Nhân số 128bit với 128bit
QInt QInt::operator*(const QInt &rhs)
{
	QInt temp = rhs;
	//Kiểm tra dấu
	int sign;
	if (*this == QInt(0, 0) || QInt(0, 0) == rhs)
		return QInt(0, 0);
	else if (*this>QInt(0, 0) && temp>QInt(0, 0))
		sign = 0;
	else if (QInt(0, 0)>temp && QInt(0, 0) > *this)
		sign = 0;
	else
		sign = 1;

	//Chia số 128bit thành bốn phần
	long long bottom[4] = { rhs.arrBits[0] >> 32, rhs.arrBits[0] & 0xffffffff, rhs.arrBits[1] >> 32,rhs.arrBits[1] & 0xffffffff };

	//Hàng thứ nhất
	QInt firstRow = *this*bottom[3];

	//Hàng thứ hai
	QInt secondRow = *this*bottom[2] << 32;

	//Hàng thứ ba
	QInt thirdRow = (*this)*bottom[1] << 64;

	//Hàng thứ tư
	QInt fourthRow = (*this)*bottom[0] << 96;

	if (sign == 0)
		return firstRow + secondRow + thirdRow + fourthRow;
	else
		return ~(firstRow + secondRow + thirdRow + fourthRow) + QInt(0, 1);
}

/*Ý tưởng toán tử /
Thực hiện như phép chia hai số nguyên thập phân
*/
QInt QInt::operator/(QInt &rhs)
{
	int sign;
	if (this->arrBits[0] >= 0 && rhs.arrBits[0] >= 0)
		sign = 0;
	else if (this->arrBits[0] < 0 && rhs.arrBits[0] < 0)
		sign = 0;
	else
		sign = 1;
	QInt dividend;
	if (this->arrBits[0] >= 0)
		dividend = *this;
	else
		dividend = (*this << 1) >> 1;
	QInt divisor;
	if (rhs.arrBits[0] >= 0)
		divisor = rhs;
	else
		divisor = (rhs << (long long)1) >> 1;
	QInt Quotient(0, 0), Remainder(0, 0);
	QInt temp;
	int i = 127;
	temp = dividend >> i;
	while (divisor > temp)
	{
		i--;
		temp = dividend >> i;
	}
	dividend = dividend << (128 - i);
	for (int j = 128 - i - 1; j < 128; j++)
	{
		if (temp>divisor || temp == divisor)
		{
			Quotient = (Quotient << 1) | QInt(0, 1);
			Remainder = temp - divisor;
			temp = (Remainder << 1) | ((dividend >> 127)&QInt(0, 1));
			dividend = dividend << 1;
		}
		else
		{
			Quotient = (Quotient << 1);
			Remainder = temp;
			temp = (Remainder << 1) | ((dividend >> 127)&QInt(0, 1));
			dividend = dividend << 1;
		}
	}
	if (sign == 1)
		Quotient = ~Quotient + QInt(0, 1);
	return Quotient;
}

QInt QInt::operator&(const QInt &otherQInt)
{
	long long temp1 = arrBits[0] & otherQInt.arrBits[0];
	long long temp2 = arrBits[1] & otherQInt.arrBits[1];
	return QInt(temp1, temp2);
}

QInt QInt::operator|(const QInt &otherQInt)
{
	long long temp1 = arrBits[0] | otherQInt.arrBits[0];
	long long temp2 = arrBits[1] | otherQInt.arrBits[1];
	return QInt(temp1, temp2);
}

QInt QInt::operator^(const QInt &otherQInt)
{
	long long temp1 = arrBits[0] ^ otherQInt.arrBits[0];
	long long temp2 = arrBits[1] ^ otherQInt.arrBits[1];
	return QInt(temp1, temp2);
}

QInt QInt::operator~ ()
{
	long long temp1 = ~arrBits[0];
	long long temp2 = ~arrBits[1];
	return QInt(temp1, temp2);
}

//Toán tử dịch bit với số lần dịch là số nguyên long long
QInt QInt:: operator<<(long long shift)
{
	//TH dịch nhiều hơn 128 bit, trả về 0
	if (shift >= 128)
		return QInt(0, 0);

	//TH dịch 64 bits
	if (shift == 64)
		return QInt(arrBits[1], 0);

	if (shift == 0)
		return *this;

	if (shift < 64)
	{
		return QInt((arrBits[0] << shift) | (arrBits[1] >> (64 - shift)), (arrBits[1] << shift));
	}

	if ((128 > shift) && (shift > 64))
	{
		return QInt(arrBits[1] << (shift - 64), 0);
	}

	return QInt(0, 0);
}

QInt QInt:: operator >> (long long shift)
{
	//TH dịch nhiều hơn 128 bit, trả về 0
	if (shift >= 128)
		return QInt(0, 0);

	//TH dịch 64 bits
	if (shift == 64)
		return QInt(0, arrBits[0]);

	if (shift == 0)
		return *this;

	if (shift < 64)
	{
		return QInt((arrBits[0] >> shift), ((arrBits[0] >> (64 - shift))) | (arrBits[1] >> shift));
	}

	if ((128 > shift) && (shift > 64))
	{
		return QInt(0, (arrBits[0] >> (shift - 64)));
	}

	return QInt(0, 0);
}

//Toán tử xoay bit
QInt rol(QInt a)
{
	QInt bit = a >> 127;
	if (bit != QInt(0, 0))// bit đầu là bit 1
		return (a << 1) | (QInt(0, 1));
	return a << 1;
}

QInt ror(QInt a)
{
	QInt bit = a &QInt(0, 1);
	if (bit != QInt(0, 0))
		return (a >> 1) | (QInt(0, 1) << 127);
	return a >> 1;
}

//Toán tử so sánh
bool QInt:: operator>(const QInt &rhs)
{
	if (arrBits[0] == rhs.arrBits[0])
	{
		return (arrBits[1] > rhs.arrBits[1]);
	}
	return (arrBits[0] > rhs.arrBits[0]);
}

bool QInt:: operator==(const QInt &rhs)
{
	return ((arrBits[0] == rhs.arrBits[0]) && (arrBits[1] == rhs.arrBits[1]));
}

bool QInt:: operator>=(const QInt &rhs)
{
	return ((*this > rhs) || (*this == rhs));
}

bool QInt:: operator!=(const QInt &rhs)
{
	if (*this == rhs)
		return 0;
	return 1;
}

QInt QInt:: operator++()
{
	return (*this + QInt(0, 1));
}

//Chuyển nhị phân sang thập phân
//Sử dụng thuật toán double-dable, chuyển chuỗi Binary sang dạng BCD(Binary coded decimal)
/*
Ý tưởng: Số 128 bit lưu trữ được số thập phân có khoảng 40 chữ số
Dùng mảng 20 số để lưu giá trị của QInt ở dạng BCD(nhị phân của các chữ số, mỗi số có giá trị từ 0->9, tốn 4 bit một số)
Gán 40 chữ số đều có giá trị 0
Tiến hành dịch bit 128 lần sang trái, (tương ứng với nhân 2, hoặc cộng với chính nó, nhân ngược để ra giá trị thập phân)
Nếu giá trị của một chữ số vượt quá 5, cộng 3 trước khi dịch tiếp để ra được giá trị trong khoảng 0->9
Xuất ra từng chữ số sau khi thực hiện xong thuật toán
*/

/*
Ví dụ với số 243 (8 bit):
0000 0000 0000   11110011   Initialization
0000 0000 0001   11100110   Shift
0000 0000 0011   11001100   Shift
0000 0000 0111   10011000   Shift
0000 0000 1010   10011000   Add 3 to ONES, since it was 7
0000 0001 0101   00110000   Shift
0000 0001 1000   00110000   Add 3 to ONES, since it was 5
0000 0011 0000   01100000   Shift
0000 0110 0000   11000000   Shift
0000 1001 0000   11000000   Add 3 to TENS, since it was 6
0001 0010 0001   10000000   Shift
0010 0100 0011   00000000   Shift
2    4    3
BCD
*/

string QInt::OutputDecimal()
{
	QInt temp(*this);
	if (this->arrBits[0] < 0)
	{
		temp = temp - QInt(0, 1);
		temp = ~temp;
	}
		

	//Đếm số bit vừa đủ để lưu this (không tính bit 0 ở đầu)
	int numberOfBits = 0;
	while (temp != QInt(0, 0))
	{
		numberOfBits++;
		temp = temp >> 1;
	}
	temp = *this;
	if (this->arrBits[0] < 0)
	{
		temp = temp - QInt(0, 1);
		temp = ~temp;
	}
	//Mảng lưu các giá trị BCD
	int arr[11] = { 0 };

	//Dựa vào số bit cần vừa đủ để lưu, biết được số lần dịch bit
	for (int i = 0; i < numberOfBits; i++)
	{
		//Lấy bit đầu tiên
		QInt QBit = (temp >> (numberOfBits - 1));
		QBit = QBit&QInt(0, 1);

		//Dịch trái các phần tử trong mảng lưu BCD
		for (int t = 0; t <10; t++)
		{
			if ((arr[t + 1] >> 15) & 1 == 1)
			{
				arr[t] = (arr[t] << 1);
				arr[t] = arr[t] | 1;
			}
			else
				arr[t] = (arr[t] << 1);
		}
		if (QBit.arrBits[1] != 0)
		{
			arr[10] = ((arr[10] << 1));
			arr[10] = arr[10] | 1;
		}
		else
		{
			arr[10] = ((arr[10] << 1));
		}
		temp = (temp << 1);
		temp = temp << (128 - numberOfBits);
		temp = temp >> (128 - numberOfBits);
		if (i == numberOfBits - 1)
			break;
		//Cộng 3 với các chữ số >=5 trước khi dịch tiếp
		for (int t = 10; t>0; t--)
		{

			//Tách số 16 bit thành 4 số 4 bit
			int num4 = (arr[t] >> 12)&int(15);
			int num3 = (arr[t] >> 8)&int(15);
			int num2 = (arr[t] >> 4) & int(15);
			int num1 = (arr[t] >> 0) & int(15);

			if (num1 >= 5)
			{
				arr[t] = arr[t] + (3 << 0);
			}
			if (num2 >= 5)
			{
				arr[t] = arr[t] + (3 << 4);
			}
			if (num3 >= 5)
			{
				arr[t] = arr[t] + (3 << 8);
			}
			if (num4 >= 5)
			{
				arr[t] = arr[t] + (3 << 12);
			}
		}

	}

	//Xuất các trị của mảng
	string result = "";
	for (int t = 0; t < 11; t++)
	{
		int num1 = (arr[t] >> 12) & 15;
		int num2 = (arr[t] >> 8) & 15;
		int num3 = (arr[t] >> 4) & 15;
		int num4 = (arr[t] >> 0) & 15;
		result.push_back(num1 + '0');
		result.push_back(num2 + '0');
		result.push_back(num3 + '0');
		result.push_back(num4 + '0');
	}
	result = SimplifyNumber(result);
	if (this->arrBits[0] < 0)
		result = "-" + result;
	return result;
}

string QInt::OutputHex()
{
	string temp = this->Binary();
	return ConvertBinToHex(temp);
}

//Hàm xuất ra nhị phân của số 64 bit
string QInt::OutputBinary()
{
	bitset<64> x(arrBits[0]);
	bitset<64> y(arrBits[1]);
	string temp1 = x.to_string();
	string temp2 = y.to_string();
	if (arrBits[0] == 0)
	{
		temp2 = SimplifyNumber(temp2);
		return temp2;
	}
	else
	{
		temp1 = SimplifyNumber(temp1);
		return temp1 + y.to_string();
	}

}
