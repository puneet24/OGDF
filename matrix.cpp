#include<iostream>

using namespace std;

//MATRIX class for implementing all the inbuilt functions and mainly for compiling encapsulation
class matrix
{
	int n,m;
	float **ptr;
	public:
	//constructor 
	matrix()
	{
		n=m=0;
	}
	matrix(int x,int y)
	{
		n=x;
		m=y;
		ptr=new float*[n];
		for(int i=0;i<n;i++)
		{
			ptr[i]=new float[m];
		}
	}
	//constructor ends
	void read()
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
				cin>>ptr[i][j];
		}
	}
	void show()
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
				cout<<ptr[i][j]<<" ";
			cout<<endl;
		}
		cout<<endl;
	}
	friend matrix operator+(matrix,matrix);	//operator overloading
	friend matrix operator*(matrix,matrix);	//operator overloading
	friend matrix operator-(matrix,matrix); //operator overloading
	friend float* jordan(matrix);	//for solving equations 
	friend void row_transform(matrix,int,int);	//swapping row transform
	friend void col_transform(matrix,int,int);	//swapping column transform
};

//function definition
matrix operator+(matrix m1,matrix m2)
{		
	if(m1.n==m2.n&&m1.m==m2.m)
	{
		matrix m3(m1.n,m1.m);
		for(int i=0;i<m1.n;i++)
		{
			for(int j=0;j<m1.m;j++)
			{
				m3.ptr[i][j]=m1.ptr[i][j]+m2.ptr[i][j];
			}
		}
		return m3;
	}
	matrix m3;
	return m3;
}

void row_transform(matrix m1,int i,int j)
{
	for(int k=0;k<m1.m;k++)
	{
		int temp=m1.ptr[i][k];
		m1.ptr[i][k]=m1.ptr[j][k];
		m1.ptr[j][k]=temp;
	}
}

void col_transform(matrix m1,int i,int j)
{
	for(int k=0;k<m1.n;k++)
	{
		int temp=m1.ptr[k][i];
		m1.ptr[k][i]=m1.ptr[k][j];
		m1.ptr[k][j]=temp;
	}
}

float* jordan(matrix m1)
{
	float *arr;
	arr=new float[m1.n];
	int a=m1.n;
	int b=m1.m;
	for(int i=0;i<a-1;i++)
	{
		if(m1.ptr[i][i]==0)
		{
			for(int j=i+1;j<a;j++)
			{
				if(m1.ptr[j][i]==0)
					continue;
				else
				{
					row_transform(m1,i,j);
					break;
				}
			}
		}
		for(int j=i+1;j<a;j++)
		{
			float val=m1.ptr[j][i]/m1.ptr[i][i];
			for(int k=0;k<b;k++)
			{
				m1.ptr[j][k]-=m1.ptr[i][k]*val;
			}
		}
	}
	for(int i=a-1;i>0;i--)
	{
		for(int j=i-1;j>=0;j--)
		{
			float val=m1.ptr[j][i]/m1.ptr[i][i];
			for(int k=0;k<b;k++)
			{
				m1.ptr[j][k]-=m1.ptr[i][k]*val;
			}
		}
	}
	for(int i=0;i<a;i++)
	{
		arr[i]=m1.ptr[i][m1.m-1]/m1.ptr[i][i];
	}
	return arr;
}

matrix operator-(matrix m1,matrix m2)
{		
	if(m1.n==m2.n&&m1.m==m2.m)
	{
		matrix m3(m1.n,m1.m);
		for(int i=0;i<m1.n;i++)
		{
			for(int j=0;j<m1.m;j++)
			{
				m3.ptr[i][j]=m1.ptr[i][j]-m2.ptr[i][j];
			}
		}
		return m3;
	}
	matrix m3;
	return m3;
}

matrix operator*(matrix m1,matrix m2)
{
	if(m1.m==m2.n)
	{
		matrix m3(m1.n,m2.m);
		for(int i=0;i<m1.n;i++)
		{
			for(int j=0;j<m2.m;j++)
			{
				m3.ptr[i][j]=0;
				for(int k=0;k<m2.n;k++)
				{
					
					m3.ptr[i][j]+=m1.ptr[i][k]*m2.ptr[k][j];
				}
			}
		}
		return m3;
	}
	matrix m3;
	return m3;
}

//main function just for implementing and testing the function defined above

int main()
{
	matrix m1(3,3),m2(3,3),m3(3,3),m4(3,4);
	m1.read();
	m2.read();
	m3=m1+m2;
	m3.show();
	m3=m1*m2;
	m3.show();
	float *s;
	m4.read();
	s=jordan(m4);
	return 0;
}
	
