#include "systemc.h"
#include "fsm.h"

void fsm::run_fsm()
{
	sc_uint<2> next_s;

	s = 0; // Initial state
	while (1) {
		wait(); // wait for any signal on sensitivity list
		wait(2, SC_NS); // delay to produce outputs.
		z.write(0);  // default value. May be overwriten later
		switch (s) {
		case 0:
			if (ten)
				next_s = 1;
			if (twenty)
				next_s = 2;
			break;
		case 1:
			if (ten)
				next_s = 2;
			if (twenty) {
				next_s = 3;
				z.write(1);
			}
			break;
		case 2:
			if (ten) {
				next_s = 3;
				z.write(1);
			}
			if (twenty) {
				next_s = 3;
				z.write(1);
			}
			break;
		case 3:
			next_s = 0;
			break;
		}
		s = next_s;
	}
}

