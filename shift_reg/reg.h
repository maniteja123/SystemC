#include<systemc.h>

SC_MODULE(sr){
	sc_in<bool> din,clk;
	sc_out< sc_uint<4> > r;

	sc_uint<4> t_r;
	void shift_reg(){
			t_r = r;
			t_r[3] = t_r[2];
			t_r[2] = t_r[1];
	                t_r[1] = t_r[0];
       	        	t_r[0] = din;
			r = t_r;
	}
	
	SC_CTOR(sr){
		SC_METHOD(shift_reg);
		sensitive << clk.pos()  ;
	}
};
