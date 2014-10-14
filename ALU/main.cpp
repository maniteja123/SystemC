#include "systemc.h"
#include "stim.h"
#include "ALU.h"
#include "mon.h"

int sc_main(int argc, char* argv[]) {   
	sc_signal < sc_uint<32> > A,B,F;   
//	sc_signal <bool> zero;
	sc_clock TestClk("TestClock", 10, SC_NS,1,SC_NS);

	stim Stim1("Stimulus");   
	Stim1.opA(A);   
	Stim1.opB(B);
	Stim1.Clk(TestClk);

	alu A1("A");
	A1.opA(A);
	A1.opB(B);
	A1.result(F);
//	A1.zero(zero);

  	mon Monitor1("Monitor");   
	Monitor1.opA(A);   
	Monitor1.opB(B);   
	Monitor1.result(F);
	Monitor1.Clk(TestClk);   
//	Monitor1.zero(zero);

	sc_start();  // run forever  
	return 0;  
}
