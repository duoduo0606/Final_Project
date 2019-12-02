#include <avr/io.h>

#include <math.h>




unsigned short litled(unsigned char col0, unsigned char row0)
{
  unsigned char i;  
  unsigned short val;
  unsigned char col[8];
  unsigned char row[8];

  for (i=0;i<8;i++)
    {
      col[i]=1;
      row[i]=0;
    }
  col[col0-1]=0;
  row[row0-1]=1;
  val = col[0]*8+col[1]*1024+col[2]*2048+col[3]*64+col[4]*8192+col[5]*32+col[6]*2+col[7]*1+row[0]*4096+row[1]*512+row[2]*16384+row[3]*256+row[4]*16+row[5]*32768+row[6]*4+row[7]*128;
 
    return (val);
}


