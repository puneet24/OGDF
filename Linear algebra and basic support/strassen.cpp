/*
 * $Revision: 2626 $
 *
 *   $NAME	: Puneet Agarwal $
 *   $Date 	: Mon Mar  6 16:04:29 IST 2014 $
 *   $PROGRAM   : STRASSEN ALGORITHM
 *   $OS	: ubuntu 13.04
 *   $COMPILER  : gcc version 4.7.3 (Ubuntu/Linaro 4.7.3-1ubuntu1)
 ***************************************************************/

/** \file
 * \brief Implementation of "STRASSEN ALGORITHM" for matrix
 * multiplication . And other basic functionalities for performing 
 * this algorithm like funtions (input matrix ,show matrix ,submatrix
 * multiplication (naive method), Addition ,Subtraction of matrices.
 *
 * \This program uses OGDF's header file named Array2D.h for
 * using Array2D class and thier basic functionalities for
 * applying STRASSEN matrix multiplication algorithm .
 *
 * \I have used OGDF_ASSERT for checking that whether the matrix 
 * is square or not. So while debugging it can be figured out 
 * easily that whats the mistake .
 *
 * This program will ask user to enter two equal sized matrix 
 * and will display matrix multiplication of the two given
 * matrix.
 *
 * In almost all the function reference is used to avoid 
 * unnecessary copying of whole 2d array.
 *
 * Standarad input output is used .
 
***************************************************************/

/*
 * Input of the program in the format :-
 * row of matrix1
 * col of matrix1
 * matrix1 
 * row of matrix2
 * col of matrix2
 * matrix2  
 *   
 * Input can be saved in the file in this format.
 * And in the terminal :-
 * ./a.out < filename > out  
 * it will generate the matrix multiplication of two matrix 
 * in the out file.
 
 * Example of input file :-
 
8
8
92   23   79   10   13   85   60   42  
19   47   71   40   66   51   30   63  
 7   49   14   69   17   82   48   22 
34   55   45   81   99   27   68   78  
54   59   73  100   35   67   21   38  
83   87   94   43   80    3   16   64 
11   91   70   65   46    4   15    1  
26   77   90   24   44   50   31   52
 
8
8
92   23   79   10   13   85   60   42  
19   47   71   40   66   51   30   63  
 7   49   14   69   17   82   48   22 
34   55   45   81   99   27   68   78  
54   59   73  100   35   67   21   38  
83   87   94   43   80    3   16   64 
11   91   70   65   46    4   15    1  
26   77   90   24   44   50   31   52

 * Ouput file will be like : -

19303 24474 27376 17964 16910 19207 14517 16009 
14263 24237 25014 22464 19058 18759 13283 17519 
12843 21144 21622 17459 20725 8782 10325 16157 
17605 30411 32411 29559 25041 22458 17307 21815 
18670 25823 27720 24695 24960 20815 18614 23006 
17818 24334 28987 24984 19268 28994 18978 20965 
8448 16039 16109 19616 16438 16275 12456 14876 
13520 23718 24623 21307 18580 19987 13623 17402

 ***************************************************************/

#include <ogdf/basic/Array2D.h>
#include <iostream>

using namespace std;
using namespace ogdf;

// Function for reading matrix 
template<class E>
void input(Array2D<E> &a)
{
	//cout<<endl;
	int row,col;
	//cout<<"Row	:	";
	cin>>row;
	//cout<<endl<<"Col	:	";
	cin>>col;
	//using inbuilt paramaterised constructor
	a.init(0,row-1,0,col-1);
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			cin>>a(i,j);
		}
	}
}

//Function for displaying matrix
//Argument List : object of Array2D<E>
template<class E>
void show(Array2D<E> &aka)
{	
	// Inbulit functions used for reading index values and dimensions of matrix
	int starti=aka.low1(),startj=aka.low2(),endi=aka.high1(),endj=aka.high2();
	for(int i=starti;i<=endi;i++)
	{
		cout<<endl;
		for(int j=startj;j<=endj;j++)
		{
			cout<<aka(i,j)<<" ";
		}
	}
	cout<<endl;
}

//calculates the submatrix from any Array2D<E> given in the argument from index (a,b) to index (c,d)
//Argument List : object of Array2D<E>,index (a,b,c,d) of matrix to be fetched
template<class E>
void submatrix(const Array2D<E> &obj,int a,int b,int c,int d,Array2D<E> &obj2)
{
	int row=c-a+1,col=d-b+1;
	//constructor used
	obj2.init(0,row-1,0,col-1);
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			obj2(i,j)=obj(i+a,j+b);
		}
	}
}

//Function for finding matrix multiplication using naive approach
//only square matrix multiplication with same size and dimensions
template<class E>
void mul(const Array2D<E> &a,const Array2D<E> &b,Array2D<E> &obj)
{
	int arow=a.size1();
	int acol=a.size2();
	int brow=b.size1();
	int bcol=b.size2();
	OGDF_ASSERT(arow==acol && acol==brow && brow==bcol);  	//checking matrix is square and equal or not
	int ai=a.low1(),aj=a.low2(),bi=b.low1(),bj=b.low2();
	obj.init(0,arow-1,0,arow-1,0);
	for(int i=0;i<arow;i++)
		for(int j=0;j<acol;j++)
			for(int k=0;k<brow;k++)
				obj(i,j)+=a(i+ai,k+aj)*b(k+bi,j+bj);
}

// Function for addition of 2 matrices of same size	
template<class E>
void add(const Array2D<E> &aobj,const Array2D<E> &bobj,Array2D<E> &cobj)
{
	int astarti=aobj.low1(),astartj=aobj.low2(),arow=aobj.size1(),acol=aobj.size2();	
	int bstarti=bobj.low1(),bstartj=bobj.low2(),brow=bobj.size1(),bcol=bobj.size2();
	//Array2D<E> c(0,arow-1,0,acol-1);	
	cobj.init(0,arow-1,0,acol-1);
	for(int i=0;i<arow;i++)
	{
		for(int j=0;j<acol;j++)
			cobj(i,j)=aobj(i+astarti,j+astartj)+bobj(i+bstarti,j+bstartj);
	}
}
 
 //FUnction for subtraction of 2 matrics
 template<class E>
void sub(const Array2D<E> &aobj,const Array2D<E> &bobj,Array2D<E> &cobj)
{
	int astarti=aobj.low1(),astartj=aobj.low2(),arow=aobj.size1(),acol=aobj.size2();	
	int bstarti=bobj.low1(),bstartj=bobj.low2(),brow=bobj.size1(),bcol=bobj.size2();
	//Array2D<E> c(0,arow-1,0,acol-1);	
	cobj.init(0,arow-1,0,acol-1);
	for(int i=0;i<arow;i++)
	{
		for(int j=0;j<acol;j++)
			cobj(i,j)=aobj(i+astarti,j+astartj)-bobj(i+bstarti,j+bstartj);
	}
}
 

//.................................STRASSEN METHOD IMPLEMENTATION..........................................................................
template<class E>		
void strassen(const Array2D<E> &a,const Array2D<E> &b,Array2D<E> &c)
{
	int astarti=a.low1(),astartj=a.low2(),arow=a.size1(),acol=a.size2();	
	int bstarti=b.low1(),bstartj=b.low2(),brow=b.size1(),bcol=b.size2();
	OGDF_ASSERT(arow==acol && acol==brow && brow==bcol);	 //checking matrix is square and equal or not
	if(arow<=2)
	{
		mul(a,b,c);	// naive method for calculating matrix multiplication of size less than or equal to 4
	}
	else
	{
		int val1=arow/2-1;
		int val2=arow-1;
		Array2D<E> a11,a12,a21,a22,b11,b12,b21,b22;
		submatrix(a,astarti,astartj,astarti+val1,astartj+val1,a11);
		submatrix(a,astarti,astartj+val1+1,astarti+val1,astartj+val2,a12);
		submatrix(a,astarti+val1+1,astartj,astarti+val2,astartj+val1,a21);
		submatrix(a,astarti+val1+1,astartj+val1+1,astarti+val2,astartj+val2,a22);
		submatrix(b,bstarti,bstartj,bstarti+val1,bstartj+val1,b11);
		submatrix(b,bstarti,bstartj+val1+1,bstarti+val1,bstartj+val2,b12);
		submatrix(b,bstarti+val1+1,bstartj,bstarti+val2,bstartj+val1,b21);
		submatrix(b,bstarti+val1+1,bstartj+val1+1,bstarti+val2,bstartj+val2,b22);
		//calulating p(i) for applying strassen method
		Array2D<E> obj1,obj2;
		add(a11,a22,obj1);
		add(b11,b22,obj2);
		Array2D<E> p1,p2,p3,p4,p5,p6,p7;
		strassen(obj1,obj2,p1);
		add(a21,a22,obj1);
		strassen(obj1,b11,p2);
		sub(b12,b22,obj2);
		strassen(a11,obj2,p3);
		sub(b21,b11,obj2);
		strassen(a22,obj2,p4);
		add(a11,a12,obj1);
		strassen(obj1,b22,p5);
		sub(a21,a11,obj1);
		add(b11,b12,obj2);
		strassen(obj1,obj2,p6);
		sub(a12,a22,obj1);
		add(b21,b22,obj2);
		strassen(obj1,obj2,p7);
		//calculating submatrix of final result matrix
		Array2D<E> c11,c22,c21,c12,cnn;
		add(p1,p4,c11);
		sub(c11,p5,cnn);
		add(cnn,p7,c11);
		add(p3,p5,c12);
		add(p2,p4,c21);
		add(p1,p3,c22);
		add(c22,p6,cnn);
		sub(cnn,p2,c22);
		c.init(0,val2,0,val2);
		//function call for info of submatrices 
		int c11i=c11.low1(),c11j=c11.low2();
		int c12i=c12.low1(),c12j=c12.low2();
		int c21i=c21.low1(),c21j=c21.low2();
		int c22i=c22.low1(),c22j=c22.low2();
		//Method for grouping of submatrix into 1
		for(int i=0;i<=val1;i++)
		{
			for(int j=0;j<=val1;j++)
			{
				c(i,j)=c11(c11i+i,c11j+j);
				c(i,j+val1+1)=c12(c12i+i,c12j+j);
				c(i+val1+1,j)=c21(c21i+i,c21j+j);
				c(i+val1+1,j+val1+1)=c22(c22i+i,c22j+j);
			}
		}
		
	}
}

//.........................STRASSEN METHOD ENDS.................................................................................


// Main function for checking functionalities of all the functions defined here.
int main()
{
	Array2D<float> matrix1,matrix2;
	input<float>(matrix1);
	input<float>(matrix2);
	show(matrix1);
	show(matrix2);
	Array2D<float> matrix3;
	strassen(matrix1,matrix2,matrix3);
	show(matrix3);
	return 0;
}

/* ............................Program Ends............................................................................................*/


