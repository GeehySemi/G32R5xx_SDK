/* CPU1 Flash sectors */

/* HEX directive required by HEX utility to generate the golden CMAC tag */
/* with one entry that represents all the allocated flash memory */
ROMS
{
  FLASH: o=0x08000000 l=0x2000, fill = 0xFFFF /* If fill not specified, then default is all 0s */
}
