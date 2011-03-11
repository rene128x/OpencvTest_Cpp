#ifndef CONFIGPARSER_H_
#define CONFIGPARSER_H_

#include <map>
#include <string>
using namespace std;

class ConfigParser {
public:
	ConfigParser(const string &configFile);

	int getProperty(const string &name);
	bool getFlag(const string &name);
	string getText(const string &name);

	void setProperty(const string &name, int val);
	void setFlag(const string &name, bool val);
	void setText(const string &name, const string &val);

	void save();
	void save(const string &path);

private:
	map<string, bool> flags;
	map<string, int> properties;
	map<string, string> texts;
	string defaultPath;
};

#endif /* CONFIGPARSER_H_ */
