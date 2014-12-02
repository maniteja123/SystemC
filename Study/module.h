//------------------------------------------------------------------
// Simple example of bit rotate
//------------------------------------------------------------------

#ifndef ROTATE_H
#define ROTATE_H

#include <systemc.h>

// Rotate module definition:
SC_MODULE(rotate)
{
// Input and output signals:
  sc_in<bool > clk;
  sc_in<sc_logic > reset;
  sc_in<sc_uint<8> > din;
  sc_out<sc_uint<8> > dout1;
  sc_out<sc_uint<8> > dout2;
  sc_out<sc_uint<8> > dout3;

// Rotate process:
  void rotate_process()
  {
// Internal variable (do not use variables for inter-process communication):
    sc_uint<8> a;

// Read input signal:
    a=din.read();
// Read and test reset signal:
    if (reset.read() == '1')
    {
// Reset output signals:
      dout1.write(0);
      dout2.write(0);
      dout3.write(0);
    }
    else
// If not reset then rising edge of clock occured:
      {
// Rotate one bit right:
        dout1.write( concat(a[0],a.range(7,1)) );
// Rotate four bits right (swap nibble):
        dout2.write( concat(din.read()(3,0),din.read().range(7,4)) );
// Rotate one bit left:
        dout3.write( concat(a.range(6,0),a.range(7,7)) );
      }
  }

// Module constructor:
  SC_CTOR(rotate)
  {
// Initialize signals:
    dout1.initialize(0);
    dout2.initialize(0);
    dout3.initialize(0);
// Register rotate_process as SC_METHOD process:
    SC_METHOD(rotate_process);
// Define sensitivity of the last registered process:
    sensitive << clk.pos() << reset.pos();
// Important - do not trigger process for time=0:
    dont_initialize();
  }
};
#endif

