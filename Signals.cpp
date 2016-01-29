/*
Copyright 2015 Orlando Aguilar Vivanco

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/


// Example of use.
//

#include <iostream>
#include <list>
#include "Signal.h"
#include "Delegate.h"
#include "PointerFunc.h"

using namespace siglot;
using namespace std;

void empty(){
	cout << "Empty" << endl;
}

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
	Classe myClass;
	
	Slot<int, float> slot;		//declaring a slot that holds functions and functors which receive 2 parameters, an int and a float
	Signal<int, float> signal;	//declares a signal compatible with the previous slot
	
		
	slot.Attach(&myClass, &Classe::miMethod);	//adds to the slot a member method of myClass
	slot.Attach(&myFloat);						//adds to the 
	slot.Attach(&Classe::StaticMethod);			//adds a static method to the slot

	signal.Connect(&slot);						//connects the signal and the slot, so that firing the signal will also fire all the elements connected to the slot
	signal(2, 3);								//fires the signal, which will fire the three elements connected to the slot

	slot.Detach(&myFloat);						//detaches the function from the slot
	signal(2, 4);								//now, firing the signal will only fire two elements of the slot

	slot.Detach(&myClass, &Classe::miMethod);	//detaches the member of myClass
	signal(2, 5);								//fires the only one element of the slot

	slot.Detach(&myClass, &Classe::miMethod2);	//tryies to detach an element that is not present in the slot. Nothing happens
	signal(2, 6);								
		
	slot.Detach(&Classe::StaticMethod);			//detaches the last element of the signal
	signal(2, 7);								//slot empty, nothing is fired

	//signal and slot for members with empty parameter list
	Signal<> empParamSignal;
	Slot<> empParamSlot;

	empParamSlot.Attach(&empty);

	empParamSignal.Connect(&empParamSlot);
	empParamSignal();
	return 0;
}

