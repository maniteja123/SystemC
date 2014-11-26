#include "systemc.h"

SC_MODULE(stim){

	sc_out < sc_uint<32> > inst;
	sc_in <bool> Clk;

	void StimGen(){
		
		wait(10,SC_NS);

		inst.write(0b00000000001000100000000000010010);

		wait(10,SC_NS);

		inst.write(0b10001100010000110010000000010010);

		wait(10,SC_NS);

		inst.write(0b10101100001000100000000000010000);
		
		wait(10,SC_NS);

		inst.write(0b10001100001001000000000000010010);

		wait(10,SC_NS);
		
		sc_stop();

	}

	SC_CTOR(stim){

		SC_THREAD(StimGen);
	}

};
		
	
