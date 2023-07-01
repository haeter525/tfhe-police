#ifndef _FETCHNAME_
#define _FETCHNAME_

struct nameCipher {
	lbcrypto::LWECiphertext nc[8][5];
};
int fetchName(nameCipher* myCipher);

#endif
