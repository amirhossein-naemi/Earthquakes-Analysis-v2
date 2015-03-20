//---------------------------------------------------------------------------
//
// Earthquakes' Events Analysis
// By Amirhossein Naemi
// March, 2015
// GIT: https://github.com/amirhossein-naemi/Earthquakes-Analysis-v2
// This program reads in one integer from a amir.in file and returns the
//
//---------------------------------------------------------------------------

#ifndef STATION_H
#define STATION_H

#include "earthquake.h"
#include <string>

// – Long­_period  (L)
// – Short_­period (B)
// – Broadband    (H)
// Case Insensitive
enum types_of_band {
    Long_period  = 1,
    Short_period = 2,
    Broadband    = 3
};

// Case Insensitive
enum types_of_instrument {
    High_Gain=1,
    Low_Gain,
    Accelerometer
};


// Case Sensitive
enum network_codes {
    CE=1,
    CI,
    FA,
    N,
    NP,
    WR
};

// not needed
enum Orientation {
	NN, E, Z
};

// Following a valid header, the input file has an indefinite number of entries,
// one per row, but no more than 300 (this limit is important, as you are
// supposed to crete an array to store the input entries). Each entry in the
// table is composed of the following:
struct station {
	network_codes network_code;
	string station_name;
	types_of_band type_of_band;
	types_of_instrument type_of_instrument;
	string Orientation;
};


inline void toupper_str(std::string& str);

int network_code_enum(string str_net_code);

string toupper_str_C(std::string str);

int type_of_instrument_enum(string str_type_of_inst);

int type_of_band_enum(string str_type_of_band);

string type_of_inst_string(types_of_instrument type_of_inst);

#endif