1. Geehy_Bin.exe
Supported instruction:
-h                        Display help
-v                         The detailed log information is displayed
-boot                   Converts all segments to bootable form
-uart8                     Specifies uart format, 8-bit mode
-spi8                    Specifies spi format, 8-bit mode
-lospcp=value      Specifies the initial value for the lospcp register
-spibrr=value       Specifies the initial value for the spibrr register
-i2c8                    Specifies i2c format, 8-bit mode
-i2cpsc=value      Specifies the initial value for the i2cpsc register
-i2cclkh=value     Specifies the initial value for the i2cclkh register
-i2cclkl=value      Specifies the initial value for the i2cclkl register
-pc=value           Specifies the value of pc
-a                       Select ascii hexadecimal
-o                       Specified output file
-m                      Select primary safe boot mode
-e                       Select extended safe boot mode
-me                    Select both primary safe boot and extended safe boot modes
-mesta=             If both primary and extended boot modes are selected, the start address of extended boot is selected
-melen=             If you select both primary and extended safe boot modes, the flash length to be verified for extended safe boot is extended
--cmac=file        Specifies the txt file that stores the cmac key
xxx.cmd              Specifies the cmd file that stores the start address of the cmac calculation, the flash length of the check, and the filling value
-tag=value         Specifies the starting address to put the tag value in
-load=value        Specifies the start address for file downloads
--load_image      Select generate bin file
--image              Select generate txt file

Uart_Example:
Geehy_Bin.exe -boot -uart8 -pc=0x00000000 -a -o flashapi_ex2_uart_kernel_CPU0_RAM.txt flashapi_ex2_uart_kernel_CPU0_RAM.bin
Geehy_Bin.exe -boot -uart8 -pc=0x08000000 -a -o flashapi_ex2_uart_kernel_BANK0_LDFU.txt flashapi_ex2_uart_kernel_BANK0_LDFU.bin
Geehy_Bin.exe -boot -uart8 -pc=0x08020000 -a -o flashapi_ex2_uart_kernel_BANK1_LDFU.txt flashapi_ex2_uart_kernel_BANK1_LDFU.bin

Secure_Example:
Geehy_Bin.exe TEST.cmd -m --image --cmac=KEY.txt TEST.bin -tag=0x08000008 -o CMAC.txt
Geehy_Bin.exe TEST.cmd -m --load_image --cmac=KEY.txt TEST.bin -tag=0x08000008 -o CMAC.bin
Geehy_Bin.exe TEST1.cmd -e --image --cmac=key.txt TEST.bin -tag=0x08003000 -load=0x08000000 -o CMAC1.txt
Geehy_Bin.exe TEST1.cmd -e --load_image --cmac=key.txt TEST.bin -tag=0x08003000 -load=0x08000000 -o CMAC1.bin


2. Geehy_Serial_flash_Programmer.exe
This application may be used to download images to geehy
Supported parameters are:

-d <device>         - The name of the device to load to.
                            r501.
-k <file>              - The file name for flash kernel.
                           This file must be in the SCI boot format.
-a <file>              - The file name for download use.
                           This file must be in the SCI boot format.
-p COM<num>   - Set the COM port to be used for communications.
-b <num>           - Set the baud rate for the COM port.
-? or -h                - Show this help.
-q                        - Quiet mode. Disable output to stdout.
-w                       - Wait for a key press before exiting.
-v                        - Enable verbose output

-d -f, and -p are mandatory parameters.  If baud rate is omitted,
the communications will occur at 9600 baud.

SCI_Example:
Geehy_Serial_flash_Programmer.exe -d r501 -k flashapi_ex2_uart_kernel_CPU0_RAM.txt -a  LED1_0x0800C000.txt -p COM11 -b 38400
GeehySerial_flash_Programmer_appln.exe  -d r501 -k flashapi_ex2_uart_kernel_CPU0_RAM.txt -a LED2_0x0800C000.txt -p COM11 -b 38400
