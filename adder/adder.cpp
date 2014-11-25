#include "systemc.h"
#include "stim.h"
#include "adder.h"
#include "mon.h"

int sc_main(int argc, char* argv[]) {   
	sc_signal<bool> XSig, YSig,ZSig,SSig,CSig;   
	sc_clock TestClk("TestClock", 10, SC_NS,1,SC_NS);  
//	sc_trace_file *tf = sc_create_vcd_trace_file("trace");


	stim Stim1("Stimulus");   
	Stim1.X(XSig);   
	Stim1.Y(YSig);
	Stim1.Z(ZSig);
	Stim1.Clk(TestClk);

	adder A1("A");
	A1.a(XSig);
	A1.b(YSig);
	A1.c(ZSig);
	A1.carry(CSig);
	A1.sum(SSig);
	
/*
	sc_trace(tf,XSig,"X");
	sc_trace(tf,YSig,"Y");
	sc_trace(tf,ZSig,"Z");
	sc_trace(tf,SSig,"S");
	sc_trace(tf,CSig,"C");
*/
  	mon Monitor1("Monitor");   
	Monitor1.X(XSig);   
	Monitor1.Y(YSig);   
	Monitor1.Z(ZSig);   
	Monitor1.S(SSig);
	Monitor1.C(CSig);
	Monitor1.Clk(TestClk);  

//	sc_close_vcd_trace_file(tf);
	sc_start();  // run forever  
	return 0;  
}
