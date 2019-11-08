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
	Int_t beginYear=1722;//Starting year
	Int_t endYear=2013;//Ending year
	Int_t bins=2013-1722;
	Int_t nAvgPoints=10;// Number of average points used to graph the moving average.
	TH1D* hist = new TH1D("hist", "Histogram", bins, beginYear, endYear);// Histogram for the data
	TH1D* hist2 = new TH1D("hist", "Histogram", bins, beginYear, endYear);//Histogram to create the blue below average effect.
	TH1D* hist3 = new TH1D("hist", "Histogram", bins, beginYear, endYear);//Histogram to add white over the blue.
	Double_t Avg;
	Double_t SumAll=0;
	Int_t t=0;
	
	Double_t x[bins-nAvgPoints];
	Double_t y[bins-nAvgPoints];
	
	//For-loop used to read data and sum it.
	for(Int_t i=beginYear; i<=endYear;i++){//Year loop
		Double_t Sum=0.0;
		Int_t n=0;
		for(Int_t j=0;j<=12;j++){//Month-loop
			for(Int_t k=0;k<=31;k++){//Day-loop
				if(AvgTempCor[i][j][k] != -273.0){//If the array value is supposed to be used. See read3Darray for more detail.
					Sum+=AvgTempCor[i][j][k];//Sum for every year.
					n++;
					
					SumAll+=AvgTempCor[i][j][k];//Sum for all years.
					t++;
				}
			}
		}
		
		hist->SetBinContent(i-beginYear+1,Sum/n);
	}
	//Filling the blue histogram with the mean temperature for all years.
	for(Int_t i=1; i<=bins;i++){
		hist2->SetBinContent(i,SumAll/t);
	}
	//For-loop for calculating averages for the moving average graph. 
	//Graph can't be over all points as we don't have values to average over close to the boundaries
	for(Int_t i=1;i<=bins-nAvgPoints;i++){
		Int_t k=nAvgPoints/2;
		x[i-1]=i+beginYear+k-1;//Adding the year value to the graph
		Double_t sum=0;
		for(Int_t n=-k;n<=k;n++)
			sum+=hist->GetBinContent(i+n+k);//Summing the nAvgPoints closest values to the point.
		y[i-1]=sum/(nAvgPoints+1);//Averaging the values
	}
	//Loop for the white histogram.
	for(Int_t i=1; i<=bins;i++){
		if(hist->GetBinContent(i) >= hist2->GetBinContent(i)){//If the years mean temperature is over the mean. 
			hist3->SetBinContent(i,hist2->GetBinContent(i));//Set the content equal to the overall average temperature
		}
		else{
			hist3->SetBinContent(i,hist->GetBinContent(i));//Otherwise set the content to the below average mean temperature.
		}
	}
			
	
	//TCanvas *cs = new TCanvas();
	// To plot this deviation from average effect we use THStack
	THStack *hs = new THStack("hs","");
	//First histogram is the red one with all data.
	hist->SetFillColor(kRed);
	hist->SetLineColor(kBlack);
	hist->SetLineWidth(1);
	hist->SetMinimum(3);
	hist->SetMaximum(8);
	hs->Add(hist);
	
	//Second histogram is the blue histogram that has the overall mean temperature as the value in every bin.
	hist2->SetFillColor(kBlue);
	hist2->SetLineColor(kBlack);
	hist2->SetLineWidth(1);
	hs->Add(hist2);
	
	//Third histogram is the white histogram to show blue when we wany and otherwise only white.
	hist3->SetFillColor(10);
	hist3->SetLineColor(kBlack);
	hist3->SetLineWidth(1);
	hs->Add(hist3);
	
	hs->Draw("nostack");//Nostack option means that their values don't stack.
	
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
