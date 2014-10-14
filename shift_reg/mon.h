#include "systemc.h"
#include "iomanip"

SC_MODULE(mon) {     
	sc_in<bool> Din;
	sc_in< sc_uint<4> > r;
	sc_in<bool> Clk;  

	void monitor()   {     
		cout << std::setw(11) << "Time";      
		cout << std::setw(8) << "Reg" << endl;    
		int i=0;
		while (true)     {       
			wait();
			cout << i;
			i++;
			cout << std::setw(10) << sc_time_stamp();       
			cout << std::setw(10) << r << endl;       
		}   
	}  

	SC_CTOR(mon)   {     
		SC_THREAD(monitor);     
		sensitive << Clk.pos();   
	} 
};
