#include "systemc.h" 
SC_MODULE(stim) {
	sc_out < sc_uint<32> > opA,opB;
	sc_in<bool> Clk;

	void StimGen()   {

		opA.write(111);     
		opB.write(101);

		wait(10,SC_NS);
		sc_stop();   
	}   

	SC_CTOR(stim)   {
		SC_THREAD(StimGen);     
			sensitive << Clk.pos();
	} 
};
