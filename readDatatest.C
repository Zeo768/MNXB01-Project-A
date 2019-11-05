// Author: Jim Klintrup

#include <iostream>
#include <fstream>
// ROOT library obejcts
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include "MyClasses.C" // Class def, imp
#include <TTree.h> // Tree histogram
#include <TFile.h> // Write, read file
#include <TClonesArray.h> // Clone object

using namespace std;

void readDatatest();

void readDatatest(){
	// open input file
	ifstream data("/home/jim/MNXB01/project/MNXB01-project/MNXB01-Project-A/datasets/uppsala_tm_1722-2013.dat");
	if(!data){
	cout << "Error: could not read from file" << endl;
	}
	// Create the outfile and data structure before the loop
	TFile* file = new TFile("readDatatest.root", "RECREATE"); // If file exist, overwrite
	TTree* tree = new TTree("tree", "Output tree"); 
	MyEvent* event = new MyEvent();
	tree->Branch("event", &event);
	TClonesArray* trackArray = new TClonesArray("MyTrack", 1000);
	tree->Bronch("track", "TClonesArray", &trackArray);
	// Constants to pass
	Int_t nYear; // Placeholder for the year
	Int_t nMonth; // Placeholder for month of current year read
	Int_t nDay; // Placeholder for current day of read month
	Double_t nAvgTemp; // Placeholder for average temperature of read day
	Double_t nAvgTempCor; // Placeholder for corrected average temperature
	Int_t nDataId; // Id number identifing where measurement was taken
	Int_t previosyear = 0;
	Int_t thisyear = 0;
	Int_t nT = 0;
	cout << "Begin while-loop" << endl;
	// make a loop for the number of events
	while(data >> nYear >> nMonth >> nDay >> nAvgTemp >> nAvgTempCor >> nDataId){
		if (nDataId==1){
			thisyear = nYear;
			cout << "Inside first if-statement" << endl; 
			if (previousyear!=thisyear && previosyear!= 0){
				cout << "Filling tree " << nYear << endl;
				curryear = nYear;
				tree->Fill(); // Pass generated data to tree structure
				trackArray->Clear(); // reset the array but do not delete memory
				nT=0; // Reset array index
				event->NTracks=nYear;
				event->fV2=nDataId;
				MyTrack* track = new((*trackArray)[nT]) MyTrack();
				nT++;
				track->fPhi=nAvgTemp;
			}
			event->NTracks=nYear;
			event->fV2=nDataId;
			MyTrack* track = new((*trackArray)[nT]) MyTrack();
			nT++;
			track->fPhi=nAvgTemp;
			previousyear = thisyear;
		}
	}
	cout << "End while-loop" << endl;
	file->Write();
	file->Close();
}
