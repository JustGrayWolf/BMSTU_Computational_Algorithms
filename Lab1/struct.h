#include <stdio.h>
#include <stdlib.h>
#define EPS 0.00001

typedef struct data_table
{
	double **table;// таблица значений
	int size_x, size_y;// размер таблицы
}data_table;

// чтение таблицы из файла в структуру
void input_from_file(data_table *d_table, char *fname);

// вычисление полинома Ньютона или Эрмита
double newton_polinom(data_table *d_table, int p, int n, double x);

// поиск индекса начального значения для апроксимации
int select_first_number(data_table *d_table, double x, int n);

// отчистка данных таблицы
void free_table(double **table, int n);