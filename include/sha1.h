/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * SHA-1
 *
 * Description:
 *      This file implements the Secure Hashing Standard as defined
 *      in FIPS PUB 180-1 published April 17, 1995.
 *
 *      The Secure Hashing Standard, which uses the Secure Hashing
 *      Algorithm (SHA), produces a 160-bit message digest for a
 *      given data stream.  In theory, it is highly improbable that
 *      two messages will produce the same message digest.  Therefore,
 *      this algorithm can serve as a means of providing a "fingerprint"
 *      for a message.
 *
 * Portability Issues:
 *      SHA-1 is defined in terms of 32-bit "words".  This code was
 *      written with the expectation that the processor has at least
 *      a 32-bit machine word size.  If the machine word size is larger,
 *      the code should still function properly.  One caveat to that
 *      is that the input functions taking characters and character
 *      arrays assume that only 8 bits of information are stored in each
 *      character.
 *
 * Caveats:
 *      SHA-1 is designed to work with messages less than 2^64 bits
 *      long. Although SHA-1 allows a message digest to be generated for
 *      messages of any number of bits less than 2^64, this
 *      implementation only works with messages with a length that is a
 *      multiple of the size of an 8-bit character.
 *
 * http://en.wikipedia.org/wiki/SHA-1
 */

#ifndef ALGO_SHA1_H__
#define ALGO_SHA1_H__

#include <stdbool.h>

/* 
 *  This structure will hold context information for the hashing
 *  operation
 */
typedef struct SHA1Context
{
    unsigned digest[5]; /* Message Digest (output)          */

    unsigned m_low;        /* Message length in bits           */
    unsigned m_high;       /* Message length in bits           */

    unsigned char block[64]; /* 512-bit message blocks      */
    int index;    /* Index into message block array   */

    int computed;               /* Is the digest computed?          */
    int corrupted;              /* Is the message digest corruped?  */
} SHA1Context;

/*
 *  Define the circular shift macro
 */
#define SHA1CircularShift(bits,word) \
                ((((word) << (bits)) & 0xFFFFFFFF) | \
                ((word) >> (32-(bits))))

/* Function prototypes */
static void sha1_process_block(SHA1Context *);
static void sha1_pad(SHA1Context *);
static void sha1_reset(SHA1Context *);
static bool sha1_final(SHA1Context *);
static void sha1_input(SHA1Context *, const unsigned char *, unsigned);

/*  
 *  sha1_reset
 *
 *  Description:
 *      This function will initialize the SHA1Context in preparation
 *      for computing a new message digest.
 *
 *  Parameters:
 *      context: [in/out]
 *          The context to reset.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *
 */
static inline void 
sha1_reset(SHA1Context *context)
{
    context->m_low             = 0;
    context->m_high            = 0;
    context->index    = 0;

    context->digest[0]      = 0x67452301;
    context->digest[1]      = 0xEFCDAB89;
    context->digest[2]      = 0x98BADCFE;
    context->digest[3]      = 0x10325476;
    context->digest[4]      = 0xC3D2E1F0;

    context->computed   = 0;
    context->corrupted  = 0;
}

/*  
 *  sha1_final
 *
 *  Description:
 *      This function will return the 160-bit message digest into the
 *      digest array within the SHA1Context provided
 *
 *  Parameters:
 *      context: [in/out]
 *          The context to use to calculate the SHA-1 hash.
 *
 *  Returns:
 *      true if successful, false if it failed.
 *
 *  Comments:
 *
 */
static inline bool 
sha1_final(SHA1Context *context)
{
    if (context->corrupted) {
        return false;
    }

    if (!context->computed) {
        sha1_pad(context);
        context->computed = 1;
    }

    return true;
}

/*  
 *  sha1_input
 *
 *  Description:
 *      This function accepts an array of octets as the next portion of
 *      the message.
 *
 *  Parameters:
 *      context: [in/out]
 *          The SHA-1 context to update
 *      message_array: [in]
 *          An array of characters representing the next portion of the
 *          message.
 *      length: [in]
 *          The length of the message in message_array
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *
 */
static void 
sha1_input(SHA1Context         *context,
                    const unsigned char *message_array,
                    unsigned            length)
{
    if (!length) {
        return;
    }

    if (context->computed || context->corrupted) {
        context->corrupted = 1;
        return;
    }

    while(length-- && !context->corrupted) {
        context->block[context->index++] = (*message_array & 0xFF);

        context->m_low += 8;
        /* Force it to 32 bits */
        context->m_low &= 0xFFFFFFFF;
        if (context->m_low == 0) {
            context->m_high++;
            /* Force it to 32 bits */
            context->m_high &= 0xFFFFFFFF;
            if (context->m_high == 0) {
                /* Message is too long */
                context->corrupted = 1;
            }
        }

        if (context->index == 64) {
            sha1_process_block(context);
        }

        message_array++;
    }
}

/*  
 *  sha1_process_block
 *
 *  Description:
 *      This function will process the next 512 bits of the message
 *      stored in the block array.
 *
 *  Parameters:
 *      None.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      Many of the variable names in the SHAContext, especially the
 *      single character names, were used because those were the names
 *      used in the publication.
 *         
 *
 */
static void 
sha1_process_block(SHA1Context *context)
{
    const unsigned K[] =            /* Constants defined in SHA-1   */      
    {
        0x5A827999,
        0x6ED9EBA1,
        0x8F1BBCDC,
        0xCA62C1D6
    };
    int         t;                  /* Loop counter                 */
    unsigned    temp;               /* Temporary word value         */
    unsigned    W[80];              /* Word sequence                */
    unsigned    A, B, C, D, E;      /* Word buffers                 */

    /*
     *  Initialize the first 16 words in the array W
     */
    for(t = 0; t < 16; t++) {
        W[t] = ((unsigned) context->block[t * 4]) << 24;
        W[t] |= ((unsigned) context->block[t * 4 + 1]) << 16;
        W[t] |= ((unsigned) context->block[t * 4 + 2]) << 8;
        W[t] |= ((unsigned) context->block[t * 4 + 3]);
    }

    for(t = 16; t < 80; t++) {
       W[t] = SHA1CircularShift(1,W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16]);
    }

    A = context->digest[0];
    B = context->digest[1];
    C = context->digest[2];
    D = context->digest[3];
    E = context->digest[4];

    for(t = 0; t < 20; t++) {
        temp =  SHA1CircularShift(5,A) +
                ((B & C) | ((~B) & D)) + E + W[t] + K[0];
        temp &= 0xFFFFFFFF;
        E = D;
        D = C;
        C = SHA1CircularShift(30,B);
        B = A;
        A = temp;
    }

    for(t = 20; t < 40; t++) {
        temp = SHA1CircularShift(5,A) + (B ^ C ^ D) + E + W[t] + K[1];
        temp &= 0xFFFFFFFF;
        E = D;
        D = C;
        C = SHA1CircularShift(30,B);
        B = A;
        A = temp;
    }

    for(t = 40; t < 60; t++) {
        temp = SHA1CircularShift(5,A) +
               ((B & C) | (B & D) | (C & D)) + E + W[t] + K[2];
        temp &= 0xFFFFFFFF;
        E = D;
        D = C;
        C = SHA1CircularShift(30,B);
        B = A;
        A = temp;
    }

    for(t = 60; t < 80; t++) {
        temp = SHA1CircularShift(5,A) + (B ^ C ^ D) + E + W[t] + K[3];
        temp &= 0xFFFFFFFF;
        E = D;
        D = C;
        C = SHA1CircularShift(30,B);
        B = A;
        A = temp;
    }

    context->digest[0] = (context->digest[0] + A) & 0xFFFFFFFF;
    context->digest[1] = (context->digest[1] + B) & 0xFFFFFFFF;
    context->digest[2] = (context->digest[2] + C) & 0xFFFFFFFF;
    context->digest[3] = (context->digest[3] + D) & 0xFFFFFFFF;
    context->digest[4] = (context->digest[4] + E) & 0xFFFFFFFF;

    context->index = 0;
}

/*  
 *  sha1_pad
 *
 *  Description:
 *      According to the standard, the message must be padded to an even
 *      512 bits.  The first padding bit must be a '1'.  The last 64
 *      bits represent the length of the original message.  All bits in
 *      between should be 0.  This function will pad the message
 *      according to those rules by filling the block array
 *      accordingly.  It will also call sha1_process_block()
 *      appropriately.  When it returns, it can be assumed that the
 *      message digest has been computed.
 *
 *  Parameters:
 *      context: [in/out]
 *          The context to pad
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *
 */
static void 
sha1_pad(SHA1Context *context)
{
    /*
     *  Check to see if the current message block is too small to hold
     *  the initial padding bits and length.  If so, we will pad the
     *  block, process it, and then continue padding into a second
     *  block.
     */
    if (context->index > 55) {
        context->block[context->index++] = 0x80;
        while(context->index < 64) {
            context->block[context->index++] = 0;
        }

        sha1_process_block(context);

        while(context->index < 56) {
            context->block[context->index++] = 0;
        }
    }
    else
    {
        context->block[context->index++] = 0x80;
        while(context->index < 56) {
            context->block[context->index++] = 0;
        }
    }

    /*
     *  Store the message length as the last 8 octets
     */
    context->block[56] = (context->m_high >> 24) & 0xFF;
    context->block[57] = (context->m_high >> 16) & 0xFF;
    context->block[58] = (context->m_high >> 8) & 0xFF;
    context->block[59] = (context->m_high) & 0xFF;
    context->block[60] = (context->m_low >> 24) & 0xFF;
    context->block[61] = (context->m_low >> 16) & 0xFF;
    context->block[62] = (context->m_low >> 8) & 0xFF;
    context->block[63] = (context->m_low) & 0xFF;

    sha1_process_block(context);
}


#endif
