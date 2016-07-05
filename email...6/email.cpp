/*Assignment no.:6(group A)
Title:Write a program in C++ /Python to analyze email header.
Batch:*/
//-------------------------------------------------------------
#include<iostream>
#include<fstream>
using namespace std;
int main()
{
char io;
ifstream file("emai.txt");
string search_str1 = "Delivered-To:" ;
string search_str2 = "Date:" ;
string search_str3 = "Subject:" ;
string search_str4 = "From:" ;
string search_str5 = "client-ip=" ;
string line ;
if(!file)
   {
     cout<<"\nGIVEN FILE DOES NOT EXIST";
   }
else
 {
      cout<<"\nGIVEN FILE CONTENTS ARE\n";
	while(getline( file, line ))
 	 {
	  if( line.find(search_str1) != string::npos )
          cout<< line << '\n' ;
	  if( line.find(search_str2) != string::npos )
          cout<< line << '\n' ;
	  if( line.find(search_str3) != string::npos )
          cout<< line << '\n' ;
	  if( line.find(search_str4) != string::npos )
          cout<< line << '\n' ;
	  if( line.find(search_str5) != string::npos )
          cout<< line << '\n' ;
	 }
  file.close();
 }
return 0;
}
//*OUTPUT:
/*ccl@ccl-OptiPlex-3020:~/Desktop$ g++ file.cpp
ccl@ccl-OptiPlex-3020:~/Desktop$ ./a.out
GIVEN FILE CONTENTS ARE
Delivered-To: pallavi82.karpe@gmail.com
Received-SPF: pass (google.com: domain of gaikwadashwini481@gmail.com designates 2607:f8b0:4003:c01::22f as permitted sender)
client-ip=2607:f8b0:4003:c01::22f;
Date: Mon, 9 Feb 2015 09:15:03 +0530
Subject: oops mcq....
From: ashwini gaikwad <gaikwadashwini481@gmail.com>*/
