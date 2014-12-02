#include "systemc.h"
#include "stim.h"
#include "half_adder.h"
#include "mon.h"

int sc_main(int argc, char* argv[]) {   
	sc_signal<bool> ASig, BSig,CSig,SSig;   
	sc_clock TestClk("TestClock", 10, SC_NS,2,SC_NS);  

	stim Stim1("Stimulus");   
	Stim1.A(ASig);   
	Stim1.B(BSig);
	Stim1.Clk(TestClk);

	half_adder HA1("HA");
	HA1.a(ASig);
	HA1.b(BSig);
	HA1.carry(CSig);
	HA1.sum(SSig);

  	mon Monitor1("Monitor");   
	Monitor1.A(ASig);   
	Monitor1.B(BSig);   
	Monitor1.C(CSig);   
	Monitor1.S(SSig);
	Monitor1.Clk(TestClk);  

	sc_start();  // run forever  
	return 0;  
}
