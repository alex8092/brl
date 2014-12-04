#include "brl.h"

int	main(int ac, char **av)
{
	t_brl_binary	*bin;

	if (ac != 2)
	{
		fprintf(stderr, "usage: %s <path_to_binary>\n", av[0]);
		return (1);
	}
	bin = brl_open(av[1]);
	if (bin)
	{
		if (brl_is_elf(bin))
			printf("format: elf\n");
		if (brl_is_64bit(bin))
			printf("format: 64bit\n");
		else
			printf("format: 32bit\n");
		if (brl_is_msb_endian(bin))
			printf("endian: msb\n");
		else
			printf("endian: lsb\n");
		brl_close(bin);
	}
	return (0);
}