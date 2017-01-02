
#include <iostream>
#include <getopt.h>
#include <stdlib.h>

#include "graph.h"

#define no_argument 0
#define required_argument 1 
#define optional_argument 2

using namespace std;

graph* g;

int main(int argc, char* argv[])
{
	const struct option longopts[] =
	{
		{"version",   no_argument,        0, 'v'},
		{"help",      no_argument,        0, 'h'},
		{"ifile",     required_argument,  0, 'i'},
		{"convert",   required_argument,  0, 'c'},

		{0,			  0,				  0,  0},
	};

	int o;
	int index = 0;
	string idir;
    int convert = -1;
    g = new graph; 
	while ((o = getopt_long(argc, argv, "i:c:vh", longopts, &index)) != -1) {
		switch(o) {
			case 'v':
				cout << "1.0" << endl;
				break;
			case 'h':
				cout << "Help coming soon" << endl;
				break;
			case 'i':
				idir = optarg;
				cout << "input dir = " << idir << endl;
				break;
            case 'c':
                convert = atoi(optarg);
				break;
			default:
                break;
		}
	}

    switch (convert) {
        case 0:
            g->prep_meta_nt(idir);
            break;
        default:
            break;
    }
    return 0;
}
