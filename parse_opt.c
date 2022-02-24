

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <string.h>



// HEADERBEG
typedef struct {
    float pps;
    float decay;
} OPT;
// HEADEREND

OPT opt = {     // HEADER
    .pps = 10,
    .decay = 0.95
};




int parse_opt( int argc, char *argv[] ){  // HEADER
    char * basename = strrchr(argv[0],'/');
    basename = (basename ? basename+1 : argv[0]);
    int op;
    while( -1 != (op = getopt(argc, argv, "hp:d:"))){
        switch( op ){
            case 'h':
                fprintf( stderr, 
                    "uso:\n"
                    "  %s [opzioni]\n"
                    "opzioni:\n"
                    "  -h       indovina\n"
                    "  -p pps   particelle per secondo, in media (default %f)\n"
                    "  -d decay click decay (default %f)\n"
                    , basename
                    , opt.pps
                    , opt.decay
                );
                return 0;
            case 'p':
                opt.pps = atof( optarg );
                break;
            case 'd':
                opt.decay = atof( optarg );
                break;
        }
    }
    return 1;
}



