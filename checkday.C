// Author: Jim Klintrup
#include "read3Darray.C"
using namespace std;
void checkday();
void checkday(){
	Int_t year;
	Double_t hot = 0;
	Double_t cold = 0;
	Int_t hotMonth = 0;
	Int_t hotDay = 0;
	Int_t coldMonth = 0;
	Int_t coldDay = 0;
	string Months[13] = {"Not a month","January","Febuary","March","April","May","June","July","August","September",
		"Oktober", "November", "December"};
	cout << "Enter the year that you wanna check for the hottest and coldest day: ";
	cin >> year;
	for (Int_t i = 1; i < 13; i++){ // Running over all elements of that year
		for (Int_t j = 1; j < 31; j++){
			if (AvgTemp[year][i][j] != -273.0){ // Only if temp is not -273.0, do this
				if (AvgTemp[year][i][j] < cold){ // If element is colder 
					cold = AvgTemp[year][i][j];  // change it
					coldMonth = i;
					coldDay = j;
				}
				if (AvgTemp[year][i][j] > hot){ // If element is hotter 
					hot = AvgTemp[year][i][j]; // change it
					hotMonth = i;
					hotDay = j;
				}
			}
		}
	}
	cout << "The hottest measured (recorded) day of " << year << " was the " << hotDay << " of " << Months[hotMonth] << " with " << hot << " degrees Celsius" << endl;
	cout << "and the coldest measured (recorded) day that same year was the " << coldDay << " of " << Months[coldMonth] << " with " << cold << " degrees Celsius" << endl;
}
