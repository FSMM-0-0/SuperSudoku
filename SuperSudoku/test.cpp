#include <cstdio>
#include <algorithm>
#include <cstring>

void funn()
{
	int empty[10];
	int sum = 0;

	//随机生成每个3*3内空格数量
	while (sum < 30 || sum > 60) {
		sum = 0;

		empty[1] = rand() % 8 + 2;
		printf("%d ", empty[1]);
		sum += empty[1];
		for (int i = 2; i <= 9; i++) {
			if (sum / (i - 1) >= 5)  //当前空格数过多，生成2~5
				empty[i] = rand() % 4 + 2;
			else                    //当前空格数过少，生成6~9
				empty[i] = rand() % 4 + 6;
			sum += empty[i];
			printf("%d ", empty[i]);
		}
		printf("\n");
	}
}

