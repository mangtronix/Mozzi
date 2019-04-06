#ifndef AUDIOCONFIGESP_H
#define AUDIOCONFIGESP_H

#if not (IS_ESP8266() || IS_ESP32())
#error This header should be included for ESP architecture, only
#endif

// AUDIO output modes. See README.md
#define PDM_VIA_I2S 1
#define PDM_VIA_SERIAL 2
#define EXTERNAL_DAC_VIA_I2S 3    // output via external DAC connected to I2S (PT8211 or similar)
#define INTERNAL_DAC 4            // output via built-in DAC of ESP32

//******* BEGIN: These are the defines you may want to change. Best not to touch anything outside this range. ************/
#if IS_ESP8266()
#define ESP_AUDIO_OUT_MODE PDM_VIA_SERIAL
#define PDM_RESOLUTION 2   // 1 corresponds to 32 PDM clocks per sample, 2 corresponds to 64 PDM clocks, etc. (and at some level you're going hit the hardware limits)
#endif

#if IS_ESP32()
#define ESP_AUDIO_OUT_MODE INTERNAL_DAC
#define PDM_RESOLUTION 1
#endif
//******* END: These are the defines you may want to change. Best not to touch anything outside this range. ************/

#if (ESP_AUDIO_OUT_MODE == EXTERNAL_DAC_VIA_I2S)
#define PDM_RESOLUTION 1   // DO NOT CHANGE THIS VALUE! Not actually PDM coded, but this define is useful to keep code simple.
#endif

#if (AUDIO_MODE == HIFI)
#error HIFI mode is not available for this CPU architecture (but check ESP_AUDIO_OUT_MODE, and PDM_RESOLUTION)
#endif

#if (STEREO_HACK == true)
#if (ESP_AUDIO_OUT_MODE != EXTERNAL_DAC_VIA_I2S)
#error Stereo is not available for the configured audio output mode
#endif
#endif

#define AUDIO_BIAS ((uint16_t) 1<<(15))

#endif        //  #ifndef AUDIOCONFIGESP_H
