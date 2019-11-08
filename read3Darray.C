// Author: Jim Klintrup
#ifndef READ3DARRAY_C
#define READ3DARRAY_C
#include <iostream>
#include <fstream>
using namespace std;
	Double_t AvgTempCor[2014][13][32]; // 3D-array for corrected temperature
void read3Darray();
void read3Darray(){
	ifstream data("datasets/uppsala_tm_1722-2013.dat");
	if(!data){
	cout << "Error: could not read from file" << endl;
	}
	Int_t nYear; // Placeholder for the year
	Int_t nMonth; // Placeholder for month of current year read
	Int_t nDay; // Placeholder for current day of read month
	Double_t nAvgTemp; // Placeholder for average temperature of read day
	Double_t nAvgTempCor; // Placeholder for corrected average temperature
	Int_t nDataId; // Id number identifing where measurement was taken
	for (Int_t year = 0; year < 2014; year++){
		for (Int_t month = 0; month < 13; month++){
			for (Int_t day = 0; day < 32; day++){
				AvgTempCor[year][month][day] = -273.0; // Fill all elements with unreal temperature
			}
		}
	}
	while(data >> nYear >> nMonth >> nDay >> nAvgTemp >> nAvgTempCor >> nDataId){
		AvgTempCor[nYear][nMonth][nDay] = nAvgTempCor; // Fill 3D array with data from file
	}
}
#endif
