#include<iostream>
#include"Vector.h"
#include"Matrix.h"

using namespace std;

int main()
{
	TMatrix<int> A(3, 3, 2);
	TMatrix<int> G(3, 3);
	TVector<int> B(3);
	TVector<int> Q(3);
	TVector<int> E;
	
	cin >> B;
	cout << "B = ";
	for (int i = 0; i < 3; i++)
	{
		cout << B[i] << " ";
	}
	cout << endl;
	cin >> Q;
	cout << "Q = ";
	for (int i = 0; i < 3; i++)
	{
		cout << Q[i] << " ";
	}
	cout << endl;
	G = A + A;
	TVector<int> R = B;
	TMatrix<int> C = A * B;
	cout << A;
	return 0;
}