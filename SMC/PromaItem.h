#define PromaType char
#define PromaParam int

#define PT_MOTOR	0x00
#define PT_THERM	0x01
#define PT_DELAY	0x02

#define PT_MOTOR_UP		0x00
#define PT_MOTOR_DOWN	0x01

typedef struct PromaItem {
	PromaType promaType;
	PromaParam wParam;
	PromaParam lParam;
} PromaItem;