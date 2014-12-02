#include<systemc.h>

SC_MODULE(half_adder){
        sc_in<bool> a,b;
        sc_out<bool> sum,carry;

        void proc_half_adder(){
	        sum = a^b;
	        carry = a&b;
	}

        SC_CTOR(half_adder){

                SC_METHOD(proc_half_adder);
                sensitive << a << b;
        }
};
