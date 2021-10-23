#include "struct.h"

int main()
{
	setbuf(stdout, NULL);
	data_table d_table;
	int ny, nx;
	double x, y;
	// чтение таблицы из файла в структуру
	input_from_file(&d_table, "input.txt");
	// ввод степени интерполяции и значения аргументов x и y
	printf("Введите степени полинома nx, ny и значения x, y: ");
	scanf("%d%d%lf%lf", &nx, &ny, &x, &y);
	// поиск индекса начальных значений для апроксимации
	int px = select_first_number_x(&d_table, x, (nx + 1));
	int py = select_first_number_y(&d_table, y, (ny + 1));
	//вычисляем значения x
	data_table *x_table = form_table(&d_table, ny + 1, nx + 1, px, py, x, y);
	
	for (int i = 0; i < nx + 1; i++)
		printf("%lf %lf\n", x_table->table[i][0], x_table->table[i][1]);

	// вычисление полинома Ньютона вывод результата
	printf("\nАпроксимированное значение в точке: %lf\n",\
	newton_polinom(x_table, 0, nx, x, 1));
	free_table(d_table.table, d_table.size_y);
	free_table(x_table->table, x_table->size_y);
	free(x_table);
	return 0;
}