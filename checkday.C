// Author: Jim Klintrup
#include "read3Darray.C"
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <THStack.h>
using namespace std;
	Double_t hot = 0;
	Double_t cold = 0;
	Int_t hotMonth = 0;
	Int_t hotDay = 0;
	Int_t coldMonth = 0;
	Int_t coldDay = 0;
	TH1D* hHot = new TH1D("hHot", "Hottest and coldest day of the year; Year; Celsius", 
	291, 1722, 2013);
	TH1D* hCold = new TH1D("hCold", "Hottest and coldest day of the year; Year; Celsius", 
	291, 1722, 2013);
	TH1D* hZero = new TH1D("hZero", "Hottest and coldest day of the year; Year; Celsius", 
	291, 1722, 2013);
void checkday();
void checkday(){
	Int_t year;
	for (Int_t k = 1722; k < 2014; k++){ // Loop over all years
		cold = 0;
		hot = 0;
		for (Int_t i = 1; i < 13; i++){ // Running over all elements of that year
			for (Int_t j = 1; j < 31; j++){
				if (AvgTempCor[k][i][j] != -273.0){ // Only if temp is not -273.0, do this
					if (AvgTempCor[k][i][j] < cold){ // If element is colder 
						cold = AvgTempCor[k][i][j];  // change it
						coldMonth = i;
						coldDay = j;
						hCold->SetBinContent(k-1722+1, cold);
					}
					if (AvgTempCor[k][i][j] > hot){ // If element is hotter 
						hot = AvgTempCor[k][i][j]; // change it
						hotMonth = i;
						hotDay = j;
						hHot->SetBinContent(k-1722+1, hot);
					}
				}
			}
		}
	}
	TF1* fitFunc = new TF1("fitFunc", "pol1", 1722, 2013);
	fitFunc->SetLineColor(kBlack);
	THStack *hs = new THStack("hs","");
	hHot->SetFillColor(kRed);
	hHot->SetLineColor(kBlack);
	hHot->SetLineWidth(1);
	hHot->SetMinimum(0);
	hHot->SetMaximum(35);
	hHot->Fit(fitFunc);
	gStyle->SetOptStat(1000000001);
	gStyle->SetOptFit(1);
	hs->Add(hHot);
	hCold->SetFillColor(kBlue);
	hCold->SetLineColor(kBlack);
	hCold->SetLineWidth(1);
	hCold->SetMinimum(-40);
	hCold->Fit(fitFunc);
	gStyle->SetOptStat(1000000001);
	gStyle->SetOptFit(1);
	hs->Add(hCold);
	hZero->SetFillColor(10);
	hZero->SetLineColor(kBlack);
	hZero->SetLineWidth(1);
	hs->Add(hZero);
	hs->Draw("nostack");
	hs->GetXaxis()->SetTitle("Year");
	hs->GetXaxis()->CenterTitle(true);
	hs->GetYaxis()->SetTitle("Celsius");
}

