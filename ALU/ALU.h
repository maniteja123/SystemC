#include <systemc.h>

SC_MODULE(alu){
	
//	sc_in <sc_uint<4> > op;
	sc_in < sc_uint<32> > opA,opB;
//	sc_out <bool> zero;
	sc_out < sc_uint<32> >result;

	sc_uint<32> dataA,dataB,res;

	void add(){
//		zero = 0;
		dataA = opA;
		dataB = opB;
		res = dataA + dataB;
		result = res ;
//		if(result == 0)
//			zero = 1;
	}

	SC_CTOR(alu){
		SC_METHOD(add);
			sensitive << opA << opB;
	}

};


