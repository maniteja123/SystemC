#include "driver.h"

void driver::prc_driver()
{
	ten.write(0);
	twenty.write(0);
	wait(15, SC_NS);

	ten.write(1);
	twenty.write(0);
	wait(10, SC_NS);

	ten.write(1);
	twenty.write(0);
	wait(10, SC_NS);

	ten.write(1);
	twenty.write(0);
	wait(10, SC_NS);
 ////////////////////////////////////////
	ten.write(0);
	twenty.write(0);
	wait(10, SC_NS);

	ten.write(0);
	twenty.write(1);
	wait(10, SC_NS);

	ten.write(0);
	twenty.write(1);
	wait(10, SC_NS);

 ////////////////////////////////////////
	ten.write(0);
	twenty.write(0);
	wait(10, SC_NS);

	ten.write(0);
	twenty.write(1);
	wait(10, SC_NS);

	ten.write(1);
	twenty.write(0);
	wait(10, SC_NS);

	ten.write(0);
	twenty.write(0);
	wait(10, SC_NS);

	ten.write(0);
	twenty.write(0);
	wait(10, SC_NS);

	sc_stop();
}
