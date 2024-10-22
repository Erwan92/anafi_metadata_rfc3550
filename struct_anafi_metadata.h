typedef struct metadata
{
  int32_t ground_distance;
  int32_t latitude;
  int32_t longitude;
  int16_t alt1;
  int8_t alt2;
  uint8_t sv;
  int16_t north_speed;
  int16_t east_speed;
  int16_t down_speed;
  int16_t air;
  int16_t drone_w;
  int16_t drone_x;
  int16_t drone_y;
  int16_t drone_z;
  int16_t frame_base_w;
  int16_t frame_base_x;
  int16_t frame_base_y;
  int16_t frame_base_z;
  int16_t frame_w;
  int16_t frame_x;
  int16_t frame_y;
  int16_t frame_z;
  uint16_t exposure_time;
  uint16_t gain;
  uint16_t awb_r_gain;
  uint16_t awb_b_gain;
  uint16_t picture_hfov;
  uint16_t picture_vfov;
  uint16_t goodput1;
  uint8_t goodput2;
  uint8_t link_quality;
  int8_t wifi_rssi;
  uint8_t battery;
  uint8_t state;
  uint8_t mode;
  uint16_t ext_id;
  uint16_t ext_length;
  uint32_t frame_timestamp_h;
  uint32_t frame_timestamp_l;
  uint16_t ext_id2;
  uint16_t ext_length2;
  int32_t  framing_target_latitude;
  int32_t  framing_target_longitude;
  int32_t  framing_target_altitude;
  int32_t  flight_destination_latitude;
  int32_t  flight_destination_longitude;
  int32_t  flight_destination_altitude;
  uint8_t  automation_animation;
  unsigned int follow_me_bool:1;
  unsigned int look_at_me_bool:1;
  unsigned int angle_locked_bool:1;
  unsigned int reserved_bits:5;
  uint16_t reserved;
  uint16_t ext_id3;
  uint16_t ext_length3;
  int16_t  min_x;
  int16_t  min_y;
  int16_t  min_temp;
  int16_t  max_x;
  int16_t  max_y;
  int16_t  max_temp;
  int16_t  probe_x;
  int16_t  probe_y;
  int16_t  probe_temp;
  uint8_t  calib_state;
  uint8_t  flags;
  uint16_t ext_id4;
  uint16_t ext_length4;
  uint32_t champ_inconnu;
  uint32_t champ_inconnu2;
  uint32_t champ_inconnu3;
} metadata;

typedef struct metadata_timestamp_ext
{
    uint16_t ext_id;               /* Extension structure id = 0x4531 */
    uint16_t ext_length;           /* Extension structure size in 32 bits words excluding the ext_id and ext_size fields */
    uint32_t frame_timestamp_h;    /* Frame timestamp (µs, monotonic), high 32 bits */
    uint32_t frame_timestamp_l;    /* Frame timestamp (µs, monotonic), low 32 bits */
} metadata_timestamp_ext;

struct metadata_followme_ext
{
    uint16_t ext_id;               /* Extension structure id = 0x4532 */
    uint16_t ext_length;           /* Extension structure size in 32 bits words excluding the ext_id and ext_size fields */
    int32_t  target_latitude;      /* Target latitude (deg), Q10.22 */
    int32_t  target_longitude;     /* Target longitude (deg), Q10.22 */
    int32_t  target_altitude;      /* Target altitude ASL (m) Q16.16 */
    uint8_t  followme_mode;        /* Follow-me feature bit field
                                    *  - bit 0: follow-me enabled (0 = disabled, 1 = enabled)
                                    *  - bit 1: mode (0 = look-at-me, 1 = follow-me)
                                    *  - bit 2: angle mode (0 = unlocked, 1 = locked)
                                    *  - bit 3-7: reserved for future use */
    uint8_t  followme_animation;   /* Follow-me animation (0 means no animation in progress) */
    uint8_t  reserved1;            /* Reserved for future use */
    uint8_t  reserved2;            /* Reserved for future use */
    uint32_t reserved3;            /* Reserved for future use */
    uint32_t reserved4;            /* Reserved for future use */
} metadata_followme_ext;

struct metadata_automation_ext
{
    uint16_t ext_id;                   /* Extension structure id = 0x4533 */
    uint16_t ext_length;               /* Extension structure size in 32 bits words excluding the
                                        * ext_id and ext_size fields */
    int32_t  framing_target_latitude;  /* Framing target latitude (deg), Q10.22 */
    int32_t  framing_target_longitude; /* Framing target longitude (deg), Q10.22 */
    int32_t  framing_target_altitude;  /* Framing target altitude ASL (m) Q16.16 */
    int32_t  flight_destination_latitude;   /* Flight destination latitude (deg), Q10.22 */
    int32_t  flight_destination_longitude;  /* Flight destination longitude (deg), Q10.22 */
    int32_t  flight_destination_altitude;   /* Flight destination altitude ASL (m) Q16.16 */
    uint8_t  automation_animation;     /* Automation animation (0 means no animation in progress) */
    uint8_t  automation_flags;         /* Automation features bit field
                                        *  - bit 0: follow-me enabled (0 = disabled, 1 = enabled)
                                        *  - bit 1: look-at-me enabled (0 = disabled, 1 = enabled)
                                        *  - bit 2: angle locked (0 = unlocked, 1 = locked)
                                        *  - bit 3-7: reserved for future use */
    uint16_t reserved;                 /* Reserved for future use */
} metadata_automation_ext;

struct metadata_thermal_ext
{
    uint16_t ext_id;               /* Extension structure id = 0x4534 */
    uint16_t ext_length;           /* Extension structure size in 32 bits words excluding the ext_id and ext_size fields */
    int16_t  min_x;                /* Minimum temperature spot x-coordinate (relative to frame width), Q11.5 */
    int16_t  min_y;                /* Minimum temperature spot y-coordinate (relative to frame height), Q11.5 */
    int16_t  min_temp;             /* Minimum temperature spot temperature value (K) Q11.5 */
    int16_t  max_x;                /* Maximum temperature spot x-coordinate (relative to frame width), Q11.5 */
    int16_t  max_y;                /* Maximum temperature spot y-coordinate (relative to frame height), Q11.5 */
    int16_t  max_temp;             /* Maximum temperature spot temperature value (K) Q11.5 */
    int16_t  probe_x;              /* Probe temperature x-coordinate (relative to frame width), Q11.5 */
    int16_t  probe_y;              /* Probe temperature y-coordinate (relative to frame height), Q11.5 */
    int16_t  probe_temp;           /* Probe temperature temperature value (K) Q11.5 */
    uint8_t  calib_state;          /* Calibration state */
    uint8_t  flags;                /* Validity flags
                                    *  - bit 0: minimum temperature spot (0 = invalid, 1 = valid)
                                    *  - bit 1: maximum temperature spot (0 = invalid, 1 = valid)
                                    *  - bit 2: probe temperature (0 = invalid, 1 = valid)
                                    *  - bit 3-7: reserved for future use */
} metadata_thermal_ext;

struct vmeta_location {
	double latitude;				/* Latitude (deg) */
	double longitude;				/* Longitude (deg) */
	double altitude_wgs84ellipsoid;	/* Altitude above the WGS84 ellipsoid (m) (NaN means unknown) */
	double altitude_egm96amsl;		/* Altitude above the EGM96 geoid (AMSL) (m) (NaN means unknown) */
	float horizontal_accuracy;		/* Horizontal location accuracy (m), zero means unknown */
	float vertical_accuracy;		/* Vertical location accuracy (m), zero means unknown */
	uint8_t sv_count;				/* GPS satellite vehicle count; set to VMETA_LOCATION_INVALID_SV_COUNT
									* if not available even if valid is set */
	uint8_t valid;					/* Validity flag (1 if the structure contents are valid, 0 otherwise;
									* when a location is valid, sv_count may still be invalid) */
} vmeta_location;

struct vmeta_frame_ext_lfic {
	float target_x;               			/* Normalized horizontal position of the target cursor in the image ([0..1]) */
	float target_y;				  			/* Normalized vertical position of the target cursor in the image ([0..1]) */
	struct vmeta_location target_location;  /* Location of the target */
	double estimated_precision;  			/* Estimated precision of the position (m) */
	double grid_precision;		 			/* Grid precision used for calculation (m) */
} vmeta_frame_ext_lfic;
