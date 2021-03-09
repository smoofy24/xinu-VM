/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

void produce(sid32 cons, sid32 prod), consume(sid32 cons, sid32 prod);

int32 n = 0;

process	main(void)
{
	
	sid32	prod, cons;

	prod = semcreate(0);
	cons = semcreate(1);

	resume( create(produce, 1024, 20, "prod", 2, cons, prod));
	resume( create(consume, 1024, 20, "cons", 2, cons, prod));
    
}

void produce(sid32 cons, sid32 prod)
{
	int32 i;
	
	for( i=1; i<20; i++) {
		wait(cons);
		n++;
		signal(prod);
	}
}

void consume(sid32 cons, sid32 prod)
{
	int32 i;

	for( i=1; i<=20; i++) {
		wait(prod);
		printf("The value of n is %d \n", n);
		signal(cons);
	}
}
