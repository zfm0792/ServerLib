#ifndef __TINY_STRING_UTIL_H__
#define __TINY_STRING_UTIL_H__

class TinyStringUtils 
{
private:
	TinyStringUtils() = delete;
	~TinyStringUtils() = delete;
	TinyStringUtils(const TinyStringUtils& rhs) = delete;
	TinyStringUtils& operator=(const TinyStringUtils& rhs) = delete;

public:
	static void trimLeft(char* string);
	static void trimRight(char* string);
	static void trim(char* string);
};

#endif // !__TINY_STRING_UTIL_H__

