#include "../lib/ConfigParser.h"

#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

void trim(string& str) {
	string::size_type pos = str.find_last_not_of(' ');
	if (pos != string::npos) {
		str.erase(pos + 1);
		pos = str.find_first_not_of(' ');
		if (pos != string::npos)
			str.erase(0, pos);
	} else
		str.erase(str.begin(), str.end());
}

ConfigParser::ConfigParser(const string &configFile) {
	defaultPath = configFile;
	ifstream entrada(configFile.c_str());
	stringstream ss(stringstream::in | stringstream::out);
	string s;
	while (getline(entrada, s)) {
		trim(s);

		if (s.length() == 0 || s[0] == '#')
			continue;

		string::size_type pos = s.find('=');
		if (pos == string::npos) {
			flags[s] = true;
		} else {
			ss.clear();
			string a = s.substr(0, pos);
			string b = s.substr(pos + 1);
			trim(a);
			trim(b);

			if (b.at(0) == '\"' || b.at(0) == '\'') {
				texts[a] = b.substr(1, b.length() - 2);
			} else {
				ss << b;
				ss >> properties[a];
			}
		}
	}

	entrada.close();
}

int ConfigParser::getProperty(const string &name) {
	return properties[name];
}
bool ConfigParser::getFlag(const string &name) {
	return flags[name];
}
string ConfigParser::getText(const string &name) {
	return texts[name];
}

void ConfigParser::setProperty(const string &name, int val) {
	properties[name] = val;
}
void ConfigParser::setFlag(const string &name, bool val) {
	flags[name] = val;
}
void ConfigParser::setText(const string &name, const string &val) {
	texts[name] = val;
}

void ConfigParser::save() {
	save(defaultPath);
}

void ConfigParser::save(const string &path) {
	ofstream salida(path.c_str());
	map<string, bool>::iterator p;
	map<string, int>::iterator q;
	map<string, string>::iterator r;

	for (p = flags.begin(); p != flags.end(); p++)
		salida << p->first << endl;
	salida << endl;
	for (q = properties.begin(); q != properties.end(); q++)
		salida << q->first << " = " << q->second << endl;
	salida << endl;
	for (r = texts.begin(); r != texts.end(); r++)
		salida << r->first << " = \"" << r->second << "\"" << endl;

	salida.close();
}
