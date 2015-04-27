
#include "string_convert.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//------------------------------------------------------------------------------------------
#define BUFSIZE (sizeof(long) * 8 + 1)

//utility function used by ultoa()
void str_reverse(char* buffer){
	char *i, *j;
	char c;
	i=buffer;
	j=buffer + strlen(buffer)-1;
	while(i<j){
		c = *i;
		*i = *j;
		*j = c;
		++i;
		--j;
	}
}




//convert long to string
char *ltoa(long N, char *str, int base)
{
      int i = 2;
      long uarg;
      char *tail, *head = str, buf[BUFSIZE];

      if (36 < base || 2 > base)
            base = 10;                    /* can only use 0-9, A-Z        */
      tail = &buf[BUFSIZE - 1];           /* last character position      */
      *tail-- = '\0';

      if (10 == base && N < 0L)
      {
            *head++ = '-';
            uarg    = -N;
      }
      else  uarg = N;

      if (uarg)
      {
            for (i = 1; uarg; ++i)
            {
                  ldiv_t r;

                  r       = ldiv(uarg, base);
                  *tail-- = (char)(r.rem + ((9L < r.rem) ?
                                  ('A' - 10L) : '0'));
                  uarg    = r.quot;
            }
      }
      else  *tail-- = '0';

      memcpy(head, ++tail, i);
      return str;
}

//convert unsigned long to string
char* ultoa(unsigned long a, char* buffer, int radix){
	if(radix<2 || radix>36){
		return NULL;
	}
	char* ptr=buffer;
	div_t result;
	if(a==0){
		ptr[0] = '0';
		ptr[1] = '\0';
		return buffer;
	}
	while(a){
		/* toolchain bug??
		result = div(a, radix);
		*/
		result.quot = a/radix;
		result.rem = a%radix;
		*ptr = result.rem;
		if(result.rem<10){
			*ptr += '0';
		}else{
			*ptr += 'a'-10;
		}
		++ptr;
		a = result.quot;
	}
	*ptr = '\0';
	str_reverse(buffer);
	return buffer;
}

//convert unsigned int to string
char* utoa(unsigned a, char* buffer, int radix){
	return ultoa((unsigned)a, buffer, radix);
}

char* itoa(int a, char* buffer, int radix){
	if(a<0){
		*buffer = '-';
		unsigned v = a==INT_MIN ? ((unsigned)INT_MAX+1) : -a;        
		ultoa((unsigned)v, buffer + 1, radix);
	}else{
		ultoa(a, buffer, radix);
	}
	return buffer;
}


// void itoa(int value, char *sp, int radix)
// {
//     char tmp[16];// be careful with the length of the buffer
//     char *tp = tmp;
//     int i;
//     unsigned v;
//     int sign;

//     sign = (radix == 10 && value < 0);
//     if (sign)   v = -value;
//     else    v = (unsigned)value;

//     while (v || tp == tmp)
//     {
//         i = v % radix;
//         v /= radix; // v/=radix uses less CPU clocks than v=v/radix does
//         if (i < 10)
//           *tp++ = i+'0';
//         else
//           *tp++ = i + 'a' - 10;
//     }

//     if (sign)
//     *sp++ = '-';
//     while (tp > tmp)
//     *sp++ = *--tp;
// }

//------------------------------------------------------------------------------------------

