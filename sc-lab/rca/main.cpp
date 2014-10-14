/*****************************************************************************
 
  main.cpp -- This is the top level file instantiating the modules and
              binding ports to signals.
 
 *****************************************************************************/

#include "systemc.h"
#include "fa.h"
#include "driver.h"

int sc_main(int ac, char *av[])
{
        sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);
	sc_signal<bool> cin;
	sc_signal<bool> a0;
	sc_signal<bool> a1;
	sc_signal<bool> a2;
	sc_signal<bool> a3;
	sc_signal<bool> b0;
	sc_signal<bool> b1;
	sc_signal<bool> b2;
	sc_signal<bool> b3;
	sc_signal<bool> s0;
	sc_signal<bool> s1;
	sc_signal<bool> s2;
	sc_signal<bool> s3;
	sc_signal<bool> c0;
	sc_signal<bool> c1;
	sc_signal<bool> c2;
	sc_signal<bool> cout;

	sc_trace_file *tf;

	driver dr("generateInputs");
	dr.a0(a0);
	dr.a1(a1);
	dr.a2(a2);
	dr.a3(a3);
	dr.b0(b0);
	dr.b1(b1);
	dr.b2(b2);
	dr.b3(b3);
	dr.cin(cin);

	fa ad0("adder0");
	ad0.a(a0);
	ad0.b(b0);
	ad0.cin(cin);
	ad0.s(s0);
	ad0.cout(c0);

	fa ad1("adder1");
	ad1.a(a1);
	ad1.b(b1);
	ad1.cin(c0);
	ad1.s(s1);
	ad1.cout(c1);

	fa ad2("adder2");
	ad2.a(a2);
	ad2.b(b2);
	ad2.cin(c1);
	ad2.s(s2);
	ad2.cout(c2);

	fa ad3("adder3");
	ad3.a(a3);
	ad3.b(b3);
	ad3.cin(c2);
	ad3.s(s3);
	ad3.cout(cout);

	// Waves:
	tf = sc_create_vcd_trace_file("waves");
        tf->set_time_unit(1, SC_NS);

	sc_trace(tf, cin, "cin");
	sc_trace(tf, a0, "a0");
	sc_trace(tf, a1, "a1");
	sc_trace(tf, a2, "a2");
	sc_trace(tf, a3, "a3");
	sc_trace(tf, b0, "b0");
	sc_trace(tf, b1, "b1");
	sc_trace(tf, b2, "b2");
	sc_trace(tf, b3, "b3");
	sc_trace(tf, s0, "s0");
	sc_trace(tf, s1, "s1");
	sc_trace(tf, s2, "s2");
	sc_trace(tf, s3, "s3");
	sc_trace(tf, cout, "cout");
	sc_trace(tf, c0, "c0");
	sc_trace(tf, c1, "c1");
	sc_trace(tf, c2, "c2");

	sc_start(200);

	sc_close_vcd_trace_file(tf);

	return 0;
}

