#pragma once

#include <stdint.h>

typedef uint32_t Elf32_Addr;
typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Off;
typedef int32_t  Elf32_Sword;
typedef uint32_t Elf32_Word;
typedef uint8_t  Elf32_Byte;

typedef uint64_t Elf64_Addr;
typedef uint16_t Elf64_Half;
typedef uint64_t Elf64_Off;
typedef int32_t  Elf64_Sword;
typedef uint32_t Elf64_Word;
typedef uint64_t Elf64_Xword;
typedef int64_t  Elf64_Sxword;
typedef uint8_t  Elf64_Byte;

enum {
	AT_NULL = 0,
	AT_PHDR = 3,
	AT_PHENT = 4,
	AT_PHNUM = 5,
	AT_PAGESZ = 6,
	AT_BASE = 7,
	AT_FLAGS = 8,
	AT_ENTRY = 9,
	AT_UID = 11,
	AT_EUID = 12,
	AT_GID = 13,
	AT_EGID  = 14,
	AT_CLKTCK = 17,
	AT_SECURE = 23,
	AT_RANDOM = 25
};

typedef struct {
	Elf32_Word a_type;
	Elf32_Word a_val;
} Elf32_auxv;

typedef struct {
	Elf64_Word a_type;
	Elf64_Word a_val;
} Elf64_auxv;

enum {
	ET_NONE = 0,
	ET_REL = 1,
	ET_EXEC = 2,
	ET_DYN = 3,
	ET_CORE = 4,
	ET_LOPROC = 0xff00,
	ET_HIPROC = 0xffff
};

enum {
	EM_NONE = 0,
	EM_X86_64 = 62,
	EM_RISCV = 243
};

enum {
	EV_NONE = 0,
	EV_CURRENT = 1
};

enum {
	EI_MAG0 = 0,
	EI_MAG1 = 1,
	EI_MAG2 = 2,
	EI_MAG3 = 3,
	EI_CLASS = 4,
	EI_DATA = 5,
	EI_VERSION = 6,
	EI_OSABI = 7,
	EI_ABIVERSION = 8,
	EI_PAD = 9,
	EI_NIDENT = 16
};

enum {
	ELFMAG0 = 0x7f,
	ELFMAG1 = 'E',
	ELFMAG2 = 'L',
	ELFMAG3 = 'F'
};

enum {
	ELFCLASSNONE = 0,
	ELFCLASS32 = 1,
	ELFCLASS64 = 2,
	ELFCLASS128 = 3
};

enum {
	ELFDATANONE = 0,
	ELFDATA2LSB = 1,
	ELFDATA2MSB = 2
};

enum {
	ELFOSABI_SYSV = 0,
	ELFOSABI_LINUX = 3,
	ELFOSABI_SOLARIS = 6,
	ELFOSABI_FREEBSD = 9
};

enum {
	ELFABIVERSION_NONE = 0
};

typedef struct {
	Elf32_Byte  e_ident[EI_NIDENT];
	Elf32_Half  e_type;
	Elf32_Half  e_machine;
	Elf32_Word  e_version;
	Elf32_Addr  e_entry;
	Elf32_Off   e_phoff;
	Elf32_Off   e_shoff;
	Elf32_Word  e_flags;
	Elf32_Half  e_ehsize;
	Elf32_Half  e_phentsize;
	Elf32_Half  e_phnum;
	Elf32_Half  e_shentsize;
	Elf32_Half  e_shnum;
	Elf32_Half  e_shstrndx;
} Elf32_Ehdr;

typedef struct {
	Elf64_Byte  e_ident[EI_NIDENT];
	Elf64_Half  e_type;
	Elf64_Half  e_machine;
	Elf64_Word  e_version;
	Elf64_Addr  e_entry;
	Elf64_Off   e_phoff;
	Elf64_Off   e_shoff;
	Elf64_Word  e_flags;
	Elf64_Half  e_ehsize;
	Elf64_Half  e_phentsize;
	Elf64_Half  e_phnum;
	Elf64_Half  e_shentsize;
	Elf64_Half  e_shnum;
	Elf64_Half  e_shstrndx;
} Elf64_Ehdr;

enum {
	PT_NULL = 0,
	PT_LOAD = 1,
	PT_DYNAMIC = 2,
	PT_INTERP = 3,
	PT_NOTE = 4,
	PT_SHLIB = 5,
	PT_PHDR = 6,
	PT_TLS = 7,
	PT_LOOS = 0x60000000,
	PT_GNU_EH_FRAME = 0x6474e550,
	PT_GNU_STACK = 0x6474e551,
	PT_GNU_RELRO = 0x6474e552,
	PT_HIOS = 0x6fffffff,
	PT_LOPROC = 0x70000000,
	PT_HIPROC = 0x7fffffff
};

enum {
	PF_X = 0x1,
	PF_W = 0x2,
	PF_R = 0x4,
	PF_MASKOS = 0x00FF0000,
	PF_MASKPROC = 0xFF000000,
};

typedef struct {
	Elf32_Word  p_type;
	Elf32_Off   p_offset;
	Elf32_Addr  p_vaddr;
	Elf32_Addr  p_paddr;
	Elf32_Word  p_filesz;
	Elf32_Word  p_memsz;
	Elf32_Word  p_flags;
	Elf32_Word  p_align;
} Elf32_Phdr;

typedef struct {
	Elf64_Word  p_type;
	Elf64_Word  p_flags;
	Elf64_Off   p_offset;
	Elf64_Addr  p_vaddr;
	Elf64_Addr  p_paddr;
	Elf64_Xword p_filesz;
	Elf64_Xword p_memsz;
	Elf64_Xword p_align;
} Elf64_Phdr;

enum {
	SHN_UNDEF = 0,
	SHN_LOPROC = 0xff00,
	SHN_HIPROC = 0xff1f,
	SHN_LOOS = 0xff20,
	SHN_HIOS = 0xff3f,
	SHN_ABS = 0xfff1,
	SHN_COMMON = 0xfff2,
	SHN_XINDEX = 0xffff,
	SHN_HIRESERVE = 0xffff,
};

enum {
	SHT_NULL = 0,
	SHT_PROGBITS = 1,
	SHT_SYMTAB = 2,
	SHT_STRTAB = 3,
	SHT_RELA = 4,
	SHT_HASH = 5,
	SHT_DYNAMIC = 6,
	SHT_NOTE = 7,
	SHT_NOBITS = 8,
	SHT_REL = 9,
	SHT_SHLIB = 10,
	SHT_DYNSYM = 11,
	SHT_INIT_ARRAY = 14,
	SHT_FINI_ARRAY = 15,
	SHT_PREINIT_ARRAY = 16,
	SHT_GROUP = 17,
	SHT_SYMTAB_SHNDX = 18,
	SHT_LOOS = 0x60000000,
	SHT_GNU_VERDEF = 0x6ffffffd,
	SHT_GNU_VERNEED = 0x6ffffffe,
	SHT_GNU_VERSYM = 0x6fffffff,
	SHT_HIOS = 0x6fffffff,
	SHT_LOPROC = 0x70000000,
	SHT_HIPROC = 0x7fffffff,
	SHT_LOUSER = 0x80000000,
	SHT_HIUSER = 0xffffffff
};

enum {
	SHF_WRITE = 0x1,
	SHF_ALLOC = 0x2,
	SHF_EXECINSTR = 0x4,
	SHF_MERGE = 0x10,
	SHF_STRINGS = 0x20,
	SHF_INFO_LINK = 0x40,
	SHF_LINK_ORDER = 0x80,
	SHF_GROUP = 0x200,
	SHF_TLS = 0x400,
	SHF_MASKOS = 0x0F000000,
	SHF_MASKPROC = 0xf0000000
};

enum {
  GRP_COMDAT = 0x1,
  GRP_MASKOS = 0x0ff00000,
  GRP_MASKPROC = 0xf0000000
};

typedef struct {
	Elf32_Word  sh_name;
	Elf32_Word  sh_type;
	Elf32_Word  sh_flags;
	Elf32_Addr  sh_addr;
	Elf32_Off   sh_offset;
	Elf32_Word  sh_size;
	Elf32_Word  sh_link;
	Elf32_Word  sh_info;
	Elf32_Word  sh_addralign;
	Elf32_Word  sh_entsize;
} Elf32_Shdr;

typedef struct {
	Elf64_Word  sh_name;
	Elf64_Word  sh_type;
	Elf64_Xword sh_flags;
	Elf64_Addr  sh_addr;
	Elf64_Off   sh_offset;
	Elf64_Xword sh_size;
	Elf64_Word  sh_link;
	Elf64_Word  sh_info;
	Elf64_Xword sh_addralign;
	Elf64_Xword sh_entsize;
} Elf64_Shdr;


typedef struct {
	Elf32_Word n_namesz;
	Elf32_Word n_descsz;
	Elf32_Word n_type;
} Elf32_Nhdr;

typedef struct {
	Elf64_Word n_namesz;
	Elf64_Word n_descsz;
	Elf64_Word n_type;
} Elf64_Nhdr;

static inline const Elf32_Byte ELF32_ST_BIND(Elf32_Word i) { return i >> 4; }
static inline const Elf32_Byte ELF32_ST_TYPE(Elf32_Word i) { return i & 0xf; }
static inline const Elf32_Byte ELF32_ST_INFO(Elf32_Word b, Elf32_Word t) { return (b << 4) | (t & 0xf); }

static inline const Elf32_Byte ELF64_ST_BIND(Elf32_Word i) { return i >> 4; }
static inline const Elf32_Byte ELF64_ST_TYPE(Elf32_Word i) { return i & 0xf; }
static inline const Elf32_Byte ELF64_ST_INFO(Elf32_Word b, Elf32_Word t) { return (b << 4) | (t & 0xf); }

enum {
	STB_LOCAL = 0,
	STB_GLOBAL = 1,
	STB_WEAK = 2,
	STB_LOOS = 10,
	STB_HIOS = 12,
	STB_LOPROC = 13,
	STB_HIPROC = 15
};

enum {
	STT_NOTYPE = 0,
	STT_OBJECT = 1,
	STT_FUNC = 2,
	STT_SECTION = 3,
	STT_FILE = 4,
	STT_LOOS = 10,
	STT_HIOS = 12,
	STT_LOPROC = 13,
	STT_HIPROC = 15
};

enum {
	STV_DEFAULT = 0,
	STV_INTERNAL = 1,
	STV_HIDDEN = 2,
	STV_PROTECTED = 3
};

typedef struct {
	Elf32_Word  st_name;
	Elf32_Addr  st_value;
	Elf32_Word  st_size;
	Elf32_Byte  st_info;
	Elf32_Byte  st_other;
	Elf32_Half  st_shndx;
} Elf32_Sym;

typedef struct {
	Elf64_Word  st_name;
	Elf64_Byte  st_info;
	Elf64_Byte  st_other;
	Elf64_Half  st_shndx;
	Elf64_Addr  st_value;
	Elf64_Xword st_size;
} Elf64_Sym;

static inline const Elf32_Word ELF32_R_SYM(Elf32_Word i) { return i >> 8; }
static inline const Elf32_Word ELF32_R_TYPE(Elf32_Word i) { return i & 0xff; }
static inline const Elf32_Word ELF32_R_INFO(Elf32_Word s, Elf32_Word t) { return (s << 8) | (t & 0xff); }

static inline const Elf64_Xword ELF64_R_SYM(Elf64_Xword i) { return i >> 32; }
static inline const Elf64_Xword ELF64_R_TYPE(Elf64_Xword i) { return i & 0xffffffffUL; }
static inline const Elf64_Xword ELF64_R_INFO(Elf64_Xword s, Elf64_Xword t) { return (s << 32) | (t & 0xffffffffUL); }

typedef struct {
	Elf32_Addr  r_offset;
	Elf32_Word  r_info;
} Elf32_Rel;

typedef struct {
	Elf32_Addr  r_offset;
	Elf32_Word  r_info;
	Elf32_Sword r_addend;
} Elf32_Rela;

typedef struct
{
	Elf64_Addr  r_offset;
	Elf64_Xword r_info;
} Elf64_Rel;

typedef struct
{
	Elf64_Addr r_offset;
	Elf64_Xword r_info;
	Elf64_Sxword r_addend;
} Elf64_Rela;

enum {
	R_X86_64_NONE = 0,
	R_X86_64_64 = 1,
	R_X86_64_PC32 = 2,
	R_X86_64_GOT32 = 3,
	R_X86_64_PLT32 = 4,
	R_X86_64_COPY = 5,
	R_X86_64_GLOB_DAT = 6,
	R_X86_64_JUMP_SLOT = 7,
	R_X86_64_RELATIVE = 8,
	R_X86_64_GOTPCREL = 9,
	R_X86_64_32 = 10,
	R_X86_64_32S = 11,
	R_X86_64_16 = 12,
	R_X86_64_PC16 = 13,
	R_X86_64_8 = 14,
	R_X86_64_PC8 = 15,
	R_X86_64_DTPMOD64 = 16,
	R_X86_64_DTPOFF64 = 17,
	R_X86_64_TPOFF64  = 18,
	R_X86_64_TLSGD = 19,
	R_X86_64_TLSLD = 20,
	R_X86_64_DTPOFF32 = 21,
	R_X86_64_GOTTPOFF = 22,
	R_X86_64_TPOFF32 = 23,
	R_X86_64_PC64 = 24,
	R_X86_64_GOTOFF64 = 25,
	R_X86_64_GOTPC32 = 26,
	R_X86_64_SIZE32 = 32,
	R_X86_64_SIZE64 = 33,
	R_X86_64_GOTPC32_TLSDESC = 34,
	R_X86_64_TLSDESC_CALL = 35,
	R_X86_64_TLSDESC = 36,
	R_X86_64_IRELATIVE = 37,
	R_X86_64_RELATIVE64 = 38
};

enum {
	R_RISCV_NONE = 0,
	R_RISCV_32 = 1,
	R_RISCV_64 = 2,
	R_RISCV_RELATIVE = 3,
	R_RISCV_COPY = 4,
	R_RISCV_JUMP_SLOT = 5,
	R_RISCV_TLS_DTPMOD32 = 6,
	R_RISCV_TLS_DTPMOD64 = 7,
	R_RISCV_TLS_DTPREL32 = 8,
	R_RISCV_TLS_DTPREL64 = 9,
	R_RISCV_TLS_TPREL32 = 10,
	R_RISCV_TLS_TPREL64 = 11,
	R_RISCV_BRANCH = 16,
	R_RISCV_JAL = 17,
	R_RISCV_CALL = 18,
	R_RISCV_CALL_PLT = 19,
	R_RISCV_GOT_HI20 = 20,
	R_RISCV_TLS_GOT_HI20 = 21,
	R_RISCV_TLS_GD_HI20 = 22,
	R_RISCV_PCREL_HI20 = 23,
	R_RISCV_PCREL_LO12_I = 24,
	R_RISCV_PCREL_LO12_S = 25,
	R_RISCV_HI20 = 26,
	R_RISCV_LO12_I = 27,
	R_RISCV_LO12_S = 28,
	R_RISCV_TPREL_HI20 = 29,
	R_RISCV_TPREL_LO12_I = 30,
	R_RISCV_TPREL_LO12_S = 31,
	R_RISCV_TPREL_ADD = 32,
	R_RISCV_ADD8 = 33,
	R_RISCV_ADD16 = 34,
	R_RISCV_ADD32 = 35,
	R_RISCV_ADD64 = 36,
	R_RISCV_SUB8 = 37,
	R_RISCV_SUB16 = 38,
	R_RISCV_SUB32 = 39,
	R_RISCV_SUB64 = 40,
	R_RISCV_GNU_VTINHERIT = 41,
	R_RISCV_GNU_VTENTRY = 42,
	R_RISCV_ALIGN = 43,
	R_RISCV_RVC_BRANCH = 44,
	R_RISCV_RVC_JUMP = 45,
	R_RISCV_RVC_LUI = 46,
	R_RISCV_GPREL_I = 47,
	R_RISCV_GPREL_S = 48,
	R_RISCV_TPREL_I = 49,
	R_RISCV_TPREL_S = 50,
	R_RISCV_RELAX = 51,
	R_RISCV_SUB6 = 52,
	R_RISCV_SET6 = 53,
	R_RISCV_SET8 = 54,
	R_RISCV_SET16 = 55,
	R_RISCV_SET32 = 56,
};

enum {
	EF_RISCV_RVC = 0x1,
	EF_RISCV_FLOAT_ABI_SINGLE = 0x2,
	EF_RISCV_FLOAT_ABI_DOUBLE = 0x4,
	EF_RISCV_FLOAT_ABI_QUAD = 0x6,
	EF_RISCV_RVE = 0x8
};

enum {
	DF_ORIGIN = 1,
	DF_SYMBOLIC = 2,
	DF_TEXTREL = 4,
	DF_BIND_NOW = 8,
	DF_STATIC_TLS = 16
};

enum {
	DT_NULL = 0,
	DT_NEEDED = 1,
	DT_PLTRELSZ = 2,
	DT_PLTGOT = 3,
	DT_HASH = 4,
	DT_STRTAB = 5,
	DT_SYMTAB = 6,
	DT_RELA = 7,
	DT_RELASZ = 8,
	DT_RELAENT = 9,
	DT_STRSZ = 10,
	DT_SYMENT = 11,
	DT_INIT = 12,
	DT_FINI = 13,
	DT_SONAME = 14,
	DT_RPATH = 15,
	DT_SYMBOLIC = 16,
	DT_REL = 17,
	DT_RELSZ = 18,
	DT_RELENT = 19,
	DT_PLTREL = 20,
	DT_DEBUG = 21,
	DT_TEXTREL = 22,
	DT_JMPREL = 23,
	DT_BIND_NOW = 24,
	DT_INIT_ARRAY = 25,
	DT_FINI_ARRAY = 26,
	DT_INIT_ARRAYSZ = 27,
	DT_FINI_ARRAYSZ = 28,
	DT_RUNPATH = 29,
	DT_FLAGS = 30,
	DT_LOOS = 0x60000000,
	DT_HIOS = 0x6fffffff,
	DT_LOPROC = 0x70000000,
	DT_HIPROC = 0x7fffffff
};

typedef struct {
	Elf32_Sword  d_tag;
	union {
		Elf32_Word  d_val;
		Elf32_Addr  d_ptr;
	} d_un;
} Elf32_Dyn;

typedef struct {
	Elf64_Sxword d_tag;
	union {
		Elf64_Xword d_val;
		Elf64_Addr  d_ptr;
	} d_un;
} Elf64_Dyn;
