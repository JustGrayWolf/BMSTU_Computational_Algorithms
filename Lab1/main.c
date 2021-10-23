#include "struct.h"

int main()
{
	setbuf(stdout, NULL);
	data_table d_table;
	int n;
	double x;
	// чтение таблицы из файла в структуру
	input_from_file(&d_table, "input.txt");
	// ввод x и n
	printf("Введите значение X и степени полинома: ");
	scanf("%lf %d", &x, &n);
	// поиск индекса начального значения для апроксимации
	int p = select_first_number(&d_table, x, (n + 1));
	// вычисление полинома Ньютона или Эрмита и вывод результата
	printf("\nАпроксимированное значение в точке: %lf\n",\
	newton_polinom(&d_table, p, n, x));
	free_table(d_table.table, d_table.size_x);
	return 0;
}