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
void readDataFile();
void readDataFile(){
	// open input file
	ifstream data("/home/jim/MNXB01/project/MNXB01-project/datasets/uppsala_tm_1722-2013.dat");
	Int_t nYear; // Placeholder for the year
	Int_t nMonth;
	Int_t nDay;
	Double_t nAvgTemp;
	Double_t nAvgTempCor;
	Int_t nDataId;
	while(data >> nYear >> nMonth >> nDay >> nAvgTemp >> nAvgTempCor >> nDataId){ // Read line, skip string, set eventNo to read number
		if (nDataId==1){
			cout << nAvgTemp << endl;
		}
	}
	data.close();
	gStyle->SetOptStat(1111);
	gStyle->SetOptFit(1111);
}
