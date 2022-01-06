#include "Func.h"

bool ContainsString(const wchar_t* source, const wchar_t* target)
{
	while (*source != '\0')
	{
		if (*source++ != *target++) 
		{
			break;
		}
	}

	return *source == '\0';
}
