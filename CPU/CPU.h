#include <systemc.h>

SC_MODULE(rf){
	sc_in <bool> clk,RegWrite,RegDst,MemtoReg;
	sc_in < sc_uint<5> > rdAddrS,rdAddrT,rdAddrD;
	sc_in < sc_uint<32> > resultR,resultM;
	sc_in < sc_uint<2> > alop;
	sc_out <sc_uint<32> > rdDataA,rdDataB;

	sc_uint<32> reg[32];
	sc_uint<5> rA,rB,w ;
	
	void readA(){
		rA = rdAddrS;
		rdDataA = reg[rA];
	}

	void readB(){
		rB = rdAddrT;
		rdDataB = reg[rB];
	}

	
	void write(){
		if(RegWrite){
			if(alop.read() == 2){
				w = rdAddrD;
				reg[w] = resultR.read();
			}else if (alop.read() == 0 && MemtoReg){
				w = rdAddrT;
				reg[w] = resultM.read();
			}
		}
	}

	void print(){
		int i;
		cout << "Regfile" << endl;
		for(i=0;i<32;i++){
			cout << reg[i] << ' ';
		}
		cout << endl;
	}
		
	SC_CTOR(rf){
		int i;
		for(i=0;i<32;i++)
			reg[i]=i;
		SC_METHOD(readA);
			sensitive << rdAddrS ;
		SC_METHOD(readB);
			sensitive << rdAddrT ;
		SC_METHOD(write);
			sensitive << clk.pos() ;
		SC_METHOD(print);
			sensitive << clk.pos();
	}
		
};

SC_MODULE(alu){
	
	sc_in < sc_uint<4> > alc;
	sc_in < sc_uint<2> > alop;
	sc_in < sc_uint<6> > op;
	sc_in < sc_uint<32> > rdDataA,rdDataB;
	sc_in < sc_uint<16> > addr;
	sc_in < bool > ALUSrc,clk;
	sc_out < bool > zero;
	//sc_out < sc_uint<32> >result;
	sc_out < sc_uint<32> > rdAddrM,wrAddrM,resultR;  // ,wrDataR;

	sc_uint<32> dataA, dataB, res;

	int i,j;
	void operate(){
		zero = false;
		dataA = rdDataA.read();
		if(ALUSrc.read() == true){
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
		switch(op.read()){
			case 0: // arithmetic
				resultR.write(res);
				break;
	
			case 35: // load
				rdAddrM.write(res);
				break;
		
			case 43:// store
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
			sensitive << rdDataA << rdDataB << alc << alop << clk.pos();
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

	sc_in <bool> clk,MemRead,MemWrite,MemtoReg;
	sc_in < sc_uint<32> > wrDataM,rdAddrM,wrAddrM;
	sc_out <sc_uint<32> > rdDataM,resultM;
	sc_uint<32> mem[32];
	sc_uint<5> r,w;

	void read(){
//		cout << "read\n";
		if(MemRead){
//			cout << "Memread\n";
			r = rdAddrM;
			rdDataM = mem[r];
		}
		if(MemtoReg){
//			cout << "Memtoreg\n";
			r = rdAddrM;
			resultM = mem[r];
		}
	}

	void write(){
//		cout << "write\n";
		if(MemWrite){
//			cout << wrAddrM << " Memwrite \n";
			w = wrAddrM;
			mem[w] = wrDataM;
		}
	}

	void print(){
		int i;
		cout << "Data Memory " <<  endl;
		for(i=0;i<32;i++)
			cout << mem[i] << ' ';
		cout << endl;	
	}

	SC_CTOR(dm){
		int i;
		for(i=0;i<32;i++)
			mem[i]=i;
		SC_METHOD(read);
			sensitive << rdAddrM ;
		SC_METHOD(write);
			sensitive << clk.pos();
		SC_METHOD(print);
			sensitive << clk.pos();
	}
};

SC_MODULE(cpu){
	sc_in < sc_uint<32> > inst;
	sc_out < sc_uint <2> > alop;
	sc_out < sc_uint <4> > alc;
	sc_out < bool > RegDst, RegWrite, ALUSrc, PCSrc, MemRead, MemWrite, MemtoReg ;
	sc_out < sc_uint<16> > addr;
	sc_out < sc_uint<5> > rs,rt,rd,shamt;
	sc_out < sc_uint<6> > func,op;
	sc_uint<6> o;

	void instr(){
		op.write(inst.read()(31,26));
		rt.write(inst.read()(20,16));		
		rs.write(inst.read()(25,21));
		rd.write(inst.read()(15,11));
		o = inst.read()(31,26);
//		shamt.write(inst.read()(10,6);

		if (o==0){   //  Arithmetic
			cout << "Rtype\n";
			alop.write(2);  // OP = 10
			func.write(inst.read()(3,0));
			RegDst.write(true);
			RegWrite.write(true);
			ALUSrc.write(false);
			MemtoReg.write(false);
			MemRead.write(false);
			MemWrite.write(false);
			if (inst.read()(5,4)==2){  
				if (inst.read()(3,0)==0){  			// add - 0000 
					alc.write(2); 			// 0010
				}else if (inst.read()(3,0)==2){		// subtract - 0010
					alc.write(6); 			// 0110
				}else if (inst.read()(3,0)==4){  		// AND - 0100
					alc.write(0);			// 0000
				}else if (inst.read()(3,0)==5){		// OR - 0101
					alc.write(1);			// 0001
				}else if (inst.read()(3,0)==10){		// set on less than - 1010
					alc.write(7);			// 0111
				}
			}	
		}else if (o==35){  // Load
			cout << "load\n";
			addr = inst.read()(15,0);
			alop.write(0);
			alc.write(2);
			RegDst.write(false);
			RegWrite.write(true);
			ALUSrc.write(true);
			MemtoReg.write(true);
			MemRead.write(true);
			MemWrite.write(false);
		}else if (o==43){  // store
			cout << "store\n";
			addr = inst.read()(15,0);
			alop.write(0);
			alc.write(2);
			RegDst.write(false);
			RegWrite.write(false);
			ALUSrc.write(true);
			MemtoReg.write(false);
			MemRead.write(false);
			MemWrite.write(true);
		}else if (o==4){  // branch
			alop.write(1);
			alc.write(6);
			RegDst.write(false);
			RegWrite.write(false);
			ALUSrc.write(false);
			MemtoReg.write(false);
			MemRead.write(false);
			MemWrite.write(false);
		}else if (o==2){ // jump
			// to be done later once PC is working								

		}else{
			RegDst.write(false);
			RegWrite.write(false);
			MemRead.write(false);
			MemWrite.write(false);
			MemtoReg.write(false);
			ALUSrc.write(false);
		}
		
	}

	SC_CTOR(cpu){
		SC_METHOD(instr);
			sensitive << inst ;
	}

};
