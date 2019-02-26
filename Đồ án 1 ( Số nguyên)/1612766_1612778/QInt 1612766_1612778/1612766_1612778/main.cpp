#include "QInt.h"

int main(int argc, char** argv)
{
	fstream fpInput, fpOutput;
	string str;// Chuỗi lưu từng dòng của input

	string nameFileInput, nameFileOutput;
	//nameFileInput = argv[1];
	//nameFileOutput = argv[2];
	//fpInput.open(nameFileInput, ios_base::in);
	//fpOutput.open(nameFileOutput, ios_base::out);
	fpInput.open("input.txt", ios_base::in);
	fpOutput.open("output.txt", ios_base::out);

	if (fpInput.fail())
	{
		cout << "fail to open input file!";
		return 0;
	}
	if (fpOutput.fail())
	{
		cout << "fail to open output file!";
		return 0;
	}
	while (fpInput.eof() == false)
	{
		getline(fpInput, str);// Đọc từng dòng
		string key1 = "";// lưu token thứ 1
		string key2 = "";// token thứ 2
		string key3 = "";// token thứ 3
		string key4 = "";// token thứ 4
		int cnt = 1;// đếm đang ở token thứ mấy
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == ' ')
			{
				cnt++;
				continue;
			}
			if (cnt == 1)
				key1 += str[i];
			else if (cnt == 2)
				key2 += str[i];
			else if (cnt == 3)
				key3 += str[i];
			else if (cnt == 4)
				key4 += str[i];
		}
		if (key4 == "")
		{
			if (key2 == "2" || key2 == "10" || key2 == "16")//Trường hợp chuyển từ hệ này sang hệ khác
			{
				if (key1 == "2")
				{
					if (key2 == "2")
						fpOutput << key3;
					else if (key2 == "10")
						fpOutput << ConvertBinToDec(key3) << endl;
					else
						fpOutput << ConvertBinToHex(key3) << endl;
				}
				else if (key1 == "10")
				{
					if (key2 == "2")
						fpOutput << ConvertDecToBin(key3) << endl;
					else if (key2 == "10")
						fpOutput << key3 << endl;
					else
						fpOutput << ConvertDecToHex(key3) << endl;
				}
				else//key1==16
				{
					if (key2 == "2")
						fpOutput << ConvertHexToBin(key3) << endl;
					else if (key2 == "10")
						fpOutput << ConvertHexToDec(key3) << endl;
					else
						fpOutput << key3 << endl;
				}
			}
			else // có thể là ror,rol hoặc ~
			{
				if (key1 == "2")
				{
					QInt q(key3, "bin");
					if (key2 == "ror")
						q = ror(q);
					else if (key2 == "rol")
						q = rol(q);
					else
						q = ~q;
					fpOutput << q.OutputBinary() << endl;
				}
				else if (key1 == "10")
				{
					QInt q(key3);
					if (key2 == "ror")
						q = ror(q);
					else if (key2 == "rol")
						q = rol(q);
					else
						q = ~q;
					fpOutput << q.OutputDecimal() << endl;
				}
				else
				{
					QInt q(key3, "hex");
					if (key2 == "ror")
						q = ror(q);
					else if (key2 == "rol")
						q = rol(q);
					else
						q = ~q;
					fpOutput << q.OutputHex() << endl;
				}
			}
		}
		else // Các thao tác trên bit cũng như các phép toán trên bit còn lại
		{
			if (key3 == "<<")
			{
				if (key1 == "2")
				{
					QInt a(key2, "bin");
					a = a << (stoi(key4));
					fpOutput << a.OutputBinary() << endl;
				}
				else if (key1 == "10")
				{
					QInt a(key2);
					a = a << (stoi(key4));
					fpOutput << a.OutputDecimal() << endl;
				}
				else//key1==16
				{
					QInt a(key2, "hex");
					a = a << (stoi(key4));
					fpOutput << a.OutputHex() << endl;
				}
			}
			else if (key3 == ">>")
			{
				if (key1 == "2")
				{
					QInt a(key2, "bin");
					a = a >> (stoi(key4));
					fpOutput << a.OutputBinary() << endl;
				}
				else if (key1 == "10")
				{
					QInt a(key2);
					a = a >> (stoi(key4));
					fpOutput << a.OutputDecimal() << endl;
				}
				else//key1==16
				{
					QInt a(key2, "hex");
					a = a >> (stoi(key4));
					fpOutput << a.OutputHex() << endl;
				}
			}
			else if (key1 == "2")
			{
				QInt a(key2, "bin");
				QInt b(key4, "bin");
				QInt res;
				if (key3 == "+")
					res = a + b;
				else if (key3 == "-")
					res = a - b;
				else if (key3 == "*")
					res = a*b;
				else if (key3 == "/")
					res = a / b;
				else if (key3 == "&")
					res = a&b;
				else if (key3 == "|")
					res = a | b;
				else if (key3 == "^")
					res = a^b;
				fpOutput << res.OutputBinary() << endl;
			}
			else if (key1 == "10")
			{
				QInt a(key2);
				QInt b(key4);
				QInt res;
				if (key3 == "+")
					res = a + b;
				else if (key3 == "-")
					res = a - b;
				else if (key3 == "*")
					res = a*b;
				else if (key3 == "/")
					res = a / b;
				else if (key3 == "&")
					res = a&b;
				else if (key3 == "|")
					res = a | b;
				else if (key3 == "^")
					res = a^b;
				fpOutput << res.OutputDecimal() << endl;
			}
			else if (key1 == "16")
			{
				QInt a(key2, "hex");
				QInt b(key4, "hex");
				QInt res;
				if (key3 == "+")
					res = a + b;
				else if (key3 == "-")
					res = a - b;
				else if (key3 == "*")
					res = a*b;
				else if (key3 == "/")
					res = a / b;
				else if (key3 == "&")
					res = a&b;
				else if (key3 == "|")
					res = a | b;
				else if (key3 == "^")
					res = a^b;
				fpOutput << res.OutputHex() << endl;
			}
		}
	}
}