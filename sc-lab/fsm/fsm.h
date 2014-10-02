
struct fsm : sc_module {
    sc_in<bool> clk;
    sc_in<bool> ten;
    sc_in<bool> twenty;

	sc_out<bool> z;

	// State
	sc_uint<2> s;

    // methods
    void run_fsm();
    
    //Constructor
    SC_CTOR( fsm ) {
		SC_THREAD( run_fsm); 
 		sensitive_pos << clk;
    }
};

