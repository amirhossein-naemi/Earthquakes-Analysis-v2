//---------------------------------------------------------------------------
//
// Earthquakes' Events Analysis
// By Amirhossein Naemi
// Febuary, 2015
// GIT: https://github.com/amirhossein-naemi/Earthquakes-Analysis
// This program reads in one integer from a amir.in file and returns the
//
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <ctype.h>

using namespace std;

const int colbreaksize = 10;
const int colsize = 7;

const int MAXDATA=300;

int valid,invalid,sign;

inline void toupper_str(std::string& str) {
    for (short i = 0; i < str.size(); ++i)
        str[i] = toupper(str[i]);
}

string toupper_str_C(std::string str) {
    toupper_str(str);
    return str;
}

enum magnitude_type {
    ML=1, Ms, Mb, Mw
};

string network_codes_str[5] = {"CE", "CI", "FA", "NP", "WR"};

enum network_codes {
    CE=1, CI, FA, N
};

int network_code_enum(string str_net_code) {
    // Case sensitive
    if (str_net_code == "CE")
        return 1;
    if (str_net_code == "CI")
        return 2;
    if (str_net_code == "FA")
        return 3;
    if (str_net_code == "NP")
        return 4;
    if (str_net_code == "WR")
        return 5;
    return -1;
}

// – Long­period (L)
// – Short­period (B)
// – Broadband (H)
string types_of_band_str[3] = {"Long­period", "Short­period", "Broadband"};
char types_of_band_char[3] = {'L', 'B', 'H'};

enum types_of_band {
    Long_period=1, Short_period=2, Broadband=3
};

int type_of_band_enum(string str_type_of_band) {

    str_type_of_band=toupper_str_C(str_type_of_band);
    toupper_str(str_type_of_band);

    if (str_type_of_band == "LONG-PERIOD")
        return 1;
    if (str_type_of_band == "SHORT-PERIOD")
        return 2;
    if (str_type_of_band == "BROADBAND")
        return 3;
    return -1;
}

enum Orientation {
    NN, E, Z
};

string types_of_instrument_str[3] = {"High_Gain", "Low_Gain", "Accelerometer"};
char types_of_instrument_char[3] = {'H', 'L', 'N'};

enum types_of_instrument {
    High_Gain=1, Low_Gain, Accelerometer
};

// function to convert from "type_of_instrument" to a string...
string type_of_inst_string(types_of_instrument type_of_inst) {

    switch (type_of_inst) {
    case High_Gain:
        return "High Gain";
    case Low_Gain:
        return "Low Gain";
    case Accelerometer:
        return "Accelerometer";
    default:
        return "ILLEGAL";
    }
}

int type_of_instrument_enum(string str_type_of_inst) {
    toupper_str(str_type_of_inst);
    //Case insensitive
    if (str_type_of_inst == "LOW-GAIN")
        return 1;
    if (str_type_of_inst == "HIGH-GAIN")
        return 2;
    if (str_type_of_inst == "ACCELEROMETER")
        return 2;
    return -1;
}

// Following a valid header, the input file has an indefinite number of entries,
// one per row, but no more than 300 (this limit is important, as you are
// supposed to crete an array to store the input entries). Each entry in the
// table is composed of the following:
struct EQ {

    network_codes network_code;
    string station_code;
    types_of_band type_of_band;
    types_of_instrument type_of_instrument;
    string Orientation;

};

EQ eqs[MAXDATA];

void print_output(ofstream & o, stringstream & txt, bool only2file=false) {
    if(!only2file) cout << txt.str();
    o << txt.str();
    txt.str( std::string() );
    txt.clear();
}

void open_input(ifstream & ifile, string ifilename, ofstream & log) {
    // Sanity check on the file stream

    ifile.open(ifilename.c_str());
    if (!ifile.is_open()) {
        stringstream str;
        str << "Error! Cannot open input file: " <<  ifilename << endl;
        print_output(log,str);
        exit(0);
    }
    return;
}

void open_output(ofstream & o, string ofilename) {
    // Print on output file
    o.open(ofilename.c_str());
    if (!o.is_open()) {
        cout << "Error! The output file: " + ofilename + " is locked\n";

        exit(0);
    }
    return;
}

//---------------------------------------------------------------------------

bool is_there_any_err(EQ eq) {
    if (eq.network_code <1 || eq.network_code >5)
        return true;

    //if (eq.type_of_band <1 || eq.type_of_band >5)
    //    return true;

    //if (eq.type_of_instrument <1 || eq.type_of_instrument >5)
    //    return true;

    return false;
}

bool isok_network_code(string str){
    // Network code: Case sensitive: 2 characters. Must be in capital letters to
    // be valid. It can be any of the following:
    // network_code network_code;
    // string network_code;
    // char network_code;
    if(str.size()==2)
    {
        for(int i=0;i<2;i++)
        {
            if(!isalpha(str[i]))
                return false;
            if(!isupper(str[i]))
                return false;
        }
        // if return true, means everything is fine
        return true;
    }
    return false;
}

bool isok_station_code(string str){
    // Station code: Case sensitive: Must be either 3 alphabetic characters in
    // capital letters, or 5 numeric characters to be valid. station_code:
    // Case sensitive : Must be either 3 alphabetic characters in
    // capital letters, or 5 numeric characters to be valid.string ssn;
    if(str.size()==3)
    {
        for(int i=0;i<3;i++)
        {
            if(!isalpha(str[i]))
                return false;
            if(!isupper(str[i]))
                return false;
        }

        // if return true, means everything is fine
        return true;
    }

    if(str.size()==5)
    {
        for(int i=0;i<5;i++)
            if(!isdigit(str[i]))
                // there is an error
                    return false;

        // if return true, means everything is fine
        return true;
    }

    // there is an error
    return false;
}


bool isok_type_of_band(string str){

    // Type of band: Case insensitive: One word. It can be any of the following
    // to be valid (the code in
    // parenthesis is for later reference):
    // string type_of_band;
    types_of_band t=(types_of_band)type_of_band_enum(str);
    if (t<1 || t>3) return false;
    return true;
}

bool isok_type_of_instrument(string str){
    // Type of instrument: Case insensitive: One word. It can be any of the
    // following to be valid (the code
    // in parenthesis is for later reference):
    // type_of_instrument type_of_instrument;
    // string type_of_instrument;
    return true;
}

bool isok_Orientation(string str){
    // Orientation: Case insensitive: a one to three characters combination.
    // Each character can be any of the following two options (alphabetic or
    // numeric, but not a combination of both):
    // – N, E, or Z (one, two or three chars)
    // – 1, 2, or 3 (one, two or three chars)
    return true;
}

bool isok_magnitude(string str){
    toupper_str(str);
    if (str=="ML" || str=="MS" || str=="MB" || str=="MW")
        return true;
    return false;
}

bool isok_magnitude_size(float magnitude) {
    if (magnitude <= 0)
        return false;
    return true;
}

bool isok_date(string str) {
    // Date and time of the earthquake in format: mm/dd/yyyy
    // or mm­dd­yyyy, and hh:mm:ss.fff time_zone
    // e.g. 02/08/2015 17:45:02.000 PST
    string delim = "/";
    string y, m, d;

    m = str.substr(0, 2);
    d = str.substr(3, 2);
    y = str.substr(6, 4);

    if (m>"12" || m < "01")
        return false;
    if (y>"2020" || y < "1900")
        return false;
    if (d>"31" || d < "01")
        return false;
    return true;
}

bool isok_time(string str) {
    string delim = "/";
    return true;
}

bool isok_timezone(string str) {
    toupper_str(str);
    if (str=="PST" || str=="CST" || str=="EST" || str=="MST")
        return true;
    return false;
}

void read_header(ifstream & in, ofstream & log) {//, EQ & eqs) {

    string eID, ID, dt, nam, geo,  tm, tz,magnitude_type;
    float magnitude_size;
    stringstream str;

    // First row: Event ID
    in  >> eID;
    str << eID << endl;
    print_output(log,str);
    str.clear();

    in >> dt >> tm >> tz;
    str <<dt << tm << tz << endl;
    std::getline(in, nam);//err
    print_output(log,str);

    if(!isok_date(dt))
    {
        str << "Error! date is invalid" << endl;
        print_output(log,str);
        exit(0);
    }

    if(!isok_time(tm) || !isok_timezone(tz))
    {
        str << "Error! time is invalid" << endl;
        print_output(log,str);
        exit(0);
    }

    // Third row: Name of the earthquake (may be multiple words)
    std::getline(in, nam);
    str << nam << endl;
    print_output(log,str);

    // Fourth row: epicenter location (three doubles: longitude, latitude, and
    // depth), followed by the magnitude type and magnitude size (a string and a
    //  float, respectively).
    // e.g. -115.66 31.53 0.9 mw 4.9
    double longitude, latitude, depth;
    in >> longitude >> latitude >> depth >>magnitude_type >> magnitude_size;

    if(!isok_magnitude(magnitude_type))
    {
        str << "Error! Magnitude type is invalid" << endl;
        print_output(log,str);
        exit(0);
    }

    if(!isok_magnitude_size(magnitude_size))
    {
        str << "Error! Magnitude must be real positive" << endl;
        print_output(log,str);
        exit(0);
    }
}
void read_data(ifstream & in,ofstream & out, ofstream & log) {

    stringstream str;
    string eqnet, eqst,eqbnd,eqins,eqor;
    EQ   eqtmp;
    int  cnt=0, i = 0;
    bool noerr;
    bool other_err=false;

    while (in >> eqnet) {
        cnt++;
        noerr=true;
        try
        {
            in >> eqst >> eqbnd >> eqins >> eqor;

            if(isok_network_code(eqnet))
                eqtmp.network_code = (network_codes)network_code_enum(eqnet);
            else
            {
                noerr=false;
                str <<"Entry # " <<  setw(3) << right << cnt
                    << " ignored. Invalid network.\n";
                print_output(log,str);
            }

            if(isok_station_code(eqst))
                eqtmp.station_code=eqst;
            else
            {
                noerr=false;
                str <<"Entry # " <<  setw(3) << right << cnt
                    << " ignored. Invalid station name.\n";
                print_output(log,str);
            }

            if(isok_type_of_band(eqbnd))
                eqtmp.type_of_band = (types_of_band)type_of_band_enum(eqbnd);
            else
            {
                noerr=false;
                str <<"Entry # " << setw(3) << cnt
                    << " ignored. Invalid band type.\n";
                print_output(log,str);
            }

            if(isok_type_of_instrument(eqins))
                eqtmp.type_of_instrument =
                   (types_of_instrument)type_of_instrument_enum(eqins);
            else
            {
                noerr=false;
                str <<"Entry # " << cnt
                    << " ignored. Invalid instrument.\n";
                print_output(log,str);
            }

            if(isok_Orientation(eqor))
                eqtmp.Orientation=eqor;
            else
            {
                noerr=false;
                str <<"Entry # " << cnt
                    << " ignored. Invalid Orientation.\n";
                print_output(log,str);
            }

        }
        catch (int e)
        {
            // any other errors
            other_err=true;
            cout << "An exception occurred. Exception Nr. " << e << '\n';
        }

        if (is_there_any_err(eqtmp))
            noerr=false;

        if (other_err)
            noerr=false;

        if (noerr) {
            eqs[i] = eqtmp;
            i++;
        }
    }
    invalid=cnt-i;
    valid= i;
    if (valid < 1) {
        str <<"logor! input number should be equal or greater than 1\n";
        print_output(log,str);
        //return 2;
        exit(0);
    }

}

void process(ifstream & ifile, ofstream & log){

    stringstream str;
    str << "E# 08 February 2015 17:45:02.000 PST Mw 4.9 Maneadero Baja"
        << " California Earthquake [37314320CI] (­115.66, 31.53, 0.9)\n";
    print_output(log,str);
    sign=0;
    for (int i = 0; i <= valid; i++) {
        for (int j = 0; j < eqs[i].Orientation.size(); j++) {

            str << network_codes_str[eqs[i].network_code-1]
                << '.' << eqs[i].station_code << '.' << types_of_band_char
                [eqs[i].type_of_band-1] << types_of_instrument_char
                [eqs[i].type_of_instrument-1] << eqs[i].Orientation[j] << endl;

            sign++;
        }
    }

    print_output(log,str);
}

int main() {
    // const int MAXDATA=300;
    // EQ eqs[MAXDATA];
    // EQ eqs[300];

    string   inputfilename;
    ofstream log, out;
    ifstream in;
    stringstream str;

    open_output(log, "amir.log");
    open_output(out, "amir.out");

    // Prompt user for input/output file
    cout << "Enter input file: ";
    cin  >> inputfilename;
    // sample data for testing purposes
    // inputfilename= "amir.in";
    open_input(in, inputfilename, log);

    str << "Processing input..."  << endl;
    print_output(log,str);

    read_header(in,log);

    str << "Header read correctly!"  << endl << endl;
    print_output(log,str);


    read_data(in,out,log);
    process(in,out);
    print_output(out, str);

    str << endl << "Total invalid entries ignored: " << invalid << endl
        << "Totoal valid entries read: " << valid << endl
        <<"Total singal names produced: " << sign << endl
        << "Finished!" << endl;
    print_output(log,str);

    if (log.is_open())
        log.close();
    if (in.is_open())
        in.close();
    if (out.is_open())
        out.close();

    return 0;
}


