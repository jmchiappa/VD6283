#ifndef __VD6283__
#define __VD6283__

#ifndef __KERNEL__
#	include <stdlib.h>
#	include <string.h>
#else
#	include <linux/string.h>
#	include <linux/bitops.h>
#	include <linux/math64.h>
#	include <linux/bug.h>
#endif

#include "STALS.h"
#include "STALS_platform.h"
#include "VD6283_map.h"

#include "STALS_compat.h"

// #ifndef VD6283_CONFIG_DEVICES_MAX
// #define VD6283_CONFIG_DEVICES_MAX		4
// #endif

#define UID_LEN					16

#define VD6283_CHANNEL_NB			STALS_ALS_MAX_CHANNELS

#ifndef ARRAY_SIZE
#	define ARRAY_SIZE(a)				(sizeof(a) / sizeof(a[0]))
#endif

#define VD6283_DC_CHANNELS_MASK			0x1f
#define VD6283_AC_CHANNELS_MASK			0x20

#define VD6283_DEFAULT_HF_TRIM			0x0e3
#define VD6283_DEFAULT_LF_TRIM			0x07
#define VD6283_DEFAULT_FILTER_CONFIG		2
#define VD6283_DEFAULT_GAIN			0x80

#define VD6283_DEFAULT_OTP_VERSION	0x15

#ifndef MAX
#	define MAX(a, b)				((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
#	define MIN(a, b)				((a) < (b) ? (a) : (b))
#endif

#define VD6283_DEFAULT_FILTER_INDEX		2

static const uint16_t GainRange[] = {
	0x42AB,		/*   66, 67 */
	0x3200,		/*   50, 00 */
	0x2154,		/*   33, 33 */
	0x1900,		/*   25, 00 */
	0x10AB,		/*   16, 67 */
	0x0A00,		/*   10, 00 */
	0x0723,		/*    7, 14 */
	0x0500,		/*    5, 00 */
	0x0354,		/*    3, 33 */
	0x0280,		/*    2, 50 */
	0x01AB,		/*    1, 67 */
	0x0140,		/*    1, 25 */
	0x0100,		/*    1, 00 */
	0x00D4,		/*    0, 83 */
	0x00B5		/*    0, 71 */
};

static const uint16_t GainRangeThreshold[] = {
	0x3A56,
	0x29AB,
	0x1D2B,
	0x14D6,
	0x0D56,
	0x0892,
	0x0612,
	0x042B,
	0x02EB,
	0x0216,
	0x0176,
	0x0121,
	0x00EB,
	0x00C5
};

enum dev_state {
	DEV_FREE = 0,
	DEV_INIT,
	DEV_ALS_RUN,
	DEV_FLICKER_RUN,
	DEV_BOTH_RUN
};

struct VD6283_device {
	enum dev_state st;
	enum STALS_Mode_t als_started_mode;
	void *client;
	void *hdl;
	uint8_t device_id;
	uint8_t revision_id;
	uint8_t dc_chan_en;
	uint8_t ac_chan_en;
	struct {
		uint8_t chan;
	} als;
	struct {
		uint8_t chan;
	} flk;
	uint16_t gains[VD6283_CHANNEL_NB];
	uint32_t exposure;
	enum STALS_FlickerOutputType_t flicker_output_type;
	enum STALS_Control_t is_otp_usage_enable;
	enum STALS_Control_t is_output_dark_enable;
	uint64_t otp_bits[2];
	struct {
		uint16_t hf_trim;
		uint8_t lf_trim;
		uint8_t filter_config;
		uint8_t filter_index;
		uint8_t gains[STALS_ALS_MAX_CHANNELS];
		uint8_t otp_version;
	} otp;
	char uid[UID_LEN];
};

typedef struct VD6283_device VD6283_device_t;

#endif