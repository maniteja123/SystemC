#include "systemc.h" 
SC_MODULE(stim) {
	sc_out<bool> Din;

	void StimGen()   {
		Din.write(true);     
		wait(10,SC_NS);

		Din.write(false);     
		wait(15,SC_NS);     
	
		Din.write(true);     
		wait(10,SC_NS);     

		Din.write(true);
		wait(15,SC_NS);     
	
		sc_stop();   
	}   

	SC_CTOR(stim)   {
		SC_THREAD(StimGen);    
	} 
};
