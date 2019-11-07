// Author: Dilan
#include <iostream>
#include <fstream>
#include "DilanFunc.C"
#include "TString.h"
#include "TCanvas.h"
#include "TDatime.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TFrame.h"

using namespace std;

void GraphSpring();
void GraphSpring(){
	
	TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);

	c1->SetFillColor(10);
	c1->SetGrid();
	
	TDatime da1(2000,01,12,0,0,0);
	TDatime da2(2000,01,12,0,0,0);
	
	

	const Int_t n = 291;
	Int_t x[n];
	Int_t y[n];

   for (Int_t i = 0; i < n; i++) {
     x[i] = i+1722;
     da2.Set(2000,SpringMonth[i+1722],SpringDay[i+1722],0,0,0);
     y[i] = da2.Convert();
   }
   TGraph *gr = new TGraph(n,x,y);
   gr->SetLineColor(2);
   gr->SetLineWidth(4);
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("The start of spring");
   gr->GetXaxis()->SetTitle("Years");
   gr->GetYaxis()->SetTimeDisplay(1);
   gr->GetYaxis()->SetTimeFormat("%m/%d");
   gr->GetYaxis()->SetTitle("Dates (m/d)");
   gr->Draw("ACP");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();


}
