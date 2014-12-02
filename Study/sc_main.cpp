//------------------------------------------------------------------
// Simple Testbench
//------------------------------------------------------------------ 

#include <systemc.h>

// Include Device Under Test module:
#include "module.h"


// -----------------------------------------------------------------
// Additional testbench module (counter)
// -----------------------------------------------------------------
SC_MODULE(counter_tb)
{
// Interface signals:
  sc_out<sc_uint<8> > cnt;

// Process counter (SC_THREAD):
  void process_counter()
  {
// Time constant:
    const sc_time t_period(3, SC_NS);

// Loop forever:
    while (1)
    {
// Wait for 3 ns:
      wait(t_period);
// Increment counter:
      cnt.write( cnt.read() + 1 );
// Generate message on stdout every 16 counts:
      if (cnt.read()%16 == 0)
        cout << "Counter=" << cnt.read() << " at " << sc_time_stamp() << endl;
// Wait for 7 ns:
      wait(7, SC_NS);
    }
  }

// Constructor:
  SC_CTOR(counter_tb) 
  {
// Initialization of cnt signal:
    cnt.initialize(0xf0);
// Register process_counter as SC_THREAD process:
    SC_THREAD(process_counter);
  }
};


// SystemC main function (Testbench):
int sc_main(int argc, char* argv[])
{
// Signals:
    sc_signal<sc_uint<8> > din, dout1, dout2, dout3, dcntr;
    sc_signal<sc_logic > rst;

// Set simulation time resolution:
    sc_set_time_resolution(100, SC_PS);
// Create clock (period=10 ns  duty=0.5  delay=2 ns):
    sc_clock clk("clk",10,SC_NS,0.5,2,SC_NS,false);
// Instantiate Device Under Test:
    rotate DUT("rotate");
// Create signal connections with DUT:
    DUT.din(dcntr);
    DUT.dout1(dout1);
    DUT.dout2(dout2);
    DUT.dout3(dout3);
    DUT.reset(rst);
    DUT.clk(clk);
// Instantiate additional testbench module:
    counter_tb CNTR_TB("counter_tb");
// Create signal connections with additional testbench module:
    CNTR_TB.cnt(dcntr);
// Create VCD file (wave.vcd file for GTKWave):
    sc_trace_file *fp;
    fp=sc_create_vcd_trace_file("wave");
// Add signals to trace file:
    sc_trace(fp,clk,"clk");
    sc_trace(fp,dout1,"dout1");
    sc_trace(fp,dout2,"dout2");
    sc_trace(fp,dout3,"dout3");
    sc_trace(fp,dcntr,"dcntr");
    sc_trace(fp,rst,"RESET");
// Set values of local signals:
    rst=SC_LOGIC_0;
// Run simulation for 4 ns:
    sc_start(4, SC_NS);
// Change values of local signals:
    rst=SC_LOGIC_1;
// Continue simulation for 15 ns:
    sc_start(15, SC_NS);
// Change values of local signals:
    rst=SC_LOGIC_0;
// Continue simulation for 2700 ns:
    sc_start(2700, SC_NS);
// Close wave.vcd file:
    sc_close_vcd_trace_file(fp);
// Simulation finished successfully:
    return 0;
}

