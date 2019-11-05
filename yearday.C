// Author: Jim Klintrup
#ifndef YEAR_C // Slitting up the classes so ROOT does not complain
#define YEAR_C

#include <TObject.h>
class year : public TObject{
public:
Int_t fYear; // Members
year();
ClassDef(year, 1); // ROOT class definition
};
ClassImp(year) // ROOT class implimentation
year::year():TObject(), fYear(-1){} // Ctor
#endif

#ifndef MONTHOFYEAR_C
#define MONTHOFYEAR_C
class month : public TObject{
	public:
	Int_t fMonth;
	month();
	ClassDef(month, 1);
};
ClassImp(month)
month::month():TObject(),fMonth(-1){}
#endif

#ifndef DAYOFYEAR_C
#define DAYOFYEAR_C
class day : public TObject{
	public:
	Int_t fDay;
	Double_t fAvgTemp;
	Double_t fAvgTempCor;
	day();
	ClassDef(day, 1);
};
ClassImp(day)
day::day():TObject(),fDay(-1), fAvgTemp(-1), fAvgTempCor(-1){}
#endif
