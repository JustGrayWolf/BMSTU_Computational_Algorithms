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
double **creat_div_diff_table(data_table *d_table, int p, int n, int ind)
{
	double **div_diff_table = malloc(n * sizeof(double *));
	for (int i = 0; i < n; i++)
	{
		div_diff_table[i] = malloc((n - i) * sizeof(double));
		// заполняет начало таблицы разделённых разностей корнями
		div_diff_table[i][0] = d_table->table[p + i][ind];
	}
	for (int i = 1; i < n; i++)
		for (int j = 0 ; j < n - i; j++)
		{
			    div_diff_table[j][i] = (div_diff_table[j][i - 1] - div_diff_table[j + 1][i - 1]) /\
				(d_table->table[p + j][0] - d_table->table[p + i + j][0]);
		}
	return div_diff_table;
}


// ищет значение приближённое к x
int find_medium_x(double **arr, int size, double x)
{
    int result = 1;
    double delta = my_abs(arr[0][1] - x);
    for (int i = 2; i < size; i++)
    {
        if (my_abs(arr[0][i] - x) < delta)
        {
            delta = my_abs(arr[0][i] - x);
            result = i;
        }
    }
    return result;
}

// ищет значение приближённое к y
int find_medium_y(double **arr, int size, double y)
{
    int result = 1;
    double delta = my_abs(arr[1][0] - y);
    for (int i = 2; i < size; i++)
    {
        if (my_abs(arr[i][0] - y) < delta)
        {
            delta = my_abs(arr[i][0] - y);
            result = i;
        }
    }
    return result;
}

int select_first_number_x(data_table *d_table, double x, int nx)
{
	int m = find_medium_x(d_table->table, d_table->size_x, x);
	if (m <= nx / 2)
		return 1;
	else if (d_table->size_x - m - 1 < (nx / 2 + nx % 2))
		return d_table->size_x - nx;
	else
		return m + 1 - nx / 2;
}

int select_first_number_y(data_table *d_table, double y, int ny)
{
	int m = find_medium_y(d_table->table, d_table->size_y, y);
	if (m <= ny / 2)
		return 1;
	else if (d_table->size_y - m - 1 < (ny / 2 + ny % 2))
		return d_table->size_y - ny;
	else
		return m + 1 - ny / 2;
}

double newton_polinom(data_table *d_table, int p, int n, double x, int ind)
{
	double k = 1, result = d_table->table[p][ind];
	double **div_diff_table = creat_div_diff_table(d_table, p, n + 1, ind);
	for (int i = 0; i < n; i++)
	{
		k *= (x - d_table->table[p + i][0]);
		result += k * div_diff_table[0][i + 1];
	}
	free_table(div_diff_table, n + 1);
	return result;
}

void input_from_file(data_table *d_table, char *fname)
{
	FILE *f = fopen(fname, "r");
	fscanf(f, "%d %d", &(d_table->size_y), &(d_table->size_x));
	d_table->table = malloc(d_table->size_y * sizeof(double *));
	for (int i = 0; i < d_table->size_y; i++)
	{
		d_table->table[i] = malloc(d_table->size_x * sizeof(double));
		for (int j = 0; j < d_table->size_x; j++)
			fscanf(f, "%lf", d_table->table[i] + j);
	}
}

//формирует таблицу для апроксимации по x
data_table *form_table(data_table *d_table, int ny, int nx, int px, int py, double x, double y)
{
	data_table *result = malloc(sizeof(data_table));
	result->table = malloc(nx * sizeof(double *));
	result->size_y = nx;
	result->size_x = 2;
	for (int i  = 0; i < nx; i++)
	{
		result->table[i] = malloc(2 * sizeof(double));
		result->table[i][0] = d_table->table[0][px + i];
		result->table[i][1] = newton_polinom(d_table, py, ny - 1, y, px + i);
	}
	return result;
}