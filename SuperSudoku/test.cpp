#include <cstdio>
#include <algorithm>
#include <cstring>

void funn()
{
	int empty[10];
	int sum = 0;

	//�������ÿ��3*3�ڿո�����
	while (sum < 30 || sum > 60) {
		sum = 0;

		empty[1] = rand() % 8 + 2;
		printf("%d ", empty[1]);
		sum += empty[1];
		for (int i = 2; i <= 9; i++) {
			if (sum / (i - 1) >= 5)  //��ǰ�ո������࣬����2~5
				empty[i] = rand() % 4 + 2;
			else                    //��ǰ�ո������٣�����6~9
				empty[i] = rand() % 4 + 6;
			sum += empty[i];
			printf("%d ", empty[i]);
		}
		printf("\n");
	}
}

