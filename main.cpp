
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
void fill_lubm_inference_type();

int main(int argc, char* argv[])
{
	const struct option longopts[] =
	{
		{"version",   no_argument,        0, 'v'},
		{"help",      no_argument,        0, 'h'},
		{"idir",      required_argument,  0, 'i'},
		{"odir",      required_argument,  0, 'o'},
		{"convert",   required_argument,  0, 'c'},
		{"job",       required_argument,  0, 'j'},
		{"qfile",     required_argument,  0, 'q'},
        {"typefile",  required_argument,  0, 't'},
		{0,			  0,				  0,  0},
	};

	int o;
	int index = 0;
	string typefile, idir, odir;
    string queryfile;
    int convert = -1;
    int job = 0;
    g = new graph; 
	while ((o = getopt_long(argc, argv, "i:c:j:o:q:t:vh", longopts, &index)) != -1) {
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
            case 'j':
                job = atoi(optarg);
				break;
			case 'o':
				odir = optarg;
				cout << "output dir = " << odir << endl;
				break;
            case 'q':
                queryfile = optarg;
                break;
            case 't':
                typefile = optarg;
                break;
			default:
                break;
		}
	}
    g->set_odir(odir);
    switch (convert) {
        case 0:
        lubm_test0(typefile, idir, odir);
            break;
        case 1:
        lubm_test1(typefile, idir, odir);
            break;
        case 2:
        lubm_test2(odir);
            break;
        case 3:
            plain_test(idir, odir, job);
            break;
        case 10:
            ldbc_test0(typefile, idir, odir);
            break;
        case 12:
            ldbc_test2(odir);
            break;
        case 20:
            darshan_test0(typefile, idir, odir);
            break;
        default:
            break;
    }

    return 0;
}
