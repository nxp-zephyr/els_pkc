/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
/*                                                                          */
/* NXP Confidential. This software is owned or controlled by NXP and may    */
/* only be used strictly in accordance with the applicable license terms.   */
/* By expressly accepting such terms or by downloading, installing,         */
/* activating and/or otherwise using the software, you are agreeing that    */
/* you have read, and that you agree to comply with and are bound by, such  */
/* license terms. If you do not agree to be bound by the applicable license */
/* terms, then you may not retain, install, activate or otherwise use the   */
/* software.                                                                */
/*--------------------------------------------------------------------------*/

/**
 * @file:  mcuxClOsccaSm2_CommonParams.h
 * @brief: OSCCA SM2 common parameters (SM2FP256v1)
 */
/**@{*/


#ifndef MCUXCLOSCCASM2_COMMONPARAMS_H_
#define MCUXCLOSCCASM2_COMMONPARAMS_H_

#include <mcuxClCore_Examples.h>
#if MCUXCL_FEATURE_RANDOMMODES_OSCCA_TRNG == 0
#include <mcuxClRandom.h>
#include <mcuxClRandomModes.h>
#include <mcuxClMemory.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#endif

/* Create buffers for private and public key */
static const uint8_t pPrivateKey[MCUXCLOSCCASM2_SM2P256_SIZE_BASEPOINTORDER] = {
    0x19, 0x42, 0x14, 0xC1, 0xD9, 0x6F, 0x8F, 0x47, 0x46, 0x89, 0xC2, 0xC4, 0x5F, 0x75, 0x5D, 0x8C,
    0x7F, 0xCE, 0x7B, 0x70, 0x99, 0xCC, 0x18, 0x6F, 0x4A, 0x61, 0x40, 0x64, 0xC7, 0x5F, 0x42, 0xAF};

static const uint8_t pPublicKey[MCUXCLOSCCASM2_SM2P256_SIZE_PRIMEP * 2] = {
    0xF2, 0x27, 0xA6, 0xE8, 0x30, 0x92, 0x0E, 0x1D, 0xF8, 0xA3, 0x41, 0x03, 0x33, 0xED, 0x32, 0xC7,
    0x55, 0x6F, 0x80, 0x7C, 0x71, 0xCD, 0x2E, 0x68, 0x51, 0xBD, 0xD1, 0x19, 0x7A, 0x43, 0x49, 0xEA,
    0x03, 0x04, 0x4E, 0x76, 0xB3, 0xD1, 0x0C, 0x61, 0xC2, 0x66, 0x94, 0xF4, 0xC9, 0xD0, 0x12, 0x1F,
    0xD7, 0x8A, 0xB1, 0x2A, 0x06, 0x28, 0x96, 0xD8, 0xBE, 0xB6, 0xD6, 0x7C, 0x59, 0x5C, 0x4C, 0xE3};

/* Create buffers for extend private and public key */
static const uint8_t privateKey[MCUXCLOSCCASM2_SM2P256_SIZE_BASEPOINTORDER] = {
    //128B2FA8 BD433C6C 068C8D80 3DFF7979 2A519A55 171B1B65 0C23661D 15897263
    0x12u, 0x8Bu, 0x2Fu, 0xA8u, 0xBDu, 0x43u, 0x3Cu, 0x6Cu,
    0x06u, 0x8Cu, 0x8Du, 0x80u, 0x3Du, 0xFFu, 0x79u, 0x79u,
    0x2Au, 0x51u, 0x9Au, 0x55u, 0x17u, 0x1Bu, 0x1Bu, 0x65u,
    0x0Cu, 0x23u, 0x66u, 0x1Du, 0x15u, 0x89u, 0x72u, 0x63u};

static const uint8_t publicKey[MCUXCLOSCCASM2_SM2P256_SIZE_PRIMEP * 2] = {
    //0AE4C779 8AA0F119 471BEE11 825BE462 02BB79E2 A5844495 E97C04FF 4DF2548A
    0x0Au, 0xE4u, 0xC7u, 0x79u, 0x8Au, 0xA0u, 0xF1u, 0x19u,
    0x47u, 0x1Bu, 0xEEu, 0x11u, 0x82u, 0x5Bu, 0xE4u, 0x62u,
    0x02u, 0xBBu, 0x79u, 0xE2u, 0xA5u, 0x84u, 0x44u, 0x95u,
    0xE9u, 0x7Cu, 0x04u, 0xFFu, 0x4Du, 0xF2u, 0x54u, 0x8Au,
    //7C0240F8 8F1CD4E1 6352A73C 17B7F16F 07353E53 A176D684 A9FE0C6B B798E857
    0x7Cu, 0x02u, 0x40u, 0xF8u, 0x8Fu, 0x1Cu, 0xD4u, 0xE1u,
    0x63u, 0x52u, 0xA7u, 0x3Cu, 0x17u, 0xB7u, 0xF1u, 0x6Fu,
    0x07u, 0x35u, 0x3Eu, 0x53u, 0xA1u, 0x76u, 0xD6u, 0x84u,
    0xA9u, 0xFEu, 0x0Cu, 0x6Bu, 0xB7u, 0x98u, 0xE8u, 0x57u};

static const uint8_t patched_rng_value [] = {
    0xa1, 0xba, 0xf0, 0xb2, 0x9f, 0x2b, 0x3d, 0x0d,
    0x12, 0x73, 0x2f, 0x43, 0x36, 0xb6, 0x6e, 0x77,
    0xd5, 0x21, 0x95, 0x72, 0x1e, 0xdb, 0x9a, 0x52,
    0xf8, 0x6d, 0x0a, 0x56, 0x55, 0xc2, 0x45, 0x82,
    0x10, 0x08, 0xe9, 0xd4, 0xbd, 0xce, 0xcd, 0x72,
    0x74, 0xd4, 0x70, 0x85, 0x09, 0x25, 0x7a, 0xe5,
    0xcf, 0x00, 0x98, 0x91, 0xce, 0x55, 0x5a, 0xce,
    0x5c, 0x81, 0xc2, 0x29, 0xda, 0xd5, 0x1b, 0x83
};

#if MCUXCL_FEATURE_RANDOMMODES_OSCCA_TRNG == 0
static mcuxClRandom_Status_t RNG_Patch_function(
    mcuxClSession_Handle_t session,
    mcuxClRandom_Context_t pCustomCtx,
    uint8_t *pOut,
    uint32_t outLength
)
{
    (void)pCustomCtx;
    (void)session;
    if(outLength > sizeof(patched_rng_value))
    {
        return MCUXCLRANDOM_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(memCopyToken, mcuxClMemory_copy(pOut, patched_rng_value, outLength, outLength));
    if(MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != memCopyToken)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

    return MCUXCLRANDOM_STATUS_OK;
}
#endif /* MCUXCL_FEATURE_RANDOMMODES_PATCHMODE */

#endif /* MCUXCLOSCCASM2_COMMONPARAMS_H_ */
