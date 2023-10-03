// gcov_test1.c
#include<stdio.h>

static void func2(void);

void
func1_child(void)
{
	printf("\nInside func1_child()\n");
	unsigned int i = 0;

	for (; i < 0xfffff777; i++);

	return;
}

void
func1(void)
{
	printf("\nInside func1()\n");
	unsigned int i = 0;

	for (; i < 0xffffffff; i++);
	func1_child();

	func2();
	return;
}

static void
func2(void)
{
	printf("\nInside func2()\n");
	unsigned int i = 0;

	for (; i < 0xfffff000; i++);
	return;
}

int
main(void)
{
	printf("\nInside main()\n");
	int i = 0;

	for (; i < 0xfffffff; i++);
	func1();
	func2();

	return 0;
}
