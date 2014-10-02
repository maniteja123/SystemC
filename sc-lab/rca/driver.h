
#include "systemc.h"

SC_MODULE (driver) {
	sc_out<bool> cin;
	sc_out<bool> a0;
	sc_out<bool> a1;
	sc_out<bool> a2;
	sc_out<bool> a3;
	sc_out<bool> b0;
	sc_out<bool> b1;
	sc_out<bool> b2;
	sc_out<bool> b3;

	void prc_driver();

	SC_CTOR( driver) {
		SC_THREAD( prc_driver);
	}
};
