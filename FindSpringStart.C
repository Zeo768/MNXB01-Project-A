// Author: Dilan
#include <iostream>
#include "read3Darray.C"	//include the 3D array
#include "TString.h"		//Include strings, used for returning dates

using namespace std;

Int_t SpringDay[291];		//Array of days, of when spring starts
Int_t SpringMonth[291];		//Array of months, of when spring starts
TString sD, sM;				//Placeholder strings for dates

void FindSpringStart();
void FindSpringStart(){		//Main func
	
	Int_t dayCount;			//Kepps track of consecutive days with temp above 0
	Bool_t spring;			//Used to break out of loop, when daycount is 7
	
	for (Int_t i = 0, ii = 0; i < 291; i++){		//Loop through years
		dayCount = 0;								//Init both variables
		spring = false;
		for (Int_t j = 0; j < 13; j++){				//Loop through months
			for (Int_t k = 0; k < 32; k++, ii++){	//Loop through days
				if (AvgTempCor[i+1722][j][k]>0 && j > 1 && j < 6){		//If current day temp is above 0 and between month 2 and 5
					if ((j == 2 && k > 14) || j !=2 ){				//If month 2, then days must be over 15 acc. to SMHI
						for(Int_t ch = 0; ch < 30; ch++){			//Loops from the first day above 0 temp to find consecutive days
							if(AvgTempCor[i+1722][j][k+ch] == -273.0){	//Correction for empty values in 3D array
								//Continue
							} else if(AvgTempCor[i+1722][j][k+ch]>0){	//If temp of current day is above 0
								dayCount += 1;						//Add 1 to daycount
								if(dayCount >= 7){					//If daycount >=7, we have spring
									spring = true;					//Spring is true
									sD="";				//Placeholder strings for dates
									sM="0";				//Because month under 10, we add 0 in front of moth to get 09 instead of 9
									sM+=Form("%d",j);	//Store the month of spring start
									if (k<10){			//Add 0 in front of day if under 10, to get right format, again
										sD+="0";
									}
									sD+=Form("%d",k);	//Store the day of spring start
									SpringMonth[i] = sM.Atoi();		//Convert to int from string
									SpringDay[i] = sD.Atoi();
									break;							//Break out, since we already found spring start for current year i
								}
							} else {			//If 7 consecutive days have not been found after 30 tries
								dayCount = 0;	//Set daycount to 0 and break out
								break;
							}
						}
					}
				}
				if(spring){		//Break out of day loop
					break;
				}
			}
			if(spring){			//Break out of month loop
				break;
			}
		}
	}
}
