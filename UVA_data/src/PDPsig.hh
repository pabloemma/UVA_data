#ifndef PDPSIG_H_
#define PDPSIG_H_


// include file for PDPsig.cc
//	char Header_Line[20][100]; // curently the header buffer can be 10 lines long with 100 characters
    const char *line1 =" This is a UVA file \n";
	//char timec1[11];
	//char timec2[11];

	const char *time1 ="35638" ; // just a random picked time
	const char *time2 ="13222.8282";// for time stamp. is the sum of both.
	std::string timell; // exact time from data file, concatenation of time 1 and time 2
	Long64_t timel;
	Double_t FreqCenterLow =212.6;    // center frequency in MHz UVa uses lower boundary, gets recalculated in write header
	Double_t FreqCenter = 0.;
	Double_t FreqStep= .0016;      // step size in MHz
	Double_t ScanPoints =500.;      // number of points
	Int_t IntScanPoints = 500;
	Double_t ScanNumber = 0.;      // scan number
	Double_t Amplitude = 0.;  // this is the value read from the file
	Double_t Temperature= 0. ; // T of crate
	Double_t ControllerV= 0. ; // 3.3 V
	Double_t TuneV= 0. ; // tune voltage
	Double_t Offset= 0. ; // linear offset
	Double_t Phase_Voltage= 0. ; // control of phase
	Double_t Peak_Area= 0. ; // calculated online peak area
	Double_t QcurveAmp= 0. ;// Qcurve amplitude
	Double_t Pol_Calib_Const= 0. ; // calcluated polarization from TE measurement
	Double_t Gain= 0. ; // Gainsetting 0:low, 1:medium, 2:high
	Double_t Pol_Sign= 0. ;// 0 if no invert, 1 if signal is inverted
	Double_t Log_Channel= 0. ;// 1 if we are using log amp
	Double_t Peak_Amp= 0. ;//
	Double_t NMRchan= 0. ; // whci coil
	Double_t PeakCenter = 0. ;//
	Double_t BeamOn= 0. ;//
	Double_t RFlevel= 0. ;//
	Double_t IFatt= 0. ; //
    const char *comma =",\n"; // for creating csv file with comma at the end of line


	Double_t HeT = 5.0; // calculated from baratron presure
	Double_t HeP = 10.0 ; // Helium Pressures



	int WriteHeader() ;
#endif /* PDPSIG_H_ */