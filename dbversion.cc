#include <db_cxx.h>
#include <stdio.h>

int main(int argc, char** argv) {
		char *version;
		int major, minor, patch;

		version = db_version( &major, &minor, &patch );
    fprintf(stdout, "#define LIBDB_VERSION %s\n", version);
    fprintf(stdout, "#define LIBDB_MAJOR %d\n", major);
    fprintf(stdout, "#define LIBDB_MINOR %d\n", minor);
    fprintf(stdout, "#define LIBDB_PATCH %d\n", patch);
    return 0;
}
