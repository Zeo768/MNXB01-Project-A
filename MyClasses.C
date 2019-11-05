// Author: Jim Klintrup
#ifndef MYEVENT_C // Slitting up the classes so ROOT does not complain
#define MYEVENT_C

#include <TObject.h>
class MyEvent : public TObject{
public:
Int_t NTracks; // Members
Double_t fV2;
MyEvent();
ClassDef(MyEvent, 1); // ROOT class definition
};
ClassImp(MyEvent) // ROOT class implimentation
MyEvent::MyEvent():TObject(),NTracks(-1),fV2(-1){} // Ctor
#endif

#ifndef MYTRACK_C
#define MYTRACK_C
class MyTrack : public TObject{
	public:
	Double_t fPhi;
	MyTrack();
	ClassDef(MyTrack, 1);
};
ClassImp(MyTrack)
MyTrack::MyTrack():TObject(),fPhi(-1){}
#endif

