#include <APA102.h>

// Define which pins to use.
const uint8_t dataPin = 11;
const uint8_t clockPin = 12;

// Create an object for writing to the LED strip.
APA102<dataPin, clockPin> ledPort;

// Set the number of LEDs
#define FLUX_LED_COUNT 13
#define POINT_LED_COUNT 5
#define FIRE_LED_COUNT 213
#define FULL_LED_COUNT (FLUX_LED_COUNT + POINT_LED_COUNT + FIRE_LED_COUNT)

// Create a buffer for holding the colors (3 bytes per color).
rgb_color colors[FULL_LED_COUNT];
rgb_color* flux_colors  = &(colors[0]);
rgb_color* point_colors = &(flux_colors[FLUX_LED_COUNT]);
rgb_color* fire_colors  = &(point_colors[POINT_LED_COUNT]);

const uint16_t brightness = 31;

////////////////////////////////////////////////////////////////
// BEGIN SECTION GENERATED BY blackbody_color_scale.py

// http://www.vendian.org/mncharity/dir3/blackbody/UnstableURLs/bbr_color.html

#define BLACKBODY_COUNT 83
// the following makes a dreceasing random distribution
#define GET_BLACKBODY_INDEX ((random(92) * random(92)) / 100) % BLACKBODY_COUNT

const rgb_color blackbody[] = {{ 12,   0,   0},
                               { 21,   0,   0},
                               { 30,   0,   0},
                               { 39,   0,   0},
                               { 48,   0,   0},
                               { 57,   0,   0},
                               { 66,   0,   0},
                               { 75,   0,   0},
                               { 84,   0,   0},
                               { 93,   0,   0},
                               {102,   0,   0},
                               {111,   0,   0},
                               {120,   0,   0},
                               {129,   0,   0},
                               {138,   0,   0},
                               {147,   0,   0},
                               {156,   0,   0},
                               {165,   0,   0},
                               {174,   0,   0},
                               {183,   0,   0},
                               {192,   0,   0},
                               {201,   0,   0},
                               {210,   6,   0},
                               {219,  15,   0},
                               {228,  24,   0},
                               {237,  33,   0},
                               {246,  42,   0},
                               {255,  51,   0},
                               {255,  51,   0},
                               {255,  69,   0},
                               {255,  82,   0},
                               {255,  93,   0},
                               {255, 102,   0},
                               {255, 111,   0},
                               {255, 118,   0},
                               {255, 124,   0},
                               {255, 130,   0},
                               {255, 135,   0},
                               {255, 141,  11},
                               {255, 146,  29},
                               {255, 152,  41},
                               {255, 157,  51},
                               {255, 162,  60},
                               {255, 166,  69},
                               {255, 170,  77},
                               {255, 174,  84},
                               {255, 178,  91},
                               {255, 182,  98},
                               {255, 185, 105},
                               {255, 189, 111},
                               {255, 192, 118},
                               {255, 195, 124},
                               {255, 198, 130},
                               {255, 201, 135},
                               {255, 203, 141},
                               {255, 206, 146},
                               {255, 208, 151},
                               {255, 211, 156},
                               {255, 213, 161},
                               {255, 215, 166},
                               {255, 217, 171},
                               {255, 219, 175},
                               {255, 221, 180},
                               {255, 223, 184},
                               {255, 225, 188},
                               {255, 226, 192},
                               {255, 228, 196},
                               {255, 229, 200},
                               {255, 231, 204},
                               {255, 232, 208},
                               {255, 234, 211},
                               {255, 235, 215},
                               {255, 237, 218},
                               {255, 238, 222},
                               {255, 239, 225},
                               {255, 240, 228},
                               {255, 241, 231},
                               {255, 243, 234},
                               {255, 244, 237},
                               {255, 245, 240},
                               {255, 246, 243},
                               {255, 247, 245},
                               {255, 248, 248}};

// END SECTION GENERATED BY blackbody_color_scale.py
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
// BEGIN SECTION GENERATED BY sign_period.m

#define CURVE_LENGTH 256
#define MS_IN_S 3000
#define MIN_FREQ 43
#define FREQUENCY_COUNT 5
#define F_NUM CURVE_LENGTH
#define F_DEN (MS_IN_S * MIN_FREQ)

const unsigned int frequencies[] = {43*F_NUM, 47*F_NUM, 53*F_NUM, 59*F_NUM, 61*F_NUM};

const uint8_t curve[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 10, 11, 11, 12, 13, 14, 16, 17, 18, 20, 21, 23, 24, 26, 28, 30, 33, 35, 38, 40, 43, 46, 49, 53, 56, 60, 64, 68, 73, 77, 82, 87, 92, 97, 102, 108, 113, 119, 125, 131, 137, 144, 150, 156, 163, 169, 175, 181, 188, 194, 200, 205, 211, 216, 221, 226, 231, 235, 239, 242, 245, 248, 250, 252, 254, 255, 255, 255, 255, 254, 252, 250, 248, 245, 242, 239, 235, 231, 226, 221, 216, 211, 205, 200, 194, 188, 181, 175, 169, 163, 156, 150, 144, 137, 131, 125, 119, 113, 108, 102, 97, 92, 87, 82, 77, 73, 68, 64, 60, 56, 53, 49, 46, 43, 40, 38, 35, 33, 30, 28, 26, 24, 23, 21, 20, 18, 17, 16, 14, 13, 12, 11, 11, 10, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// END SECTION GENERATED BY sign_period.m
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
// BEGIN SECTION GENERATED BY flux_capacitor.py

#define FLUX_FRAME_MS 130
#define FLUX_STEP ((now / 130) % 4)
#define FLUX_ON_COUNT 255
const rgb_color flux_off =  {  0,   0,   0};
const rgb_color flux_on[] = {{ 64,  36,   5},
                             { 65,  37,   6},
                             { 66,  38,   7},
                             { 67,  39,   8},
                             { 68,  40,   9},
                             { 69,  41,  10},
                             { 70,  42,  11},
                             { 71,  43,  12},
                             { 72,  44,  13},
                             { 73,  45,  14},
                             { 74,  46,  15},
                             { 75,  47,  16},
                             { 76,  48,  17},
                             { 77,  49,  18},
                             { 78,  50,  19},
                             { 79,  51,  20},
                             { 80,  52,  21},
                             { 81,  53,  22},
                             { 82,  54,  23},
                             { 83,  55,  24},
                             { 84,  56,  25},
                             { 85,  57,  26},
                             { 86,  58,  27},
                             { 87,  59,  28},
                             { 88,  60,  29},
                             { 89,  61,  30},
                             { 90,  62,  31},
                             { 91,  63,  32},
                             { 92,  64,  33},
                             { 93,  65,  34},
                             { 94,  66,  35},
                             { 95,  67,  36},
                             { 96,  68,  37},
                             { 97,  69,  38},
                             { 98,  70,  39},
                             { 99,  71,  40},
                             {100,  72,  41},
                             {101,  73,  42},
                             {102,  74,  43},
                             {103,  75,  44},
                             {104,  76,  45},
                             {105,  77,  46},
                             {106,  78,  47},
                             {107,  79,  48},
                             {108,  80,  49},
                             {109,  81,  50},
                             {110,  82,  51},
                             {111,  83,  52},
                             {112,  84,  53},
                             {113,  85,  54},
                             {114,  86,  55},
                             {115,  87,  56},
                             {116,  88,  57},
                             {117,  89,  58},
                             {118,  90,  59},
                             {119,  91,  60},
                             {120,  92,  61},
                             {121,  93,  62},
                             {122,  94,  63},
                             {123,  95,  64},
                             {124,  96,  65},
                             {125,  97,  66},
                             {126,  98,  67},
                             {127,  99,  68},
                             {128, 100,  69},
                             {129, 101,  70},
                             {130, 102,  71},
                             {131, 103,  72},
                             {132, 104,  73},
                             {133, 105,  74},
                             {134, 106,  75},
                             {135, 107,  76},
                             {136, 108,  77},
                             {137, 109,  78},
                             {138, 110,  79},
                             {139, 111,  80},
                             {140, 112,  81},
                             {141, 113,  82},
                             {142, 114,  83},
                             {143, 115,  84},
                             {144, 116,  85},
                             {145, 117,  86},
                             {146, 118,  87},
                             {147, 119,  88},
                             {148, 120,  89},
                             {149, 121,  90},
                             {150, 122,  91},
                             {151, 123,  92},
                             {152, 124,  93},
                             {153, 125,  94},
                             {154, 126,  95},
                             {155, 127,  96},
                             {156, 128,  97},
                             {157, 129,  98},
                             {158, 130,  99},
                             {159, 131, 100},
                             {160, 132, 101},
                             {161, 133, 102},
                             {162, 134, 103},
                             {163, 135, 104},
                             {164, 136, 105},
                             {165, 137, 106},
                             {166, 138, 107},
                             {167, 139, 108},
                             {168, 140, 109},
                             {169, 141, 110},
                             {170, 142, 111},
                             {171, 143, 112},
                             {172, 144, 113},
                             {173, 145, 114},
                             {174, 146, 115},
                             {175, 147, 116},
                             {176, 148, 117},
                             {177, 149, 118},
                             {178, 150, 119},
                             {179, 151, 120},
                             {180, 152, 121},
                             {181, 153, 122},
                             {182, 154, 123},
                             {183, 155, 124},
                             {184, 156, 125},
                             {185, 157, 126},
                             {186, 158, 127},
                             {187, 159, 128},
                             {188, 160, 129},
                             {189, 161, 130},
                             {190, 162, 131},
                             {191, 163, 132},
                             {192, 164, 133},
                             {193, 165, 134},
                             {194, 166, 135},
                             {195, 167, 136},
                             {196, 168, 137},
                             {197, 169, 138},
                             {198, 170, 139},
                             {199, 171, 140},
                             {200, 172, 141},
                             {201, 173, 142},
                             {202, 174, 143},
                             {203, 175, 144},
                             {204, 176, 145},
                             {205, 177, 146},
                             {206, 178, 147},
                             {207, 179, 148},
                             {208, 180, 149},
                             {209, 181, 150},
                             {210, 182, 151},
                             {211, 183, 152},
                             {212, 184, 153},
                             {213, 185, 154},
                             {214, 186, 155},
                             {215, 187, 156},
                             {216, 188, 157},
                             {217, 189, 158},
                             {218, 190, 159},
                             {219, 191, 160},
                             {220, 192, 161},
                             {221, 193, 162},
                             {222, 194, 163},
                             {223, 195, 164},
                             {224, 196, 165},
                             {225, 197, 166},
                             {226, 198, 167},
                             {227, 199, 168},
                             {228, 200, 169},
                             {229, 201, 170},
                             {230, 202, 171},
                             {231, 203, 172},
                             {232, 204, 173},
                             {233, 205, 174},
                             {234, 206, 175},
                             {235, 207, 176},
                             {236, 208, 177},
                             {237, 209, 178},
                             {238, 210, 179},
                             {239, 211, 180},
                             {240, 212, 181},
                             {241, 213, 182},
                             {242, 214, 183},
                             {243, 215, 184},
                             {244, 216, 185},
                             {245, 217, 186},
                             {246, 218, 187},
                             {247, 219, 188},
                             {248, 220, 189},
                             {249, 221, 190},
                             {250, 222, 191},
                             {251, 223, 192},
                             {252, 224, 193},
                             {253, 225, 194},
                             {254, 226, 195},
                             {255, 227, 196},
                             {255, 228, 197},
                             {255, 229, 198},
                             {255, 230, 199},
                             {255, 231, 200},
                             {255, 232, 201},
                             {255, 233, 202},
                             {255, 234, 203},
                             {255, 235, 204},
                             {255, 236, 205},
                             {255, 237, 206},
                             {255, 238, 207},
                             {255, 239, 208},
                             {255, 240, 209},
                             {255, 241, 210},
                             {255, 242, 211},
                             {255, 243, 212},
                             {255, 244, 213},
                             {255, 245, 214},
                             {255, 246, 215},
                             {255, 247, 216},
                             {255, 248, 217},
                             {255, 249, 218},
                             {255, 250, 219},
                             {255, 251, 220},
                             {255, 252, 221},
                             {255, 253, 222},
                             {255, 254, 223},
                             {255, 255, 224},
                             {255, 255, 225},
                             {255, 255, 226},
                             {255, 255, 227},
                             {255, 255, 228},
                             {255, 255, 229},
                             {255, 255, 230},
                             {255, 255, 231},
                             {255, 255, 232},
                             {255, 255, 233},
                             {255, 255, 234},
                             {255, 255, 235},
                             {255, 255, 236},
                             {255, 255, 237},
                             {255, 255, 238},
                             {255, 255, 239},
                             {255, 255, 240},
                             {255, 255, 241},
                             {255, 255, 242},
                             {255, 255, 243},
                             {255, 255, 244},
                             {255, 255, 245},
                             {255, 255, 246},
                             {255, 255, 247},
                             {255, 255, 248},
                             {255, 255, 249},
                             {255, 255, 250},
                             {255, 255, 251},
                             {255, 255, 252},
                             {255, 255, 253},
                             {255, 255, 254},
                             {255, 255, 255},
                             {255, 255, 255},
                             {255, 255, 255},
                             {255, 255, 255},
                             {255, 255, 255}};
const rgb_color flux_on_mid[] = {{  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 {  0,   0,   0},
                                 { 64,  36,   5},
                                 { 66,  38,   7},
                                 { 68,  40,   9},
                                 { 70,  42,  11},
                                 { 72,  44,  13},
                                 { 74,  46,  15},
                                 { 76,  48,  17},
                                 { 78,  50,  19},
                                 { 80,  52,  21},
                                 { 82,  54,  23},
                                 { 84,  56,  25},
                                 { 86,  58,  27},
                                 { 88,  60,  29},
                                 { 90,  62,  31},
                                 { 92,  64,  33},
                                 { 94,  66,  35},
                                 { 96,  68,  37},
                                 { 98,  70,  39},
                                 {100,  72,  41},
                                 {102,  74,  43},
                                 {104,  76,  45},
                                 {106,  78,  47},
                                 {108,  80,  49},
                                 {110,  82,  51},
                                 {112,  84,  53},
                                 {114,  86,  55},
                                 {116,  88,  57},
                                 {118,  90,  59},
                                 {120,  92,  61},
                                 {122,  94,  63},
                                 {124,  96,  65},
                                 {126,  98,  67},
                                 {128, 100,  69},
                                 {130, 102,  71},
                                 {132, 104,  73},
                                 {134, 106,  75},
                                 {136, 108,  77},
                                 {138, 110,  79},
                                 {140, 112,  81},
                                 {142, 114,  83},
                                 {144, 116,  85},
                                 {146, 118,  87},
                                 {148, 120,  89},
                                 {150, 122,  91},
                                 {152, 124,  93},
                                 {154, 126,  95},
                                 {156, 128,  97},
                                 {158, 130,  99},
                                 {160, 132, 101},
                                 {162, 134, 103},
                                 {164, 136, 105},
                                 {166, 138, 107},
                                 {168, 140, 109},
                                 {170, 142, 111},
                                 {172, 144, 113},
                                 {174, 146, 115},
                                 {176, 148, 117},
                                 {178, 150, 119},
                                 {180, 152, 121},
                                 {182, 154, 123},
                                 {184, 156, 125},
                                 {186, 158, 127},
                                 {188, 160, 129},
                                 {190, 162, 131},
                                 {192, 164, 133},
                                 {194, 166, 135},
                                 {196, 168, 137},
                                 {198, 170, 139},
                                 {200, 172, 141},
                                 {202, 174, 143},
                                 {204, 176, 145},
                                 {206, 178, 147},
                                 {208, 180, 149},
                                 {210, 182, 151},
                                 {212, 184, 153},
                                 {214, 186, 155},
                                 {216, 188, 157},
                                 {218, 190, 159},
                                 {220, 192, 161},
                                 {222, 194, 163},
                                 {224, 196, 165},
                                 {226, 198, 167},
                                 {228, 200, 169},
                                 {230, 202, 171},
                                 {232, 204, 173},
                                 {234, 206, 175},
                                 {236, 208, 177},
                                 {238, 210, 179},
                                 {240, 212, 181},
                                 {242, 214, 183},
                                 {244, 216, 185},
                                 {246, 218, 187},
                                 {248, 220, 189},
                                 {250, 222, 191},
                                 {252, 224, 193},
                                 {254, 226, 195},
                                 {255, 228, 197},
                                 {255, 230, 199},
                                 {255, 232, 201},
                                 {255, 234, 203},
                                 {255, 236, 205},
                                 {255, 238, 207},
                                 {255, 240, 209},
                                 {255, 242, 211},
                                 {255, 244, 213},
                                 {255, 246, 215},
                                 {255, 248, 217},
                                 {255, 250, 219},
                                 {255, 252, 221},
                                 {255, 254, 223},
                                 {255, 255, 225},
                                 {255, 255, 227},
                                 {255, 255, 229},
                                 {255, 255, 231},
                                 {255, 255, 233},
                                 {255, 255, 235},
                                 {255, 255, 237},
                                 {255, 255, 239},
                                 {255, 255, 241},
                                 {255, 255, 243},
                                 {255, 255, 245},
                                 {255, 255, 247},
                                 {255, 255, 249},
                                 {255, 255, 251},
                                 {255, 255, 253},
                                 {255, 255, 255},
                                 {255, 255, 255},
                                 {255, 255, 255}};

#define FLUX_POWER_UP_LOOPS 
#define FLUX_TIME (((now - start) * FLUX_ON_COUNT) / (FLUX_FRAME_MS * FLUX_POWER_UP_LOOPS))

// END SECTION GENERATED BY flux_capacitor.py
////////////////////////////////////////////////////////////////

#define KNIFE_SW_PIN 3

unsigned long now;
unsigned long switch_start;
unsigned long lastFire;

/* Converts a color from HSV to RGB.
 * h is hue, as a number between 0 and 360.
 * s is the saturation, as a number between 0 and 255.
 * v is the value, as a number between 0 and 255. */
rgb_color hsvToRgb(uint16_t h, uint8_t s, uint8_t v)
{
    uint8_t f = (h % 60) * 255 / 60;
    uint8_t p = (255 - s) * (uint16_t)v / 255;
    uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t r = 0, g = 0, b = 0;
    switch((h / 60) % 6){
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
    }
    return rgb_color(r, g, b);
}

inline uint8_t get_curve(unsigned int i) {
    return curve[((now * frequencies[i]) / F_DEN) % CURVE_LENGTH];
}

void setup()
{
    lastFire = 0;
    
    pinMode(KNIFE_SW_PIN, INPUT_PULL_UP);
    
    // zero all colors
    for (int i = 0; i < FULL_LED_COUNT; i++) {
      colors[i] = rgb_color(0, 0, 0);
    }
    ledPort.write(colors, FULL_LED_COUNT, brightness);

    now = millis();
    switch_start = now;
}

void loop()
{
    now = millis();
    if (!digitalRead(KNIFE_PIN_SW)) {
        switch_start = now;
    }
    
    // points
    for (unsigned int i = 0; i < POINT_LED_COUNT; i++) {
        point_colors[i] = rgb_color(get_curve(i), 0, 0);
    }
    
    // flux
    unsigned int = FLUX_TIME;
    switch(FLUX_STEP)
    {
        case 0:
            flux_colors[ 0] = flux_on[FLUX_TIME];
            flux_colors[ 8] = flux_on[FLUX_TIME];
            flux_colors[12] = flux_on[FLUX_TIME];

            flux_colors[ 1] = flux_off;
            flux_colors[ 7] = flux_off;
            flux_colors[11] = flux_off;

            flux_colors[ 2] = flux_off;
            flux_colors[ 6] = flux_off;
            flux_colors[10] = flux_off;

            flux_colors[ 3] = flux_off;
            flux_colors[ 5] = flux_off;
            flux_colors[ 9] = flux_off;
            break;
        case 1:
            flux_colors[ 0] = flux_off;
            flux_colors[ 8] = flux_off;
            flux_colors[12] = flux_off;

            flux_colors[ 1] = flux_on[FLUX_TIME];
            flux_colors[ 7] = flux_on[FLUX_TIME];
            flux_colors[11] = flux_on[FLUX_TIME];

            flux_colors[ 2] = flux_off;
            flux_colors[ 6] = flux_off;
            flux_colors[10] = flux_off;

            flux_colors[ 3] = flux_off;
            flux_colors[ 5] = flux_off;
            flux_colors[ 9] = flux_off;
            break;
        case 2:
            flux_colors[ 0] = flux_off;
            flux_colors[ 8] = flux_off;
            flux_colors[12] = flux_off;

            flux_colors[ 1] = flux_off;
            flux_colors[ 7] = flux_off;
            flux_colors[11] = flux_off;

            flux_colors[ 2] = flux_on[FLUX_TIME];
            flux_colors[ 6] = flux_on[FLUX_TIME];
            flux_colors[10] = flux_on[FLUX_TIME];

            flux_colors[ 3] = flux_off;
            flux_colors[ 5] = flux_off;
            flux_colors[ 9] = flux_off;
            break;
        default:
            flux_colors[ 0] = flux_off;
            flux_colors[ 8] = flux_off;
            flux_colors[12] = flux_off;

            flux_colors[ 1] = flux_off;
            flux_colors[ 7] = flux_off;
            flux_colors[11] = flux_off;

            flux_colors[ 2] = flux_off;
            flux_colors[ 6] = flux_off;
            flux_colors[10] = flux_off;

            flux_colors[ 3] = flux_on[FLUX_TIME];
            flux_colors[ 5] = flux_on[FLUX_TIME];
            flux_colors[ 9] = flux_on[FLUX_TIME];
            break;
    }
    // middle
    flux_colors[4] = flux_on_mid[FLUX_TIME]
    
    // fire
    if (now - lastFire > 100) {
        for (unsigned int i = 0; i < 20; i++) {
            fire_colors[random(FIRE_LED_COUNT)] = blackbody[GET_BLACKBODY_INDEX];
        }
        lastFire = now;
    }
    ledPort.write(colors, FULL_LED_COUNT, brightness);
}
