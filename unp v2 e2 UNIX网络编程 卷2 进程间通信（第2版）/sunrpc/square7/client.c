#include	"unpipc.h"
#include	"square.h"

int
main(int argc, char **argv)
{
	CLIENT		*cl;
	square_in	in;
	square_out	out;

	if (argc != 4)
		err_quit("usage: client <hostname> <integer-value> <protocol>");

	cl = Clnt_create(argv[1], SQUARE_PROG, SQUARE_VERS, argv[3]);

	in.arg1 = atol(argv[2]);
	if (squareproc_2(&in, &out, cl) != RPC_SUCCESS)
		err_quit("%s", clnt_sperror(cl, argv[1]));

	printf("result: %ld\n", out.res1);
	exit(0);
}
