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
	Int_t preyear = 0; // previous year check
	Int_t count = 0; // Count for how many years
	for (Int_t i = 0; i < 2014; i++){
		for (Int_t j = 0; j < 13; j++){
			for (Int_t k = 0; k < 32; k++){
				AvgTempCor[i][j][k] = -273.0; // Fill all elements with unreal temperature
			}
		}
	}
	while(data >> nYear >> nMonth >> nDay >> nAvgTemp >> nAvgTempCor >> nDataId){
		AvgTempCor[nYear][nMonth][nDay] = nAvgTempCor; // Fill 3D array with data from file
	}
}
#endif
