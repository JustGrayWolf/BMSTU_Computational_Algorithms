#include "struct.h"

double my_abs(double d)
{
    return (d < 0) ? -d : d;
}

void free_table(double **table, int n)
{
	for (int i = 0; i < n; i++)
		free(table[i]);
	free(table);
}

//создаёт и высчитывает таблицу разделённых разностей
double **creat_div_diff_table(data_table *d_table, int p, int n)
{
	double **div_diff_table = malloc(n * sizeof(double *));
	for (int i = 0; i < n; i++)
	{
		div_diff_table[i] = malloc((n - i) * sizeof(double));
		// заполняет начало таблицы разделённых разностей корнями или 
		// кратными корнями в зависимости от числа столбцов входной таблицы
		div_diff_table[i][0] = d_table->table[p + i / (d_table->size_y - 1)][1];
	}
	for (int i = 1; i < n; i++)
		for (int j = 0 ; j < n - i; j++)
		{
			//в случае не кратных корней вычисляет разделённую разницу
			//иначе записывает значение соответствующей производной
		    if ((my_abs(div_diff_table[j][i - 1] - div_diff_table[j + 1][i - 1]) > EPS) ||\
			(d_table->size_y - 1) <= i)
			    div_diff_table[j][i] = (div_diff_table[j][i - 1] - div_diff_table[j + 1][i - 1]) /\
				(d_table->table[p + j / (d_table->size_y - 1)][0] - d_table->table[p + (i + j) / (d_table->size_y - 1)][0]);
			else
			    div_diff_table[j][i] = d_table->table[p + j / (d_table->size_y - 1)][i + 1];
		}
	return div_diff_table;
}


// ищет значение приближённое к x
int find_medium(double **arr, int size, double x)
{
    int result = 0;
    double delta = my_abs(arr[0][0] - x);
    for (int i = 1; i < size; i++)
    {
        if (my_abs(arr[i][0] - x) < delta)
        {
            delta = my_abs(arr[i][0] - x);
            result = i;
        }
    }
    return result;
}

int select_first_number(data_table *d_table, double x, int n)
{
    n = n / (d_table->size_y - 1) + ((n % (d_table->size_y - 1)) ? 1 : 0);
	int m = find_medium(d_table->table, d_table->size_x, x);
	if (m <= n / 2)
		return 0;
	else if (d_table->size_x - m < (n / 2 + n % 2))
		return d_table->size_x - n;
	else
		return m - n / 2;
}

double newton_polinom(data_table *d_table, int p, int n, double x)
{
	double k = 1, result = d_table->table[p][1];
	double **div_diff_table = creat_div_diff_table(d_table, p, n + 1);
	for (int i = 0; i < n; i++)
	{
		k *= (x - d_table->table[p + i / (d_table->size_y - 1)][0]);
		result += k * div_diff_table[0][i + 1];
	}
	free_table(div_diff_table, n + 1);
	return result;
}

void input_from_file(data_table *d_table, char *fname)
{
	FILE *f = fopen(fname, "r");
	fscanf(f, "%d %d", &(d_table->size_x), &(d_table->size_y));
	d_table->table = malloc(d_table->size_x * sizeof(double *));
	for (int i = 0; i < d_table->size_x; i++)
	{
		d_table->table[i] = malloc(d_table->size_y * sizeof(double));
		for (int j = 0; j < d_table->size_y; j++)
			fscanf(f, "%lf", d_table->table[i] + j);
	}
}