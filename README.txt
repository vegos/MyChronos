
 MMMM   MMMM ---------- CCCCCC - HH --------------------------------------------
  MMM   MMM            CC    CC  HH      
  MMMM MMMM            CC        HH
  MM MMM MM   YY   YY  CC        HHHHHH  R RRRR   OOOOO  N NNNN   OOOOO   SSSSS
  MM  M  MM   YY   YY  CC        HH   HH  RR  RR OO   OO NN   NN OO   OO SS
  MM     MM   YY   YY  CC        HH   HH  RR     OO   OO NN   NN OO   OO  SSSSS
  MM     MM   YY   YY  CC    CC  HH   HH  RR     OO   OO NN   NN OO   OO      SS 
 MMMM   MMMM   YYYYYY   CCCCCC   HH   HH RRRR     OOOOO  NN   NN  OOOOO   SSSSS
                   YY
              YY   YY
 ------------- YYYYY ------------------------------- (c)2013, Antonis Maglaras -



Texas Instruments eZ430 Chronos Development Kit

http://www.ti.com/tool/ez430-chronos&DCMP=Chronos&HQS=Other+OT+chronos
http://processors.wiki.ti.com/index.php/EZ430-Chronos


MyChronos is a modified stock firmware (v.1.7)
Or to be more specific: At least, it's a way for me to start learning and 
customizing the eZ430 to my needs :)

Note that I have not include almost everything to make it a real import on CCS 
due to some errors when uploading. I will fix it someday in the near future!
Till then, you can just replace the original firmware files (BUT don't forget
to take a backup of your working set first :)).




Menu Structure:
---------------

Line 1:
- Time (Up for Seconds)
- Altitude
- Barometer in hPa
- Alarm
- Accelerometer Z-Axis (Up for X-Axis or Y-Axis)

Line 2:
- Date (Down for Year, 3-letters day of week name or 3-letters month name or 
  2-letters day-of-week or day)
- Temperature (Down for Max, Min measurement)
- Battery Voltage
- Ctrl (Control: old PPT mode, for use with my custom python script)
- Sync (for synching time with my ntp -- it does not sync altitude &
  temperature. I guess the watch knows better that my Linux what the
  temperature and the altitude is...)
- Accel (old ACC. Not in use by me)
- Stopwatch
- RESET (Down for resetting the temperature max/min statistics)
- RFBSL (in my white-PCB is not working but I leave it for now...)



To Do:
------

Add some statistics like Altitude Min/Max/Average, Temperature Average,
Acceleration Peak, free-fall counter, maximum acceleration/difference from 
start etc...
