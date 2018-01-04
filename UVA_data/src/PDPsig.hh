#ifndef PDPSIG_H_
#define PDPSIG_H_


// include file for PDPsig.cc
//	char Header_Line[20][100]; // curently the header buffer can be 10 lines long with 100 characters
    const char *line1 =" This is a UVA file \n";
	char timec1[11];
	char timec2[11];

	std::string time1;
	std::string time2; // for time stamp. is the sum of both.
	std::string timell; // exact time from data file, concatenation of time 1 and time 2
	Long64_t timel;
	Double_t FreqCenter ;   // center frequency in MHz
	Double_t FreqStep;      // step size in MHz
	Double_t ScanPoints;      // number of points
	Int_t IntScanPoints;
	Double_t ScanNumber;      // scan number
	Double_t Amplitude;  // this is the value read from the file
	Double_t Temperature; // T of crate
	Double_t ControllerV; // 3.3 V
	Double_t TuneV; // tune voltage
	Double_t Offset; // linear offset
	Double_t Phase_Voltage; // control of phase
	Double_t Peak_Area; // calculated online peak area
	Double_t QcurveAmp;// Qcurve amplitude
	Double_t Pol_Calib_Const; // calcluated polarization from TE measurement
	Double_t Gain; // Gainsetting 0:low, 1:medium, 2:high
	Double_t Pol_Sign;// 0 if no invert, 1 if signal is inverted
	Double_t Log_Channel;// 1 if we are using log amp
	Double_t Peak_Amp;//
	Double_t NMRchan; // whci coil
	Double_t PeakCenter ;//
	Double_t BeamOn;//
	Double_t RFlevel;//
	Double_t IFatt; //
    const char *comma =","; // for creating csv file with comma at the end of line


	Double_t HeT; // calculated from baratron presure
	Double_t HeP; // Helium Pressures



	int WriteHeader() ;
#endif /* PDPSIG_H_ */