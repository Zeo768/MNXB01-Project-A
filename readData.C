// Author Jim Klintrup
#include <iostream>
#include <fstream>
// ROOT library obejcts
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include "yearday.C" // Class def, imp
#include <TTree.h> // Tree histogram
#include <TFile.h> // Write, read file
#include <TClonesArray.h> // Clone object
using namespace std;
void readDataFile();
void readDataFile(){
	// Create the outfile and data structure before the loop
	TFile* file = new TFile("readData.root", "RECREATE"); // If file exist, overwrite
	TTree* tree = new TTree("tree", "Output tree"); // Create tree for structure
	year* theyear = new year();
	tree->Branch("theyear", &theyear);
	TClonesArray* dayArray = new TClonesArray("day", 1000);
	tree->Bronch("day", "TClonesArray", &dayArray);
	// open input file
	ifstream data("/home/jim/MNXB01/project/MNXB01-project/MNXB01-Project-A/datasets/uppsala_tm_1722-2013.dat");
	if(!data){
	cout << "Error: could not read from file" << endl;
	}
	Int_t nYear; // Placeholder for the year
	Int_t nMonth; // Placeholder for month of current year read
	Int_t nDay; // Placeholder for current day of read month
	Double_t nAvgTemp; // Placeholder for average temperature of read day
	Double_t nAvgTempCor; // Placeholder for corrected average temperature
	Int_t nDataId; // Id number identifing where measurement was taken
	Int_t curryear = 0;
	Int_t nT = 0;
	while(data >> nYear >> nMonth >> nDay >> nAvgTemp >> nAvgTempCor >> nDataId){ // Read line
		curryear = nYear;
		if (nDataId==1){
			cout << nYear << endl;
			if(curryear!=nYear){
				tree->Fill();
				dayArray->Clear();
				curryear=nYear;
				theyear->fYear=curryear;
				nT = 0;
			}
			day* theday = new((*dayArray)[nT]) day();
			nT++;
			theday->fAvgTemp=nAvgTemp;
			theday->fAvgTempCor=nAvgTempCor;
		}
	}
	file->Write();
	file->Close();
	cout << "2" << endl;
	data.close();
}
