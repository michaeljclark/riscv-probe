#include <stdio.h>

int main(int argc, char **argv)
{
	volatile int a;
	int b, c, d, e, f, g, h, i, j, k, l, m;
	printf("hang\n");
	for (;;) {
		a = b;
		b = c;
		c = d;
		d = e;
		e = f;
		f = g;
		g = h;
		h = i;
		i = j;
		j = k;
		k = l;
		l = m;
		m = a;
	}
}
