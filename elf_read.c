/*
 * License: MIT
 *
 * Copyright (c) 2020 James Bensley.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#include <elf.h>       // EI_NIDENT, Elf64_Ehdr, Elf64_Shdr, ELFMAG, SHN_UNDEF,
                       // SHT_STRTAB
#include <inttypes.h>  // PRI*N
#include <stdio.h>     // FILE, fclose(), fopen(), fprintf(), fread(), fseek(),
                       // ftell()
#include <string.h>    // memcmp()
#include <stdlib.h>    // EXIT_FAILURE, EXIT_SUCCESS, free(), malloc()

#include "./elf_read.h"


int32_t load_file(const char* filename, void** file_data, uint64_t* file_len) {

    printf("Loading file: %s\n", filename);
    FILE* fp = fopen(filename, "rb");

    if (fp == NULL) {

        fprintf(stderr, "Error opening fp %s for reading\n", filename);
        return(EXIT_FAILURE);

    } else {

        fseek(fp, 0L, SEEK_END);
        *file_len = ftell(fp);

        *file_data = malloc(*file_len);
        if (*file_data == NULL) {
            fprintf(stderr, "Failed to malloc space for file\n");
            fclose(fp);
            return(EXIT_FAILURE);
        }

        fseek(fp, 0L, SEEK_SET);
        if (fread(*file_data, *file_len, 1, fp) != 1) {
            printf("Failed to fread() file %s\n", filename);
            fclose(fp);
            return(EXIT_FAILURE);
        }

        fclose(fp);
        printf("Loaded %" PRIu64 " bytes\n", *file_len);

        return(EXIT_SUCCESS);

    }

}


int32_t read_elf_header(void* file_data, uint64_t file_len) {

    /*
    Define the ELF header at the start of the file, the headers look
    like this:

    #define EI_NIDENT 16
    typedef struct {
        unsigned char e_ident[EI_NIDENT];
        uint16_t      e_type;
        uint16_t      e_machine;
        uint32_t      e_version;
        ElfN_Addr     e_entry;
        ElfN_Off      e_phoff;
        ElfN_Off      e_shoff;
        uint32_t      e_flags;
        uint16_t      e_ehsize;
        uint16_t      e_phentsize;
        uint16_t      e_phnum;
        uint16_t      e_shentsize;
        uint16_t      e_shnum;
        uint16_t      e_shstrndx;
    } ElfN_Ehdr;
    */
    Elf64_Ehdr *elf_header;
    elf_header = file_data;


    // Check if the file header is a valid ELF header
    if (elf_header->e_ident[0] == 0x7f &&
        elf_header->e_ident[1] == 'E' &&
        elf_header->e_ident[2] == 'L' &&
        elf_header->e_ident[3] == 'F') {
        printf("ELF magic bytes present\n");
    } else {
        printf("Magic bytes don't match ELF\n");
        printf("e_type == %" PRIu16 "\n", elf_header->e_type);
        printf("e_ident[0] == %" PRIX8" \n", elf_header->e_ident[0]);
        printf("e_ident[1] == %c\n", elf_header->e_ident[1]);
        printf("e_ident[2] == %c\n", elf_header->e_ident[2]);
        printf("e_ident[3] == %c\n", elf_header->e_ident[3]);
        return(EXIT_FAILURE);
    }

    if (memcmp(elf_header->e_ident, ELFMAG, SELFMAG) == 0) {
        printf("Valid ELF identity\n");
    } else {
        printf("Invalid ELF identity\n");
        return (EXIT_FAILURE);
    }
    printf("\n");


    /*
     Within the ELF elf_header:
     elf_header->e_shoff == Section elf_header table file offset.
     A file's section elf_header table lets one locate all the files's sections.
     The section elf_header table is an array of Elf32_Shdr or Elf64_Shdr structures.
     e_shnum holds the number of entries the section elf_header table contains.
     e_shentsize holds the size in bytes of each entry.
     e_shstrndx contains index of the section elf_header table entry that contains the section names. 
     */

    printf("Section header table (elf_header->e_shoff) == 0x%" PRIX64
        " (%" PRIu64 ")\n", elf_header->e_shoff, elf_header->e_shoff);
    printf("Section header table entry size (elf_header->e_shentsize) == "
        "%" PRIu16 "\n", elf_header->e_shentsize);
    printf("Section header table entries (elf_header->e_shnum) == "
        "%" PRIu16 "\n", elf_header->e_shnum);
    printf("\n");


    /*
    Define a section header table entry, specifically for the string 
    table entry. SHT entries looks like this:
    typedef struct {
        uint32_t   sh_name;
        uint32_t   sh_type;
        uint64_t   sh_flags;
        Elf64_Addr sh_addr;
        Elf64_Off  sh_offset;
        uint64_t   sh_size;
        uint32_t   sh_link;
        uint32_t   sh_info;
        uint64_t   sh_addralign;
        uint64_t   sh_entsize;
    } Elf64_Shdr;
    */
    Elf64_Shdr *shdr_string = NULL;

    printf("Section header table index for string table "
        "(elf_header->e_shstrndx) == %" PRIu16 "\n",
        elf_header->e_shstrndx);

    if (elf_header->e_shstrndx == SHN_UNDEF) {
        printf("This ELF elf_header has no section name string table!\n");
    } else {

        // Offset to the string table section header in the section header table
        uint64_t sht_e_string_off = elf_header->e_shoff +
        (elf_header->e_shstrndx * elf_header->e_shentsize);

        printf("String table section header entry offset in section "
            "header table == 0x%" PRIX64 " (%" PRIu64 ")\n",
            sht_e_string_off, sht_e_string_off);

        shdr_string = (Elf64_Shdr*)((uint8_t*)file_data + sht_e_string_off);
        if (shdr_string->sh_type == SHT_STRTAB) {
            printf("Entry type for string table entry in section header "
                "table (Elf64_Shdr->sh_type) == SHT_STRTAB (%" PRIu32 ")\n",
                SHT_STRTAB);
        } else {
            printf("Entry type for string table entry in section header "
                "table (Elf64_Shdr->sh_type) != SHT_STRTAB (%" PRIu32 ")\n",
                SHT_STRTAB);
            return(EXIT_FAILURE);
        }

        // Offset to string table section in file
        printf("String section offset (Elf64_Shdr->sh_offset) == "
            "%" PRIu64 "\n", shdr_string->sh_offset);

        // Size of string table in file
        printf("String section size (Elf64_Shdr->sh_size) == "
            "%" PRIu64 "\n", shdr_string->sh_size);

        // Size of each entry in the string table
        printf("String section size (Elf64_Shdr->sh_entsize) == "
            "%" PRIu64 "\n", shdr_string->sh_entsize);
        if (shdr_string->sh_entsize == 0)
            printf("0 means variably sized entries!\n");

        printf("\n");
    }


    // Display each section header table entry
    for (uint16_t i = 0; i < elf_header->e_shnum; i++) {

        uint64_t sht_e_offset = elf_header->e_shoff +
            (i * elf_header->e_shentsize);
        printf("Section header table entry %" PRIu16 ":\n", i);

        Elf64_Shdr *shdr = (Elf64_Shdr*)((uint8_t*)file_data + sht_e_offset);

        printf("Section header table entry offset == 0x%" PRIX64 " (%"
            PRIu64 ")\n", sht_e_offset, sht_e_offset);

        printf("Section offset == 0x%" PRIX64 " (%" PRIu64 ")\n",
            shdr->sh_offset, shdr->sh_offset);

        printf("Section type == 0x%" PRIX32 " (%" PRIu32 ") %s\n",
            shdr->sh_type, shdr->sh_type, shdr_type_to_str(shdr->sh_type));

        if (shdr_string != NULL) {
            printf("Section name == %s\n",
                (uint8_t*)file_data + shdr_string->sh_offset + shdr->sh_name);

        }

        char flags[100] = {0};
        strcpy(flags, "NULL");
        shdr_flags_to_str(flags, shdr->sh_flags);
        printf("Section flags 0x%" PRIX64 " (%" PRIu64 ") == %s\n",
            shdr->sh_flags, shdr->sh_flags, flags);

        printf("Section length == 0x%" PRIX64 " (%" PRIu64 ")\n",
            shdr->sh_size, shdr->sh_size);

        printf("\n");
    }

    return(EXIT_SUCCESS);

}


void shdr_flags_to_str(char *flags, uint64_t sh_flags) {

    if ((sh_flags & SHF_WRITE) == SHF_WRITE) {
        strcat(flags, "SHF_WRITE ");
    }
    if ((sh_flags & SHF_ALLOC) == SHF_ALLOC) {
        strcat(flags, "SHF_ALLOC ");
    }
    if ((sh_flags & SHF_EXECINSTR) == SHF_EXECINSTR) {
        strcat(flags, "SHF_EXECINSTR ");
    }
    if ((sh_flags & SHF_MERGE) == SHF_MERGE) {
        strcat(flags, "SHF_MERGE ");
    }
    if ((sh_flags & SHF_STRINGS) == SHF_STRINGS) {
        strcat(flags, "SHF_STRINGS ");
    }
    if ((sh_flags & SHF_INFO_LINK) == SHF_INFO_LINK) {
        strcat(flags, "SHF_INFO_LINK ");
    }
    if ((sh_flags & SHF_LINK_ORDER) == SHF_LINK_ORDER) {
        strcat(flags, "SHF_LINK_ORDER ");
    }
    if ((sh_flags & SHF_OS_NONCONFORMING) == SHF_OS_NONCONFORMING) {
        strcat(flags, "SHF_OS_NONCONFORMING ");
    }
    if ((sh_flags & SHF_GROUP) == SHF_GROUP) {
        strcat(flags, "SHF_GROUP ");
    }
    if ((sh_flags & SHF_TLS) == SHF_TLS) {
        strcat(flags, "SHF_TLS ");
    }
    if ((sh_flags & SHF_COMPRESSED) == SHF_COMPRESSED) {
        strcat(flags, "SHF_COMPRESSED ");
    }
    if ((sh_flags & SHF_MASKOS) == SHF_MASKOS) {
        strcat(flags, "SHF_MASKOS ");
    }
    if ((sh_flags & SHF_MASKPROC) == SHF_MASKPROC) {
        strcat(flags, "SHF_MASKPROC ");
    }
    if ((sh_flags & SHF_ORDERED) == SHF_ORDERED) {
        strcat(flags, "SHF_ORDERED ");
    }
    if ((sh_flags & SHF_EXCLUDE) == SHF_EXCLUDE) {
        strcat(flags, "SHF_EXCLUDE ");
    }

}

const char * shdr_type_to_str(uint32_t shdr_type) {

    switch (shdr_type) {
        case SHT_NULL:
            return "SHT_NULL";
        case SHT_PROGBITS:
            return "SHT_PROGBITS";
        case SHT_SYMTAB:
            return "SHT_SYMTAB";
        case SHT_STRTAB:
            return "SHT_STRTAB";
        case SHT_RELA:
            return "SHT_RELA";
        case SHT_HASH:
            return "SHT_HASH";
        case SHT_DYNAMIC:
            return "SHT_DYNAMIC";
        case SHT_NOTE:
            return "SHT_NOTE";
        case SHT_NOBITS:
            return "SHT_NOBITS";
        case SHT_REL:
            return "SHT_REL";
        case SHT_SHLIB:
            return "SHT_SHLIB";
        case SHT_DYNSYM:
            return "SHT_DYNSYM";
        case SHT_NUM:
            return "SHT_NUM";
        case SHT_LOPROC:
            return "SHT_LOPROC";
        case SHT_HIPROC:
            return "SHT_HIPROC";
        case SHT_LOUSER:
            return "SHT_LOUSER";
        case SHT_HIUSER:
            return "SHT_HIUSER";
        default:
            return NULL;
    }

    return NULL;
}


int32_t main(int32_t argc, char* argv[]) {

    void* file_data = NULL;
    uint64_t file_len = 0;

    if (load_file(argv[1], &file_data, &file_len) == EXIT_FAILURE) {
        free(file_data);
        return(EXIT_FAILURE);
    }

    if (read_elf_header(file_data, file_len) == EXIT_FAILURE) {
        free(file_data);
        return(EXIT_FAILURE);
    }

    free(file_data);
    return(EXIT_SUCCESS);

}