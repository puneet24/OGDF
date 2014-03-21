

#include <ogdf/basic/Array2D.h>
#include <iostream>

using namespace std;
using namespace ogdf;

// Function for reading matrix 
template<class E>
Array2D<E> input()
{
	cout<<endl;
	int row,col;
	cout<<"Row	:	";
	cin>>row;
	cout<<endl<<"Col	:	";
	cin>>col;
	//using paramaterised constructor already defined in Array2D.h header fle
	Array2D<E> a(0,row-1,0,col-1,0);
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			cin>>a(i,j);
		}
	}
	cout<<endl;
	return a;
}
//....function ends..................

//Function for displaying matrix
template<class E>
void show(Array2D<E> a)
{	
	//functions used for index values and dimensions of matrix
	int starti=a.low1(),startj=a.low2(),endi=a.high1(),endj=a.high2();
	for(int i=starti;i<=endi;i++)
	{
		cout<<endl;
		for(int j=startj;j<=endj;j++)
		{
			cout<<a(i,j)<<" ";
		}
	}
	cout<<endl;
}

//function for row transformation in matrix with arguments row numbers to be changed
template<class E>
void row_transform(Array2D<E> &m1,int i,int j)
{
	int len=m1.size1();
	for(int k=0;k<len;k++)
	{
		int temp=m1(i,k);
		m1(i,k)=m1(j,k);
		m1(j,k)=temp;
	}
}
//........function ends...............

//.....................Function for finding determinant............................................................
//optimised way by making triangular matrix 
template<class E>
float determinant(Array2D<E> obj)
{
	int len=obj.size1();
	float ans=1;
	for(int i=0;i<len-1;i++)
	{
		if(obj(i,i)==0)
		{
			for(int j=i+1;j<len;j++)
			{
				if(obj(j,i)!=0)
				{
					row_transform(obj,i,j);
					break;
				}
			}
		}
		ans*=obj(i,i);
		for(int j=i+1;j<len;j++)
		{
			float val=obj(j,i)/obj(i,i);
			for(int k=0;k<len;k++)
			{
				obj(j,k)=obj(j,k)-val*obj(i,k);
			}
		}
		show(obj);
	}
	return ans*obj(len-1,len-1);
}
//........................determinant function ends.........................................................

//main function for checking functionalities of all the functions defined here.
int main()
{
	Array2D<float> a;
	a=input<float>();
	show(a);
	cout<<determinant(a)<<endl;
	cout<<a.det()<<endl;
	return 0;
}
//..........................end of program....................................................


