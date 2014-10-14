#include "driver.h"

void driver::prc_driver()
{
	sc_int<4> a, b;

	a   = "0b0000";
	b   = "0b0000";
	cin.write(0);
	a0.write(a[0]);
	a1.write(a[1]);
	a2.write(a[2]);
	a3.write(a[3]);
	b0.write(b[0]);
	b1.write(b[1]);
	b2.write(b[2]);
	b3.write(b[3]);
	wait(30, SC_NS);

	a   = "0b0001";
	b   = "0b1111";
	cin.write(0);
	a0.write(a[0]);
	a1.write(a[1]);
	a2.write(a[2]);
	a3.write(a[3]);
	b0.write(b[0]);
	b1.write(b[1]);
	b2.write(b[2]);
	b3.write(b[3]);
	wait(30, SC_NS);

	a   = "0b0011";
	b   = "0b0010";
	cin.write(0);
	a0.write(a[0]);
	a1.write(a[1]);
	a2.write(a[2]);
	a3.write(a[3]);
	b0.write(b[0]);
	b1.write(b[1]);
	b2.write(b[2]);
	b3.write(b[3]);
	wait(30, SC_NS);
}
