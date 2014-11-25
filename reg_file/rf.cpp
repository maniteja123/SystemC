#include "systemc.h"
#include "stim.h"
#include "rf.h"
#include "mon.h"

int sc_main(int argc, char* argv[]) {   
	sc_signal<bool> Write;
	sc_signal < sc_uint<5> > rdAddrA,rdAddrB,wrAddr;
	sc_signal < sc_uint<32> > rdDataA,rdDataB,wrData;
	sc_clock TestClk("TestClock", 10, SC_NS,0,SC_NS);  

	stim Stim1("Stimulus");   
	Stim1.write(Write);   
	Stim1.rdAddrA(rdAddrA);
	Stim1.rdAddrB(rdAddrB);
	Stim1.wrAddr(wrAddr);
	Stim1.wrData(wrData);

	rf RF1("SR1");
	RF1.write(Write);
	RF1.clk(TestClk);
	RF1.rdAddrA(rdAddrA);
	RF1.rdAddrB(rdAddrB);
	RF1.wrAddr(wrAddr);
	RF1.rdDataA(rdDataA);
	RF1.rdDataB(rdDataB);
	RF1.wrData(wrData);

  	mon Monitor1("Monitor");   
	Monitor1.Clk(TestClk);  
	Monitor1.write(Write);
	Monitor1.rdAddrA(rdAddrA);
	Monitor1.rdAddrB(rdAddrB);
	Monitor1.wrAddr(wrAddr);
	Monitor1.rdDataA(rdDataA);
	Monitor1.rdDataB(rdDataB);
	Monitor1.wrData(wrData);

	sc_start();  // run forever  
	return 0;  
}
