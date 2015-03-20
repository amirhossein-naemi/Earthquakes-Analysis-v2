//---------------------------------------------------------------------------
//
// Earthquakes' Events Analysis
// By Amirhossein Naemi
// March, 2015
// GIT: https://github.com/amirhossein-naemi/Earthquakes-Analysis-v2
// This program reads in one integer from a amir.in file and returns the
//
//---------------------------------------------------------------------------

#include "earthquake.h"
#include "station.h"
#include <ctime>
#include <time.h>
#include <sys/timeb.h>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

earthquake EQ = {};

const int MAXDATA = 300;
station stations[MAXDATA];

int valid, invalid, sign;

string types_of_band_str[3]       = { "Longperiod", "Shortperiod","Broadband" };
char types_of_band_char[3]        = { 'L', 'B', 'H' };
string types_of_instrument_str[3] = { "High_Gain", "Low_Gain",
"Accelerometer" };
char types_of_instrument_char[3]  = { 'H', 'L', 'N' };
string network_codes_str[5]       = { "CE", "CI", "FA", "NP", "WR" };

void toupper_str(std::string& str) {

    for (size_t i = 0; i < str.size(); ++i)
        str[i] = toupper(str[i]);
}

string toupper_str_C(std::string str) {
    toupper_str(str);
    return str;
}

std::vector<std::string> &split(const std::string &s, char delim,
    std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void print(ofstream & o, stringstream & txt, bool only2file = false) {
    std::cout.precision(3);
    o.precision(3);
    if (!only2file) cout << txt.str();
    o << txt.str();
    txt.str(std::string());
    txt.clear();
}

void open_input(ifstream & ifile, string ifilename, ofstream & log) {
    // Sanity check on the file stream

    ifile.open(ifilename.c_str());
    if (!ifile.is_open()) {
        stringstream str;
        str << "Error! Cannot open input file: " << ifilename << endl;
        print(log, str);
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

// check for rest of the errors
bool is_there_any_err(station st) {

    if (st.network_code <1 || st.network_code >5)
        return true;

    return false;
}

bool isok_network_code(string str){
    // Network code: Case sensitive: 2 characters. Must be in capital letters to
    // be valid. It can be any of the following:
    // network_code network_code;
    // string network_code;
    // char network_code;
    if (str.size() == 2)
    {
        for (int i = 0; i < 2; i++)
        {
            if (!isalpha(str[i]))
                return false;
            if (!isupper(str[i]))
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
    // Case Sensitive : Must be either 3 alphabetic characters in
    // capital letters, or 5 numeric characters to be valid.string ssn;
    if (str.size() == 3)
    {
        for (int i = 0; i < 3; i++)
        {
            if (!isalpha(str[i]))
                return false;
            if (!isupper(str[i]))
                return false;
        }

        // if return true, means everything is fine
        return true;
    }

    if (str.size() == 5)
    {
        for (int i = 0; i < 5; i++)
        if (!isdigit(str[i]))
        {
            // there is an error
            return false;
        }

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
    types_of_band t = (types_of_band)type_of_band_enum(str);
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
    // N, E, or Z (one, two or three chars)
    // 1, 2, or 3 (one, two or three chars)

    toupper_str(str);
    size_t n = str.size();
    if (!isdigit(str[0]))
    {
        for (int i = 0; i < n; i++)
        {
            if (!(str[i] == 'N' || str[i] == 'E' || str[i] == 'Z'))
                return false; // there is an error
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (!(str[i] == '1' || str[i] == '2' || str[i] == '3'))
                return false; // there is an error
        }
    }

    return true;
}

bool isok_magnitude(string str){
    toupper_str(str);
    if (str == "ML" || str == "MS" || str == "MB" || str == "MW")
        return true;
    return false;
}

bool isok_magnitude_size(float magnitude) {
    if (magnitude <= 0)
    return false;
    return true;
}

bool isok_date() {

    if (EQ.yr > 2100 || EQ.yr<1900)
        return false;

    if (EQ.day>31 || EQ.day < 1)
        return false;

    return true;

}

bool isok_time(string str) {
    string delim = "/";
    return true;
}

bool isok_timezone(string str) {
    toupper_str(str);
    if (str == "PST" || str == "CST" || str == "EST" || str == "MST")
        return true;
    return false;
}

void parse_dt(string str2, ofstream & log)
{

    string dt, tm, tz;
    string year, mnth, day, hour, min, sec, ms;

    char str[50];
    strncpy(str, str2.c_str(), sizeof(str));
    str[sizeof(str)-1] = 0;

    replace(str, str + strlen(str), '/', ' ');
    replace(str, str + strlen(str), ':', ' ');

    std::vector<std::string> aln = split(str2, ' ');
    std::vector<std::string> adt = split(aln[0], '/');
    std::vector<std::string> atm = split(aln[1], ':');
    std::vector<std::string> asc = split(atm[2], '.');

    day  = adt[1];
    year = adt[2];
    hour = atm[0];
    min  = atm[1];
    sec  = asc[0];
    ms   = asc[1];
    tz   = aln[2];

    EQ.month = mnth_str2enum(adt[0]);
    EQ.day   = str2int(day);
    EQ.yr    = str2int(year);
    EQ.hr    = str2int(hour);
    EQ.min   = str2int(min);
    EQ.sec   = str2int(sec);
    EQ.ms    = str2int(ms);
    EQ.tz    = tz;

    stringstream stro;
    if (!isok_date())
    {
        stro << "Error! date is invalid" << endl;
        print(log, stro);
        exit(0);
    }

    if (!isok_time(aln[1]) || !isok_timezone(tz))
    {
        stro << "Error! time is invalid" << endl;
        print(log, stro);
        exit(0);
    }
}

void parse_mag(string lm, ofstream & log){
    
    // Fourth row: epicenter location (three doubles: longitude, latitude, and
    // depth), followed by the magnitude type and magnitude size (a string and a
    // float, respectively). e.g. -115.66 31.53 0.9 mw 4.9

    char* pEnd;
    stringstream str;
    string longitude, latitude, elevation, geo, magnitude_type, magnitude_size;
    float fmagnitude_size;
    
    //istringstream is not standard/not compatible with mingw
    
    std::vector<std::string> astr = split(lm, ' ');
    
    longitude      = astr[0];
    latitude       = astr[1];
    elevation      = astr[2];
    magnitude_type = astr[3];
    magnitude_size = astr[4];

    char cmagnitude_size[50];
    strcpy(cmagnitude_size, magnitude_size.c_str());

    fmagnitude_size = std::strtod(cmagnitude_size, &pEnd);
    if (!isok_magnitude(magnitude_type))
    {
        str << "Error! Magnitude type is invalid" << endl;
        print(log, str);
        exit(0);
    }

    EQ.magnitude = fmagnitude_size;
    char clongitude[10], clatitude[10], celevation[10];

    strcpy(celevation, elevation.c_str());
    strcpy(clatitude, latitude.c_str());
    strcpy(celevation, elevation.c_str());

    EQ.lon = std::strtod(clongitude, &pEnd);
    EQ.lat = std::strtod(clatitude, &pEnd);
    EQ.elv = std::strtod(celevation, &pEnd);

    if (!isok_magnitude_size(fmagnitude_size))
    {
        str << "Error! Magnitude must be real positive" << endl;
        print(log, str);
        exit(0);
    }
}

void read_header(ifstream & in, ofstream & log) {

    string lID, ldt, lnam, lm, eID, ID, dt, nam, geo, tm, tz, magnitude_type;
    stringstream str;

    std::getline(in, lID);
    std::getline(in, ldt);
    std::getline(in, lnam);
    std::getline(in, lm);

    parse_dt(ldt, log);
    parse_mag(lm, log);

    // First row: Event ID
    str << eID << endl;
    print(log, str);
    str.clear();

    EQ.earthquake_name = lnam;
    EQ.id = lID;

    // Third row: Name of the earthquake (may be multiple words)
    str << lnam << endl;
    print(log, str, true);

}


void read_data(ifstream & in, ofstream & out, ofstream & log) {

    stringstream str;
    string eqnet, eqst, eqbnd, eqins, eqor;
    station   eqtmp;
    int  cnt = 0, i = 0;
    bool noerr;
    bool other_err = false;

    while (in >> eqnet) {
        cnt++;
        noerr = true;
        try
        {
            in >> eqst >> eqbnd >> eqins >> eqor;

            if (isok_network_code(eqnet))
                eqtmp.network_code = (network_codes)network_code_enum(eqnet);
            else
            {
                noerr = false;
                str << "Entry # " << setw(3) << right << cnt
                    << " ignored. Invalid network.\n";
                print(log, str);
            }

            if (isok_station_code(eqst))
                eqtmp.station_name = eqst;
            else
            {
                noerr = false;
                str << "Entry # " << setw(3) << right << cnt
                    << " ignored. Invalid station name.\n";
                print(log, str);
            }

            if (isok_type_of_band(eqbnd))
                eqtmp.type_of_band = (types_of_band)type_of_band_enum(eqbnd);
            else
            {
                noerr = false;
                str << "Entry # " << setw(3) << cnt
                    << " ignored. Invalid band type.\n";
                print(log, str);
            }

            if (isok_type_of_instrument(eqins))
                eqtmp.type_of_instrument =
                (types_of_instrument)type_of_instrument_enum(eqins);
            else
            {
                noerr = false;
                str << "Entry # " << setw(3) << cnt
                    << " ignored. Invalid instrument.\n";
                print(log, str);
            }

            if (isok_Orientation(eqor))
                eqtmp.Orientation = eqor;
            else
            {
                noerr = false;
                str << "Entry # " << setw(3) << cnt
                    << " ignored. Invalid Orientation.\n";
                print(log, str);
            }

        }
        catch (int e)
        {
            // any other errors
            other_err = true;
            cout << "An exception occurred. Exception Nr. " << e << '\n';
        }

        if (is_there_any_err(eqtmp))
            noerr = false;

        if (other_err)
            noerr = false;

        if (noerr) {


            stations[i] = eqtmp;
            i++;
        }
    }
    invalid = cnt - i;
    valid = i;
    if (valid < 1) {
        str << "logor! input number should be equal or greater than 1\n";
        print(log, str);
        //return 2;
        exit(0);
    }

}

void process(ifstream & ifile, ofstream & log){

    stringstream str, str2;
    str.precision(3);
    str << "# " << EQ.day << " " << mnth_enum2str(EQ.month) << " " << EQ.yr
        << " " << EQ.hr << ":" << EQ.min << ":" << EQ.sec << ":"
        << std::setprecision(3) << EQ.ms << " " << EQ.tz << " "
        << EQ.magnitude_Type << " " << EQ.magnitude << " "
        << EQ.earthquake_name << " [" << EQ.id << "] ("
        << EQ.lon << ", " << EQ.lat << ", " << EQ.elv << ")" << endl;

    sign = 0;
    for (int i = 0; i <= valid; i++) {
        for (size_t j = 0; j < stations[i].Orientation.size(); j++) {

            str2 << EQ.id << '.'
                << network_codes_str[stations[i].network_code - 1]
                << '.' << stations[i].station_name << '.'
                << types_of_band_char[stations[i].type_of_band - 1]
                << types_of_instrument_char[stations[i].type_of_instrument - 1]
                << stations[i].Orientation[j] << endl;

            sign++;
        }
    }

    str << sign << endl;

    print(log, str, true);

    print(log, str2, true);
}

int main() {

    string       inputfilename;
    ofstream     log, out;
    ifstream     in;
    stringstream str;

    open_output(log, "amir.log");
    open_output(out, "amir.out");

    // Prompt user for input/output file
    cout << "Enter input file: ";
    cin >> inputfilename;

    // sample data for testing purposes
    // inputfilename = "amir.in";

    str << endl << "Opening file: " << inputfilename << endl;
    open_input(in, inputfilename, log);

    str << "Processing input..." << endl;
    print(log, str);

    read_header(in, log);

    str << "Header read correctly!" << endl << endl;
    print(log, str);


    read_data(in, out, log);
    process(in, out);
    print(out, str);

    str << endl << "Total invalid entries ignored: " << invalid << endl
        << "Totoal valid entries read: "   << valid << endl
        << "Total singal names produced: " << sign << endl;
    print(log, str);

    if (log.is_open())
        log.close();
    if (in.is_open())
        in.close();
    if (out.is_open())
        out.close();

    return 0;
}


