

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include "parse_opt.h"

#undef NDEBUG
#include <assert.h>



//float rand_gauss (){
//  // media 1 range 0,2
//  assert ( sizeof ( int ) >= 4 );
//  float r = 0;
//  r += rand();
//  r += rand();
//  r += rand();
//  r += rand();
//  return r / (2.0*RAND_MAX);
//}

void MyAudioCallback ( void * userdata, Uint8 * stream, int len_bytes ){

    SDL_AudioSpec * have = (SDL_AudioSpec*) userdata;

    static int delay = 0;
    static float s = 0;
    static float c = 1;


    short * frame = (short*)stream;
    int len_frames = len_bytes / sizeof(*frame);
    for (; len_frames; len_frames --, frame ++ ){
        
        // "sleep" some time
        if( delay -- < 0 ){
            // set next delay
//            float r = rand_gauss ();
            float r = rand () * (2.0/opt.pps) / RAND_MAX;
//            fprintf( stderr, "r %f\n", r );
            delay = have->freq * r;  // sec
//            fprintf ( stderr, "%d\n", delay );
            // gen pulse
            c = 1;
            s = 0;
        }

        *frame = c * 32767;

        // reinsch/magic circle osc
        c = (c - s * 0.2) * opt.decay;  // pulse decay
        s += c;
    }
}



int main ( int argc, char * argv [] ){ 

    if( ! parse_opt ( argc, argv )) return 1;
    
    assert( 0 == SDL_Init( SDL_INIT_AUDIO ));
    atexit(SDL_Quit);
    
        
    SDL_AudioSpec want, have;
    SDL_AudioDeviceID dev;

    SDL_zero(want);
    want.freq     = 44100;
    want.format   = AUDIO_S16;
    want.channels = 1;
    want.samples  = 1024;
    want.callback = MyAudioCallback;
    want.userdata = &have;

    assert( dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0 ));
    
    
    SDL_PauseAudioDevice(dev, 0);  // start audio playing.
    getchar();
    SDL_CloseAudioDevice(dev);

    return 0;
}


