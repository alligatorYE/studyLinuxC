#include	"unpipc.h"

int
main(int argc, char **argv)
{
	sem_t	*sem;
	int		val;

	if (argc != 2)
		err_quit("usage: semgetvalue <name>");

	sem = Sem_open(argv[1], 0);
	Sem_getvalue(sem, &val);
	printf("value = %d\n", val);

	exit(0);
}
