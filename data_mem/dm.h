#include <systemc. h>

SC_MODULE(dm){

	sc_in <bool> memRead,memWrite;
	sc_in < sc_uint<32> > wrData,rdAddr,wrAddr;
	sc_out <sc_uint<32> > rdData;

	sc_uint<32> reg[32];
	sc_uint<5> r,w;

	void read(){
		r = rdAddr;
		rdData = reg[r];
	}

	void write(){
		w = wrAddr;
		reg[w] = wrData;
	}

	SC_CTOR(dm){
		SC_METHOD(read);
			sensitive << memRead << rdAddr ;
		SC_METHOD(write);
			sensitive << memWrite << wrAddr << wrData ;
	}
};
