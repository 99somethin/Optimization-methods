#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

float f(float x) 
{
	float a = ((x * x * x) - (12 * x ) + 10);
	return a;
}
void print(float a, float b, float x, float z,float L)
{
	cout << "b=" << b << ", a=" << a << ", y=" << x << ", z=" << z << ", L=" << L << "\n" << endl;
}
int main()
{
	float a = 1;
	float b = 3;
	float l = 0.2;
	float L = 2;
	int k = 0;
	cout << "k=" << k << endl;
	float y = a + ((3 - sqrt(5)) / 2) * (b - a);
	float z = a + b - y;
	while (true) 
	{
		float Fy = f(y);
		float Fz = f(z);
		
		if (Fy <= Fz) 
		{
			a = a;
			b = z;
			z = y;
			y = a + b - z;
			L = abs(b - a);
			print(a, b, y, z,L);
			

			if (L <= l) 
			{
				cout << "L=" << L << endl;
				float x = (a + b) / 2;
				float Fx = f(x);
				cout << "x*=" << x << "; f(x*)=" << Fx << endl;
				break;
			}
			else
			{
				k++;
				cout << "k=" << k << endl;
			}
		}
		else
		{
			a = y;
			b = b;
			y = z;
			z = a + b - z;
			L = abs(b - a);
			print(a, b, y, z,L);
			if (L <= l) 
			{
				cout << "L=" << L << endl;
				float x = (a + b) / 2;
				float Fx = f(x);
				cout << "x*=" << x << "; f(x*)=" << Fx << endl;
				cout << "k=" << k + 1 << endl;
				break;
			}
			else
			{
				k++;
				cout << "k=" << k << endl;
			}
		}
	}
}




