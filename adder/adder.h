#include<systemc.h>
#include "half_adder.h"
SC_MODULE(adder){
	sc_in<bool> a,b,c;
	sc_out<bool> sum,carry;
	
	sc_signal<bool> c1,c2,s1;
	
	void proc_adder(){
		carry = c1|c2;	
	}
	
	half_adder hf1;
	half_adder hf2;
	SC_CTOR(adder): hf1("hf1"), hf2("hf2")	{
		hf1.a(a);
		hf1.b(b);
		hf1.carry(c1);
		hf1.sum(s1);
		hf2.a(s1);
		hf2.b(c);
		hf2.carry(c2);
		hf2.sum(sum);  // named port binding
/*		hf1(a,b,s1,c1);
		hf1(s1,c,sum,c2); */  // positional port binding
		SC_METHOD(proc_adder);
		sensitive << c1<< c2 ;
	}
};
