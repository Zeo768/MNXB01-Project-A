// Author: Dilan
#include <iostream>
#include <fstream>
#include "read3Darray.C"
#include "TString.h"

using namespace std;
Int_t SpringDay[2014];
Int_t SpringMonth[2014];
TString sD, sM;
void FindSpringStart();
void FindSpringStart(){
	Int_t dayCount;
	Bool_t spring;
	
	for (Int_t i = 0, ii = 0; i < 2014; i++){
		dayCount = 0;
		spring = false;
		for (Int_t j = 0; j < 13; j++){
			for (Int_t k = 0; k < 32; k++, ii++){
				if (AvgTempCor[i][j][k]>0 && j > 1 && j < 6){
					if ((j == 2 && k > 14) || j !=2 ){
						for(Int_t ch = 0; ch < 100; ch++){
							if(AvgTempCor[i][j][k+ch] == -273.0 && i > 1721){
								//Fix this logic, but it works, so i dont know...
							} else if(AvgTempCor[i][j][k+ch]>0){
								//cout << ch << endl;
								dayCount += 1;
								if(dayCount >= 7){
									spring = true;
									sD="";
									sM="";
									//s= Form("%d",i);
									if (j<10){
										sM+="0";
									}
									sM+=Form("%d",j);
									if (k<10){
										sD+="0";
									}
									sD+=Form("%d",k);
									cout << sM << sD << endl;
									SpringMonth[i] = sM.Atoi();
									SpringDay[i] = sD.Atoi();
									break;
								}
							} else {
								dayCount = 0;
								break;
							}
						}
					}
				}
				if(spring){
					break;
				}
			}
			if(spring){
				break;
			}
		}

	}
}
