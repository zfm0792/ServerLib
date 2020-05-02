#include "CConfigReader.h"

#include <stdio.h>
#include <string.h>

CConfigReader::CConfigReader(const char* filename)
{
	LoadFile(filename);
}

CConfigReader::~CConfigReader()
{
}

char* CConfigReader::getConfigName(const char* name)
{
	if (!m_load_ok)
		return NULL;

	char* value = NULL;
	std::map<std::string, std::string>::iterator it = m_config_map.find(name);
	if (it != m_config_map.end())
		value = (char*)it->second.c_str();

	return value;
}

int CConfigReader::setConfigValue(const char* name, const char* value)
{
	if (!m_load_ok)
		return -1;
	
	std::map<std::string, std::string>::iterator it = m_config_map.find(name);

	if (it != m_config_map.end())
		it->second = value;
	else
	{
		m_config_map.insert(std::make_pair(name, value));
	}
	return writeFile();
}

void CConfigReader::LoadFile(const char* filename)
{
	m_config_file.clear();
	m_config_file.append(filename);
	FILE* fp = fopen(filename, "r");
	if (!fp)
		return;

	char buf[256];
	for (;;)
	{
		//每次读取一行
		char* p = fgets(buf, 256, fp);
		if (!p)
			break;

		size_t len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = 0;

		char* ch = strchr(buf, '#');
		if (ch) // 找到了#  注释信息   
			*ch = 0;

		if (strlen(buf) == 0)
			continue;

		parseLine(buf);
	}
	fclose(fp);
	m_load_ok = true;
}

int CConfigReader::writeFile(const char* filename)
{
	FILE* fp = NULL;
	if (filename == NULL)
		fp = fopen(m_config_file.c_str(), "w");
	else
		fp = fopen(filename, "w");

	if (fp == NULL)
		return -1;

	char szParire[128];
	auto it = m_config_map.begin();

	for (;it != m_config_map.end();it++)
	{
		memset(szParire, 0, sizeof(szParire));
		snprintf(szParire, sizeof(szParire), "%s=%s\n", it->first.c_str(), it->second.c_str());
		size_t ret = fwrite(szParire, strlen(szParire), 1, fp);
		if (ret != 1)
		{
			fclose(fp);
			return -1;
		}
	}
	fclose(fp);
	return 0;
}

void CConfigReader::parseLine(char* line)
{
	//[aaaa] ==== 默认已经处理掉了  没有找到 "=" 号
	char* p = strchr(line, '=');
	if (p == NULL)
		return ;

	*p = 0;
	char* key = trimSpace(line);
	char* value = trimSpace(p+1);

	if (key && value)
	{
		m_config_map.insert(std::make_pair(key, value));
	}

}

char* CConfigReader::trimSpace(char* name)
{
	char* start_pos = name;

	while ((*start_pos == ' ') || (*start_pos == '\t') || (*start_pos == '\r'))
		start_pos++;

	if (strlen(start_pos) == 0)
		return NULL;

	char* end_pos = name + strlen(name) - 1;

	while ((*end_pos == ' ') || (*end_pos == '\t') || (*end_pos == '\r'))
	{
		*end_pos = 0;
		end_pos--;
	}

	int len = (int)(end_pos - start_pos) + 1;

	if (len <= 0)
		return NULL;
	
	return start_pos;
}
