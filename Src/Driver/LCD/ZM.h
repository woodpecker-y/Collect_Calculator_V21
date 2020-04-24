#ifndef _ZM_H_
#define _ZM_H_

#include "main.h" 

#ifdef _ZM_C_
#define ZM_EXT
#else 
#define ZM_EXT extern
#endif

#ifdef _ZM_C_
#endif 
//*****************************************************************************************************************************************

ZM_EXT  const unsigned char ZKIndex[];
ZM_EXT  const unsigned char ASCII12[][12];
ZM_EXT  const unsigned char ASCII13[][13];
ZM_EXT  const unsigned char ASCII15[][15];
ZM_EXT  const unsigned char ASCII16[][16];


ZM_EXT  const unsigned char Zkarry12[][24];
ZM_EXT  const unsigned char Zkarry13[][26];
ZM_EXT  const unsigned char Zkarry15[][30];
ZM_EXT  const unsigned char Zkarry16[][32];
#endif	/* ZM_H */

