#include <iostream>
#include <fstream>
#include "cinemaMain.h"
using namespace std;
void menuTuiGraphicPrint()
{
	cout << "\033[1;31m"
	 << ifstream("../menuTuiGraphic.txt").rdbuf()
	<< "\033[0m";
	getChoice();
}
int main()
{
	menuTuiGraphicPrint();
}
