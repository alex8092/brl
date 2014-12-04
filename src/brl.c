#include "brl.h"

static inline bool	_intern_brl_is_elf(t_brl_binary *bin)
{
	return (bin->magic == BRL_FORMAT_ELF);
}

static inline bool	_intern_brl_elf_is_64(t_brl_binary *bin)
{
	return (((t_brl_elf_head *)bin->header)->arch == 2);
}

static inline bool	_intern_brl_elf_is_msb_endian(t_brl_binary *bin)
{
	return (((t_brl_elf_head *)bin->header)->endian == 2);
}

static void			_brl_read_elf_header(t_brl_binary *bin)
{
	size_t	more_len = 0;

	bin->header = malloc(sizeof(t_brl_elf_head));
	if (bin->header)
	{
		fread(bin->header, sizeof(t_brl_elf_head), 1, bin->fd);
		if (_intern_brl_elf_is_64(bin))
			more_len = sizeof(t_brl_elf_64);
		else
			more_len = sizeof(t_brl_elf_32);
		bin->header_more = malloc(more_len);
		fread(bin->header_more, more_len, 1, bin->fd);
		if (_intern_brl_elf_is_64(bin))
			printf("entry point : %lx\n", ((t_brl_elf_64 *)bin->header_more)->entry_point);
		else
			printf("entry point : %x\n", ((t_brl_elf_32 *)bin->header_more)->entry_point);
	}
}

static void			_brl_read_magic(t_brl_binary *bin)
{
	fread(&bin->magic, sizeof(bin->magic), 1, bin->fd);
	if (_intern_brl_is_elf(bin))
		_brl_read_elf_header(bin);
}

t_brl_binary		*brl_open(const char *path)
{
	t_brl_binary	*bin;

	bin = (t_brl_binary *)malloc(sizeof(*bin));
	if (bin)
	{
		bin->fd = fopen(path, "r");
		if (!bin->fd) {
			brl_close(bin);
			bin = NULL;
		}
		else
			_brl_read_magic(bin);
	}
	return (bin);
}

void				brl_close(t_brl_binary *bin)
{
	if (bin)
	{
		if (bin->fd)
			fclose(bin->fd);
		if (bin->header)
			free(bin->header);
		free(bin);
	}
}

bool				brl_is_elf(t_brl_binary *bin)
{
	return (_intern_brl_is_elf(bin));
}

bool				brl_is_64bit(t_brl_binary *bin)
{
	if (bin->magic == BRL_FORMAT_ELF)
		return _intern_brl_elf_is_64(bin);
	return (false);
}

bool				brl_is_msb_endian(t_brl_binary *bin)
{
	if (bin->magic == BRL_FORMAT_ELF)
		return _intern_brl_elf_is_msb_endian(bin);
	return (false);
}