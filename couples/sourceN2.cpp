#include <iostream>
#include <omp.h>

int main()
{
	printf("Before\n");

	int n = 10;
	int p = 5;

//#pragma omp parallel firstprivate(p) //num_threads(20)
//	{
//		//p = 0;
//		p++;
//		int k = omp_get_thread_num();
//		int size = omp_get_num_threads();
//		printf("Hello from thread %d out of %d\n", k, size);
//		printf("p = %d\n", p);
//	}


	int max = 0;
	const int N = 100000;
	int a[N];

#pragma omp parallel //num_threads(4)
{
		printf("Parallel\n");

#pragma omp for //schedule(runtime)
		for (int i = 0; i < N; i++)
		{
#pragma omp atomic
			max++;

			/*if (a[i] > max)
#pragma omp critical
			{
				if (a[i] > max)
					max = a[i];
			}*/



			//printf("iter - %d thread - %d\n",i, omp_get_thread_num());
		}
		






//#pragma omp sections
//		{
//#pragma omp section
//			{
//				printf("section - 0 thread - %d\n", omp_get_thread_num());
//			}
//
//#pragma omp section
//			{
//				printf("section - 1 thread - %d\n", omp_get_thread_num());
//			}
//#pragma omp section
//			{
//				printf("section - 2 thread - %d\n", omp_get_thread_num());
//			}
//#pragma omp section
//			{
//				printf("section - 3 thread - %d\n", omp_get_thread_num());
//			}
//#pragma omp section
//			{
//				printf("section - 4 thread - %d\n", omp_get_thread_num());
//			}
//#pragma omp section
//			{
//				printf("section - 5 thread - %d\n", omp_get_thread_num());
//			}
//		}

	}



	printf("After k = %d\n",max);

	return EXIT_SUCCESS;
}
