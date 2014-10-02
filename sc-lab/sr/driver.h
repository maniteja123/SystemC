
#include "systemc.h"

SC_MODULE (driver) {
	sc_out<bool> din;

	void prc_driver();

	SC_CTOR( driver) {
		SC_THREAD( prc_driver);
	}
};
