#source: x-arcv-apex-01-a.s
#source: x-arcv-apex-01-b.s
#source: x-arcv-apex-01-c.s
#ld: -m[riscv_choose_64_or_32_emul]
#objdump: -s

.*:[ 	]+file format .*

#...
Contents of section \.text:
#...
Contents of section \.riscv\.attributes:
#...
Contents of section .riscvapex.1.11.1:
 0000 0c010b01 0100666f 6f300000.*
Contents of section .riscvapex.1.11.2:
 0000 0c010b02 1100666f 6f310000.*
Contents of section .riscvapex.1.11.3:
 0000 0c010b03 5100666f 6f320000.*
Contents of section .riscvapex.1.11.4:
 0000 0c010b04 7100666f 6f330000.*
Contents of section .riscvapex.2.11.5:
 0000 0c010b05 0200666f 6f340000.*
Contents of section .riscvapex.2.11.6:
 0000 0c010b06 1200666f 6f350000.*
Contents of section .riscvapex.4.11.7:
 0000 0c010b07 4400666f 6f360000.*
Contents of section .riscvapex.4.11.8:
 0000 0c010b08 5400666f 6f370000.*
Contents of section .riscvapex.8.11.9:
 0000 0c010b09 0800666f 6f380000.*
#pass
