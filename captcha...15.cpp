/*Assignment:3(group C) 
TITLE:Implement a program to generate and verify CAPTCHA image.
Batch:
Roll no.:
*/
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
static const char arr[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";
int strlength = sizeof(arr) - 1;
	char randomno()
	{
	return arr[rand() % strlength];
	}

int main()
{
	int ch,roll,flag=0;
	char str[5],name[5],code[5];

	do
	{
	cout<<"\t\t\tName: ";
	cin>>name;
	cout<<"\t\t\tRoll no: ";
	cin>>roll;
	cout<<"\t\t\tCaptcha: ";
	srand(time(0));
	for( int i = 0; i <5; ++i)
	{
	  str[i] = randomno();
	}
	for(int i=0;i<5;i++)
	cout << str[i];
	cout<<"\n\t\t\tEnter Captcha: ";
	cin>>code;
	for(int i=0;i<5;i++)
	{
	if(str[i]==code[i])
	{
	flag=0;
	}
	else
	{
	flag=1;		
	break;
	}
	}
	if(flag==0)
	{
	cout<<"\t\t\tCode Match..!!";
	}
	else
	{
	cout<<"\t\t\tInvalid Code please try again...!!!";
	}
	cout<<"\n\t\t\t-------------------";
	cout<<"\n\t\t\t1.Refresh\t2.Exit ";
	cin>>ch;
	}while(ch==1);
 }
/*OUTPUT:
ccl@ccl-OptiPlex-3020:~/Desktop/te40$ g++ image.cpp
ccl@ccl-OptiPlex-3020:~/Desktop/te40$ ./a.out
			Name: poonam
			Roll no: 40
			Captcha: rfL&5
			Enter Captcha: rfL&5
			Code Match..!!
			-------------------
			1.Refresh	2.Exit 1
			Name: pallavi
			Roll no: 36
			Captcha: XTa9b
			Enter Captcha: Xta9b
			Invalid Code please try again...!!!
			-------------------
			1.Refresh	2.Exit 2
*/


