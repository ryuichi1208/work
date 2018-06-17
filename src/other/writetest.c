#include <fcntl.h>
#include <getopt.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "test.h"

#define BLOCKSIZE (1024*1024)
#define FILE_OUT    "fileout"
#define FILE_MODE   0644
#define MAX_FILENAME_LEN 1024

int Verbosity = 0;
int DefaultSeed = 0;
char Filename[MAX_FILENAME_LEN] = FILE_OUT;
off_t NumBlocks = 1;
char *TCID = "writetest";
int TST_TOTAL = 2;

void buf_init(void)
{
	static int seed = 0;
	if (seed == 0)
		seed = DefaultSeed;
	srand(seed);
}

void buf_fill(uint8_t * buf)
{
	int i;
	for (i = 0; i < BLOCKSIZE; i++) {
		*buf = (rand() & 0xff);
		buf++;
	}
}

int write_file(off_t num_blocks, const char *filename)
{
	int fd;
	int ret = 0;
	off_t block;
	uint8_t buf[BLOCKSIZE];

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC | O_LARGEFILE,
		  FILE_MODE);
	if (fd < 0) {
		perror(TCID);
		return (-1);
	}
	for (block = 0; block < num_blocks; block++) {
		int rv;
		if (Verbosity > 2)
			tst_resm(TINFO, "Block: %lld/%lld  (%3lld%%)\r",
				 (long long int)block,
				 (long long int)num_blocks,
				 (long long int)(block * 100 / num_blocks));
		buf_fill(buf);
		rv = write(fd, buf, BLOCKSIZE);
		if (rv != BLOCKSIZE) {
			ret = -1;
			break;
		}
	}
	if (Verbosity > 2)
		tst_resm(TINFO, "Block: %lld/%lld  (%3lld%%)\r",
			 (long long int)block, (long long int)num_blocks,
			 (long long int)(block * 100 / num_blocks));
	close(fd);
	return (ret);
}

int verify_file(off_t num_blocks, const char *filename)
{
	int fd;
	int ret = 0;
	off_t block;
	uint8_t buf_actual[BLOCKSIZE];
	char buf_read[BLOCKSIZE];

	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		perror(TCID);
		return (-1);
	}
	for (block = 0; block < num_blocks; block++) {
		int rv;
		int n;
		if (Verbosity > 2)
			tst_resm(TINFO, "Block: %lld/%lld  (%3lld%%)\r",
				 (long long int)block,
				 (long long int)num_blocks,
				 (long long int)(block * 100 / num_blocks));
		buf_fill(buf_actual);
		rv = read(fd, buf_read, BLOCKSIZE);
		if (rv != BLOCKSIZE) {
			ret = -1;
			break;
		}
		for (n = 0; n < BLOCKSIZE; n++) {
			int ba, br;
			ba = buf_actual[n] & 0xff;
			br = buf_read[n] & 0xff;
			if (ba != br) {
				if (Verbosity > 2)
					tst_resm(TINFO,
						 "Mismatch: block=%lld +%d bytes offset=%lld read: %02xh actual: %02xh\n",
						 (long long int)block, n,
						 (long long
						  int)((block * BLOCKSIZE) + n),
						 br, ba);
				ret++;
			}
		}
	}
	close(fd);
	if (Verbosity > 2)
		tst_resm(TINFO, "Block: %lld/%lld  (%3lld%%)\r",
			 (long long int)block, (long long int)num_blocks,
			 (long long int)(block * 100 / num_blocks));
	return (ret);
}

void usage(void)
{
	printf("%s [-v] [-b blocks] [-s seed] [-o filename]\n", TCID);
	printf("\n"
	       "   -v          - increase verbosity level\n"
	       "   blocks      - number of blocks to write\n"
	       "   seed        - seed to use (0 to use timestamp)\n"
	       "   filename    - name of output file\n");
}

void parse_args(int argc, char **argv)
{
	int c;

	while (1) {
		int option_index = 0;
		static struct option long_options[] = {
			{"blocks", 1, 0, 'b'},
			{"out", 1, 0, 'o'},
			{"seed", 1, 0, 's'},
			{"verbose", 0, 0, 'v'},
			{"help", 0, 0, 'h'},
			{0, 0, 0, 0}
		};
		c = getopt_long(argc, argv, "hvb:o:s:", long_options,
				&option_index);
		if (c == -1)
			break;
		switch (c) {
		case 'b':
			NumBlocks = strtoul(optarg, NULL, 0);
			break;
		case 'o':
			strncpy(Filename, optarg, MAX_FILENAME_LEN);
			break;
		case 's':
			DefaultSeed = strtoul(optarg, NULL, 0);
			break;
		case 'v':
			Verbosity++;
			break;
		case 'h':
		default:
			usage();
			exit(-1);
		}
	}
}

int main(int argc, char *argv[])
{
	int rv;

	DefaultSeed = time(NULL);
	parse_args(argc, argv);
	buf_init();
	rv = write_file(NumBlocks, Filename);
	if (rv == 0) {
		printf("Write: Success");
	} else {
		printf("Write: Failure");
	}

	buf_init();
	rv = verify_file(NumBlocks, Filename);
	if (rv == 0) {
		printf("Verify: Success\n");
	} else {
		printf("Verify: Failure");
		printft("Total mismatches: %d bytes\n", rv);
	}

	return 0;
}
