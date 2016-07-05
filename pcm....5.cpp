#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;
class quantized
{
	public:
		int max,min,l,br,n;
		float pam,delta,qv;
		void getdata()
		{
			cout<<"\n enter max,min,l";
			cin>>max>>min>>l;
			cout<<"\n enter pam value";
			cin>>pam;
			delta=(max-min)/l;
		
			qv=delta*pam;
		}
		void display()
		{
			//cout<<"br is"<<br;
			cout<<"delta is"<<delta;
		}
		void zone();
		void quant();
		
};
void quantized::zone()
{
	int a=min,b=min+delta;
	int c=0,d=delta;
	
for(int i=0;i<(l/2);i++)
{
	cout<<"\n zone"<<i<<"is from"<<a<<"to"<<b;
	a=a+delta;
	b=b+delta;	
}
for(int j=(l/2);j<l;j++)
{
	cout<<"\n zone"<<j<<"is from"<<c<<"to"<<d;
	c=c+delta;
	d=d+delta;
}
}
void quantized::quant()
{
	if(0<=qv & qv<=delta)
	{
		
		cout<<"\nvalue is in zone 4";
		cout<<"digital signal is 100";
	}
	else if(min<=qv & qv<=(min+delta))
	{
			cout<<"\nvalue is in zone 0";
			cout<<"digital signal is 100";
	}
		else if((min+delta)<=qv & qv<=(min+(2*delta)))
	{
		if (l >1)
			{
			cout<<"\nvalue is in zone 1";
			cout<<"digital signal is 001";
			}
	}
		else if((min+(2*delta))<=qv & qv<=(min+(3*delta)))
			
	{
			cout<<"\nvalue is in zone 2";
			cout<<"digital signal is 010";
	}
		else if((min+(3*delta))<=qv & qv<=0)

	{
			cout<<"\nvalue is in zone 3";
			cout<<"digital signal is 011";
	}
		else if((delta)<=qv & qv<=((2*delta)))
	{
			cout<<"\nvalue is in zone 5";
			cout<<"digital signal is 101";
	}
		else if(((2*delta))<=qv & qv<=((3*delta)))
	{
			cout<<"\nvalue is in zone 6";
			cout<<"digital signal is 110";
	}
		else if((3*delta)<=qv & qv<=(4*delta))
	{
			cout<<"\nvalue is in zone 7";
			cout<<"digital signal is 111";
	}
}

	

int main()
{
	quantized q;
	q.getdata();
	q.display();
	q.zone();
	q.quant();
	return 0;
}
