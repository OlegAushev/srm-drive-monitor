#include "objectdictionary.h"


namespace microcanopen {

extern const std::map<ODEntryKey, ODEntryValue> OBJECT_DICTIONARY = {
{{0x1008, 0x00}, {"INFO", "DEVICE", "DEVICE NAME", "", OD_STRING, true, false}},
{{0x5FFF, 0x00}, {"INFO", "SOFTWARE", "SOFTWARE VERSION", "", OD_UINT32, true, false}},
{{0x5FFF, 0x01}, {"INFO", "SOFTWARE", "BUILD CONFIGURATION", "", OD_STRING, true, false}},

{{0x2000, 0x00}, {"WATCH",	"NULL", "SYS_TIME",		"s",	OD_FLOAT32,	true,	false}},
{{0x2000, 0x01}, {"WATCH",	"NULL", "DRIVE_STATE",		"",	OD_ENUM,	true,	false}},
{{0x2000, 0x02}, {"WATCH",	"NULL", "FAULTS",		"",	OD_UINT32, 	true,	false}},
{{0x2000, 0x03}, {"WATCH",	"NULL", "DC_VOLAGE",		"V",	OD_FLOAT32, 	true,	false}},
{{0x2000, 0x04}, {"WATCH",	"NULL", "DC_CURRENT",		"A",	OD_FLOAT32, 	true,	false}},
{{0x2000, 0x05}, {"WATCH",	"NULL", "FIELD_CURRENT",	"A",	OD_FLOAT32, 	true,	true}},
{{0x2000, 0x06}, {"WATCH",	"NULL", "STATOR_CURRENT",	"A",	OD_FLOAT32, 	true,	false}},
{{0x2000, 0x07}, {"WATCH",	"NULL", "PHA_CURRENT",		"A",	OD_FLOAT32, 	true,	false}},
{{0x2000, 0x08}, {"WATCH",	"NULL", "PHB_CURRENT",		"A",	OD_FLOAT32, 	true,	false}},
{{0x2000, 0x09}, {"WATCH",	"NULL", "PHC_CURRENT",		"A",	OD_FLOAT32, 	true,	false}},
{{0x2000, 0x0A}, {"WATCH",	"NULL", "D_CURRENT",		"A",	OD_FLOAT32, 	true,	false}},
{{0x2000, 0x0B}, {"WATCH",	"NULL", "Q_CURRENT",		"A",	OD_FLOAT32, 	true,	false}},
{{0x2000, 0x0C}, {"WATCH",	"NULL", "PHA_TEMP",		"°C",	OD_FLOAT32, 	true,	false}},
{{0x2000, 0x0D}, {"WATCH",	"NULL", "PHB_TEMP",		"°C",	OD_FLOAT32,	true,	false}},
{{0x2000, 0x0E}, {"WATCH",	"NULL", "PHC_TEMP",		"°C",	OD_FLOAT32, 	true,	false}},
{{0x2000, 0x0F}, {"WATCH",	"NULL", "AIR_TEMP",		"°C",	OD_FLOAT32, 	true,	false}},
{{0x2000, 0x10}, {"WATCH",	"NULL", "MOTOR_S_TEMP",		"°C",	OD_FLOAT32, 	true,	false}},
{{0x2000, 0x11}, {"WATCH",	"NULL", "MOTOR_FW_TEMP",	"°C",	OD_FLOAT32, 	true,	false}},
{{0x2000, 0x12}, {"WATCH",	"NULL", "GAMMA_ANGLE_DEG",	"°",	OD_FLOAT32, 	true,	true}},
{{0x2000, 0x13}, {"WATCH",	"NULL", "SPEED_RPM",		"rpm",	OD_FLOAT32, 	true,	true}},
{{0x2000, 0x14}, {"WATCH",	"NULL", "TORQUE",		"Nm",	OD_FLOAT32, 	true,	false}},
{{0x2000, 0x15}, {"WATCH",	"NULL", "MECH_POWER",		"W",	OD_FLOAT32, 	true,	false}},
{{0x2000, 0x16}, {"WATCH",	"NULL", "OUT_ELEC_POWER",	"W",	OD_FLOAT32, 	true,	false}},

{{0x2001, 0x00}, {"DRIVE CONTROL", 	"NULL", "POWER UP DRIVE", 			"",	OD_FUNC,	false,	true}},
{{0x2001, 0x01}, {"DRIVE CONTROL",	"NULL", "POWER DOWN DRIVE", 			"",	OD_FUNC, 	false,	true}},

{{0x2002, 0x00}, {"SYSTEM CONTROL", 	"NULL", "RESET DEVICE", 			"",	OD_FUNC, 	false,	true}},
{{0x2002, 0x01}, {"SYSTEM CONTROL", 	"NULL", "RESET PARAMETERS", 			"",	OD_FUNC, 	false,	true}},
{{0x2002, 0x02}, {"SYSTEM CONTROL", 	"NULL", "APPLY PARAMETERS", 			"",	OD_FUNC, 	false,	true}},
{{0x2002, 0x03}, {"SYSTEM CONTROL", 	"NULL", "BEGIN POSITION SENSOR CALIBRATION", 	"",	OD_FUNC, 	false,	true}},
{{0x2002, 0x04}, {"SYSTEM CONTROL", 	"NULL", "INVERT ROTATION", 			"",	OD_FUNC, 	false,	true}},
{{0x2002, 0x05}, {"SYSTEM CONTROL", 	"NULL", "RESET FAULTS", 			"",	OD_FUNC, 	false,	true}},


{{0x2100, 0x00}, {"CONFIG",	"MOTOR",	"R", 			"Ω",	OD_FLOAT32,	true,	true}},
{{0x2100, 0x01}, {"CONFIG",	"MOTOR",	"LD", 			"H",	OD_FLOAT32, 	true,	true}},
{{0x2100, 0x02}, {"CONFIG",	"MOTOR",	"KLD", 			"",	OD_FLOAT32, 	true,	true}},
{{0x2100, 0x03}, {"CONFIG",	"MOTOR",	"LQ", 			"H",	OD_FLOAT32, 	true,	true}},
{{0x2100, 0x04}, {"CONFIG",	"MOTOR",	"KLQ", 			"",	OD_FLOAT32, 	true,	true}},
{{0x2100, 0x05}, {"CONFIG",	"MOTOR",	"OTP_STATOR", 		"°C",	OD_FLOAT32, 	true,	true}},
{{0x2100, 0x06}, {"CONFIG",	"MOTOR",	"OTP_FW", 		"°C",	OD_FLOAT32,	true,	true}},

{{0x2101, 0x00}, {"CONFIG",	"MODEL",	"REFERENCE", 		"n-M",	OD_ENUM, 	true,	true}},
{{0x2101, 0x01}, {"CONFIG",	"MODEL",	"KP_SPEED", 		"",	OD_FLOAT32, 	true,	true}},
{{0x2101, 0x02}, {"CONFIG",	"MODEL",	"KI_SPEED", 		"",	OD_FLOAT32, 	true,	true}},
{{0x2101, 0x03}, {"CONFIG",	"MODEL",	"KP_ID", 		"",	OD_FLOAT32, 	true,	true}},
{{0x2101, 0x04}, {"CONFIG",	"MODEL",	"KI_ID", 		"",	OD_FLOAT32, 	true,	true}},
{{0x2101, 0x05}, {"CONFIG",	"MODEL",	"KP_IQ", 		"",	OD_FLOAT32, 	true,	true}},
{{0x2101, 0x06}, {"CONFIG",	"MODEL",	"KI_IQ", 		"",	OD_FLOAT32, 	true,	true}},
{{0x2101, 0x07}, {"CONFIG",	"MODEL",	"KP_IF", 		"",	OD_FLOAT32, 	true,	true}},
{{0x2101, 0x08}, {"CONFIG",	"MODEL",	"KI_IF", 		"",	OD_FLOAT32, 	true,	true}},
{{0x2101, 0x09}, {"CONFIG",	"MODEL",	"IS_MOTOR_MAX", 	"A",	OD_FLOAT32, 	true,	true}},
{{0x2101, 0x0A}, {"CONFIG",	"MODEL",	"IS_GENER_MAX", 	"A",	OD_FLOAT32, 	true,	true}},
{{0x2101, 0x0B}, {"CONFIG",	"MODEL",	"IF_MAX", 		"A",	OD_FLOAT32, 	true,	true}},
{{0x2101, 0x0C}, {"CONFIG",	"MODEL",	"TORQUE_POS_MAX", 	"Nm",	OD_FLOAT32, 	true,	true}},
{{0x2101, 0x0D}, {"CONFIG",	"MODEL",	"TORQUE_NEG_MAX",	"Nm",	OD_FLOAT32, 	true,	true}},
{{0x2101, 0x0E}, {"CONFIG",	"MODEL",	"SPEED_MAX",		"rpm",	OD_FLOAT32, 	true,	true}},

{{0x2102, 0x00}, {"CONFIG",	"CONVERTER",	"UVP_DC",		"V",	OD_FLOAT32, 	true,	true}},
{{0x2102, 0x01}, {"CONFIG",	"CONVERTER",	"OVP_DC",		"V",	OD_FLOAT32, 	true,	true}},
{{0x2102, 0x02}, {"CONFIG",	"CONVERTER",	"OCP_PHASE", 		"A",	OD_FLOAT32, 	true,	true}},
{{0x2102, 0x03}, {"CONFIG",	"CONVERTER",	"OCP_FIELD", 		"A",	OD_FLOAT32, 	true,	true}},
{{0x2102, 0x04}, {"CONFIG",	"CONVERTER",	"OCP_DC",		"A",	OD_FLOAT32, 	true,	true}},
{{0x2102, 0x05}, {"CONFIG",	"CONVERTER",	"OTP_JUNCTION",		"°C",	OD_FLOAT32, 	true,	true}},
{{0x2102, 0x06}, {"CONFIG",	"CONVERTER",	"OTP_AIR",		"°C",	OD_FLOAT32, 	true,	true}},

{{0x2103, 0x00}, {"CONFIG",	"CONTACTOR",	"DCLINK_THRESHOLD",	"V",	OD_FLOAT32, 	true,	true}},
{{0x2103, 0x01}, {"CONFIG",	"CONTACTOR",	"DCLINK_TIMEOUT",	"ms",	OD_UINT32, 	true,	true}},
{{0x2103, 0x02}, {"CONFIG",	"CONTACTOR",	"DCLINK_HOLDUP",	"ms",	OD_UINT32, 	true,	true}},

{{0x2104, 0x00}, {"CONFIG",	"MCOSERVER",	"PERIOD_HB",		"ms",	OD_UINT32, 	true,	true}},
{{0x2104, 0x01}, {"CONFIG",	"MCOSERVER",	"PERIOD_TPDO1",		"ms",	OD_UINT32, 	true,	true}},
{{0x2104, 0x02}, {"CONFIG",	"MCOSERVER",	"PERIOD_TPDO2",		"ms",	OD_UINT32, 	true,	true}},
{{0x2104, 0x03}, {"CONFIG",	"MCOSERVER",	"PERIOD_TPDO3",		"ms",	OD_UINT32, 	true,	true}},
{{0x2104, 0x04}, {"CONFIG",	"MCOSERVER",	"PERIOD_TPDO4",		"ms",	OD_UINT32, 	true,	true}},

{{0xFFFF, 0xFF}, {"NULL", "NULL", "END_OF_OD", "", OD_FUNC, false, false}}
};





}
