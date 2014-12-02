#include "systemc.h"

SC_MODULE(stim){

	sc_out < sc_uint<32> > inst;
	sc_in <bool> Clk;

	void StimGen(){
		
		wait(10,SC_NS);

		inst.write(0b00000000001000100010000000100000);

		wait(10,SC_NS);

		inst.write(0b00000000100000100011000000100000);

		wait(10,SC_NS);

		inst.write(0b10101100100000110000000000000010);

		wait(10,SC_NS);

		inst.write(0b10001100100000100000000000000010);
		
		wait(10,SC_NS);

		inst.write(0b10001100001001010000000000000001);

		wait(10,SC_NS);
		
		sc_stop();

	}

	SC_CTOR(stim){

		SC_THREAD(StimGen);
	}

};
		
	
