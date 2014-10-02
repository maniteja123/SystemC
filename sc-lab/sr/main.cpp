/*****************************************************************************
 
  main.cpp -- This is the top level file instantiating the modules and
              binding ports to signals.
 
 *****************************************************************************/

#include "systemc.h"
#include "sr.h"
#include "driver.h"

int sc_main(int ac, char *av[])
{
        sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);
	sc_signal<bool> din;
	sc_signal<sc_int<4> > r;

	sc_trace_file *tf;

	sc_clock clk ("ID", 10, SC_NS, 0.5, 10, SC_NS, true);

	driver dr("generateInputs");
	dr.din(din);

	sr shr("shift_reg");
	shr.din(din);
	shr.clk(clk);
	shr.r(r);

	// Waves:
	tf = sc_create_vcd_trace_file("waves");
        tf->set_time_unit(1, SC_NS);

	sc_trace(tf, clk, "clk");
	sc_trace(tf, din, "din");
	sc_trace(tf, r, "r");

	sc_start(-1);

	sc_close_vcd_trace_file(tf);

	return 0;
}

