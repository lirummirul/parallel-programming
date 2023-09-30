#include <iostream>
using namespace std;

int max(int &a, int &b)
{
	a = 65;
	if (a > b)
		return a;
	return b;
}


int main()
{
	int k = 5, l = 8;
	double x = 1.0;

	
	printf("max = %d\n", max(k,l));

	printf("k = %d   x = %f    %s\n", k, x, "abcd");
	//cout << "k=" << k << endl;


	const int n = 10;
	int a[n*n];


	int m = 5;
	int* b;

	b = new int[n*n];

	//b[i*n+j]
	// malloc(n * sizeof(int));
	
	srand(time(NULL));

	for (int i = 0; i < n; i++)
	{
		b[i] = rand() % 100;
		//printf("a[%d] = %d\n", i, a[i]);
	}

	for (int i = 0; i < n; i++)
	{
		printf("a[%d] = %d\n", i, b[i]);
	}

	delete b;
	//free(b);



	return EXIT_SUCCESS;
}
