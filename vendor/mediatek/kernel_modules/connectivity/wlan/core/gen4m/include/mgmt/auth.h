/******************************************************************************
 *
 * This file is provided under a dual license.  When you use or
 * distribute this software, you may choose to be licensed under
 * version 2 of the GNU General Public License ("GPLv2 License")
 * or BSD License.
 *
 * GPLv2 License
 *
 * Copyright(C) 2016 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 *
 * BSD LICENSE
 *
 * Copyright(C) 2016 MediaTek Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************/
/*
 * Id: //Department/DaVinci/BRANCHES/MT6620_WIFI_DRIVER_V2_3/
 *							include/mgmt/auth.h#1
 */

/*! \file  auth.h
 *    \brief This file contains the authentication REQ/RESP of
 *	   IEEE 802.11 family for MediaTek 802.11 Wireless LAN Adapters.
 */


#ifndef _AUTH_H
#define _AUTH_H

/*******************************************************************************
 *                         C O M P I L E R   F L A G S
 *******************************************************************************
 */

/*******************************************************************************
 *                    E X T E R N A L   R E F E R E N C E S
 *******************************************************************************
 */

/*******************************************************************************
 *                              C O N S T A N T S
 *******************************************************************************
 */

/*******************************************************************************
 *                         D A T A   T Y P E S
 *******************************************************************************
 */

/*******************************************************************************
 *                            P U B L I C   D A T A
 *******************************************************************************
 */

/*******************************************************************************
 *                           P R I V A T E   D A T A
 *******************************************************************************
 */

/*******************************************************************************
 *                                 M A C R O S
 *******************************************************************************
 */

/*******************************************************************************
 *                  F U N C T I O N   D E C L A R A T I O N S
 *******************************************************************************
 */
/*----------------------------------------------------------------------------*/
/* Routines in auth.c                                                         */
/*----------------------------------------------------------------------------*/
void authAddIEChallengeText(struct ADAPTER *prAdapter,
			    struct MSDU_INFO *prMsduInfo);

#if !CFG_SUPPORT_AAA
uint32_t authSendAuthFrame(struct ADAPTER *prAdapter,
			   struct STA_RECORD *prStaRec,
			   uint16_t u2TransactionSeqNum);
#else
uint32_t
authSendAuthFrame(struct ADAPTER *prAdapter,
			  struct STA_RECORD *prStaRec,
			  uint8_t uBssIndex,
			  struct SW_RFB *prFalseAuthSwRfb,
			  uint16_t u2TransactionSeqNum,
			  uint16_t u2StatusCode);
#endif /* CFG_SUPPORT_AAA */

uint32_t authCheckTxAuthFrame(struct ADAPTER *prAdapter,
			struct MSDU_INFO *prMsduInfo,
			uint16_t u2TransactionSeqNum);

uint32_t authCheckRxAuthFrameTransSeq(struct ADAPTER
			*prAdapter, struct SW_RFB *prSwRfb);

uint32_t
authCheckRxAuthFrameStatus(struct ADAPTER *prAdapter,
			   struct SW_RFB *prSwRfb,
			   uint16_t u2TransactionSeqNum,
			   uint16_t *pu2StatusCode);

uint32_t authHandleIEChallengeText(struct ADAPTER *prAdapter,
		struct SW_RFB *prSwRfb, struct IE_HDR *prIEHdr);

uint32_t authHandleRSNE(struct ADAPTER *prAdapter,
		struct SW_RFB *prSwRfb, struct IE_HDR *prIEHdr);

uint32_t authProcessRxAuth2_Auth4Frame(struct ADAPTER
				       *prAdapter, struct SW_RFB *prSwRfb);

uint32_t
authSendDeauthFrame(struct ADAPTER *prAdapter,
		    struct BSS_INFO *prBssInfo,
		    struct STA_RECORD *prStaRec,
		    struct SW_RFB *prClassErrSwRfb, uint16_t u2ReasonCode,
		    PFN_TX_DONE_HANDLER pfTxDoneHandler);

uint32_t authProcessRxDeauthFrame(struct SW_RFB *prSwRfb,
			uint8_t aucBSSID[], uint16_t *pu2ReasonCode);

uint32_t
authProcessRxAuth1Frame(struct ADAPTER *prAdapter,
			struct SW_RFB *prSwRfb,
			uint8_t aucExpectedBSSID[],
			uint16_t u2ExpectedAuthAlgNum,
			uint16_t u2ExpectedTransSeqNum,
			uint16_t *pu2ReturnStatusCode);
uint32_t
authProcessRxAuthFrame(struct ADAPTER *prAdapter,
			struct SW_RFB *prSwRfb,
			struct BSS_INFO *prBssInfo,
			uint16_t *pu2ReturnStatusCode);

void authAddMDIE(struct ADAPTER *prAdapter,
		 struct MSDU_INFO *prMsduInfo);

uint32_t authCalculateFTIELen(struct ADAPTER *prAdapter, uint8_t ucBssIdx,
			     struct STA_RECORD *prStaRec);

void authAddFTIE(struct ADAPTER *prAdapter,
		 struct MSDU_INFO *prMsduInfo);

uint32_t authCalculateRSNIELen(struct ADAPTER *prAdapter, uint8_t ucBssIdx,
			       struct STA_RECORD *prStaRec);

void authAddRSNIE(struct ADAPTER *prAdapter,
		  struct MSDU_INFO *prMsduInfo);

uint32_t authAddRSNIE_impl(struct ADAPTER *prAdapter,
		  struct MSDU_INFO *prMsduInfo, uint8_t ucR0R1);

void authHandleFtIEs(struct ADAPTER *prAdapter, struct SW_RFB *prSwRfb,
		     struct IE_HDR *prIEHdr);

u_int8_t
authFloodingCheck(struct ADAPTER *prAdapter,
		struct BSS_INFO *prP2pBssInfo,
		struct SW_RFB *prSwRfb);

#endif /* _AUTH_H */
