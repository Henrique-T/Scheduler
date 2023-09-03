#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "INE5412.h"

int main()
{

	/*
		I'm still uncertain about how to make the program cpu agnostic.
		The idea is that any kind of cpu can call our program and freely use the scheduler,
		not only INE5412. How to do that?

		A solution would be to directly create an instance of Scheduler here and pass the CPU
		as a parameter. But that would make the cpu be a part of the scheduler, and not the
		other way around.

	*/

	printf("TEST\n");
	// Create an instance of INE5412.
	INE5412 cpu;
	return 1;
}