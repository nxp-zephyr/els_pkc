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
 * @file  mcuxClRandomModes_PatchMode_CtrDrbg_AES256_DRG3_example.c
 * @brief Example for the mcuxClRandomModes component
 *
 * @example mcuxClRandomModes_PatchMode_CtrDrbg_AES256_DRG3_example.c
 * @brief   Example for the mcuxClRandomModes component
 */

#include <mcuxClRandom.h>
#include <mcuxClRandomModes.h>
#include <mcuxClSession.h>
#include <internal/mcuxClSession_Internal.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClExample_Session_Helper.h>
#include <mcuxClCore_Examples.h>
#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxClExample_ELS_Helper.h>

/******************************************************************************
 * Local and global function declarations
 ******************************************************************************/
static mcuxClRandom_Status_t RNG_Patch_function(
    mcuxClSession_Handle_t session,
    mcuxClRandom_Context_t pCustomCtx,
    uint8_t *pOut,
    uint32_t outLength
)
{
    mcuxClSession_Descriptor_t *sessionCustom = (mcuxClSession_Descriptor_t *) mcuxClSession_allocateWords_cpuWa(session, sizeof(mcuxClSession_Descriptor_t) / sizeof(uint32_t));

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(si_status, token, mcuxClSession_init(
    /* mcuxClSession_Handle_t session:      */ sessionCustom,
    /* uint32_t * const cpuWaBuffer:       */ mcuxClSession_allocateWords_cpuWa(session, MCUXCLRANDOMMODES_MAX_CPU_WA_BUFFER_SIZE / sizeof(uint32_t)),
    /* uint32_t cpuWaSize:                 */ MCUXCLRANDOMMODES_MAX_CPU_WA_BUFFER_SIZE,
    /* uint32_t * const pkcWaBuffer:       */ NULL,
    /* uint32_t pkcWaSize:                 */ 0U
    ));
    /* mcuxClSession_init is a flow-protected function: Check the protection token and the return value */
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != token) || (MCUXCLSESSION_STATUS_OK != si_status))
    {
        return MCUXCLRANDOM_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* DRBG initialization                                                    */
    /**************************************************************************/

    /* Initialize an AES-256 CTR_DRBG DRG.3 */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(ri_status, init_token, mcuxClRandom_init(
                                        sessionCustom,
                                        (mcuxClRandom_Context_t)pCustomCtx,
                                        mcuxClRandomModes_Mode_CtrDrbg_AES256_DRG3
                                   ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_init) != init_token) || (MCUXCLRANDOM_STATUS_OK != ri_status))
    {
      return MCUXCLRANDOM_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* Generate random byte strings                                           */
    /**************************************************************************/
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(rg_status, generate_token, mcuxClRandom_generate(
                                        sessionCustom,
                                        pOut,
                                        outLength
                                   ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate) != generate_token) || (MCUXCLRANDOM_STATUS_OK != rg_status))
    {
      return MCUXCLRANDOM_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Random uninit. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(ru_status, uninit_token, mcuxClRandom_uninit(sessionCustom));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_uninit) != uninit_token) || (MCUXCLRANDOM_STATUS_OK != ru_status))
    {
      return MCUXCLRANDOM_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();    

    /** Destroy Session and cleanup Session **/
    if(!mcuxClExample_Session_Clean(sessionCustom))
    {
        return MCUXCLRANDOM_STATUS_ERROR;
    }

    /* Free workarea (sessionCustom and random cpuWaBuffer) */
    mcuxClSession_freeWords_cpuWa(session, (MCUXCLRANDOMMODES_MAX_CPU_WA_BUFFER_SIZE / sizeof(uint32_t)) + (sizeof(mcuxClSession_Descriptor_t) / sizeof(uint32_t)));

    return MCUXCLRANDOM_STATUS_OK;
}

/** Performs an example usage of the mcuxClRandom and mcuxClRandomModes components with patch mode.
 * @retval true  The example code completed successfully
 * @retval false The example code failed */
bool mcuxClRandomModes_PatchMode_CtrDrbg_AES256_DRG3_example(void)
{
    /**************************************************************************/
    /* Preparation                                                            */
    /**************************************************************************/

    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_ERROR;
    }

    mcuxClSession_Descriptor_t sessionDesc;
    mcuxClSession_Handle_t session = &sessionDesc;
    MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_SESSION(session, MCUXCLRANDOMMODES_MAX_CPU_WA_BUFFER_SIZE + sizeof(mcuxClSession_Descriptor_t), 0u);

    /* Fill mode descriptor with the relevant data */
    uint32_t customModeDescBytes[(MCUXCLRANDOMMODES_PATCHMODE_DESCRIPTOR_SIZE + sizeof(uint32_t) - 1U)/sizeof(uint32_t)];
    mcuxClRandom_ModeDescriptor_t *mcuxClRandomModes_Mode_Custom = (mcuxClRandom_ModeDescriptor_t *) customModeDescBytes;

    uint32_t rngContext[MCUXCLRANDOMMODES_CTR_DRBG_AES256_CONTEXT_SIZE_IN_WORDS] = {0};
    /**************************************************************************/
    /* RANDOM Patch Mode creation, use                                        */
    /* mcuxClRandomModes_Mode_CtrDrbg_AES256_DRG3 as customer generate Algo    */
    /**************************************************************************/
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(cp_status, cp_token, mcuxClRandomModes_createPatchMode(
                                        mcuxClRandomModes_Mode_Custom,
                                        (mcuxClRandomModes_CustomGenerateAlgorithm_t)RNG_Patch_function,
                                        (mcuxClRandom_Context_t)rngContext,
                                        256U
                                   ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_createPatchMode) != cp_token) || (MCUXCLRANDOM_STATUS_OK != cp_status))
    {
      return MCUXCLEXAMPLE_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* patch mode initialization                                              */
    /**************************************************************************/
    uint32_t* rngContextPatched = NULL;
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(ri_status, init_token, mcuxClRandom_init(
                                        session,
                                        (mcuxClRandom_Context_t)rngContextPatched,
                                        mcuxClRandomModes_Mode_Custom
                                   ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_init) != init_token) || (MCUXCLRANDOM_STATUS_OK != ri_status))
    {
      return MCUXCLEXAMPLE_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* Generate several random byte strings                                   */
    /**************************************************************************/
    /* Buffers to store the generated random values in. */
    uint8_t drbg_buffer1[3u];
    uint8_t drbg_buffer2[16u];
    uint8_t drbg_buffer3[31u];


    /* Generate random values of smaller amount than one word size. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(rg1_status, generate1_token, mcuxClRandom_generate(
                                        session,
                                        drbg_buffer1,
                                        3u
                                   ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate) != generate1_token) || (MCUXCLRANDOM_STATUS_OK != rg1_status))
    {
      return MCUXCLEXAMPLE_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Generate random values of multiple of word size. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(rg2_status, generate2_token, mcuxClRandom_generate(
                                        session,
                                        drbg_buffer2,
                                        16u
                                   ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate) != generate2_token) || (MCUXCLRANDOM_STATUS_OK != rg2_status))
    {
      return MCUXCLEXAMPLE_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Generate random values of larger amount than but not multiple of one word size. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(rg3_status, generate3_token, mcuxClRandom_generate(
                                        session,
                                        drbg_buffer3,
                                        31u
                                   ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate) != generate3_token) || (MCUXCLRANDOM_STATUS_OK != rg3_status))
    {
      return MCUXCLEXAMPLE_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* Cleanup                                                                */
    /**************************************************************************/

    /* Random uninit. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(ru_status, uninit_token, mcuxClRandom_uninit(session));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_uninit) != uninit_token) || (MCUXCLRANDOM_STATUS_OK != ru_status))
    {
      return MCUXCLEXAMPLE_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /** Destroy Session and cleanup Session **/
    if(!mcuxClExample_Session_Clean(session))
    {
        return MCUXCLEXAMPLE_ERROR;
    }

    /** Disable the ELS **/
    if(!mcuxClExample_Els_Disable())
    {
        return MCUXCLEXAMPLE_ERROR;
    }

    return MCUXCLEXAMPLE_OK;
}