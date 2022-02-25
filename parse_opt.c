

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <string.h>



// HEADERBEG
typedef struct {
    float cpm;
    float decay;
} OPT;
// HEADEREND

OPT opt = {     // HEADER
    .cpm = 20,  // suona simile al fondo standard (nessuna relazione coi 0.2 µSv/h però)
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
                    "  -p cpm   conteggi/minuto, in media (default %f)\n"
                    "  -d decay click decay (default %f)\n"
                    , basename
                    , opt.cpm
                    , opt.decay
                );
                return 0;
            case 'p':
                opt.cpm = atof( optarg );
                break;
            case 'd':
                opt.decay = atof( optarg );
                break;
        }
    }
    return 1;
}



