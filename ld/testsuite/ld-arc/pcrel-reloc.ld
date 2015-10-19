/* Default linker script, for normal executables */
OUTPUT_FORMAT("elf32-littlearc", "elf32-bigarc",
              "elf32-littlearc")

OUTPUT_ARCH(arc)
ENTRY(__start)

SECTIONS
{
  /* Read-only sections, merged into text segment: */
  PROVIDE (__start = 0x10000);
  . = 0x10000 + SIZEOF_HEADERS;

  .text           : {*(.text .stub .text.*)} =0
  .data           : {__SDATA_BEGIN__ = .;*(.data)}

  /DISCARD/ : { *(.__arc_profile_*) }
  /DISCARD/ : { *(.note.GNU-stack) }
}
