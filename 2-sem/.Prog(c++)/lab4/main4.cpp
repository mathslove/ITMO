/*
* Лабораторная работа по программированию #4
* Выполнил:	Маслов Михаил
* Группа:	M3106
* Вариант:	1
*
* Задание:
	Реализовать все указанные интерфейсы (абстрактные базовые классы) для
	классов (согласно варианту):
	Функционал системы:
	- Хранение множества фигур
	- Динамическое добавление фигур пользователем. (через консоль)
	- Отобразить все фигуры.
	- Суммарная площадь всех фигур.
	- Суммарный периметр всех фигур.
	- Центр масс всей системы.
	- Память, занимаемая всеми экземплярами классов.
	- Сортировка фигур между собой по массе.
	Вопросы для обдумывания:
		- Есть ли необходимость делать методы сравнения по массе виртуальными?
		- Получится ли также перегрузить операторы сравнения для интерфейса
		BaseCObject чтобы сравнивать объекты по объему занимаемой памяти?
		- Предположите, что в дальнейшем придется изменить код таким образом,
		чтобы фигуры (оставаясь сами по себе плоскими) задавались уже не в
		двумерном, а в трехмерном пространстве. Укажите как бы вы действовали?
		Что пришлось бы изменить?
* Вариант:
*	C) Равностороний треугольник // Triangle
	A) Круг // Circle
 */

#include "menu/Menu.h"

int main(){
    Menu s;
    s.Start();
    return 0;
}