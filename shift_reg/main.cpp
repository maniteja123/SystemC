#include "systemc.h"
#include "stim.h"
#include "reg.h"
#include "mon.h"

int sc_main(int argc, char* argv[]) {   
	sc_signal<bool> Din;   
	sc_signal< sc_uint<4> > r;
	sc_clock TestClk("TestClock", 10, SC_NS,0,SC_NS);  

	stim Stim1("Stimulus");   
	Stim1.Din(Din);   

	sr SR1("SR1");
	SR1.din(Din);
	SR1.clk(TestClk);
	SR1.r(r);

  	mon Monitor1("Monitor");   
	Monitor1.Din(Din); 
	Monitor1.r(r);
	Monitor1.Clk(TestClk);  

	sc_start();  // run forever  
	return 0;  
}
