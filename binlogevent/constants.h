#include<iostream>
#include<inttypes.h>
#define mask(__b) \
		((uint32_t)(__b)==32 ? 0xffffffff : \
		      ((uint32_t)(__b)==24 ? 0xffffff : \
		       ((uint32_t)(__b)==16 ? 0xffff : \
			((uint32_t)(__b)==8 ? 0xff : 0xffffffffffffffff ))))

#define bytes_col_count(__b) \
		((uint64_t)(__b)<0xfb ? 1 : \
		 	((uint64_t)(__b)==0xfc ? 2 : \
			 	((uint64_t)(__b)==0xfd ? 3 : 8)))
