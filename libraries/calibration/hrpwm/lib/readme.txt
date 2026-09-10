SOFTWARE USAGE DETAILS FOR DRIVERLIB BASED SFO LIB

1. Add "Include" Files:
   E.g.:
        #include "SFO_V1.h"

2. Variable Declarations:
   E.g.:
        int MEP_ScaleFactor; // Global variable used by the SFO library
                             // Result can be used for all HRPWM channels
                             // This variable is also copied to HRMSTEP
                             // register by SFO() function.
        uint16_t status = SFO_INCOMPLETE;
        volatile uint32_t PWM[] = {0, PWM1_BASE, PWM2_BASE...};
        

3. MEP_ScaleFactor Initialization:
   The SFO() should be called to calculate an initial MEP_ScaleFactor value.
   E.g.:
   while(status == SFO_INCOMPLETE)
   {
       status = SFO();
       if(status == SFO_ERROR)
       {
           //
           // SFO function returns 2 if an error occurs, that MEP
           // steps/coarse step exceeds maximum of 255.
           //
           while(1);
       }
   }

4. Application Code:
   while the application is runing, the SFO function should be re-run periodically as part of a slower
   back-ground loop.
   E.g.:
   void main ()
   {
       while(1)
       {
           status = SFO();
           if(status == SFO_ERROR)
           {
               //
               // SFO function returns 2 if an error occurs,
               // that MEP steps/coarse step exceeds maximum of 255.
               //
               while(1);
           }
       }
   }