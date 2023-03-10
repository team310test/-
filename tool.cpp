#include "all.h"

//ƒVƒƒƒbƒtƒ‹ŠÖ”
void shuffle(int order[], unsigned int size)
{
	unsigned int i, j;
	int tmp;


	i = size - 1;

	while (i > 0) {

		j = rand() % (i + 1);


		tmp = order[j];
		order[j] = order[i];
		order[i] = tmp;

		i--;
	}
}
