#include "TSystem.h"
#include "TFile.h"
#include "TROOT.h"
#include "TF1.h"
#include "TTree.h"
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>

// modified by ak to compile on Mac with C11

using namespace std;
   

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
std::string temp = "PDPout.root";
const char *outFileName = temp.c_str();
extern int optind;
gROOT->Reset(); 
//TROOT troot();
TFile outFile(outFileName,"recreate");
Double_t Polarization,Area,He4Press,He4Temp,DoseDeposited;
Int_t ExperimentNum;
Int_t EventNum;
TTree PDPvar("PDPvar","PDP Tree");
PDPvar.Branch("EventNum",&EventNum,"EventNum/I");    
PDPvar.Branch("Polarization",&Polarization,"Polarization/D");  
PDPvar.Branch("Area",&Area,"Area/D");
PDPvar.Branch("ExperimentNum",&ExperimentNum,"ExperimentNum/I");
PDPvar.Branch("He4Press",&He4Press,"He4Press/D");
PDPvar.Branch("DoseDeposited",&DoseDeposited,"DoseDeposited/D");
 
  // Here is the data we want.
  data_t data;

  // Here is the file containing the data. Read it into data.
//  ifstream infile( "/home/dustin/work/g2pPDP/g2p/Log/2012-04-18_07h46m15s.csv" );
//  ifstream infile("/home/dustin/work/g2pPDP/g2p/Log/2012-04-26_16h14m14s.csv");
// Or wherever your file is located
  ifstream infile("/home/ptgroup/newevents.csv");
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
    //for (unsigned i = 0; i < data[n].size(); i++){
    //cout<<data[n][i]<<endl;
    EventNum = (int)data[n][0];
    Polarization = data[n][2];
    DoseDeposited = data[n][1];
    //Area = data[n][2];
    //He4Press =0.001*data[n][25];
    ExperimentNum = data[n][3];

    if(EventNum!=0) PDPvar.Fill();
    //}
    }
  
  outFile.Write(); // write to the output file
  outFile.Close(); // close the output file
  
  return 0;
  }
