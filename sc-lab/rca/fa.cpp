#include "systemc.h"
#include "fa.h"

void fa::adder()
{
	while (1) {
		wait(); // wait for any signal on sensitivity list
		wait(5, SC_NS); // delay to produce outputs.

		cout = (a & b) | (a & cin) | (b & cin);
		s = a ^ b ^ cin;
	}
}

