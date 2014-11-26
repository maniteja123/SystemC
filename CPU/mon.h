#include "iomanip"

SC_MODULE(mon) {     
	sc_in < sc_uint<32> > inst;
	sc_in < sc_uint<6> > func,op;
	sc_in < sc_uint<5> > rs,rt,rd,shamt,wrAddrR;
	sc_in < sc_uint<2> > alop;
	sc_in < sc_uint<4> > alc;
	sc_in < bool > RegDst, RegWrite, ALUSrc, PCSrc, MemRead, MemWrite, MemtoReg,zero;
	sc_in < sc_uint<16> > addr;
	sc_in < sc_uint<32> > resultR,resultM,rdDataA,rdDataB,wrDataM,rdAddrM,rdDataM,wrAddrM;  //,wrDataR,rdAddrI,rdDataI;
	sc_in <bool> Clk;

	void monitor()   {     
		cout << std::setw(11) << "Time";     
		cout << std::setw(10) << "inst";     
		cout << std::setw(5) << "func";     
		cout << std::setw(5) << "op";     
		cout << std::setw(5) << "rs"; 
		cout << std::setw(5) << "rt";
		cout << std::setw(5) << "rd";
		cout << std::setw(5) << "alc";
		cout << std::setw(5) << "alop";
		cout << std::setw(10) << "ALUSrc";
		cout << std::setw(10) << "RegDst";
		cout << std::setw(10) << "RegWrite";
		cout << std::setw(10) << "PCSrc";
		cout << std::setw(10) << "MemRead";
		cout << std::setw(10) << "MemWrite";
		cout << std::setw(10) << "MemtoReg";
		cout << std::setw(5) << "zero";
		cout << endl ;
		int i=0;
		while(true){
			wait();
			cout << i;
			i++;
			cout << std::setw(10) << sc_time_stamp();
			cout << std::setw(10) << inst;       
			cout << std::setw(5) << func;   
			cout << std::setw(5) << op;           
			cout << std::setw(5) << rs;
			cout << std::setw(5) << rt;
			cout << std::setw(5) << rd ;
			cout << std::setw(5) << alc ;
			cout << std::setw(5) << alop ;
			cout << std::setw(10) << ALUSrc ;
			cout << std::setw(10) << RegDst ;
			cout << std::setw(10) << RegWrite ;
			cout << std::setw(10) << PCSrc ;
			cout << std::setw(10) << MemRead ;
			cout << std::setw(10) << MemWrite ;
			cout << std::setw(5) << MemtoReg ;
			cout << endl;
		}
	}

	SC_CTOR(mon)   {     
		SC_THREAD(monitor);
			sensitive << Clk.pos() ;
	} 
};
