#include "systemc.h"
SC_MODULE(stim) {
        sc_out<bool> write;
        sc_out < sc_uint<5> > rdAddrA,rdAddrB,wrAddr;
        sc_out < sc_uint<32> > wrData;

        void StimGen()   {
                write.write(true);
                wrAddr.write(4);
                wrData.write(1110101010101);
                wait(10,SC_NS);

                write.write(false);
                rdAddrA.write(4);
                wait(15,SC_NS);

                write.write(false);
                rdAddrB.write(4); 
                wait(15,SC_NS);

                write.write(true);
                wrAddr.write(2);   
                wrData.write(110101010001);
                wait(10,SC_NS);

                write.write(false);
                rdAddrA.write(2);
		wait(10,SC_NS);                                
                sc_stop();
        }

        SC_CTOR(stim)   {
                SC_THREAD(StimGen);
        }
};
