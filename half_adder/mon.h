#include "systemc.h"
#include "iomanip"

SC_MODULE(mon) {     
	sc_in<bool> A,B,C,S;     
	sc_in<bool> Clk;  

	void monitor()   {     
		cout << std::setw(10) << "Time";     
		cout << std::setw(2) << "A";     
		cout << std::setw(2) << "B";     
		cout << std::setw(2) << "C";     
		cout << std::setw(2) << "S" << endl;     
//		wait();
		int i=0;
		while (true)     {       
			cout << i;
			i++;
			cout << std::setw(10) << sc_time_stamp();       
			cout << std::setw(2) << A.read();       
			cout << std::setw(2) << B.read();       
			cout << std::setw(2) << C.read();      	
			cout << std::setw(2) << S.read() << endl;       
			wait();    // wait for 1 clock cycle     
		}   
	}  

	SC_CTOR(mon)   {     
		SC_THREAD(monitor);     
		sensitive << Clk.pos();   
	} 
};
