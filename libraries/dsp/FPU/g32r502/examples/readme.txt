FILE:    readme.txt
TITLE:   FPU examples - code region and linker notes
VERSION: 1.0.0
DATE:    2026-06-30

FPU Examples - Code Execution Region
============================================================

Overview
------------------------------------------------------------
Application code for every example below is linked to ITCM
(0x00000000) on MDK, IAR, and Eclipse.
Linker scripts: g32r502xc_itcm_ram_noramvector.sct /
g32r502xcx7_itcm_ram_noramvector.icf / g32r502xc_itcm_ram_noramvector.ld.

Interrupt / RAM vector table
------------------------------------------------------------
These examples use *_noramvector.* scripts. They do NOT reserve RAM for
.bss.ram.intvec and do not use Interrupt_initVectorTable().

Examples are for benchmark and library validation only. For product
firmware with NVIC interrupts, use general linker templates and follow:

  driverlib/g32r502/examples/eval/empty_projects/empty_mathlib_project

See device_support/g32r502/common/{sct,icf,ld}/readme.txt.

Examples
------------------------------------------------------------
No.  Example                                 
------------------------------------------------------------
1    fft/cfft_f32                            
2    fft/cfft_f32_inplace                    
3    fft/cfft_f32_unaligned                  
4    fft/cfft_f32_windowed                   
5    fft/icfft_f32                           
6    fft/irfft_f32                           
7    fft/rfft_adc_f32                        
8    fft/rfft_adc_f32_unaligned              
9    fft/rfft_adc_f32_windowed               
10   fft/rfft_alt_f32                        
11   fft/rfft_alt_f32_unaligned              
12   fft/rfft_alt_f32_windowed               
13   fft/rfft_f32                            
14   filter/fir_f32                          
15   filter/iir_f32                          
16   vector/abs_sp_cv                        
17   vector/add_sp_csxcv                     
18   vector/add_sp_cvxcv                     
19   vector/iabs_SP_CV                       
20   vector/mac_sp_cvxcv                     
21   vector/mac_sp_i16rvxcv                  
22   vector/mac_sp_rvxcv                     
23   vector/maxidx_SP_RV_2                   
24   vector/mean_SP_CV_2                     
25   vector/mpy_SP_CSxCS                     
26   vector/mpy_SP_CVxCV                     
27   vector/mpy_SP_CVxCVC                    
28   vector/mpy_SP_RMxRM                     
29   vector/mpy_SP_RSxRV_2                   
30   vector/mpy_SP_RVxCV                     
31   vector/mpy_SP_RVxRV_2                   
32   vector/rnd_sp_rs                        
33   vector/sub_SP_CSxCV                     
34   vector/sub_sp_cvxcv                     
------------------------------------------------------------
