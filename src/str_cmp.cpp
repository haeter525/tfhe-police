//==================================================================================
// BSD 2-Clause License
//
// Copyright (c) 2014-2022, NJIT, Duality Technologies Inc. and other contributors
//
// All rights reserved.
//
// Author TPOC: contact@openfhe.org
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//==================================================================================

/*
  Example for the FHEW scheme using the default bootstrapping method (GINX)
 */

#include "binfhecontext.h"
#include "str_cmp.h"

using namespace lbcrypto;
LWECiphertext byte_comp(LWECiphertext b1[8], LWECiphertext b2[8], ConstLWEPrivateKey sk, BinFHEContext cc){
	auto check = cc.Encrypt(sk, 1);
	for(int i = 0 ;i < 5; i++){
		auto temp = cc.EvalBinGate(XNOR, b1[i], b2[i]);
		check = cc.EvalBinGate(AND, check, temp);	
	}
	return check;
}
LWECiphertext str_comp(LWECiphertext s1[8][5], LWECiphertext s2[8][5], ConstLWEPrivateKey sk, BinFHEContext cc){
	auto check = cc.Encrypt(sk, 1);
	for(int i = 0 ;i < 8; i++){
		auto temp = byte_comp(s1[i], s2[i], sk, cc);
		check = cc.EvalBinGate(AND, check, temp);	
	}
	return check;
}



