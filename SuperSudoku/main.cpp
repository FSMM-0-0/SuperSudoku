#include "work.h"
using namespace std;

int main(int argc, char *argv[])
{
	long _begin_time = clock();
	//srand((unsigned)time(NULL));

	work(argv);

	long _end_time = clock();
	printf("time = %ld ms\n", _end_time - _begin_time);

	return 0;
}