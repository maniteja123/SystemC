
struct sr : sc_module {
    sc_in<bool> clk;
    sc_in<bool> din;

	sc_out<sc_int<4> > r;

    // methods
    void shift();
    
    //Constructor
    SC_CTOR( sr ) {

	SC_THREAD( shift); 
 		sensitive_pos << clk;
    }
};

