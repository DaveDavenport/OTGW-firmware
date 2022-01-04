#ifndef OPEN_THERM_TYPES_H
#define OPEN_THERM_TYPES_H
#include <stdint.h>

/** Master Slave Status */
typedef struct OTDataMSStatus {
  struct {
    uint8_t ch : 1;
    uint8_t dhw : 1;
    uint8_t cooling : 1;
    uint8_t otc : 1;
    uint8_t ch2 : 1;
    uint8_t reserved : 3;
  } master;
  struct {
    uint8_t ch : 1;
    uint8_t dhw : 1;
    uint8_t cooling : 1;
    uint8_t otc : 1;
    uint8_t ch2 : 1;
    uint8_t reserved : 3;
  } slave;
} OTDataMSStatus;

/** Application specific flags + fault code */
typedef struct OTDataAppsFFLags {
  uint8_t service_request : 1;
  uint8_t lockout_reset : 1;
  uint8_t low_water_pres : 1;
  uint8_t gas_flame_fault : 1;
  uint8_t air_press_fault : 1;
  uint8_t water_over_temp : 1;
  uint8_t reserved : 2;
  uint8_t oem_fault_code;
} OTDataAppsFFLags;

/** Slave configuration and member id */
typedef struct OTDataSlaveConfig {
  uint8_t dhw_present : 1;
  uint8_t control_type : 1;
  uint8_t cooling_config : 1;
  uint8_t dwh_config : 1;
  uint8_t low_off : 1;
  uint8_t ch2_present : 1;
  uint8_t reserved : 2;
  uint8_t member_id;
} OTDataSlaveConfig;

/** Time representation */
typedef struct OTDataTime {
  uint8_t dow : 3;
  uint8_t hours : 5;
  uint8_t minutes;
} OTDataTime;

typedef union OTDataValue {
  /** used for unsigned 16 bit. */
  uint16_t unsigned_short;
  /** used for signed 16bit and when divided by 256.f as float. */
  int16_t signed_short;
  /** 2*u8 */
  struct {
    uint8_t high;
    uint8_t low;
  } split_unsigned;
  /** 2*s8 */
  struct {
    int8_t high;
    int8_t low;
  } split_signed;

  /** Status */
  OTDataMSStatus ms_status;
  /** Application specific flags + fault code */
  OTDataAppsFFLags apps_fault_flags;
  /** Slave configuration and member id */
  OTDataSlaveConfig slave_config;
  /** Time */
  OTDataTime time;
} OTDataValue;

typedef union OTFrame {
  /**  Direct access to frame. */
  uint32_t direct;
  /** Split over the different fields. */
  struct {
    /** Parity bit */
    uint8_t parity : 1;
    uint8_t msg_type : 3;
    uint8_t spares : 4;
    uint8_t data_id : 8;
    OTDataValue data_value;
  } split __attribute__((packed));
} OTFrame;

#endif // OPEN_THERM_TYPES_H
