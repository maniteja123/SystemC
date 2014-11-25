#include "systemc.h"
#include "iomanip"

SC_MODULE(mon) {     
	sc_in< sc_uint<5> > wrAddr,rdAddrA,rdAddrB;
	sc_in< sc_uint<32> > rdDataA,rdDataB,wrData;
	sc_in<bool> Clk,write;

	void monitor()   {     
		cout << std::setw(11) << "Time";
		cout << std::setw(10) << "Write";
		cout << std::setw(10) << "wrAddr";
		cout << std::setw(10) << "rdAddrA";
		cout << std::setw(10) << "rdAddrB";	
		cout << std::setw(20) << "wrData";
		cout << std::setw(20) << "rdDataA";
		cout << std::setw(20) << "rdDataB" << endl;    
		int i=0;
		while (true)     {       
			wait();
			cout << i;
			i++;
			cout << std::setw(10) << sc_time_stamp();       
			cout << std::setw(10) << write ;
			cout << std::setw(10) << wrAddr ;
			cout << std::setw(10) << rdAddrA ;
			cout << std::setw(10) << rdAddrB ;
			cout << std::setw(20) << wrData ;
			cout << std::setw(20) << rdDataA ;
			cout << std::setw(20) << rdDataB << endl ;
		}   
	}  

	SC_CTOR(mon)   {     
		SC_THREAD(monitor);     
			sensitive << Clk.pos();   
	} 
};
