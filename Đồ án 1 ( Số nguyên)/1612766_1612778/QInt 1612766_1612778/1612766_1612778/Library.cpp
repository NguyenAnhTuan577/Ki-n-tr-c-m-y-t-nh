#include "Library.h"
#include "QInt.h"

string SimplifyNumber(string &str)
{
	int i = 0;
	while (str[i] == '0')
	{
		i++;
		//if (str[i] != '0')
		//break;
	}
	str = str.erase(0, i);
	return str;
}

string ConvertDecToBin(string &str)
{
	QInt q;
	string temp = AbsoluteValue(str);
	q.setBit(q.ConvertPosDecToBin(temp), str);
	return q.Binary();
}

string ConvertHexToBin(string &str)
{
	str = SimplifyNumber(str);
	string result = "";
	vector<int> a;
	for (int i = 0; i < str.length(); i++)
	{
		if ((str[i] - '0') >= 0 && (str[i] - '0') <= 9)
		{
			a.push_back(str[i] - '0');
		}
		if (str[i] == 'A' || str[i] == 'a')
		{
			a.push_back(10);
		}
		if (str[i] == 'B' || str[i] == 'b')
		{
			a.push_back(11);
		}
		if (str[i] == 'C' || str[i] == 'c')
		{
			a.push_back(12);
		}
		if (str[i] == 'D' || str[i] == 'd')
		{
			a.push_back(13);
		}
		if (str[i] == 'E' || str[i] == 'e')
		{
			a.push_back(14);
		}
		if (str[i] == 'F' || str[i] == 'f')
		{
			a.push_back(15);
		}
	}
	for (int i = 0; i < a.size(); i++)
	{
		bitset<4> x(a[i]);
		string temp = x.to_string();
		result = result + temp;
	}

	return result;
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

string ConvertBinToDec(string &str)
{
	//Chuỗi lưu dấu
	string sign = "";
	if (str.length() == 128 && str[0] == '1')
		sign.push_back('-');
	else
		sign.push_back('+');
	QInt q;
	q.setBit(str, sign);
	QInt temp = q;

	//Đếm số bit vừa đủ để lưu this (không tính bit 0 ở đầu)
	int numberOfBits = 0;
	while (temp != QInt(0, 0))
	{
		numberOfBits++;
		temp = temp >> 1;
	}
	temp = q;
	//Mảng lưu các giá trị BCD
	int arr[11] = { 0 };

	//Dựa vào số bit cần vừa đủ để lưu, biết được số lần dịch bit
	for (int i = 0; i < numberOfBits; i++)
	{
		//Lấy bit đầu tiên
		QInt QBit = (temp >> (numberOfBits - 1))&QInt(0, 1);

		//Dịch trái các phần tử trong mảng lưu BCD
		for (int t = 0; t <11; t++)
		{
			if (t == 10)
			{
				arr[t] = arr[t] << 1;
				break;
			}
			if (((arr[t + 1] >> 15) & 1) == 0)
				arr[t] = (arr[t] << 1);
			else
				arr[t] = (arr[t] << 1) | 1;
		}
		if (QBit == QInt(0, 1))
		{
			arr[10] = arr[10] | 1;
		}
		temp = ((temp << 1) << (128 - numberOfBits)) >> (128 - numberOfBits);
		if (i == numberOfBits - 1)
			break;
		//Cộng 3 với các chữ số >=5 trước khi dịch tiếp
		for (int t = 0; t<11; t++)
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
	return result;

}

string ConvertHexToDec(string &str)
{
	string temp = ConvertHexToBin(str);
	return ConvertBinToDec(temp);
}

string ConvertBinToHex(string &str)
{
	string result = "";
	str = SimplifyNumber(str);
	string temp;
	int length = str.length();
	if (length % 4 == 0)
		temp = str;
	else if (length % 4 == 1)
		temp = "000" + str;
	else if (length % 4 == 2)
		temp = "00" + str;
	else if (length % 4 == 3)
		temp = "0" + str;

	for (int i = 0; i < temp.length(); i = i + 4)
	{
		string digit = temp.substr(i, 4);
		if (digit == "0000")
			result = result + "0";
		else if (digit == "0001")
			result = result + "1";
		else if (digit == "0010")
			result = result + "2";
		else if (digit == "0011")
			result = result + "3";
		else if (digit == "0100")
			result = result + "4";
		else if (digit == "0101")
			result = result + "5";
		else if (digit == "0110")
			result = result + "6";
		else if (digit == "0111")
			result = result + "7";
		else if (digit == "1000")
			result = result + "8";
		else if (digit == "1001")
			result = result + "9";
		else if (digit == "1010")
			result = result + "A";
		else if (digit == "1011")
			result = result + "B";
		else if (digit == "1100")
			result = result + "C";
		else if (digit == "1101")
			result = result + "D";
		else if (digit == "1110")
			result = result + "E";
		else if (digit == "1111")
			result = result + "F";
	}
	return result;
}

string ConvertDecToHex(string &str)
{
	string temp = ConvertDecToBin(str);
	return ConvertBinToHex(temp);
}

string AbsoluteValue(string &str)
{
	string temp = str;
	if (temp[0] == '-')
		temp = temp.erase(0, 1);
	return temp;
}