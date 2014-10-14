#include "driver.h"

void driver::prc_driver()
{
	din.write(0);
	wait(15, SC_NS);

	din.write(1);
	wait(10, SC_NS);

	din.write(1);
	wait(10, SC_NS);

	din.write(1);
	wait(10, SC_NS);

	din.write(1);
	wait(10, SC_NS);

	din.write(0);
	wait(10, SC_NS);

	din.write(1);
	wait(10, SC_NS);

	din.write(1);
	wait(10, SC_NS);

	din.write(1);
	wait(10, SC_NS);

	din.write(1);
	wait(10, SC_NS);

	sc_stop();
}
