/* --------------------------------------------------------------------
EXTREME TUXRACER

Copyright (C) 2010 Extreme Tuxracer Team

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
---------------------------------------------------------------------*/

#include "spx.h"

#include <sstream>
#include <iomanip>
#include <iostream>

static char cbuffer[4096];
static string EnumStr;

void SetEnum (string s) { EnumStr = s;}

// --------------------------------------------------------------------
//					elementary string functions
// --------------------------------------------------------------------

char *NewStr (const char *s) {
    char *dest;
    dest = (char *) malloc (sizeof(char) * (strlen(s) + 1));
    if (dest == NULL) printf ("malloc failed\n");
    strcpy (dest, s);
    return dest;
}

string MakePathStr (string src, string add) {
	string res = src;
	res += SEP;
	res += add;
	return res;
}

void SInsertN (string &s, unsigned int pos, const string ins) {
	if (pos > s.size()) pos = s.size();
	s.insert (pos, ins);
}

void SDeleteN (string &s, unsigned int pos, int count) {
	if (pos > s.size()) pos = s.size();
	s.erase (pos, count);
}

int SPosN (string &s, const string find) {
	return s.find (find);
}

void STrimLeftN (string &s) {
	int i = 0;
	while (s[i] == ' ' || s[i] == '\t') i++;
	if (i > 0) SDeleteN (s, 0, i);
}

void STrimRightN (string &s) {
	int i = s.size() -1;
	while ((s[i] == ' ' || s[i] == '\t') && i >= 0) i--;
	s.erase (i+1);	
}

void STrimN (string &s) {
	STrimLeftN (s);
	STrimRightN (s);
}

// --------------------------------------------------------------------
//				conversion functions
// --------------------------------------------------------------------

void Int_StrN (string &s, const int val) {
	ostringstream os;
	os << val;
	s = os.str();
}

string Int_StrN (const int val) {
	ostringstream os;
	os << val;
	return os.str();
}

string Int_StrN (const int val, const int count) {
	ostringstream os;
	os << val;
	string s = os.str();
	while (s.size() < (unsigned int)count) SInsertN (s, 0, "0");
	return s;
}

void Float_StrN (string &s, const float val, const int count) {
	ostringstream os;
	os << setprecision(count) << fixed << val;
	s = os.str();
}

string Float_StrN (const float val, const int count) {
	ostringstream os;
	os << setprecision(count) << fixed << val;
	return os.str();
}

string Vector_StrN (const TVector3 v, const int count) {
	string res = Float_StrN (v.x, count);
	res += " " + Float_StrN (v.y, count);
	res += " " + Float_StrN (v.z, count);
	return res;
}

int Str_IntN (const string &s, const int def) {
	int val;
	istringstream is(s);
	is >> val;
	if (is.fail()) return def; else return val;
}

bool Str_BoolN (const string &s, const bool def) {
	int val;
	istringstream is(s);
	is >> val;
	if (is.fail()) return def;
	return (val != 0);
}

bool Str_BoolNX (const string &s, const bool def) {
	string decode = "[0]0[1]1[true]1[false]0";
	string valstr;
	if (def == true) valstr = SPStrN (decode, s, "1");
	else valstr = SPStrN (decode, s, "0");
	int val;
	istringstream is(valstr);
	is >> val;
	if (is.fail()) return def;
	return (val != 0);
}

float Str_FloatN (const string &s, const float def) {
	float val;
	istringstream is(s);
	is >> val;
	if (is.fail()) return def; else return val;
}

TVector2 Str_Vector2N (const string &s, const TVector2 def) {
	float x, y;
	istringstream is(s);
	is >> x >> y;
	if (is.fail()) return def;
	else return MakeVector2 (x, y);
}

TVector2 Str_Vector2N (const string &s) {
	float x, y;
	istringstream is(s);
	is >> x >> y;
	if (is.fail()) return MakeVector2 (0, 0);
	else return MakeVector2 (x, y);
}

TVector3 Str_Vector3N (const string &s, const TVector3 def) {
	float x, y, z;
	istringstream is(s);
	is >> x >> y >> z;
	if (is.fail()) return def;
	else return MakeVector (x, y, z);
}

TIndex3 Str_Index3N (const string &s, const TIndex3 def) {
	int i, j, k;
	istringstream is(s);
	is >> i >> j >> k;
	if (is.fail()) return def;
	else return MakeIndex3 (i, j, k);
}

TVector3 Str_Vector3N (const string &s) {
	float x, y, z;
	istringstream is(s);
	is >> x >> y >> z;
	if (is.fail()) return MakeVector (0, 0, 0);
	else return MakeVector (x, y, z);
}

TTuple4 MakeTuple4 (double a, double b, double c, double d) {
	TTuple4 res;
	res.a = a;
	res.b = b;
	res.c = c;
	res.d = d;
	return res;
}

TTuple4 Str_Tuple4N (const string &s) {
	float a, b, c, d;
	istringstream is(s);
	is >> a >> b >> c >> d;
	if (is.fail()) return MakeTuple4 (0, 0, 0, 0);
	else return MakeTuple4 (a, b, c, d);
}

TVector4 Str_Vector4N (const string &s, const TVector4 def) {
	float x, y, z, w;
	istringstream is(s);
	is >> x >> y >> z >> w;
	if (is.fail()) return def;
	else return MakeVector4 (x, y, z, w);
}

TColor Str_ColorN (const string &s, const TColor def) {
	float r, g, b, a;
	istringstream is(s);
	is >> r >> g >> b >> a;
	if (is.fail()) return def;
	else return MakeColor (r, g, b, a);
}

TColor3 Str_Color3N (const string &s, const TColor3 def) {
	float r, g, b;
	istringstream is(s);
	is >> r >> g >> b;
	if (is.fail()) return def;
	else return MakeColor3 (r, g, b);
}

void Str_ArrN (const string &s, float *arr, int count, float def) {
	istringstream is(s);
	switch (count) {
		case 1: is >> arr[0]; break;
		case 2: is >> arr[0] >> arr[1]; break;
		case 3: is >> arr[0] >> arr[1] >> arr[2]; break;
		case 4: is >> arr[0] >> arr[1] >> arr[2] >> arr[3]; break;
		default: break;
	}
	if (is.fail()) for (int i=0; i<count; i++) arr[i] = def;
}

string Bool_StrN (const bool val) {
	if (val == true) return "true"; else return "false";
}

// --------------------------------------------------------------------
//				SP functions for parsing lines
// --------------------------------------------------------------------

string SPItemN (string &s, const string &tag) {
	int i = 0;
	unsigned int ii = 0;
	string item = "";
	if (s.size() == 0 || tag.size() == 0) return item;

	string tg = "[" + tag + "]";
	i = SPosN (s, tg);
	if (i < 0) return item;
	ii = i + tg.size();
	while (s[ii] != '[' && s[ii] != '#' && ii < s.size()) {
		item += s[ii];
		ii++;
	}
 	return item;
}

void SPItemN (string &s, const string &tag, string &item) {
	int i = 0;
	unsigned int ii = 0;

	item = "";
	if (s.size() == 0 || tag.size() == 0) return;

	string tg = "[" + tag + "]";
	i = SPosN (s, tg);
	if (i < 0) return;
	ii = i + tg.size();
	while (s[ii] != '[' && s[ii] != '#' && ii < s.size()) {
		item += s[ii];
		ii++;
	}
}

string SPStrN (string &s, const string &tag, const string def) {
	string item = SPItemN (s, tag);
	if (item.size() < 1) return def;
	STrimN (item);
	return item;
}

int SPIntN (string &s, const string &tag, const int def) {
	return (Str_IntN (SPItemN (s, tag), def));
}

int SPEnumN (string &s, const string &tag, int def) {
	string item = SPItemN (s, tag);	
	STrimN (item);
	if (item.size() < 1) return def;
	return SPIntN (EnumStr, item, def);;
}

bool SPBoolN (string &s, const string &tag, const bool def) {
	return (Str_BoolN (SPItemN (s, tag), def));
}

bool SPBoolNX (string &s, const string &tag, const bool def) {
	string item = SPItemN (s, tag);
	STrimN (item);
	return Str_BoolNX (item, def);
}

float SPFloatN (string &s, const string &tag, const float def) {
	return (Str_FloatN (SPItemN (s, tag), def));
}

TVector2 SPVector2N (string &s, const string &tag, const TVector2 def) {
	return (Str_Vector2N (SPItemN (s, tag), def));
}

TVector2 SPVector2N (string &s, const string &tag) {
	return (Str_Vector2N (SPItemN (s, tag)));
}

TVector3 SPVector3N (string &s, const string &tag, const TVector3 def) {
	return (Str_Vector3N (SPItemN (s, tag), def));
}

TIndex3 SPIndex3N (string &s, const string &tag, const TIndex3 def) {
	return (Str_Index3N (SPItemN (s, tag), def));
}

TVector3 SPVector3N (string &s, const string &tag) {
	return (Str_Vector3N (SPItemN (s, tag)));
}

TTuple4 SPTuple4N (string &s, const string &tag) {
	return (Str_Tuple4N (SPItemN (s, tag)));
}

TVector4 SPVector4N (string &s, const string &tag, const TVector4 def) {
	return (Str_Vector4N (SPItemN (s, tag), def));
}

TColor SPColorN (string &s, const string &tag, const TColor def) {
	return (Str_ColorN (SPItemN (s, tag), def));
}

TColor3 SPColor3N (string &s, const string &tag, const TColor3 def) {
	return (Str_Color3N (SPItemN (s, tag), def));
}

void SPArrN (string &s, const string &tag, float *arr, int count, float def) {
	Str_ArrN (SPItemN (s, tag), arr, count, def);
}

bool SPExistsN  (string &s, const string &tag) {
	string tg = "[" + tag + "]";
	int i = SPosN (s, tg);
	if (i < 0) return false;
	return true;
}

int SPPosN (string &s, const string &tag) {
	string tg = "[" + tag + "]";
	return SPosN (s, tg);
}

// --------------------------------------------------------------------
// 			compatibility
// --------------------------------------------------------------------

void SInsertO (char *s, int pos, const char *str) {
	char buff[5012];
	int lng = strlen (s);
	if (pos > lng) pos = lng;
	if (pos == lng) {
		strcat (s, str);	
	} else {
		memmove (buff, s+pos, lng-pos+1);
		s[pos] = '\0';
		strcat (s, str);
		strcat (s, buff);
	}
}

void Int_CharN (char *s, const int val) {
	sprintf (s, "%i", val);
}

void Int_CharN (char *s, const int val, const int cnt) {
	sprintf (s, "%i", val);
	while (strlen (s) < (unsigned int)cnt) SInsertO (s, 0, "0");
}

char *NewStrN (const char *s) {
    char *dest;
    dest = (char *) malloc (sizeof(char) * (strlen(s) + 1));
    if (dest == 0) Message ("malloc failed","");
    strcpy (dest, s);
    return dest;
}

void SPCharN (string &s, const string &tag, char *result) {
	string item = SPItemN (s, tag);
	if (item.size() < 1) return;
	STrimN (item);
	strcpy (result, item.c_str());
}

char *SPNewCharN (string &s, const string &tag) {
	string item = SPItemN (s, tag);
	if (item.size() < 1) return 0;
	STrimN (item);
	return NewStrN (item.c_str());
}

// ------------------ add ---------------------------------------------

void SPAddIntN (string &s, const string &tag, const int val) {
	s += "[";
	s += tag;
	s += "]";
	s += Int_StrN (val);
}

void SPAddFloatN (string &s, const string &tag, const float val, int count) {
	s += "[";
	s += tag;
	s += "]";
	s += Float_StrN (val, count);
}

void SPAddStrN (string &s, const string &tag, const string &val) {
	s += "[";
	s += tag;
	s += "]";
	s += val;
}

void SPAddVec2N (string &s, const string &tag, const TVector2 val, int count) {
	s += "[";
	s += tag;
	s += "]";
	s += ' ';
	s += Float_StrN (val.x, count);
	s += " ";
	s += Float_StrN (val.y, count);
}

void SPAddVec3N (string &s, const string &tag, const TVector3 val, int count) {
	s += "[";
	s += tag;
	s += "]";
	s += ' ';
	s += Float_StrN (val.x, count);
	s += " ";
	s += Float_StrN (val.y, count);
	s += " ";
	s += Float_StrN (val.z, count);
}

void SPAddIndx3N  (string &s, const string &tag, const TIndex3 val) {
	s += "[";
	s += tag;
	s += "]";
	s += ' ';
	s += Int_StrN (val.i);
	s += ' ';
	s += Int_StrN (val.j);
	s += ' ';
	s += Int_StrN (val.k);
}

void SPAddIndx4N  (string &s, const string &tag, const TIndex4 val) {
	s += '[';
	s += tag;
	s += ']';
	s += ' ';
	s += Int_StrN (val.i);
	s += ' ';
	s += Int_StrN (val.j);
	s += ' ';
	s += Int_StrN (val.k);
	s += ' ';
	s += Int_StrN (val.l);
}

void SPAddBoolN (string &s, const string &tag, const bool val) {
	s += '[';
	s += tag;
	s += ']';
	if (val == true) s += "true"; else s+= "false";
}

// --------------------------------------------------------------------

void SPSetIntN (string &s, const string &tag, const int val) {
	int pos = SPPosN (s, tag);
	if (pos >= 0) {
		int ipos = pos + tag.size() + 2;
		string item = SPItemN (s, tag);
		if (item.size() > 0) SDeleteN (s, ipos, item.size()); 
		SInsertN (s, ipos, Int_StrN (val));
	} else SPAddIntN (s, tag, val);
}

void SPSetFloatN (string &s, const string &tag, const float val, int count) {
	int pos = SPPosN (s, tag);
	if (pos >= 0) {
		int ipos = pos + tag.size() + 2;
		string item = SPItemN (s, tag);
		if (item.size() > 0) SDeleteN (s, ipos, item.size()); 
		SInsertN (s, ipos, Float_StrN (val, count));
	} else SPAddFloatN (s, tag, val, count);
}

void SPSetStrN (string &s, const string &tag, const string &val) {
	int pos = SPPosN (s, tag);
	if (pos >= 0) {
		int ipos = pos + tag.size() + 2;
		string item = SPItemN (s, tag);
		if (item.size() > 0) SDeleteN (s, ipos, item.size()); 
		SInsertN (s, ipos, val);
	} else SPAddStrN (s, tag, val);
}

// --------------------------------------------------------------------
//					class CSPList
// --------------------------------------------------------------------


CSPList::CSPList (int maxlines) {
	fmax = maxlines;
	flines = new string [maxlines];
	fflag = new int [maxlines];
	fcount = 0;
	fnewlineflag = 0;
}

CSPList::CSPList (int maxlines, int newlineflag) {
	fmax = maxlines;
	flines = new string [maxlines];
	fflag = new int [maxlines];
	fcount = 0;
	fnewlineflag = newlineflag;
}

CSPList::~CSPList () {
	if (flines != 0) delete []flines;
	delete []fflag;
}

string CSPList::Line (int idx) {
	if (idx < 0 || idx >= fcount) return "";
	return flines[idx];
}

const char *CSPList::LineC (int idx) {
	if (idx < 0 || idx >= fcount) return "";
	return flines[idx].c_str();
}

int CSPList::Count () { return fcount; }

void CSPList::Clear () { 
	fcount = 0; 
}

void CSPList::Add (string line) {
	if (fcount < fmax) {
		flines[fcount] = line; 	
		fcount++;
	}
}

void CSPList::Add (string line, int flag) {
	if (fcount < fmax) {
		flines[fcount] = line; 	
		fflag[fcount] = flag;
		fcount++;
	}
}

void CSPList::Append (string line, int idx) {
	if (idx < 0 || idx >= fcount) return;
	flines[idx] += line;
}

void CSPList::SetFlag (int idx, int flag) {
	if (idx < 0 || idx >= fcount) return;
	fflag[idx] = flag;
}

int CSPList::Flag (int idx) {
	if (idx < 0 || idx >= fcount) return 0;
	return fflag[idx];
}

void CSPList::Print () {
	for (int i=0; i<fcount; i++) cout << flines[i] << endl;
}

char lastchar (const string s) {
	return s[s.length()-1];
}

bool CSPList::Load (const string &filepath) {
	FILE *tempfile;
	string line;
	bool valid;
	bool fwdflag;

	bool backflag = false;
	tempfile = fopen (filepath.c_str(), "r");
	if (tempfile == 0) {
		Message ("CSPList::Load - unable to open","");
		return false;
	} else {
	    while (fgets (cbuffer, 4000, tempfile)) {
			line = cbuffer;
			STrimN (line);

			// delete new line char if in string
			int npos = line.rfind ('\n');
			if (npos >= 0) SDeleteN (line, npos, 1);

			valid = true;
			if (line.size() < 1) valid = false;	// empty line
			if (line[0] == '#') valid = false;	// comment line
			
			if (valid) {
				if (fcount < fmax) {
					if (fnewlineflag == 0) {
						if (cbuffer[0] == '*' || fcount < 1) Add (line);
						else Append (line, fcount-1);
					} else if (fnewlineflag == 1) {
						if (lastchar (line) == '\\') {
							SDeleteN (line, line.length()-1, 1);
							fwdflag = true;
						} else {
							fwdflag = false;
						}

						if (backflag == false) Add (line);
						else Append (line, fcount-1);

						backflag = fwdflag;
					}
				} else {
					Message ("CSPList::Load - not enough lines","");
					return false;
				}
			}
    	}
		fclose (tempfile); 
		return true;
	}
}

bool CSPList::Load (string dir, string filename) {
	return Load (dir + SEP + filename);
}

bool CSPList::Save (const string &filepath) {
	FILE *tempfile;
	string line;

	tempfile = fopen (filepath.c_str(), "w");
	if (tempfile == 0) {
		Message ("CSPList::Save - unable to open","");
		return false;
	} else {
		for (int i=0; i<fcount; i++) {
			line = flines[i] + '\n';
			fputs (line.c_str(), tempfile);
		}
		fclose (tempfile);
		return true;
	}
}

bool CSPList::Save (string dir, string filename) {
	return Save (dir + SEP + filename);
}

void CSPList::MakeIndex (string &index, const string &tag) {
	index = "";
	string item;
	int idx = 0;

	for (int i=0; i<fcount; i++) {
		item = SPItemN (flines[i], tag);
		STrimN (item);
		if (item.size() > 0) {
			index += "[";
			index += item;			
			index += "]";
			index += Int_StrN (idx);
			idx++;
		}
	}
}


