#include<stdio.h>
struct sudoku{
	int value = 0;
	int location[2];
	int candidate[9];
	int candidate_cnt = 0;
};
bool check_missing_x[9];
bool check_missing_y[9];
bool check_missing_box[9];

sudoku map[9][9];

int missing_cnt = 0;

void scan_horizontal(int x)
{
	for (int i = 0; i < 9; i++)
		check_missing_x[i] = true;

	for (int i = 0; i < 9; i++)
		if (map[x][i].value != 0)
			check_missing_y[map[x][i].value - 1] = false;
}
void scan_vertical(int y)
{
	for (int i = 0; i < 9; i++)
		check_missing_y[i] = true;

	for (int i = 0; i < 9; i++)
		if (map[i][y].value != 0)
			check_missing_y[map[i][y].value - 1] = false;
}
int main()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			scanf_s("%d", &map[i][j].value);
			for (int k = 0; k < 9; k++)
				map[i][j].candidate[k] = 0;
			map[i][j].location[0] = i;
			map[i][j].location[1] = j;
			if (map[i][j].value == 0)
				missing_cnt++;
		}
	}
	while (missing_cnt > 0)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				scan_horizontal(i);
				scan_vertical(j);

				for (int k = 0; k < 9; k++)
				{
					if (check_missing_x[k] && check_missing_y[k] && map[i][j].candidate_cnt >= 0)
					{
						map[i][j].candidate[k]++;
						map[i][j].candidate_cnt++;
					}
				}
				if (map[i][j].candidate_cnt == 1)
				{
					map[i][j].candidate_cnt = -1;
					for (int k = 0; k < 9; k++)
					{
						if (map[i][j].candidate[k] >= 1)
						{
							map[i][j].value = k + 1;
							missing_cnt--;
							break;
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%d ", map[i][j].value);
		}
		printf("\n");
	}
}