// test_share.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	fstream fs;
	fs.open("\\\\172.16.2.213\\1234\\hello.txt",ios::out|ios::app);
	//fs.open("D:\\1234\\hello.txt", ios::out|ios::app);
	fs << "my name is hjj!\n";
	fs.close();
    return 0;
}

