
#include <iostream>
#include <getopt.h>
#include <stdlib.h>

#include "graph.h"
#include "test1.h"

#define no_argument 0
#define required_argument 1 
#define optional_argument 2

//using namespace std;

graph* g;

void ontology_lubm();

int main(int argc, char* argv[])
{
	const struct option longopts[] =
	{
		{"version",   no_argument,        0, 'v'},
		{"help",      no_argument,        0, 'h'},
		{"idir",      required_argument,  0, 'i'},
		{"odir",      required_argument,  0, 'o'},
		{"convert",   required_argument,  0, 'c'},
		{"qfile",     required_argument,  0, 'q'},
		{0,			  0,				  0,  0},
	};

	int o;
	int index = 0;
	string idir, odir;
    string queryfile;
    int convert = -1;
    g = new graph; 
	while ((o = getopt_long(argc, argv, "i:c:o:q:vh", longopts, &index)) != -1) {
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
			case 'o':
				odir = optarg;
				cout << "output dir = " << odir << endl;
				break;
            case 'q':
                queryfile = optarg;
               break; 
			default:
                break;
		}
	}

    switch (convert) {
        case 0:
            ontology_lubm();
            g->prep_graph(idir, odir);
            break;
        default:
            break;
    }

    test1();
    lubm_1();
    return 0;
}
