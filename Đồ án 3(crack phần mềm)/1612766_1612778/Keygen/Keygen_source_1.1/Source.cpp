#include<iostream>

using namespace std;

int main()
{
	int id;
	int serial = 0;
	cout << "Nhap vao so ID(toi da 4 so): ";
	cin >> id;
	serial = 6*(id + 984) - 1;
	cout << "So serial la: " << serial << endl;
	system("pause");
	return 0;
}