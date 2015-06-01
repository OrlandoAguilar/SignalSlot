// Signals.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <list>
#include "Signal.h"
#include "Slot.h"
#include "Delegate.h"
#include "PointerFunc.h"

using namespace siglot;
using namespace std;

void myFloat(int a, float b){
	cout << a<<b <<"my float"<< endl;
}

class Classe{
public:
	void miMethod(int a,float b){
		cout << a<<b << "my method "<<endl;
	}

	void miMethod2(int a, float b){
		cout << a<<b <<"my method2"<< endl;
	}

	static void StaticMethod(int a, float b){
		cout << a<<b <<"static method"<< endl;
	}
};

int main(int argc, char* argv[])
{
	Slot<int, float> slot;
	
	Classe clase;
		
	Signal<int, float> signal;

	slot.Attach(&clase, &Classe::miMethod);
		
	slot.Attach(&myFloat);

	slot.Attach(&Classe::StaticMethod);

	signal.Connect(&slot);
	signal(2, 3);

	slot.Detach(&myFloat);
	signal(2, 4);

	slot.Detach(&clase, &Classe::miMethod);
	signal(2, 5);

	slot.Detach(&clase, &Classe::miMethod2);
	signal(2, 6);
		
	slot.Detach(&Classe::StaticMethod);
	signal(2, 7);

	return 0;
}

