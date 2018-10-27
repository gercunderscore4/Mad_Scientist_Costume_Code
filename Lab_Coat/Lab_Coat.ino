// Create an object for writing to the LED strip.
#include <APA102.h>
#define LED_DATA_PIN 11
#define LED_CLOCK_PIN 12
APA102<LED_DATA_PIN, LED_CLOCK_PIN> ledPort;

#define BRIGHTNESS 10 //31

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

// timing
unsigned long now;

// switches
#define KNIFE_SW_PIN 3
#define TOGGLE_1_SW_PIN 4
#define TOGGLE_2_SW_PIN 5

bool knife_state;
bool prev_knife_state;
unsigned long knife_start;
unsigned long knife_stop;
bool toggle_1_state;
bool toggle_2_state;

////////////////////////////////////////////////////////////////
// BEGIN SECTION GENERATED BY blackbody_color_scale.py

// http://www.vendian.org/mncharity/dir3/blackbody/UnstableURLs/bbr_color.html

#define FIRE_PERIOD 10
#define FIRE_CHANGE_COUNT 10

#define BLACKBODY_COUNT 52
// the following makes a dreceasing random distribution
#define GET_BLACKBODY_INDEX ((random(73) * random(73)) / 100) % BLACKBODY_COUNT

const rgb_color blackbody[] = {{3,0,0},{12,0,0},{21,0,0},{30,0,0},{39,0,0},{48,0,0},{57,0,0},{66,0,0},{75,0,0},{84,0,0},{93,0,0},{102,0,0},{111,0,0},{120,0,0},{129,0,0},{138,0,0},{147,0,0},{156,0,0},{165,0,0},{174,0,0},{183,0,0},{192,0,0},{201,0,0},{210,6,0},{219,15,0},{228,24,0},{237,33,0},{246,42,0},{255,51,0},{255,51,0},{255,69,0},{255,82,0},{255,93,0},{255,102,0},{255,111,0},{255,118,0},{255,124,0},{255,130,0},{255,135,0},{255,141,11},{255,146,29},{255,152,41},{255,157,51},{255,162,60},{255,166,69},{255,170,77},{255,174,84},{255,178,91},{255,182,98},{255,185,105},{255,189,111},{255,192,118}};

unsigned long last_fire;

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
#define FLUX_LIGHTS 4
#define FLUX_STEP ((now / FLUX_FRAME_MS) % FLUX_LIGHTS)
#define FLUX_ON_COUNT 26
const rgb_color flux_off =  {  0,   0,   0};
const rgb_color flux_on[] = {{64,36,5},{74,46,15},{84,56,25},{94,66,35},{104,76,45},{114,86,55},{124,96,65},{134,106,75},{144,116,85},{154,126,95},{164,136,105},{174,146,115},{184,156,125},{194,166,135},{204,176,145},{214,186,155},{224,196,165},{234,206,175},{244,216,185},{254,226,195},{255,236,205},{255,246,215},{255,255,225},{255,255,235},{255,255,245},{255,255,255}};
const rgb_color flux_on_mid[] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{68,40,9},{88,60,29},{108,80,49},{128,100,69},{148,120,89},{168,140,109},{188,160,129},{208,180,149},{228,200,169},{248,220,189},{255,240,209},{255,255,229},{255,255,249}};

#define FLUX_POWER_UP_LOOPS 7

inline unsigned int flux_time (void) {
    return min(FLUX_ON_COUNT - 1, ((now - knife_start) * FLUX_ON_COUNT) / (FLUX_LIGHTS * FLUX_FRAME_MS * FLUX_POWER_UP_LOOPS));
}

// END SECTION GENERATED BY flux_capacitor.py
////////////////////////////////////////////////////////////////

/*
 * PURPOSE:
 *     Set Flux Capactior LEDS
 * GLOBALS:
 *     now
 *     start_switch
 * INPUTS:
 *     (none)
 * OUTPUTS:
 *     (none)
 */
void set_flux_LEDs (void) {
    if (toggle_2_state) {
        // determine color
        unsigned int flux_index = knife_state? flux_time() : 0;
        rgb_color flux_color = flux_on[flux_index];
    
        // middle
        flux_colors[4] = flux_on_mid[flux_index];
        
        // lines
        switch(FLUX_STEP)
        {
            case 0:
                flux_colors[ 0] = flux_color;
                flux_colors[ 8] = flux_color;
                flux_colors[12] = flux_color;
    
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
    
                flux_colors[ 1] = flux_color;
                flux_colors[ 7] = flux_color;
                flux_colors[11] = flux_color;
    
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
    
                flux_colors[ 2] = flux_color;
                flux_colors[ 6] = flux_color;
                flux_colors[10] = flux_color;
    
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
    
                flux_colors[ 3] = flux_color;
                flux_colors[ 5] = flux_color;
                flux_colors[ 9] = flux_color;
                break;
        }
    } else {
        for (unsigned int i = 0; i < FLUX_LED_COUNT; i++) {
            flux_colors[i] = rgb_color(0, 0, 0);
        }
    }
}

/*
 * PURPOSE:
 *     Get color curve location for a given point LED
 * GLOBALS:
 *     now
 * INPUTS:
 *     (none)
 * OUTPUTS:
 *     (none)
 */
inline uint8_t get_curve(unsigned int i) {
    return toggle_1_state ? curve[((now * frequencies[i]) / F_DEN) % CURVE_LENGTH] : 0;
}

#define RAMP_FREQ 1

inline uint8_t get_ramp_up (void) {
    return curve[min(CURVE_LENGTH / 2, ((now - knife_start) * RAMP_FREQ * CURVE_LENGTH) / (MS_IN_S))];
}

inline uint8_t get_ramp_down (void) {
    return curve[min(CURVE_LENGTH / 2, ((now - knife_stop) * RAMP_FREQ * CURVE_LENGTH) / (MS_IN_S)) + (CURVE_LENGTH / 2)];
}

void set_point_LEDs (void) {
    uint8_t ramp = knife_state ? get_ramp_up() : get_ramp_down();
    for (unsigned int i = 0; i < POINT_LED_COUNT; i++) {
        point_colors[i] = rgb_color(max(ramp, get_curve(i)), 0, 0);
    }
}

void set_fire_LEDs (void) {
    if (knife_state && ((now - knife_start) > (MS_IN_S / (RAMP_FREQ * 2)))) {
        if (now - last_fire > FIRE_PERIOD) {
            for (unsigned int i = 0; i < FIRE_CHANGE_COUNT; i++) {
                fire_colors[random(FIRE_LED_COUNT)] = blackbody[GET_BLACKBODY_INDEX];
            }
            last_fire = now;
        }
    } else {
        for (unsigned int i = 0; i < FIRE_LED_COUNT; i++) {
            fire_colors[i] = rgb_color(0, 0, 0);
        }
    }
}

void setup() {
    Serial.begin(9600); // debug
    pinMode(LED_BUILTIN, OUTPUT); // debug
    digitalWrite(LED_BUILTIN, LOW); //debug
    
    now = 0;

    // fire timing
    last_fire = 0;
    
    // knife siwtch
    pinMode(KNIFE_SW_PIN, INPUT_PULLUP);
    knife_state = false;
    prev_knife_state = false;
    knife_start = 0;
    knife_stop = 0;
    
    // toggle switches
    pinMode(TOGGLE_1_SW_PIN, INPUT_PULLUP);
    toggle_1_state = false;
    pinMode(TOGGLE_2_SW_PIN, INPUT_PULLUP);
    toggle_2_state = false;
    
    // zero all colors
    for (int i = 0; i < FULL_LED_COUNT; i++) {
      colors[i] = rgb_color(0, 0, 0);
    }
    ledPort.write(colors, FULL_LED_COUNT, BRIGHTNESS);
}

void loop() {
    now = millis();
    
    // knife switch
    prev_knife_state = knife_state;
    knife_state = !digitalRead(KNIFE_SW_PIN); // invert reading
    if (knife_state != prev_knife_state) {
        if (knife_state) {
            knife_start = now;
            //digitalWrite(LED_BUILTIN, HIGH); // debug
        } else {
            knife_stop = now;
            //digitalWrite(LED_BUILTIN, LOW); //debug
        }
    }
    
    // toggle switches
    toggle_1_state = !digitalRead(TOGGLE_1_SW_PIN); // invert reading
    toggle_2_state = !digitalRead(TOGGLE_2_SW_PIN); // invert reading
    digitalWrite(LED_BUILTIN, toggle_2_state);
    
    // flux capacitor
    set_flux_LEDs();

    // points
    set_point_LEDs();
    
    // fire
    set_fire_LEDs();
    
    // draw
    ledPort.write(colors, FULL_LED_COUNT, BRIGHTNESS);
}
