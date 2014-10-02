#include<systemc.h>

SC_MODULE(hello_world){
	SC_CTOR(hello_world){
	}

	void say_hello(){
		cout<<"hello systemc\n";
	}
};

int sc_main(int argc,char *argv[]){
	hello_world hello("hi");
	hello.say_hello();
	return 0;
}
