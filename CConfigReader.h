#ifndef __CONF_H__
#define __CONF_H__

#include <map>
#include <string>
class CConfigReader {
public:
	CConfigReader(const char* filename);
	~CConfigReader();

	char* getConfigName(const char* name);
	int setConfigValue(const char* name, const char* value);
private:
	void LoadFile(const char* filename);
	int writeFile(const char* filename = NULL);
	void parseLine(char* line);
	char* trimSpace(char* name);
private:
	bool								m_load_ok;
	std::map<std::string, std::string>	m_config_map;
	std::string							m_config_file;

};

#endif // !__CCONFIG_H__

