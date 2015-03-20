//---------------------------------------------------------------------------
//
// Earthquakes' Events Analysis
// By Amirhossein Naemi
// March, 2015
// GIT: https://github.com/amirhossein-naemi/Earthquakes-Analysis-v2
// This program reads in one integer from a amir.in file and returns the
//
//---------------------------------------------------------------------------

#include "station.h"




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

int network_code_enum(string str_net_code) {
	// Case Sensitive
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


int type_of_band_enum(string str_type_of_band) {

	str_type_of_band = toupper_str_C(str_type_of_band);
	toupper_str(str_type_of_band);

	if (str_type_of_band == "LONG-PERIOD")
		return 1;
	if (str_type_of_band == "SHORT-PERIOD")
		return 2;
	if (str_type_of_band == "BROADBAND")
		return 3;
	return -1;
}

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
