#include <systemc.h>

SC_MODULE(im){
	sc_in < sc_uint<5> > rdAddr;
	sc_out < sc_uint<32> > rdData;
	
	sc_uint<32> reg[32];
	sc_uint<5> r;

	void read(){
		r = rdAddr;
		rdData = reg[r];
	}

	SC_CTOR(im){
		SC_METHOD(read);
			sensitive << rdAddr ;
	}

}
	
