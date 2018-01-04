#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>  
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TFile.h"
#include "TROOT.h"
#include "TF1.h"


#include "PDPsig.hh"
using namespace std;

FILE *fp; // Output csv file
   

typedef vector <double> record_t; 
typedef vector <record_t> data_t;
istream& operator >> ( istream& ins, record_t& record )
  {
  // make sure that the returned record contains only the stuff we read now
  record.clear();

  // read the entire line into a string (a CSV record is terminated by a newline)
  string line;
  getline( ins, line );

  // now we'll use a stringstream to separate the fields out of the line
  stringstream ss( line );
  string field;
  while (getline( ss, field, ',' ))
    {
    // for each field we wish to convert it to a double
    // (since we require that the CSV contains nothing but floating-point values)
    stringstream fs( field );
    double f = 0.0;  // (default value is 0.0)
    fs >> f;

    // add the newly-converted field to the end of the record
    record.push_back( f );
    }

  // Now we have read a single line, converted into a list of fields, converted the fields
  // from strings to doubles, and stored the results in the argument record, so
  // we just return the argument stream as required for this kind of input overload function.
  return ins;
  }

//-----------------------------------------------------------------------------
// Let's likewise overload the stream input operator to read a list of CSV records.
// This time it is a little easier, just because we only need to worry about reading
// records, and not fields.
istream& operator >> ( istream& ins, data_t& data )
  {
  // make sure that the returned data only contains the CSV data we read here
  data.clear();

  // For every record we can read from the file, append it to our resulting data
  record_t record;
  while (ins >> record)
    {
    data.push_back( record );
    }

  // Again, return the argument stream as required for this kind of input stream overload.
  return ins;  
  }
  
int main(){


// open output csv file 
	  fp = fopen("POLUVAfile.csv","w");




std::string temp ="PDPout.root";
const char *outFileName = temp.c_str();
extern int optind;
gROOT->Reset(); 
//TROOT troot();  
TFile outFile(outFileName,"recreate");
Double_t signal, freq;
Int_t EventNum, TimeStamp;

TTree PDPvar("PDPvar","PDP Tree");
PDPvar.Branch("freq",&freq,"freq/D");    
PDPvar.Branch("signal",&signal,"signal/D");  

  // Here is the data we want.
  data_t data;

  // Here is the file containing the data. Read it into data.
  //ifstream infile("/home/dustin/store/work/Target/2015-04/2015-05-12_18h20m46s-PolySignal.csv" );
  //ifstream infile("/home/dustin/store/work/g2pPDP/Log/2012-03-16_11h42m30s-base-RawSignal.csv" );
  //ifstream infile("/home/dustin/store/work/g2pPDP/Log/2012-03-16_11h42m30s-PolySignal.csv" );
  //ifstream infile("/home/dustin/store/work/Target/2015-04/2015-05-27_12h22m16s-PolySignal.csv" );
  //ifstream infile("/home/dustin/store/work/Target/data_look/anime_fast/SignalToNoise/dat/2016-12-04_16h30m45s-PolySignal.csv" );
  //ifstream infile("/home/dustin/store/work/Target/data_look/anime_fast/SignalToNoise/dat/2016-12-05_19h33m11s-PolySignal.csv" );
  ifstream infile("/Users/klein/UVaNMR/2016-12-05_19h25m40s-RawSignal.csv");

infile >> data;

  // Complain if something went wrong.
  if (!infile.eof())
    {
    cout << "bad file\n";
    return 1;
    }

  infile.close();
   
/*
  // Otherwise, list some basic information about the file.
  cout << "Your CSV file contains " << data.size() << " records.\n";

  unsigned max_record_size = 0;
  for (unsigned n = 0; n < data.size(); n++)
    if (max_record_size < data[ n ].size())
      max_record_size = data[ n ].size();
      cout << "The largest record has " << max_record_size << " fields.\n";

//cout << "The first field in the second record contains the value " << (int)data[ 1 ][ 0 ] << ".\n";
*/

for (unsigned n = 0; n < data.size(); n++){
    int k = WriteHeader();
    ofstream myfile;
    //myfile.open ("nmr.dat");
    EventNum = n+1;
    TimeStamp = (int)data[n][0];

    if(TimeStamp>0){  // event selection
for (unsigned i = 1; i < data[n].size(); i++){

    // write data to csv file
    
    signal = data[n][i]*20/1.4; // what is this fudge factor?
    fprintf(fp,"%lf %s ",data[n][i],comma);
   
    
    
    //myfile <<32.3+i*0.0016 <<" "<< signal<<"\n";
    freq = 212.600+i*0.0016;
    //myfile <<212.600+i*0.0016 <<" "<< signal<<"\n";
    //cout << data[ n ].size()<<" "<<32.3+i*0.0016 <<" "<< signal<<"\n";
     if(i==200){   // The position in the line 
    PDPvar.Fill();
    }   
if(i==data[ n ].size()-1){

    //myfile.close();
    //gSystem->Exec("gnuplot ppoints.gnuplot");
    //TString lable; char b[10];
    //sprintf(b,"%d",TimeStamp); lable=b;
    //gSystem->Exec("mv plot.gif test_plots/"+lable+".gif");
    //gSystem->Exec("rm nmr.dat");  
    }
    }
  }
}
  //myfile.close();
  outFile.Write(); // write to the output file
  outFile.Close(); // close the output file
  fclose (fp) ; // close the cvs file

  return 0;
  }
  
  
  
int WriteHeader()
/* this routine writes the header in the csv file at every sweep
It follows the LANL NMR format, so that we can read th file with the converter
*/
{
// recalculate the frequency center
    FreqCenter = FreqCenterLow + (ScanPoints)/2.*FreqStep;


/*for dummy header.  */
	for(int k = 0;k<10;k++)
	{
	  fputs(line1,fp);
	}
//    cout<<" I am in header \n";
    fprintf(fp,"%s %s",time1,comma);

    fprintf(fp,"%s %s",time2,comma);
    fprintf(fp,"%lf %s ",FreqCenter, comma);


    fprintf(fp,"%lf %s ",FreqStep,comma);
    fprintf(fp,"%lf %s ",ScanPoints,comma);
    IntScanPoints = (int) ScanPoints; // need this for the memory allocation of array
    fprintf(fp,"%lf %s ",  ScanNumber,comma);
    fprintf(fp,"%lf %s ",  Temperature,comma);
    fprintf(fp,"%lf %s ",  ControllerV,comma);
    fprintf(fp,"%lf %s ",  TuneV,comma);
    fprintf(fp,"%lf %s ",  Offset,comma);

	fprintf(fp,"%lf %s ",  Phase_Voltage,comma);
	fprintf(fp,"%lf %s ",  Peak_Area,comma);
	fprintf(fp,"%lf %s ",  QcurveAmp,comma);
	fprintf(fp,"%lf %s ",  Pol_Calib_Const,comma);
	fprintf(fp,"%lf %s ",  Gain,comma);
	fprintf(fp,"%lf %s ",  Pol_Sign,comma); // 0 if not inverted 1, if inverted
	fprintf(fp,"%lf %s ",  Log_Channel,comma);
	fprintf(fp,"%lf %s ",  Peak_Amp,comma);
	fprintf(fp,"%lf %s ",  NMRchan,comma);   // ph1 stands for placeholder
	fprintf(fp,"%lf %s ",  PeakCenter,comma);
	fprintf(fp,"%lf %s ",  BeamOn,comma);   // ph1 stands for placeholder
	fprintf(fp,"%lf %s ",  RFlevel,comma);
	fprintf(fp,"%lf %s ",  IFatt,comma);   // ph1 stands for placeholder
	fprintf(fp,"%lf %s ",  HeT,comma);   // ph1 stands for placeholder
	fprintf(fp,"%lf %s ",  HeP,comma);

    	  


return 0;
}
