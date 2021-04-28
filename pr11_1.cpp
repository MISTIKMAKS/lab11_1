#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void CreateBinary(char* fname)
{
	ofstream fout(fname, ios::binary);
	if (!fout)
	{
		cerr << "Error opening file '" << fname << "'" << endl;
		return;
	}
	char ch;
	string s;
	do
	{
		cin.get();
		cin.sync();
		cout << "Enter line: "; getline(cin, s);
		//for (unsigned i = 0; i < s.length(); i++) {
			fout.write((char*)&s, sizeof(s));
		//}
		cout << "Continue? (y/n): "; cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	cout << endl;
	fout.close();
}
void PrintBinary(char* fname)
{
	ifstream fin(fname, ios::binary);
	if (!fin)
	{
		cerr << "Error opening file '" << fname << "'" << endl;
		return;
	}
	int c;
	while (fin.read((char*)&c, sizeof(c)))
	{
		cout << c << endl;
		cout << endl;
	}
	cout << endl;
	fin.close();
}
void ProcessBinary(char* fname, char* gname)
{
	ifstream f(fname, ios::binary);
	ofstream g(gname, ios::binary);
	int x, xmin, xmax;
	int k1 = 0, k2 = 0;
	while (f.read((char*)&x, sizeof(x))) {
		if ((k1 == 0) && (x % 2 == 1)) {  //перше непарне 
			xmax = x; k1++;
		}
		if ((k2 == 0) && (x % 2 == 0)) {  //перше парне 
			xmin = x; k2++;
		}
		if ((k2 > 0) && (x < xmin) && (x % 2 == 0)) {
			xmin = x;
		}
		if ((k1 > 0) && (x > xmax) && (x % 2 == 1)) {
			xmax = x;
		}
	}
	g.write((char*)&xmax, sizeof(xmax));
	g.write((char*)&xmin, sizeof(xmin));
	g.close();
	f.close();
}
int main()
{
	char fname[100];
	cout << "Enter file name 1: "; cin >> fname;
	CreateBinary(fname);
	PrintBinary(fname);

	char gname[100];
	cout << "Enter file name 2: "; cin >> gname;
	ProcessBinary(fname, gname);
	PrintBinary(gname);
	return 0;
}