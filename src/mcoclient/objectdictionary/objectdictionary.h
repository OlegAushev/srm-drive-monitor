#pragma once


#include "../mcodef.h"
#include <QString>
#include <map>


namespace microcanopen {

extern const std::map<ODEntryKey, ODEntryValue> OBJECT_DICTIONARY;

inline ODEntryKey findODEntry(const QString& name)
{
	auto entryIt = find_if(OBJECT_DICTIONARY.begin(), OBJECT_DICTIONARY.end(),
		[name](const auto& entry)
		{
			return entry.second.name == name;
		});
	if (entryIt == OBJECT_DICTIONARY.end())
	{
		return {0xFFFF, 0xFF};
	}
	return entryIt->first;
}



}


