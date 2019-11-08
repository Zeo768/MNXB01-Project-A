// Author: Jim Klintrup
#include "read3Darray.C"
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <THStack.h> // Stacking hisograms ontop of eachother
using namespace std;
	Double_t hot = 0; // Placeholder for hot temperature
	Double_t cold = 0; // Placeholder for cold temperature
	TH1D* hHot = new TH1D("hHot"  , "", 291, 1722, 2013); // Histogram for hottest day, 291 bins between 1722 and 2013
	TH1D* hCold = new TH1D("hCold", "", 291, 1722, 2013); // Histogram for coldest day, 291 bins between 1722 and 2013
	TH1D* hZero = new TH1D("hZero", "", 291, 1722, 2013); // Histogram used to split up histograms for hottest and coldest
void checkday();
void checkday(){
	for (Int_t k = 1722; k < 2014; k++){ // Loop over years
		cold = 0;
		hot = 0;
		for (Int_t i = 1; i < 13; i++){ // Running over all elements of that year
			for (Int_t j = 1; j < 31; j++){
				if (AvgTempCor[k][i][j] != -273.0){ // Only if temp is not -273.0, do this
					if (AvgTempCor[k][i][j] < cold){ // If element is colder 
						cold = AvgTempCor[k][i][j];  // change it
						hCold->SetBinContent(k-1722+1, cold); // Set bin content to new value
					}
					if (AvgTempCor[k][i][j] > hot){ // If element is hotter 
						hot = AvgTempCor[k][i][j]; // change it
						hHot->SetBinContent(k-1722+1, hot); // Set bin content to new value
					}
				}
			}
		}
	}
	TF1* fitFunc = new TF1("fitFunc", "pol1", 1722, 2013); // A fit function of degree one, linear fit
	fitFunc->SetLineColor(kBlack); // Calling SetLineColer function, setting line color to black
	THStack *hs = new THStack("hs",""); // New stack for stacking histograms
	hHot->SetFillColor(kRed); // Fill histogram with color red
	hHot->SetLineColor(kBlack); // Line color of bins
	hHot->SetLineWidth(1); // Line witdh for bin lines
	hHot->SetMinimum(0); // Bottom of the histogram
	hHot->SetMaximum(35); // Top of histogram
	hHot->Fit(fitFunc); // Fit the histogram with the function fitFunc
	gStyle->SetOptStat(1000000001); // Display the name of the histogram hHot in canvas
	gStyle->SetOptFit(1); // Display fit parameters in canvas
	hs->Add(hHot); // Add the histogram to the stack
	hCold->SetFillColor(kBlue); // Set fill color of histogram hCold
	hCold->SetLineColor(kBlack); // Set line color of bins in histogram
	hCold->SetLineWidth(1); // Set line width of bins
	hCold->SetMinimum(-40); // Set bottom of histogram
	hCold->Fit(fitFunc); // Fit fitFunc to histogram hCold
	gStyle->SetOptStat(1000000001); // Display name of histogram in canvas
	gStyle->SetOptFit(1); // Display fit parameters in canvas
	hs->Add(hCold); // Add histogram to stack
	hZero->SetFillColor(10); // Set fill color to white
	hZero->SetLineColor(kBlack); // Set line color
	hZero->SetLineWidth(1); // Set line width
	hs->Add(hZero); // Add to stack
	hs->Draw("nostack"); // Draw the stack of histograms
	hs->GetXaxis()->SetTitle("Year"); // Name of x-axis
	hs->GetXaxis()->CenterTitle(true); // Center the name of x-axis
	hs->GetYaxis()->SetTitle("Celsius"); // Name of y-axis
}

