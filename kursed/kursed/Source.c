#include<stdio.h>
#include<locale.h>
#include<math.h>
#include <string.h>
double sch_y(double x)
{
	double y;
	
		y = (((pow(sin(x), 2) * cos(x)) / (x + 1)) + ((x + 3) / (1 + cos(pow(x,2)))));

	return y;
}
double sch_v(double x)
{
	double y=0;
	if (x > 0)
	{
		for (int k = 3; k <= 9; k++)
		{
			y += pow(x, (-1 * k));
		}
	}
	if (x <= 0)
	{
		y = pow((2 - x), (2 - x));
	}
	return y;
}
//Указатель функции
typedef double (*Tsch) (double);
//Прототипы функции
double sch_y(double);
double sch_v(double);
void result(Tsch, double, double, double);
//интервалы
/* result_1(Tsch f, double xn, double xk, double h)
{
	for (double x = xn + 1; x < xk; x += h)
	{
	printf("\n| x | F(x) |");
	printf("\n|%3.2lf |%3.5lf |", x, f(x));
	}
}
void result_2(Tsch f, double xn, double xk, double h)
{
	for (double x = xn; x < xk; x += h)
	{
		printf("\n| x | F(x) |");
		printf("\n|%3.2lf |%3.5lf |", x, f(x));
	}
}
void result_3(Tsch f, double xn, double xk, double h)
{
	for (double x = xn + 1; x <= xk; x += h)
	{
		printf("\n| x | F(x) |");
		printf("\n|%3.2lf |%3.5lf |", x, f(x));
	}
}*/
void t_result(Tsch f, double xn, double xk, double h)
{
	char t=' ';
	printf("\n|%3cx%3c|%7cF(x)%6c|",t,t,t,t);
	for (double x = xn; x <= xk; x += h)
	{
		
		printf("\n| %5.2lf | %15.10lf |", x, f(x));
	}
}
//график?
void plot(double x0, double x1, Tsch f)
{
	int SCREENW = 40, SCREENH = 40;//размеры поля вывода в символах
	char screen[40][40];
	double x, y[40];
	double ymin = 0, ymax = 0;
	double hx, hy;
	int i, j;
	int xz, yz;
	hx = (x1 - x0) / (SCREENW - 1);
	for (i = 0, x = x0; i < SCREENW; ++i, x += hx)
	{
		y[i] = f(x); //расчет значений функции для каждой точки поля вывода графика
		if (y[i] < ymin) ymin = y[i];
		if (y[i] > ymax) ymax = y[i];
	}
	hy = (ymax - ymin) / (SCREENH - 1);
	yz = (int)floor(ymax / hy + 0.5);
	xz = (int)floor((0. - x0) / hx + 0.5);
	//построение осей и заполнение массива отображения пробелами
	for (j = 0; j < SCREENH; ++j)
		for (i = 0; i < SCREENW; ++i)
		{
			if (j == yz && i == xz) screen[i][j] = '+';
			else if (j == yz) screen[i][j] = '-';
			else if (i == xz) screen[i][j] = '|';
			else screen[i][j] = ' ';
		}
	//определение положения значения функции на поле вывода
	for (i = 0; i < SCREENW; ++i)
	{
		j = (int)floor((ymax - y[i]) / hy + 0.5);
		screen[i][j] = '*';
	}
	//печать массива символов
	for (j = 0; j < SCREENH; ++j)
	{
		for (i = 0; i < SCREENW; ++i)  putchar(screen[i][j]);
		putchar('\n');
	}
}
void main()
{
	setlocale(LC_ALL, "RUS");
	double x, x1, x2, sh;
	int r=-1;
	char s1, s2, semicolon;
	while (r!=0)
	{
		printf("\nВыберите расчёт:\nЧтобы найти значение функции F1(x) с заданным значением аргумента, нажмите 1.\nЧтобы найти значение функции F2(x) с заданным значением аргумента, нажмите 2.\nЧтобы найти значение функции F1(x) на заданном интервале (xn;xk), полуинтервале [xn;xk) или (xn;xk], отрезке [xn;xk] нажмите 3.\nЧтобы найти значение функции F2(x) на заданном интервале (xn;xk), полуинтервале [xn;xk) или (xn;xk], отрезке [xn;xk] нажмите 4.\nЧтобы нарисовать график для F1(x), нажмите 5.\nЧтобы нарисовать график для F2(x), нажмите 6.\nДля выхода из программы нажмите 0\n");
		scanf("%d", &r);
		switch (r)
		{
		 case 1:
			printf("Введите аргумент x:");
			scanf("%lf", &x);
			if (x == -1) printf("Введено недопустимое значение аргумента");
			else printf("%lf", sch_y(x));
			break;
		 case 2:
			printf("Введите аргумент x:");
			scanf("%lf", &x);
			printf("%f", sch_v(x));
			break;
		 case 3:
			 printf("Введите интервал, или полуинтервал, или отрезок:");
				 scanf(" %c%lf%c%lf%c",&s1,&x1,&semicolon,&x2,&s2);
			 printf("\nВведите шаг табуляции:");
				 scanf("%lf", &sh);
				 if (s1 == '(') x1 += sh; 
				 if (s2 == ')') x2 -= sh;
				 t_result (sch_y, x1, x2, sh);
				 break;
				 /*if ((s1 == '(') && (s2 == ')'))
					 result_1(sch_y, x1, x2, sh);
				 else if ((s1 == '[') && (s2 == ')'))
					 result_2(sch_y, x1, x2, sh);
				 else if ((s1 == '(') && (s2 == ']'))
					 result_3(sch_y, x1, x2, sh);
				 else if ((s1 == '[') && (s2 == ']'))
					 result_4(sch_y, x1, x2, sh);
				 else
					 printf("Ошибка!");
				 break;*/
		 case 4:
			 printf("Введите интервал, или полуинтервал, или отрезок:");
				scanf(" %c%lf%c%lf%c", &s1, &x1, &semicolon, &x2, &s2);
			 printf("\nВведите шаг табуляции:");
				scanf("%lf", &sh);
				if (s1 == '(') x1 += sh;
				if (s2 == ')') x2 -= sh;
				t_result(sch_v, x1, x2, sh);
				break;
			/* if ((s1 == '(') && (s2 == ')'))
				 result_1(sch_v, x1, x2, sh);
			 else if ((s1 == '[') && (s2 == ')'))
				 result_2(sch_v, x1, x2, sh);
			 else if ((s1 == '(') && (s2 == ']'))
				 result_3(sch_v, x1, x2, sh);
			 else if ((s1 == '[') && (s2 == ']'))
				 result_4(sch_v, x1, x2, sh);
			 else
				 printf("Ошибка!");
			 break;*/
		 case 5:
			 printf("Введите интервал, или полуинтервал, или отрезок:");
			 scanf(" %c%lf%c%lf%c", &s1, &x1, &semicolon, &x2, &s2);
			 printf("\nВведите шаг табуляции:");
			 scanf("%lf", &sh);
			 plot(x1, x2, sch_y);
			 break;
		 case 6:
			 printf("Введите интервал, или полуинтервал, или отрезок:");
			 scanf(" %c%lf%c%lf%c", &s1, &x1, &semicolon, &x2, &s2);
			 printf("\nВведите шаг табуляции:");
			 scanf("%lf", &sh);
			 plot(x1, x2, sch_v);
			 break;
		 default:
			 printf("Ошибка!");
			 break;
		}
	}
}