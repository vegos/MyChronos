 MMMM   MMMM            CCCCCC   HH
  MMM   MMM            CC    CC  HH      
  MMMM MMMM   YY   YY  CC        HHHHHH  R RRRR   OOOOO  N NNNN   OOOOO   SSSSS
  MM MMM MM   YY   YY  CC        HH   HH  RR  RR OO   OO NN   NN OO   OO SS
  MM  M  MM   YY   YY  CC        HH   HH  RR     OO   OO NN   NN OO   OO  SSSSS
  MM     MM   YY   YY  CC    CC  HH   HH  RR     OO   OO NN   NN OO   OO      SS 
 MMMM   MMMM   YYYYYY   CCCCCC   HH   HH RRRR     OOOOO  NN   NN  OOOOO   SSSSS
                   YY
              YY   YY
               YYYYY


Texas Instruments eZ430 Chronos Development Kit
http://www.ti.com/tool/ez430-chronos&DCMP=Chronos&HQS=Other+OT+chronos
http://processors.wiki.ti.com/index.php/EZ430-Chronos?DCMP=Chronos&HQS=Other+OT+chronoswiki


MyChronos is a modified stock firmware (v.1.7) -- at least, it's a way for me to start learning & customizing the eZ430 to my needs :)


Menu Structure:
--------------

Line 1:
- Time (Up for Seconds)
- Altitude
- Barometer in hPa
- Alarm
- Accelerometer Z-Axis (Up for X-Axis & Y-Axis)

Line 2:
- Date (Up for Year, 3-letters day of week name, 3-letters month name & 2-letters day-of-week & day)
- Battery Voltage
- Ctrl (Control: old PPT mode, for use with my custom python script)
- Sync (for synching time with my ntp -- it does not sync altitude & temperature)
- Accel (old ACC. Not in use by me)
- Stopwatch
- RESET (old RFBSL, in my white-PCB is not working)



To Do:
-----

Add some statistics like Altitude/Temperature High/Low/Average,
Acceleration (Peak, free-fall counter, maximum acceleration/difference from start).
