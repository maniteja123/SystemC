#include "iomanip"

SC_MODULE(mon) {     
//	sc_in<bool> zero;
	sc_in < sc_uint<32> > opA,opB,result;
	sc_in <bool> Clk;
	void monitor()   {     
		cout << std::setw(11) << "Time";     
		cout << std::setw(10) << "opA";     
		cout << std::setw(10) << "opB";     
		cout << std::setw(10) << "result" << endl;     
//		cout << std::setw(5) << "zero" << endl ;
		wait();
		cout << std::setw(10) << sc_time_stamp();
		cout << std::setw(10) << opA;       
		cout << std::setw(10) << opB;       
		cout << std::setw(10) << result << endl;      	
//		cout << std::setw(5) << zero.read() << endl;

	}     

	SC_CTOR(mon)   {     
		SC_THREAD(monitor);
			sensitive << Clk.pos() ;
	} 
};
