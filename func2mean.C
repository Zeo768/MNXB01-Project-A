//Author: Daniel Magdalinski

#include <iostream>
#include <fstream>
#include <vector>

#include "read3Darray.C"

#include <TH1.h>
#include <TF1.h>
#include <TStyle.h> 
#include <THStack.h>
#include <TColor.h>
#include <TGraph.h>
#include <TCanvas.h>

//Global variables
//AvgTempCor
//AvgTemp
using namespace std;

void func2mean();

void func2mean(){
	Int_t beginYear=1722;
	Int_t endYear=2013;
	Int_t bins=2013-1722;
	Int_t nAvgPoints=10;
	TH1D* hist = new TH1D("hist", "Histogram", bins, beginYear, endYear);
	TH1D* hist2 = new TH1D("hist", "Histogram", bins, beginYear, endYear);
	TH1D* hist3 = new TH1D("hist", "Histogram", bins, beginYear, endYear);
	Double_t Avg;
	Double_t SumAll=0;
	Int_t t=0;
	
	Double_t x[bins-nAvgPoints];
	Double_t y[bins-nAvgPoints];
	
	for(Int_t i=beginYear; i<=endYear;i++){
		Double_t Sum=0.0;
		Int_t n=0;
		for(Int_t j=0;j<=12;j++){
			for(Int_t k=0;k<=31;k++){
				if(AvgTempCor[i][j][k] != -273.0){
					Sum+=AvgTempCor[i][j][k];
					SumAll+=AvgTempCor[i][j][k];
					n++;
					t++;
				}
			}
		}

		if(n>320)
			hist->SetBinContent(i-beginYear+1,Sum/n);
		else
			hist->SetBinContent(i-beginYear,0);
	}
	for(Int_t i=1; i<=bins;i++){

		hist2->SetBinContent(i,SumAll/t);
		if(hist->GetBinContent(i)==0)
			hist->SetBinContent(i,1);
	}
	
	for(Int_t i=1;i<=bins-nAvgPoints;i++){
		Int_t k=nAvgPoints/2;
		x[i-1]=i+beginYear+k-1;
		Double_t sum=0;
		for(Int_t n=-k;n<=k;n++)
			sum+=hist->GetBinContent(i+n+k);
		y[i-1]=sum/(nAvgPoints+1);
	}
	for(Int_t i=beginYear; i<=endYear;i++){
		if(hist->GetBinContent(i-beginYear) >= hist2->GetBinContent(i-beginYear)){
			hist3->SetBinContent(i-beginYear,hist2->GetBinContent(i-beginYear));
		}
		else{
			hist3->SetBinContent(i-beginYear,hist->GetBinContent(i-beginYear));
		}
	}
			
	
	//TCanvas *cs = new TCanvas();
	
	THStack *hs = new THStack("hs","");
	hist->SetFillColor(kRed);
	hist->SetLineColor(kBlack);
	hist->SetLineWidth(1);

	hist->SetMinimum(3);
	hist->SetMaximum(8);
	
	hs->Add(hist);
	
	hist2->SetFillColor(kBlue);
	hist2->SetLineColor(kBlack);
	hist2->SetLineWidth(1);
	hs->Add(hist2);
	
	hist3->SetFillColor(10);
	hist3->SetLineColor(kBlack);
	hist3->SetLineWidth(1);
	hs->Add(hist3);
	hs->Draw("nostack");
	TGraph *gr=new TGraph(bins-nAvgPoints,x,y);
	
	gr->SetLineWidth(4);
	
	hs->SetTitle("Yearly Mean Temperature, Uppsala 1722-2013");
    hs->GetXaxis()->SetTitle("Year");
    hs->GetYaxis()->SetTitle("Temperature[Celsius]");
    hs->GetXaxis()->CenterTitle(kTRUE);
    hs->GetYaxis()->CenterTitle(kTRUE);
    hs->SetMinimum(2);
	gr->Draw("SAME C");
	
}
