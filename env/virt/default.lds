OUTPUT_ARCH( "riscv" )

ENTRY( reset_vector )

MEMORY
{
  ram   (wxa!ri) : ORIGIN = 0x80000000, LENGTH = 128M
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
  } >ram AT>ram :text

  .rodata : {
    *(.rodata .rodata.*)
  } >ram AT>ram :text

  .data : {
    *(.sdata .sdata.*)
    *(.data .data.*)
  } >ram AT>ram :data

  .bss : {
    *(.sbss .sbss.*)
    *(.bss .bss.*)
  } >ram AT>ram :bss
}
