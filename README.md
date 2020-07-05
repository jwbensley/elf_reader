# ELF Reader

#### What is it
Example program which can read Linux ELF file headers.

#### Example output

```bash
$ gcc -o elf_read elf_read.c -pedantic -Wall -Werror && ./elf_read /bin/bash

Loading file: /bin/bash
Loaded 1037528 bytes
ELF magic bytes present
Valid ELF identity

Section header table (elf_header->e_shoff) == 0xFCD98 (1035672)
Section header table entry size (elf_header->e_shentsize) == 64
Section header table entries (elf_header->e_shnum) == 29

Section header table index for string table (elf_header->e_shstrndx) == 28
String table section header entry offset in section header table == 0xFD498 (1037464)
Entry type for string table entry in section header table (Elf64_Shdr->sh_type) == SHT_STRTAB (3)
String section offset (Elf64_Shdr->sh_offset) == 1035412
String section size (Elf64_Shdr->sh_size) == 258
String section size (Elf64_Shdr->sh_entsize) == 0
0 means variably sized entries!

Section header table entry 0:
Section header table entry offset == 0xFCD98 (1035672)
Section offset == 0x0 (0)
Section type == 0x0 (0) SHT_NULL
Section name == 
Section flags 0x0 (0) == NULL
Section length == 0x0 (0)

Section header table entry 1:
Section header table entry offset == 0xFCDD8 (1035736)
Section offset == 0x238 (568)
Section type == 0x1 (1) SHT_PROGBITS
Section name == .interp
Section flags 0x2 (2) == NULLSHF_ALLOC 
Section length == 0x1C (28)

Section header table entry 2:
Section header table entry offset == 0xFCE18 (1035800)
Section offset == 0x254 (596)
Section type == 0x7 (7) SHT_NOTE
Section name == .note.ABI-tag
Section flags 0x2 (2) == NULLSHF_ALLOC 
Section length == 0x20 (32)

Section header table entry 3:
Section header table entry offset == 0xFCE58 (1035864)
Section offset == 0x274 (628)
Section type == 0x7 (7) SHT_NOTE
Section name == .note.gnu.build-id
Section flags 0x2 (2) == NULLSHF_ALLOC 
Section length == 0x24 (36)

Section header table entry 4:
Section header table entry offset == 0xFCE98 (1035928)
Section offset == 0x298 (664)
Section type == 0x6FFFFFF6 (1879048182) (null)
Section name == .gnu.hash
Section flags 0x2 (2) == NULLSHF_ALLOC 
Section length == 0x489C (18588)

Section header table entry 5:
Section header table entry offset == 0xFCED8 (1035992)
Section offset == 0x4B38 (19256)
Section type == 0xB (11) SHT_DYNSYM
Section name == .dynsym
Section flags 0x2 (2) == NULLSHF_ALLOC 
Section length == 0xD6F8 (55032)

Section header table entry 6:
Section header table entry offset == 0xFCF18 (1036056)
Section offset == 0x12230 (74288)
Section type == 0x3 (3) SHT_STRTAB
Section name == .dynstr
Section flags 0x2 (2) == NULLSHF_ALLOC 
Section length == 0x8C53 (35923)

Section header table entry 7:
Section header table entry offset == 0xFCF58 (1036120)
Section offset == 0x1AE84 (110212)
Section type == 0x6FFFFFFF (1879048191) (null)
Section name == .gnu.version
Section flags 0x2 (2) == NULLSHF_ALLOC 
Section length == 0x11EA (4586)

Section header table entry 8:
Section header table entry offset == 0xFCF98 (1036184)
Section offset == 0x1C070 (114800)
Section type == 0x6FFFFFFE (1879048190) (null)
Section name == .gnu.version_r
Section flags 0x2 (2) == NULLSHF_ALLOC 
Section length == 0xD0 (208)

Section header table entry 9:
Section header table entry offset == 0xFCFD8 (1036248)
Section offset == 0x1C140 (115008)
Section type == 0x4 (4) SHT_RELA
Section name == .rela.dyn
Section flags 0x2 (2) == NULLSHF_ALLOC 
Section length == 0xC0 (192)

Section header table entry 10:
Section header table entry offset == 0xFD018 (1036312)
Section offset == 0x1C200 (115200)
Section type == 0x4 (4) SHT_RELA
Section name == .rela.plt
Section flags 0x42 (66) == NULLSHF_ALLOC SHF_INFO_LINK 
Section length == 0x13E0 (5088)

Section header table entry 11:
Section header table entry offset == 0xFD058 (1036376)
Section offset == 0x1D5E0 (120288)
Section type == 0x1 (1) SHT_PROGBITS
Section name == .init
Section flags 0x6 (6) == NULLSHF_ALLOC SHF_EXECINSTR 
Section length == 0x1A (26)

Section header table entry 12:
Section header table entry offset == 0xFD098 (1036440)
Section offset == 0x1D600 (120320)
Section type == 0x1 (1) SHT_PROGBITS
Section name == .plt
Section flags 0x6 (6) == NULLSHF_ALLOC SHF_EXECINSTR 
Section length == 0xD50 (3408)

Section header table entry 13:
Section header table entry offset == 0xFD0D8 (1036504)
Section offset == 0x1E350 (123728)
Section type == 0x1 (1) SHT_PROGBITS
Section name == .plt.got
Section flags 0x6 (6) == NULLSHF_ALLOC SHF_EXECINSTR 
Section length == 0x8 (8)

Section header table entry 14:
Section header table entry offset == 0xFD118 (1036568)
Section offset == 0x1E360 (123744)
Section type == 0x1 (1) SHT_PROGBITS
Section name == .text
Section flags 0x6 (6) == NULLSHF_ALLOC SHF_EXECINSTR 
Section length == 0x9BF62 (638818)

Section header table entry 15:
Section header table entry offset == 0xFD158 (1036632)
Section offset == 0xBA2C4 (762564)
Section type == 0x1 (1) SHT_PROGBITS
Section name == .fini
Section flags 0x6 (6) == NULLSHF_ALLOC SHF_EXECINSTR 
Section length == 0x9 (9)

Section header table entry 16:
Section header table entry offset == 0xFD198 (1036696)
Section offset == 0xBA2E0 (762592)
Section type == 0x1 (1) SHT_PROGBITS
Section name == .rodata
Section flags 0x2 (2) == NULLSHF_ALLOC 
Section length == 0x1E9F0 (125424)

Section header table entry 17:
Section header table entry offset == 0xFD1D8 (1036760)
Section offset == 0xD8CD0 (888016)
Section type == 0x1 (1) SHT_PROGBITS
Section name == .eh_frame_hdr
Section flags 0x2 (2) == NULLSHF_ALLOC 
Section length == 0x4094 (16532)

Section header table entry 18:
Section header table entry offset == 0xFD218 (1036824)
Section offset == 0xDCD68 (904552)
Section type == 0x1 (1) SHT_PROGBITS
Section name == .eh_frame
Section flags 0x2 (2) == NULLSHF_ALLOC 
Section length == 0x16F9C (94108)

Section header table entry 19:
Section header table entry offset == 0xFD258 (1036888)
Section offset == 0xF3DF0 (998896)
Section type == 0xE (14) (null)
Section name == .init_array
Section flags 0x3 (3) == NULLSHF_WRITE SHF_ALLOC 
Section length == 0x8 (8)

Section header table entry 20:
Section header table entry offset == 0xFD298 (1036952)
Section offset == 0xF3DF8 (998904)
Section type == 0xF (15) (null)
Section name == .fini_array
Section flags 0x3 (3) == NULLSHF_WRITE SHF_ALLOC 
Section length == 0x8 (8)

Section header table entry 21:
Section header table entry offset == 0xFD2D8 (1037016)
Section offset == 0xF3E00 (998912)
Section type == 0x1 (1) SHT_PROGBITS
Section name == .jcr
Section flags 0x3 (3) == NULLSHF_WRITE SHF_ALLOC 
Section length == 0x8 (8)

Section header table entry 22:
Section header table entry offset == 0xFD318 (1037080)
Section offset == 0xF3E08 (998920)
Section type == 0x6 (6) SHT_DYNAMIC
Section name == .dynamic
Section flags 0x3 (3) == NULLSHF_WRITE SHF_ALLOC 
Section length == 0x1F0 (496)

Section header table entry 23:
Section header table entry offset == 0xFD358 (1037144)
Section offset == 0xF3FF8 (999416)
Section type == 0x1 (1) SHT_PROGBITS
Section name == .got
Section flags 0x3 (3) == NULLSHF_WRITE SHF_ALLOC 
Section length == 0x8 (8)

Section header table entry 24:
Section header table entry offset == 0xFD398 (1037208)
Section offset == 0xF4000 (999424)
Section type == 0x1 (1) SHT_PROGBITS
Section name == .got.plt
Section flags 0x3 (3) == NULLSHF_WRITE SHF_ALLOC 
Section length == 0x6B8 (1720)

Section header table entry 25:
Section header table entry offset == 0xFD3D8 (1037272)
Section offset == 0xF46C0 (1001152)
Section type == 0x1 (1) SHT_PROGBITS
Section name == .data
Section flags 0x3 (3) == NULLSHF_WRITE SHF_ALLOC 
Section length == 0x85C8 (34248)

Section header table entry 26:
Section header table entry offset == 0xFD418 (1037336)
Section offset == 0xFCC88 (1035400)
Section type == 0x8 (8) SHT_NOBITS
Section name == .bss
Section flags 0x3 (3) == NULLSHF_WRITE SHF_ALLOC 
Section length == 0x5BB8 (23480)

Section header table entry 27:
Section header table entry offset == 0xFD458 (1037400)
Section offset == 0xFCC88 (1035400)
Section type == 0x1 (1) SHT_PROGBITS
Section name == .gnu_debuglink
Section flags 0x0 (0) == NULL
Section length == 0xC (12)

Section header table entry 28:
Section header table entry offset == 0xFD498 (1037464)
Section offset == 0xFCC94 (1035412)
Section type == 0x3 (3) SHT_STRTAB
Section name == .shstrtab
Section flags 0x0 (0) == NULL
Section length == 0x102 (258)
```