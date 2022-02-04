#pragma once


#include <cstddef>
#include <cstdint>
#include <cstring>
#include <QString>


namespace microcanopen {


class NodeId
{
public:
	const unsigned int value;
	explicit NodeId(unsigned int _value) : value(_value) {}
};


enum class NmtState
{
	INITIALIZING = 0x00,
	STOPPED = 0x04,
	OPERATIONAL = 0x05,
	PRE_OPERATIONAL = 0x7F
};


enum class CobType
{
	NMT,
	SYNC,
	EMCY,
	TIME,
	TPDO1,
	RPDO1,
	TPDO2,
	RPDO2,
	TPDO3,
	RPDO3,
	TPDO4,
	RPDO4,
	TSDO,
	RSDO,
	HEARTBEAT
};


const size_t COB_TYPE_COUNT = 15;


const unsigned int cobFunctionCode[COB_TYPE_COUNT] = {
	0x000,	// NMT
	0x080,	// SYNC
	0x080,	// EMCY
	0x100,	// TIME
	0x180,	// TPDO1
	0x200,	// RPDO1
	0x280,	// TPDO2
	0x300,	// RPDO2
	0x380,	// TPDO3
	0x400,	// RPDO3
	0x480,	// TPDO4
	0x500,	// RPDO4
	0x580,	// TSDO
	0x600,	// RSDO
	0x700	// HEARTBEAT
};


inline unsigned int cobId(CobType cobType, unsigned int nodeId)
{
	if ((cobType == CobType::NMT) || (cobType == CobType::SYNC) || (cobType == CobType::TIME))
	{
		return cobFunctionCode[static_cast<size_t>(cobType)];
	}
	return cobFunctionCode[static_cast<size_t>(cobType)] + nodeId;
}


const unsigned int cobDataLen[COB_TYPE_COUNT] = {
	2,	// NMT
	0,	// SYNC
	2,	// EMCY
	6,	// TIME
	8,	// TPDO1
	8,	// RPDO1
	8,	// TPDO2
	8,	// RPDO2
	8,	// TPDO3
	8,	// RPDO3
	8,	// TPDO4
	8,	// RPDO4
	8,	// TSDO
	8,	// RSDO
	1	// HEARTBEAT
};


enum class TpdoNum {NUM1, NUM2, NUM3, NUM4};
enum class RpdoNum {NUM1, NUM2, NUM3, NUM4};


class CobSdoData
{
private:
	uint32_t m_data = 0;
public:
	CobSdoData() = default;
	CobSdoData(uint32_t val) { memcpy(&m_data, &val, sizeof(uint32_t)); }
	CobSdoData(float val) { memcpy(&m_data, &val, sizeof(uint32_t)); }

	uint32_t u32() const
	{ 
		uint32_t val;
		memcpy(&val, &m_data, sizeof(uint32_t));
		return val;
	}
	
	float f32() const
	{ 
		float val;
		memcpy(&val, &m_data, sizeof(uint32_t));
		return val;
	}
};


const uint32_t SDO_CCS_WRITE = 1;
const uint32_t SDO_SCS_WRITE = 3;
const uint32_t SDO_CCS_READ = 2;
const uint32_t SDO_SCS_READ = 2;


struct CobSdo
{
	uint32_t dataSizeIndicated : 1;
	uint32_t expeditedTransfer : 1;
	uint32_t dataEmptyBytes : 2;
	uint32_t reserved : 1;
	uint32_t cs : 3;
	uint32_t index : 16;
	uint32_t subindex : 8;
	CobSdoData data = {};
	CobSdo() = default;
	uint64_t all() const
	{
		uint64_t data = 0;
		memcpy(&data, this, sizeof(CobSdo));
		return data;
	}
};


enum ODEntryDataType
{
	OD_FLOAT32,
	OD_UINT32,
	OD_ENUM,
	OD_FUNC,
	OD_STRING
};


struct ODEntryKey
{
	unsigned int index;
	unsigned int subindex;
};

inline bool operator<(const ODEntryKey& lhs, const ODEntryKey& rhs)
{
	return (lhs.index < rhs.index) || ((lhs.index == rhs.index) && (lhs.subindex < rhs.subindex));
}


struct ODEntryValue
{
	QString category;
	QString subcategory;
	QString name;
	QString unit;
	ODEntryDataType dataType;
	bool readAccess;
	bool writeAccess;
};


} // namespace microcanopen
