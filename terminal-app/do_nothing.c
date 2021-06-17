#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int opt;
    char *filename = NULL;

    int i_flag = 0;
    int g_flag = 0;

    while ( (opt = getopt(argc, argv, "hi:g:")) != -1 ) {
        switch(opt) {
            case 'h':
                printf("\033[1;37mThis application does absolutely nothing.\n\n");
                printf("Available options:\n");
                printf("-i <file>\tDoes nothing with specified file. \n");
                printf("-g <file>\tDoes nothing with specified file, but in \033[0;32mgreen color\033[0;37m.\n");

                break;
            case 'i':
                filename = optarg;
                i_flag = 1;
                break;
            case 'g':
                filename = optarg;
                g_flag = 1;
                break;
            default:
                printf("Use -h to display help.\n");
                return 0;
        }
    }

    if (!i_flag && !g_flag) {
        printf("Use -h to display help.\n");
    }

    if ((i_flag || g_flag) && !filename) {
        printf("You must specify a destination file name.\n");
        return 1;
    }

    if (i_flag) {
        printf("Doing nothing with %s file...\n", filename);
        printf("Done.\n");
    }

    if (g_flag) {
        printf("\033[0;32mDoing nothing with %s file...\n", filename);
        printf("Done.\n");
    }

    return 0;

}
