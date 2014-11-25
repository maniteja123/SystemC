#include <systemc.h>

SC_MODULE(rf){
	sc_in <bool> clk,RegWrite,RegDst;
	sc_in < sc_uint<5> > wrAddrR,rdAddrS,rdAddrT,rdAddrD;
	sc_in < sc_uint<32> > wrDataR;
	sc_out <sc_uint<32> > rdDataA,rdDataB;

	sc_uint<32> reg[32];
	sc_uint<5> rA,rB,w ;
	
	void readA(){
		rA = rdAddrS;
		rdDataA = reg[rA];
	}

	void readB(){
		if(RegDst)
			rB = rdAddrD;
		else
			rB = rdAddrT;
		rdDataB = reg[rB];
	}

	
	void write(){
		if(RegWrite){
			w = wrAddrR;
			reg[w]=wrDataR;
		}
	}
		
	SC_CTOR(rf){
		SC_METHOD(readA);
			sensitive << rdAddrS ;
		SC_METHOD(readB);
			sensitive << rdAddrD << rdAddrT ;
		SC_METHOD(write);
			sensitive << wrAddrR << wrDataR << RegWrite << clk.pos() ;
	}
		
};

SC_MODULE(alu){
	
	sc_in < sc_uint<4> > alc;
	sc_in < sc_uint<2> > alop;
	sc_in < sc_uint<32> > rdDataA,rdDataB;
	sc_in < sc_uint<16> > addr;
	sc_in < bool > ALUSrc;
	sc_out < bool > zero;
	//sc_out < sc_uint<32> >result;
	sc_out < sc_uint<32> > wrDataR,rdAddrM,wrAddrM;

	sc_uint<32> dataA, dataB, res;

	int i,j;
	void operate(){
		zero = false;
		dataA = rdDataA.read();
		if(ALUSrc){
			dataB = addr.read();			
			j = dataB[15];
			for(i=16;i<32;i++)
				dataB[i]=j;	
		}else{
			dataB = rdDataB.read();
		}
		
		switch(alc.read()){
			
			case 0:
				res = dataA && dataB;
				break;

			case 1:
				res = dataA || dataB;
				break;

			case 2:
				res = dataA + dataB;
				break;

			case 6:
				res = dataA - dataB;
				break;
			
			case 7:
				if(dataA < dataB)
					res = 0;
				break;

			case 12:
				res = ~(dataA || dataB);
				break;
			
		}
		//result.write(res);
		if(res == 0)
			zero = true;
		switch(alop.read()){
			case 0: // arithmetic
		//		wrDataR.write(result);
				wrDataR.write(res);
				break;
	
			case 35: // load
		//		rdAddrM.write(result);
				rdAddrM.write(res);
				break;
		
			case 43:// store
		//		wrAddrM.write(result);
				wrAddrM.write(res);
				break;

			case 4:	
				break;

			case 2:
				break;
		
		}

	}

	
	
	SC_CTOR(alu){
		SC_METHOD(operate);
			sensitive << rdDataA << rdDataB << alc << alop ;
	}

};

SC_MODULE(im){
	sc_in < sc_uint<32> > rdAddrI;
	sc_out < sc_uint<32> > rdDataI;
	
	sc_uint<32> reg[32],r;

	void read(){
		r = rdAddrI;
		rdDataI = reg[r];
	}

	SC_CTOR(im){
		SC_METHOD(read);
			sensitive << rdAddrI ;
	}

};

SC_MODULE(dm){

	sc_in <bool> MemRead,MemWrite,MemtoReg;
	sc_in < sc_uint<32> > wrDataM,rdAddrM,wrAddrM;
	sc_out <sc_uint<32> > rdDataM,wrDataR;
	sc_uint<32> reg[32];
	sc_uint<5> r,w;

	void read(){
		if(MemRead){
			r = rdAddrM;
			rdDataM = reg[r];
		}
		if(MemtoReg){
			wrDataR.write(rdDataM.read());
		}
	}

	void write(){
		if(MemWrite){
			w = wrAddrM;
			reg[w] = wrDataM;
		}
	}

	SC_CTOR(dm){
		SC_METHOD(read);
			sensitive << MemRead << rdAddrM ;
		SC_METHOD(write);
			sensitive << MemWrite << wrAddrM << wrDataM ;
	}
};

SC_MODULE(cpu){
	sc_in < sc_uint<32> > inst;
	sc_out < sc_uint <2> > alop;
	sc_out < sc_uint <4> > alc;
	sc_out < bool > RegDst, RegWrite, ALUSrc, PCSrc, MemRead, MemWrite, MemtoReg ;
	sc_out < sc_uint<16> > addr;
	sc_uint<5> rs,rt,rd,shamt;
	sc_uint<6> func,op;

	void instr(){
		op = inst.read()(31,26);
		rs = inst.read()(25,21);
		rt = inst.read()(20,16);

		if (op==0){   //  Arithmetic
			alop.write(2);  // OP = 10
			func = inst.read()(3,0);
			rt = inst.read()(15,11);
			RegDst.write(true);
			RegWrite.write(false);
			ALUSrc.write(false);
			MemtoReg.write(false);
			MemRead.write(false);
			MemWrite.write(false);
			if (inst.read()(5,4)==2){  
				if (func==0){  			// add - 0000 
					alc.write(2); 			// 0010
				}else if (func==2){		// subtract - 0010
					alc.write(6); 			// 0110
				}else if (func==4){  		// AND - 0100
					alc.write(0);			// 0000
				}else if (func==5){		// OR - 0101
					alc.write(1);			// 0001
				}else if (func==10){		// set on less than - 1010
					alc.write(7);			// 0111
				}
			}	
		}else if (op=35){  // Load
			addr = inst.read()(15,0);
			alop.write(0);
			alc.write(2);
			RegDst.write(false);
			RegWrite.write(true);
			ALUSrc.write(true);
			MemtoReg.write(true);
			MemRead.write(true);
			MemWrite.write(false);
		}else if (op==43){  // store
			addr = inst.read()(15,0);
			alop.write(0);
			alc.write(2);
			RegDst.write(false);
			RegWrite.write(false);
			ALUSrc.write(true);
			MemtoReg.write(false);
			MemRead.write(false);
			MemWrite.write(false);
		}else if (op==4){  // branch
			alop.write(1);
			alc.write(6);
			RegDst.write(false);
			RegWrite.write(false);
			ALUSrc.write(false);
			MemtoReg.write(false);
			MemRead.write(false);
			MemWrite.write(false);
		}else if (op==2){ // jump
								

		}
		
	}

	SC_CTOR(cpu){
		SC_METHOD(instr);
			sensitive << inst ;
	}

};
