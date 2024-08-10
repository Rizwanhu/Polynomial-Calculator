#include<iostream>
#include <fstream>
#include <cmath>
//#include "Header.h"
using namespace std;

ifstream rdr("Text.txt");

class polynomial
{
	public:

	int d;
	int* cs;

};

void load_polynomial(polynomial* &ps,int &size ) {

	rdr >> size;
	ps = new polynomial[size]{};
	char ch;
	for (int i = 0; i < size; i++)
	{
		
		rdr >> ps[i].d >> ch;
		int degree = ps[i].d;
		ps[i].cs = new int[ps[i].d + 1];

		for (int j = 0, ci=degree; j < ps[i].d+1; j++,ci--)
		{
			rdr >> ps[i].cs[ci];
		}

	}


}

void print(polynomial* &ps, int &size) {


	for (int i = 0; i < size; i++)
	{

		cout << "P" << i + 1 << "(x): ";
		int temp = ps[i].d;
		for (int j = 0 , f=0, vf=temp; j < ps[i].d + 1; j++,temp--,vf--)
		{
			if (ps[i].cs[vf]>0)
			{	
				f++;
				if(f!=1)
				cout << " + ";
				cout << ps[i].cs[vf];
				if(temp!=0)
				cout << "X^" << temp;
			}

			else if (ps[i].cs[vf]<0)
			{
				cout << ps[i].cs[vf];
				if(temp!=0)
				cout << "X^" << temp;
			}

		}
		cout << endl;
	}




}


polynomial add(polynomial a, polynomial b) {

	polynomial result;
	result.d = max(a.d, b.d);

	result.cs = new int[result.d];

	for (int i = 0; i < result.d+1 ; i++)
	{
		if (a.d<i)
		{
			a.cs[i] = 0;
		}
		else if (b.d<i)
		{
			b.cs[i] = 0;
		}
		result.cs[i] = a.cs[i] + b.cs[i];
	}

	return result;
}




polynomial subtract(polynomial a, polynomial b) {

	polynomial result;
	result.d = max(a.d, b.d);

	result.cs = new int[result.d];

	for (int i = 0; i < result.d + 1; i++)
	{
		if (a.d < i)
		{
			a.cs[i] = 0;
		}
		else if (b.d < i)
		{
			b.cs[i] = 0;
		}
		result.cs[i] = a.cs[i] - b.cs[i];
	}

	return result;

}


int get_constant(polynomial hop, int index) {

	return hop.cs[index];
}


polynomial multiply(polynomial poly1, polynomial poly2) {

	polynomial result;
	result.d = poly1.d + poly2.d;
	result.cs = new int[result.d + 1];

	for (int i = 0; i <= result.d; i++) {
		result.cs[i] = 0;
	}

	for (int i = 0; i <= poly1.d; i++) {
		for (int j = 0; j <= poly2.d; j++) {
			result.cs[i + j] += poly1.cs[i] * poly2.cs[j];
		}
	}

	return result;

}



polynomial indefinite_integral(polynomial p) {
	polynomial result;
	result.d = p.d + 1;

	result.cs = new int[result.d + 1];

	result.cs[0] = 0;

	for (int i = 1; i <= result.d; i++) {
		result.cs[i] = p.cs[i - 1] / (i);
	}

	return result;
}



polynomial derivative(polynomial p) {
	polynomial result;
	result.d = p.d - 1;

	if (result.d < 0) {
		result.d = 0;
		result.cs[0] = 0;
		return result;
	}

	result.cs = new int[result.d + 1];

	for (int i = 0; i <= result.d; i++) {
		result.cs[i] = p.cs[i + 1] * (i + 1);
	}

	return result;
}

/*

polynomial remainder(polynomial a, polynomial b) {

	return divide(a, b);
}



int operator()(int x) const {
	int result = 0;
	for (int i = 0; i <= d; i++) {
		result += cs[i] * std::pow(x, i);
	}
	return result;
}




*/




int main() {

	polynomial* ps;
	int size;
	load_polynomial(ps, size);
	print(ps,size);

	cout << endl;
	cout << "p3(x) = p1(x) + p2(x) : " << endl;
	ps[2] = add(ps[0], ps[1]);
	print(ps, size);

	cout << endl;

	cout << "p3(x) = p1(x) - p2(x) : " << endl;
	ps[2] = subtract(ps[0], ps[1]);
	print(ps, size);

	cout << endl;


	int poly, num;
	cout << "Enter the polynomial (1,2,3) in which you want to find the desired coffiecient of the index : " << endl;
	cin >> poly;
	cout << "Now enter the index of that polynomial whose constant you want : " << endl;
	cin >> num;
	int find_cofficent = get_constant(ps[poly-1], num);
	cout << "The P" << poly << "(x) : with coefficent " << num << " have the constant " << find_cofficent << endl;

	cout << "p3(x) = p1(x) * p2(x) : " << endl;
	ps[2] = multiply(ps[0], ps[1]);
	print(ps,size);

	cout << endl;
/*
	cout << "p3(x) = p1(x) / p2(x) : " << endl;
	ps[2] = divide(ps[0], ps[1]);
	print(ps, size);
*/



	cout << "p3(x) = p1(x) {Derivative} : " << endl;
	ps[2] = derivative(ps[0]);
	print(ps, size);

	cout << endl;


	cout << "p3(x) = p1(x) {indefinite Integral} : " << endl;
	ps[2] = indefinite_integral(ps[0]);
	print(ps, size);

	cout << endl;





	return 0;
}

