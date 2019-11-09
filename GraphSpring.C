// Author: Dilan
#include <iostream>			//Include standard
#include <fstream>
#include "FindSpringStart.C"		//Include the Spring start arrays
//#include "TString.h"
#include "TCanvas.h"
#include "TDatime.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TFrame.h"
#include "TF1.h"
#include "TLegend.h"

using namespace std;

void GraphSpring();			//The Graphing function
void GraphSpring(){
	
	TDatime da1(2000,01,12,0,0,0);		//Datime used for division of y-axis since we're handling dates
	
	const Int_t n = 291;				//Set size of arrays, 291 is the difference between year 2013 and 1722
	Int_t x[n], y[n];
	
	for (Int_t i = 0; i < n; i++) {		//Fills x-axis with years, 1722-2013
		x[i] = i+1722;
		//Sets da1 to the spring start of year i, but replaced the year with 2000 so every date is in the same year
		da1.Set(2000,SpringMonth[i],SpringDay[i],0,0,0);		
		y[i] = da1.Convert();			//Fills y-axis with spring start dates
	}
	
	TCanvas *c1 = new TCanvas("c1","The start of spring",1900,900);		//Canvas for graph
	TGraph *gr = new TGraph(n,x,y);						//The graph
	gr->SetLineColor(2);								//Set line width, color, style and title
	gr->SetLineWidth(4);
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(21);
	gr->SetTitle("The start of spring");				
	gr->GetXaxis()->SetTitle("Years");					//Set properties for x-axis
	gr->GetXaxis()->CenterTitle();
	gr->GetXaxis()->SetLimits(1700,2040);				//Set limits of x-axis
	gr->GetYaxis()->SetTimeDisplay(1);					//Set properties for y-axis (convert to time format)
	gr->GetYaxis()->SetTimeFormat("%m/%d");				//Set time format
	gr->GetYaxis()->SetTitle("Dates (Month/Day)");
	gr->GetYaxis()->CenterTitle();
	gr->SetMaximum(960768000);							//Set limits of y-axis (Unix Time Stamp)
	gr->SetMinimum(949363200);
	gr->Draw("AP");										//Draw all data points
   
	TF1 *fa1 = new TF1("fa1","pol0");					//Polynomial fits, p0 and p1
	fa1->SetLineColor(1);
	gr->Fit(fa1,"Q");
	TF1 *fa2 = new TF1("fa2","pol1");
	fa2->SetLineColor(2);
	gr->Fit(fa2,"Q+");
	
	TLegend *legend = new TLegend(0.3,0.7,0.7,0.9);		//Initialize the legend and set it.
	legend->SetHeader("Polynomial fits for spring start");
	legend->AddEntry(fa1,"p0 = 03/23 +/- 1 month","l");
	legend->AddEntry(fa2,"p1 = (-17 +/- 18) minutes per year","l");
	legend->Draw();


	c1->SetGrid();							//Settings for canvas
	c1->Update();
	c1->GetFrame()->SetFillColor(11);
	c1->Modified();
}
