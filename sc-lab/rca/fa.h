
struct fa : sc_module {
    sc_in<bool> a;
    sc_in<bool> b;
    sc_in<bool> cin;

	sc_out<bool> s;
	sc_out<bool> cout;

    // methods
    void adder();
    
    //Constructor
    SC_CTOR( fa ) {

	SC_THREAD( adder); 
 		sensitive << a;
		sensitive << b;
		sensitive << cin;
    }
};

