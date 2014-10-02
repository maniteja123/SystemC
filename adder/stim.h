#include "systemc.h" 
SC_MODULE(stim) {
	sc_out<bool> X,Y,Z;
	sc_in<bool> Clk;
	void StimGen()   {
		X.write(false);     
		Y.write(false);
		Z.write(true);
		wait();

		X.write(false);     
		Y.write(true);     
		Z.write(true);
		wait();     
	
		X.write(true);     
		Y.write(false);     
		Z.write(true);
		wait();     

		X.write(true);     
		Y.write(true);     
		Z.write(true);
		wait();     
		
		sc_stop();   
	}   

	SC_CTOR(stim)   {
		SC_THREAD(StimGen);     
		sensitive << Clk.pos();   
	} 
};
