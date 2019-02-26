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
#include "QInt.h"
using namespace std;

string SimplifyNumber(string &str); //Hàm thu gọn chuỗi chứa số cần xuất, xóa bỏ các số 0 ở đầu chuỗi  cần xuất ra

									//Các hàm chuyển chuổi từ hệ này sang chuỗi hệ khác
string ConvertDecToBin(string &str);
string ConvertHexToBin(string &str);

string ConvertBinToDec(string &str);
string ConvertHexToDec(string &str);

string ConvertBinToHex(string &str);
string ConvertDecToHex(string &str);

string AbsoluteValue(string &str); //Hàm trả về giá trị tuyệt đối