#ifndef BRL_H
# define BRL_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdint.h>

# define BRL_FORMAT_ELF			0x464c457f

// Elf filetype format
# define BRL_ELF_FILETYPE_NONE	0
# define BRL_ELF_FILETYPE_REPO	1
# define BRL_ELF_FILETYPE_EXEC	2
# define BRL_ELF_FILETYPE_OBJ	3
# define BRL_ELF_FILETYPE_CORE	4

// Elf target machine
# define BRL_ELF_TARGET_NONE			0
# define BRL_ELF_TARGET_SPARC			2
# define BRL_ELF_TARGET_INTEL_80386		3
# define BRL_ELF_TARGET_MOTOROLA_68000	4
# define BRL_ELF_TARGET_INTEL_I860		7
# define BRL_ELF_TARGET_MISP_I			8
# define BRL_ELF_TARGET_INTEL_I960		19
# define BRL_ELF_TARGET_POWERPC			20
# define BRL_ELF_TARGET_ARM				40
# define BRL_ELF_TARGET_INTEL_IA64		50
# define BRL_ELF_TARGET_X64				62


typedef struct 					s_brl_elf_head
{
	char						arch;
	char						endian;
	char						header_version;
	char						abi;
	char						unused[5];
	char						length;
	char						type;
	char						target;
	char						version;
}	__attribute__((packed))		t_brl_elf_head;

typedef struct 					s_brl_elf_32
{
	uint32_t					entry_point;
	uint32_t					prog_head;
	uint32_t					areas_head;
	uint32_t					flags;
	uint16_t					elf_head_size;
	uint16_t					prog_head_entry_size;
	uint16_t					prog_head_count;
	uint16_t					areas_head_entry_size;
	uint16_t					areas_head_count;
	uint16_t					names_entry_in_area;
}	__attribute__((packed))		t_brl_elf_32;

typedef struct 					s_brl_elf_64
{
	uint64_t					entry_point;
	uint64_t					prog_head;
	uint64_t					areas_head;
	uint32_t					flags;
	uint16_t					elf_head_size;
	uint16_t					prog_head_entry_size;
	uint16_t					prog_head_count;
	uint16_t					areas_head_entry_size;
	uint16_t					areas_head_count;
	uint16_t					names_entry_in_area;
}	__attribute__((packed))		t_brl_elf_64;

typedef struct		s_brl_binary
{

	FILE			*fd;
	uint32_t		magic;
	void			*header;
	void			*header_more;

}					t_brl_binary;

t_brl_binary		*brl_open(const char *path);
bool				brl_is_elf(t_brl_binary *bin);
bool				brl_is_64bit(t_brl_binary *bin);
bool				brl_is_msb_endian(t_brl_binary *bin);
void				brl_close(t_brl_binary *bin);

#endif