// Author: Jim Klintrup
#include <TTree.h>
#include <TFile.h>
using namespace std;
void treetest();
void treetest(){
	TTree mytree("mytree","the title of the tree"); // The tree
	Double_t array_1[3]= {0}; //test array with zeros
	mytree.Branch("thefirstbranch", array_1 , "arr_1[3]/D"); // New branch, its title, adress of array(array already adress), type of input.
	array_1[0]=1.1;
	array_1[1]=2.3;
	array_1[2]=3.5;
	mytree.Fill();
	mytree.Print();
}
