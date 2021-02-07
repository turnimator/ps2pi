/* Bit Operation Macros */
#define SET(x,y) (x|=(1<<y))	// Set bit y in x
#define CLR(x,y) (x&=(~(1<<y)))	// Clear bit y in x
#define CHK(x,y) (x & (1<<y))	// Check if bit y in x is set
#define TOG(x,y) (x^=(1<<y))	// Toggle bit y in x

/* Delays */
#define CLK_DELAY  		20
#define BYTE_DELAY 		10
#define CMD_DELAY 		10
#define MAX_RETRIES 	8

/* Maximum number of init tries */
#define MAX_INIT_ATTEMPT 	50

/* Controller Modes - From: http://www.lynxmotion.com/images/files/ps2cmd01.txt */
#define DIGITALMODE 	0x41
#define ANALOGMODE 		0x73
#define ALLPRESSUREMODE	0x79
#define DS2NATIVEMODE	0xF3

/* Button Masks */
//              From data bit 0 (PS2data[3])
#define BTN_SELECT 		0
#define	BTN_LEFT_JOY	1
#define	BTN_RIGHT_JOY	2
#define	BTN_START		3
#define	BTN_UP			4
#define	BTN_RIGHT		5
#define	BTN_DOWN		6
#define	BTN_LEFT		7
//              From data bit 1 (PSdata[4])
#define	BTN_L2			0
#define	BTN_R2			1
#define	BTN_L1			2
#define	BTN_R1			3
#define	BTN_TRIANGLE	4
#define	BTN_CIRCLE		5
#define	BTN_X			6
#define	BTN_SQUARE		7

/* Action numbers */
#define ACTION_SELECT 		0
#define	ACTION_LEFT_JOY		1
#define	ACTION_RIGHT_JOY	2
#define	ACTION_START		3
#define	ACTION_UP			4
#define	ACTION_RIGHT		5
#define	ACTION_DOWN			6
#define	ACTION_LEFT			7
//              From data bit 1 (PSdata[4])
#define	ACTION_L2			8
#define	ACTION_R2			9
#define	ACTION_L1			10
#define	ACTION_R1			11
#define	ACTION_TRIANGLE		12
#define	ACTION_CIRCLE		13
#define	ACTION_X			14
#define	ACTION_SQUARE		15
#define ACTION_ARRAY_SIZE	16


/* Byte Numbers of PSdata[] For Button Pressures */
#define	PRES_RIGHT 		10
#define	PRES_LEFT 		11
#define	PRES_UP 		12
#define	PRES_DOWN 		13
#define	PRES_TRIANGLE 	14
#define	PRES_CIRCLE 	15
#define	PRES_X		 	16
#define	PRES_SQUARE 	17
#define	PRES_L1		 	18
#define	PRES_R1		 	19
#define	PRES_L2		 	20
#define	PRES_R2		 	21

/* Controller Commands */
static unsigned char enterConfigMode[] = { 0x01, 0x43, 0x00, 0x01, 0x00 };
static unsigned char set_mode_analog_lock[] =
{ 0x01, 0x44, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00 };
static unsigned char exitConfigMode[] =
{ 0x01, 0x43, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A };
static unsigned char type_read[] =
{ 0x01, 0x45, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A };
static unsigned char config_AllPressure[] =
{ 0x01, 0x4F, 0x00, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00 };

struct action_t {
	void (*f)(int pressure, void* user_data); 
	int pressure; // placeholder for now
	void *user_data;
};

/* Class declaration */
class ps2pi_t {
public:
	unsigned char begin(int _commandPin, int _dataPin, int _clkPin,
						int _attnPin);
	int reInitializeController(char controllerMode);
	int reInitializeController();
	int readPS2(void);
	void dispatch();
	void readAndDispatch();
	void setMajorMode(int mode = 1);
	inline bool isValid() {
		return (PS2data[2] == 0x5a);
	}
	inline bool isXPressed() {
		return (isValid() && ~PS2data[4] & (1 << BTN_X));
	}
	inline void setXAction(void ((*a)(int pressure, void* user_data)), void *user_data) { action[ACTION_X].f = a; action[ACTION_X].user_data=user_data; }
	
	inline bool isCirclePressed() {
		return (isValid() && ~PS2data[4] & (1 << BTN_CIRCLE));
	}
	inline void setCircleAction(void ((*a)(int pressure, void* user_data)), void *user_data) { action[ACTION_CIRCLE].f = a; action[ACTION_CIRCLE].user_data=user_data; }
	
	
	inline bool isTrianglePressed() {
		return (isValid() && ~PS2data[4] & (1 << BTN_TRIANGLE));
	}
	inline void setTriangleAction(void ((*a)(int pressure, void* user_data)), void *user_data) { action[ACTION_TRIANGLE].f = a; action[ACTION_TRIANGLE].user_data=user_data; }
		
	inline bool isSquarePressed() {
		return (isValid() && ~PS2data[4] & (1 << BTN_SQUARE));
	}
	inline void setSquareAction(void ((*a)(int pressure, void* user_data)), void *user_data) { action[ACTION_SQUARE].f = a; action[ACTION_SQUARE].user_data=user_data; }
	
	inline bool isSelectPressed() {
		return (isValid() && ~PS2data[3] & (1 << BTN_SELECT));
	}
	inline void setSelectAction(void ((*a)(int pressure, void* user_data)), void *user_data) { action[ACTION_SELECT].f = a; action[ACTION_SELECT].user_data=user_data; }
	
	
	inline bool isLeftJoyPressed() {
		return (isValid() && ~PS2data[3] & (1 << BTN_LEFT_JOY));
	}
	inline void setLeftJoyAction(void ((*a)(int pressure, void* user_data)), void *user_data) { action[ACTION_LEFT_JOY].f = a; action[ACTION_LEFT_JOY].user_data=user_data; }
	
	inline bool isRightJoyPressed() {
		return (isValid() && ~PS2data[3] & (1 << BTN_RIGHT_JOY));
	}
	inline void setRightJoyAction(void ((*a)(int pressure, void* user_data)), void *user_data) { action[ACTION_RIGHT_JOY].f = a; action[ACTION_RIGHT_JOY].user_data=user_data; }
	
	inline bool isStartPressed() {
		return (isValid() && ~PS2data[3] & (1 << BTN_START));
	}
	inline void setStartAction(void ((*a)(int pressure, void* user_data)), void *user_data) { action[ACTION_START].f = a; action[ACTION_START].user_data=user_data; }
	
	inline bool isPadUpPressed() {
		return (isValid() && ~PS2data[3] & (1 << BTN_UP));
	}
	inline void setPadUpAction(void ((*a)(int pressure, void* user_data)), void *user_data) { action[ACTION_UP].f = a; action[ACTION_UP].user_data=user_data; }
	
	
	inline bool isPadRightPressed() {
		return (isValid() && ~PS2data[3] & (1 << BTN_RIGHT));
	}
	inline void setPadRightAction(void ((*a)(int pressure, void* user_data)), void *user_data) { action[ACTION_RIGHT].f = a; action[ACTION_RIGHT].user_data=user_data; }
	
	
	inline bool isPadDownPressed() {
		return (isValid() && ~PS2data[3] & (1 << BTN_DOWN));
	}
	inline void setPadDownAction(void ((*a)(int pressure, void* user_data)), void *user_data) { action[ACTION_DOWN].f = a; action[ACTION_DOWN].user_data=user_data; }
	
		
	inline bool isPadLeftPressed() {
		return (isValid() && ~PS2data[3] & (1 << BTN_LEFT));
	}
	inline void setPadLeftAction(void ((*a)(int pressure, void* user_data)), void *user_data) { action[ACTION_LEFT].f = a; action[ACTION_LEFT].user_data=user_data; }
	
	
	inline bool isL2Pressed() {
		return (isValid() && ~PS2data[4] & (1 << BTN_L2));
	}
	inline void setL2Action(void ((*a)(int pressure, void* user_data)), void *user_data) { action[ACTION_L2].f = a; action[ACTION_L2].user_data=user_data; }
	
		
	inline bool isR2Pressed() {
		return (isValid() && ~PS2data[4] & (1 << BTN_R2));
	}
	inline void setR2Action(void ((*a)(int pressure, void* user_data)), void *user_data) { action[ACTION_R2].f = a; action[ACTION_R2].user_data=user_data; }
	
		
	inline bool isL1Pressed() {
		return (isValid() && ~PS2data[4] & (1 << BTN_L1));
	}
	inline void setL1Action(void ((*a)(int pressure, void* user_data)), void *user_data) { action[ACTION_L1].f = a; action[ACTION_L1].user_data=user_data; }
	
	
	inline bool isR1Pressed() {
		return (isValid() && ~PS2data[4] & (1 << BTN_R1));
	}
	inline void setR1Action(void ((*a)(int pressure, void* user_data)), void *user_data) { action[ACTION_R1].f = a; action[ACTION_R1].user_data=user_data; }
	
	
	char getLeftX();
	char getLeftY();
	char getRighX();
	char getRighY();
	
	inline char getMode() {
		return PS2data[1];
	}
	void printData();
private:
	char controller_type;
	unsigned char PS2data[21];
	action_t action[ACTION_ARRAY_SIZE];
	unsigned char transmitByte(char byte);
	void transmitCmdString(unsigned char *string, int length);
	void clk(bool h);
	char controllerMode;
	int commandPin;
	int dataPin;
	int attnPin;
	int clkPin;
};


