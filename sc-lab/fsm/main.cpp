/*****************************************************************************
 
  main.cpp -- This is the top level file instantiating the modules and
              binding ports to signals.
 
 *****************************************************************************/

#include "systemc.h"
#include "fsm.h"
#include "driver.h"

int sc_main(int ac, char *av[])
{
        sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);
	sc_signal<bool> ten;
	sc_signal<bool> twenty;
	sc_signal<bool> z;

	sc_trace_file *tf;

	sc_clock clk ("ID", 10, SC_NS, 0.5, 10, SC_NS, true);

	driver dr("generateInputs");
	dr.ten(ten);
	dr.twenty(twenty);

	fsm fs("fsm");
	fs.ten(ten);
	fs.twenty(twenty);
	fs.clk(clk);
	fs.z(z);

	// Waves:
	tf = sc_create_vcd_trace_file("waves");
        tf->set_time_unit(1, SC_NS);

	sc_trace(tf, clk, "clk");
	sc_trace(tf, ten, "ten");
	sc_trace(tf, twenty, "twenty");
	sc_trace(tf, z, "z");
	sc_trace(tf, fs.s, "s");

	sc_start(-1);

	sc_close_vcd_trace_file(tf);

	return 0;
}

