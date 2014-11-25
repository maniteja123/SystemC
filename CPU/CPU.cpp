#include "systemc.h"
#include "CPU.h"
#include "stim.h"
#include "mon.h"

int sc_main(int argc, char* argv[]){

	sc_signal < sc_uint<32> > inst;
	sc_signal < sc_uint<6> > func,op;
	sc_signal < sc_uint<5> > rs,rt,rd,shamt,wrAddrR;
	sc_signal < sc_uint<2> > alop;
	sc_signal < sc_uint<4> > alc;
	sc_signal < bool > RegDst, RegWrite, ALUSrc, PCSrc, MemRead, MemWrite, MemtoReg,zero;
	sc_signal < sc_uint<16> > addr;
	sc_signal < sc_uint<32> > wrDataR,rdDataA,rdDataB,wrDataM,rdAddrM,rdDataM,wrAddrM,rdAddrI,rdDataI;

	sc_clock TestClk("TestClock", 10, SC_NS,1,SC_NS);

	rf R("R");
	R.clk(TestClk);
	R.RegWrite(RegWrite);
	R.RegDst(RegDst);
	R.wrAddrR(wrAddrR);
	R.wrDataR(wrDataR);
	R.rdAddrS(rs);
	R.rdAddrT(rt);
	R.rdAddrD(rd);
	R.rdDataA(rdDataA);
	R.rdDataB(rdDataB);

	//im I("I");
	//sc_in < sc_uint<5> > rdAddr;
	//sc_out < sc_uint<32> > rdData;

	dm D("D");
	D.MemRead(MemRead);
	D.MemWrite(MemWrite);
	D.MemtoReg(MemtoReg);
	D.wrDataM(wrDataM);
	D.rdAddrM(rdAddrM);
	D.wrAddrM(wrAddrM);
	D.rdDataM(rdDataM);
	D.wrDataR(wrDataR);
	
	alu A("A");
	A.alc(alc);
	A.alop(alop);
	A.rdDataA(rdDataA);
	A.rdDataB(rdDataB);
	A.addr(addr);
	A.ALUSrc(ALUSrc);
	A.zero(zero);
//	A.result(result);
	A.wrDataR(wrDataR);
	A.rdAddrM(rdAddrM);
	A.wrAddrM(wrAddrM);

	cpu C("C");
	C.inst(inst);
	C.alop(alop);
	C.alc(alc);
	C.RegDst(RegDst);
	C.RegWrite(RegWrite);
	C.ALUSrc(ALUSrc);
	C.PCSrc(PCSrc);
	C.MemRead(MemRead);
	C.MemWrite(MemWrite);
	C.MemtoReg(MemtoReg);
	C.addr(addr);

	return 0;


}
