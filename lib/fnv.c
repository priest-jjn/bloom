/*
 * hash_32 - 32 bit Fowler/Noll/Vo hash code
 *
 ***
 *
 * Please do not copyright this code.  This code is in the public domain.
 *
 * LANDON CURT NOLL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO
 * EVENT SHALL LANDON CURT NOLL BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * By:
 *  chongo <Landon Curt Noll> /\oo/\
 *      http://www.isthe.com/chongo/
 *
 * Share and Enjoy!  :-)
 */

#include <stdlib.h>
#include "fnv.h"


/*
 * 32 bit magic FNV-0 and FNV-1 prime
 */
#define FNV_32_PRIME ((Fnv32_t)0x01000193)


/*
 * fnv_32_buf - perform a 32 bit Fowler/Noll/Vo hash on a buffer
 *
 * input:
 *  buf  - start of buffer to hash
 *  len  - length of buffer in octets
 *  hval  - previous hash value or 0 if first call
 *
 * returns:
 *  32 bit hash as a static hash type
 *
 * NOTE: To use the 32 bit FNV-0 historic hash, use FNV0_32_INIT as the hval
 *   argument on the first call to either fnv_32_buf() or fnv_32_str().
 *
 * NOTE: To use the recommended 32 bit FNV-1 hash, use FNV1_32_INIT as the hval
 *   argument on the first call to either fnv_32_buf() or fnv_32_str().
 */
Fnv32_t fnv_32_buf (void *buf, size_t len, Fnv32_t hval) {
  unsigned char *bp = (unsigned char *)buf;  /* start of buffer */
  unsigned char *be = bp + len;    /* beyond end of buffer */

  /*
   * FNV-1 hash each octet in the buffer
   */
  while (bp < be) {

    /* multiply by the 32 bit FNV magic prime mod 2^32 */
#if defined(NO_FNV_GCC_OPTIMIZATION)
    hval *= FNV_32_PRIME;
#else
    hval += (hval<<1) + (hval<<4) + (hval<<7) + (hval<<8) + (hval<<24);
#endif

    /* xor the bottom with the current octet */
    hval ^= (Fnv32_t)*bp++;
  }

  /* return our new hash value */
  return hval;
}


/*
 * fnv_32_str - perform a 32 bit Fowler/Noll/Vo hash on a string
 *
 * input:
 *  str  - string to hash
 *  hval  - previous hash value or 0 if first call
 *
 * returns:
 *  32 bit hash as a static hash type
 *
 * NOTE: To use the 32 bit FNV-0 historic hash, use FNV0_32_INIT as the hval
 *   argument on the first call to either fnv_32_buf() or fnv_32_str().
 *
 * NOTE: To use the recommended 32 bit FNV-1 hash, use FNV1_32_INIT as the hval
 *   argument on the first call to either fnv_32_buf() or fnv_32_str().
 */
Fnv32_t fnv_32_str (char *str, Fnv32_t hval) {
  unsigned char *s = (unsigned char *)str;  /* unsigned string */

  /*
   * FNV-1 hash each octet in the buffer
   */
  while (*s) {

    /* multiply by the 32 bit FNV magic prime mod 2^32 */
#if defined(NO_FNV_GCC_OPTIMIZATION)
    hval *= FNV_32_PRIME;
#else
    hval += (hval<<1) + (hval<<4) + (hval<<7) + (hval<<8) + (hval<<24);
#endif

    /* xor the bottom with the current octet */
    hval ^= (Fnv32_t)*s++;
  }

  /* return our new hash value */
  return hval;
}
