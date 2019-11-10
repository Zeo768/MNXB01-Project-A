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
	Int_t nAvgPoints=20;// Number of average points used to graph the moving average.
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
			
	
	TCanvas *cs = new TCanvas();
	// To plot this deviation from average effect we use THStack
	THStack *hs = new THStack("hs","");
	//First histogram is the red one with all data.
	hist->SetFillColor(kRed);
	hist->SetLineColor(kBlack);
	hist->SetLineWidth(1);
	hist->SetMinimum(2);
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
	
	
	
	hs->SetTitle("Yearly Mean Temperature, Uppsala 1722-2013");
    hs->GetXaxis()->SetTitle("Year");
    hs->GetYaxis()->SetTitle("Temperature[Celsius]");
    hs->GetXaxis()->CenterTitle(kTRUE);
    hs->GetYaxis()->CenterTitle(kTRUE);
    hs->SetMinimum(2);
    
    
    TGraph *gr=new TGraph(bins-nAvgPoints,x,y);
	gr->SetLineWidth(4);
	gr->Draw("SAME C");
	
	
	/*
	// Fit with a smaller amount of gaussians, follows the moving average with a smoothe function but does not give a good future prediction.
	Double_t par[21];
	TF1 *g1 = new TF1("g1","gaus",1722+nAvgPoints/2,1755);
	TF1 *g2 = new TF1("g2","gaus",1755,1785);
	TF1 *g3 = new TF1("g3","gaus",1785,1837);
	TF1 *g4 = new TF1("g4","gaus",1839,1870);
	TF1 *g5 = new TF1("g5","gaus",1880,1925);
	TF1 *g6 = new TF1("g6","gaus",1927,1958);
	TF1 *g7 = new TF1("g7","gaus",1960,2013-nAvgPoints/2);
	TF1 *total = new TF1("total","gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)+gaus(15)+gaus(18)",1722,2013);
	total->SetLineColor(1);
	total->SetLineWidth(4);
	gr->Fit(g1,"R0");
	gr->Fit(g2,"R+0");
    gr->Fit(g3,"R+0");
	gr->Fit(g4,"R+0");
	gr->Fit(g5,"R+0");
	gr->Fit(g6,"R+0");
	gr->Fit(g7,"R+0");
	g1->GetParameters(&par[0]);
	g2->GetParameters(&par[3]);
	g3->GetParameters(&par[6]);
	g4->GetParameters(&par[9]);
	g5->GetParameters(&par[12]);
	g6->GetParameters(&par[15]);
	g7->GetParameters(&par[18]);

	total->SetParameters(par);
	gr->Fit(total,"R+");
	*/
	
	
	
	
	
	
	/*
	
	//Fitting the graph with a lot of gaussian, a bit to many for the fit to be appropriate.
	Double_t par[42];
	TF1 *g1 = new TF1("g1","gaus",1730,1755);
	TF1 *g2 = new TF1("g2","gaus",1757,1768);
	TF1 *g3 = new TF1("g3","gaus",1771,1782);
	TF1 *g4 = new TF1("g4","gaus",1785,1805);
	TF1 *g5 = new TF1("g5","gaus",1810,1840);
	TF1 *g6 = new TF1("g6","gaus",1840,1868);
	TF1 *g7 = new TF1("g7","gaus",1868,1879);
	TF1 *g8 = new TF1("g8","gaus",1879,1900);
	TF1 *g9 = new TF1("g9","gaus",1900,1926);
	TF1 *g10 = new TF1("g10","gaus",1930,1939);
	TF1 *g11 = new TF1("g11","gaus",1943,1955);
	TF1 *g12 = new TF1("g12","gaus",1965,1980);
	TF1 *g13 = new TF1("g13","gaus",1981,2013-nAvgPoints/2);
	TF1 *g14 = new TF1("g14","gaus",1722+nAvgPoints/2,1730);
	TF1 *total = new TF1("total","gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)+gaus(15)+gaus(18)+gaus(21)+gaus(24)+gaus(27)+gaus(30)+gaus(33)+gaus(36)+gaus(39)",1722,2013);
	total->SetLineColor(1);
	total->SetLineWidth(4);
	gr->Fit(g1,"R0");
	gr->Fit(g2,"R+0");
    gr->Fit(g3,"R+0");
	gr->Fit(g4,"R+0");
	gr->Fit(g5,"R+0");
	gr->Fit(g6,"R+0");
	gr->Fit(g7,"R+0");
	gr->Fit(g8,"R+0");
	gr->Fit(g9,"R+0");
	gr->Fit(g10,"R+0");
	gr->Fit(g11,"R+0");
	gr->Fit(g12,"R+0");
	gr->Fit(g13,"R+0");
	gr->Fit(g14,"R+0");
	g1->GetParameters(&par[0]);
	g2->GetParameters(&par[3]);
	g3->GetParameters(&par[6]);
	g4->GetParameters(&par[9]);
	g5->GetParameters(&par[12]);
	g6->GetParameters(&par[15]);
	g7->GetParameters(&par[18]);
	g8->GetParameters(&par[21]);
	g9->GetParameters(&par[24]);
	g10->GetParameters(&par[27]);
	g11->GetParameters(&par[30]);
	g12->GetParameters(&par[33]);
	g13->GetParameters(&par[36]);
	g14->GetParameters(&par[39]);

	total->SetParameters(par);
	gr->Fit(total,"R+");
	*/
}
