#include "systemc.h"
#include "iomanip"

SC_MODULE(mon) {     
	sc_in<bool> X,Y,Z,C,S;     
	sc_in<bool> Clk;  

	void monitor()   {     
		cout << std::setw(11) << "Time";     
		cout << std::setw(2) << "X";     
		cout << std::setw(2) << "Y";     
		cout << std::setw(2) << "Z";     
		cout << std::setw(5) << "C";     
		cout << std::setw(2) << "S" << endl;    
		int i=0;
		while (true)     {       
			wait();
			cout << i;
			i++;
			cout << std::setw(10) << sc_time_stamp();       
			cout << std::setw(2) << X.read();       
			cout << std::setw(2) << Y.read();       
			cout << std::setw(2) << Z.read();      	
			cout << std::setw(5) << C.read();     
			cout << std::setw(2) << S.read() << endl;
		}   
	}  

	SC_CTOR(mon)   {     
		SC_THREAD(monitor);     
		sensitive << Clk.pos();   
	} 
};
