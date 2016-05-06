/* 
 * Copyright (c) 2010, Intel Corporation
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright notice, 
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, 
 *       this list of conditions and the following disclaimer in the documentation 
 *       and/or other materials provided with the distribution.
 *     * Neither the name of Intel Corporation nor the names of its contributors 
 *       may be used to endorse or promote products derived from this software 
 *       without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
*/

// 2016, Amirali Sanatinia (amirali@ccs.neu.edu)


#if (__cplusplus)
extern "C" {
#endif

#include "iaesni.h"
#include "iaes_asm_interface.h"

#if (__cplusplus)
}
#endif

#include <stdio.h>
#include <string.h>


#ifdef _WIN32
#include <intrin.h>
#else

static void __cpuid(unsigned int where[4], unsigned int leaf) {
  asm volatile("cpuid":"=a"(*where),"=b"(*(where+1)), "=c"(*(where+2)),"=d"(*(where+3)):"a"(leaf));
  return;
}
#endif


#include <stdlib.h>

#ifdef __APPLE__
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif

#include <memory.h>

#ifndef _WIN32
#include <alloca.h>
#ifndef _alloca
#define _alloca alloca
#endif
#endif

#define BLOCK_SIZE (16) //in bytes
#define AES_128_KEYSIZE (16) //in bytes
#define AES_192_KEYSIZE (24) //in bytes
#define AES_256_KEYSIZE (32) //in bytes


/* 
 * check_for_aes_instructions()
 *   return 1 if support AES-NI and 0 if don't support AES-NI
 */

int check_for_aes_instructions()
{
	unsigned int cpuid_results[4];
	int yes=1, no=0;

	__cpuid(cpuid_results,0);

	if (cpuid_results[0] < 1)
		return no;
/*
 *      MSB         LSB
 * EBX = 'u' 'n' 'e' 'G'
 * EDX = 'I' 'e' 'n' 'i'
 * ECX = 'l' 'e' 't' 'n'
 */
	
	if (memcmp((unsigned char *)&cpuid_results[1], "Genu", 4) != 0 ||
		memcmp((unsigned char *)&cpuid_results[3], "ineI", 4) != 0 ||
		memcmp((unsigned char *)&cpuid_results[2], "ntel", 4) != 0)
		return no;

	__cpuid(cpuid_results,1);

	if (cpuid_results[2] & AES_INSTRCTIONS_CPUID_BIT)
		return yes;

	return no;
}

void intel_AES_enc128(UCHAR *plainText,UCHAR *cipherText,UCHAR *key,size_t numBlocks)
{
	DEFINE_ROUND_KEYS
	sAesData aesData;
	aesData.in_block = plainText;
	aesData.out_block = cipherText;
	aesData.expanded_key = expandedKey;
	aesData.num_blocks = numBlocks;

	iEncExpandKey128(key,expandedKey);
	iEnc128(&aesData);
}

void intel_AES_enc128_CBC(UCHAR *plainText,UCHAR *cipherText,UCHAR *key,size_t numBlocks,UCHAR *iv)
{
	DEFINE_ROUND_KEYS
	sAesData aesData;
	aesData.in_block = plainText;
	aesData.out_block = cipherText;
	aesData.expanded_key = expandedKey;
	aesData.num_blocks = numBlocks;
	aesData.iv = iv;

	iEncExpandKey128(key,expandedKey);
	iEnc128_CBC(&aesData);
}


void intel_AES_enc192(UCHAR *plainText,UCHAR *cipherText,UCHAR *key,size_t numBlocks)
{
	DEFINE_ROUND_KEYS
	sAesData aesData;
	aesData.in_block = plainText;
	aesData.out_block = cipherText;
	aesData.expanded_key = expandedKey;
	aesData.num_blocks = numBlocks;

	iEncExpandKey192(key,expandedKey);
	iEnc192(&aesData);
}


void intel_AES_enc192_CBC(UCHAR *plainText,UCHAR *cipherText,UCHAR *key,size_t numBlocks,UCHAR *iv)
{
	DEFINE_ROUND_KEYS
	sAesData aesData;
	aesData.in_block = plainText;
	aesData.out_block = cipherText;
	aesData.expanded_key = expandedKey;
	aesData.num_blocks = numBlocks;
	aesData.iv = iv;

	iEncExpandKey192(key,expandedKey);
	iEnc192_CBC(&aesData);
}


void intel_AES_enc256(UCHAR *plainText,UCHAR *cipherText,UCHAR *key,size_t numBlocks)
{
	DEFINE_ROUND_KEYS
	sAesData aesData;
	aesData.in_block = plainText;
	aesData.out_block = cipherText;
	aesData.expanded_key = expandedKey;
	aesData.num_blocks = numBlocks;

	iEncExpandKey256(key,expandedKey);
	iEnc256(&aesData);
}


void intel_AES_enc256_CBC(UCHAR *plainText,UCHAR *cipherText,UCHAR *key,size_t numBlocks,UCHAR *iv)
{
	DEFINE_ROUND_KEYS
	sAesData aesData;
	aesData.in_block = plainText;
	aesData.out_block = cipherText;
	aesData.expanded_key = expandedKey;
	aesData.num_blocks = numBlocks;
	aesData.iv = iv;

	iEncExpandKey256(key,expandedKey);
	iEnc256_CBC(&aesData);
}

