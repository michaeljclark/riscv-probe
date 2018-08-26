OUTPUT_ARCH( "riscv" )

ENTRY( reset_vector )

MEMORY
{
  flash (rxai!w) : ORIGIN = 0x20400000, LENGTH = 128M
  ram   (wxa!ri) : ORIGIN = 0x80000000, LENGTH = 64K
}

PHDRS
{
  text PT_LOAD;
  data PT_LOAD;
  bss PT_LOAD;
}

SECTIONS
{
  .text : {
    *(.text.init)
    *(.text .text.*)
  } >flash AT>flash :text

  .rodata : {
    *(.rodata .rodata.*)
  } >flash AT>flash :text

  .data : {
    *(.sdata .sdata.*)
    *(.data .data.*)
  } >ram AT>ram :data

  .bss : {
    *(.sbss .sbss.*)
    *(.bss .bss.*)
  } >ram AT>ram :bss
}
