// Author: Jim Klintrup
#include <iostream>
#include <fstream>
using namespace std;
void read3Darray();
void read3Darray(){
	ifstream data("/home/jim/MNXB01/project/MNXB01-project/MNXB01-Project-A/datasets/uppsala_tm_1722-2013.dat");
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
	//while(data >> nYear >> nMonth >> nDay >> nAvgTemp >> nAvgTempCor >> nDataId){ // Read each line 
		////if (nDataId==1){ // Using only Uppsala data
			//if (preyear!=nYear){
				//count++;
				//preyear=nYear;
			//}
		////}
	//}
	//cout << count << endl;
	Double_t AvgTemp[2014][13][32]; // 3D-array for average temperature
	for (Int_t i = 0; i < 2014; i++){
		for (Int_t j = 0; j < 13; j++){
			for (Int_t k = 0; k < 32; k++){
				AvgTemp[i][j][k] = -273.0; // Fill all elements with unreal temperature
			}
		}
	}
	ifstream data2("/home/jim/MNXB01/project/MNXB01-project/MNXB01-Project-A/datasets/uppsala_tm_1722-2013.dat");
	if(!data2){
	cout << "Error: could not read from file" << endl;
	}
	while(data2 >> nYear >> nMonth >> nDay >> nAvgTemp >> nAvgTempCor >> nDataId){
		AvgTemp[nYear][nMonth][nDay] = nAvgTemp; // Fill 3D array with data from file
	}
	//cout << AvgTemp[1870][6][3] << endl;
	for (Int_t l = 1722; l < 2014; l++){ // Checking for missing data or otherwise wrong
		for (Int_t m = 1; m < 13; m++){
			for (Int_t n = 1; n < 32; n++){
				if (AvgTemp[l][m][n] == -273.0){
					cout << l << " " << m << " " << n << endl;
				}
			}
		}
	}
}
