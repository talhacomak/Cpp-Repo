#include <iostream> 
#include <locale.h> 
#include <fstream>
using namespace std; 
int main() 
{
	setlocale(LC_ALL, "Turkish");
		ifstream fileread;
        fileread.open("input.txt", ios::in);
        string okunan;

        while (!fileread.eof())
        {
        	getline(fileread, okunan);
        	cout << okunan << "\n";
        }
	return 0; 
}
