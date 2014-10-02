#include <systemc.h>

SC_MODULE(rf){
	sc_in <bool>clk,write;
	sc_in < sc_uint<5> > wrAddr,rdAddrA,rdAddrB;
	sc_in < sc_uint<32> > wrData;
	sc_out <sc_uint<32> > rdDataA,rdDataB;

	sc_uint<32> reg[32];
	
	
	void readA(){
		rdDataA = reg[rdAddrA];
	}

	void readB(){
		rdDataB = reg[rdArrdB];
	}

	
	void write(){
		if(write){
			reg[wrAddr]=wrData;
		}
	}
		
	SC_CTOR(rf){
		SC_METHOD(readA);
			sensitive << rdAddrA;
		SC_METHOD(readB);
			sensitive  << rdAddrB;
		SC_METHOD(write);
			sensitive << wrAddr << wrData << clk.pos() << write;
	}
		
}	
