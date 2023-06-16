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
	for(int i = 0 ;i < 8; i++){
		auto temp = cc.EvalBinGate(XNOR, b1[i], b2[i]);
		check = cc.EvalBinGate(AND, check, temp);	
	}
	return check;
}
LWECiphertext str_comp(LWECiphertext s1[8][8], LWECiphertext s2[8][8], ConstLWEPrivateKey sk, BinFHEContext cc){
	auto check = cc.Encrypt(sk, 1);
	for(int i = 0 ;i < 8; i++){
		auto temp = byte_comp(s1[i], s2[i], sk, cc);
		check = cc.EvalBinGate(AND, check, temp);	
	}
	return check;
}
/*
int main() {
    // Sample Program: Step 1: Set CryptoContext

    auto cc = BinFHEContext();

    // STD128 is the security level of 128 bits of security based on LWE Estimator
    // and HE standard. Other common options are TOY, MEDIUM, STD192, and STD256.
    // MEDIUM corresponds to the level of more than 100 bits for both quantum and
    // classical computer attacks.
    cc.GenerateBinFHEContext(STD128);

    // Sample Program: Step 2: Key Generation

    // Generate the secret key
    auto sk = cc.KeyGen();

    std::cout << "Generating the bootstrapping keys..." << std::endl;

    // Generate the bootstrapping keys (refresh and switching keys)
    cc.BTKeyGen(sk);

    std::cout << "Completed the key generation." << std::endl;
    
    // Sample Program: Step 3: Encryption
    
    // Encrypt two ciphertexts representing Boolean True (1).
    // By default, freshly encrypted ciphertexts are bootstrapped.
    // If you wish to get a fresh encryption without bootstrapping, write
    // auto   ct1 = cc.Encrypt(sk, 1, FRESH);
    //auto ct1 = cc.Encrypt(sk, 1);
    //auto ct2 = cc.Encrypt(sk, 0);

    // Sample Program: Step 4: Evaluation

    // Compute (1 AND 1) = 1; Other binary gate options are OR, NAND, and NOR
    //auto ctAND1 = cc.EvalBinGate(AND, ct1, ct2);

    // Compute (NOT 1) = 0
    //auto ct2Not = cc.EvalNOT(ct2);

    // Compute (1 AND (NOT 1)) = 0
    //auto ctAND2 = cc.EvalBinGate(AND, ct2Not, ct1);

    // Computes OR of the results in ctAND1 and ctAND2 = 1
    //auto ctResult = cc.EvalBinGate(OR, ctAND1, ctAND2);
    //auto ctResult = cc.EvalBinGate(XNOR, ct1, ct2);
    //auto ctResult2 = cc.EvalBinGate(XOR, ct1, ctResult);
    // Sample Program: Step 5: Decryption

    LWEPlaintext result[16];
    for(int i = 0;i < 16; i++){
    	cc.Decrypt(sk, ct[i], &result[i]);
    	std:: cout << result[i] << " ";
    }
    std:: cout << std::endl; 
    ///std::cout << "Result of encrypted computation of (1 AND 1) OR (1 AND (NOT 1)) = " << result << std::endl;
    bool str1[8][8], str2[8][8];
    for(int i = 0;i < 8; i++){
    	for(int j = 0;j < 8; j++){
    		if(i % 2){
    			str1[i][j] = 1;
    			str2[i][j] = 1;
    		}
    		else {
    			str1[i][j] = 0;
    			str2[i][j] = 0;
    		}
    	}
    }
    str2[6][5] = 1;
  
    LWECiphertext c1[8][8], c2[8][8];
    for(int i = 0;i < 8; i++){
    	for(int j = 0;j < 8; j++){
    		c1[i][j] = cc.Encrypt(sk,str1[i][j]);
    		c2[i][j] = cc.Encrypt(sk,str2[i][j]);
    	}
    }
    
    auto res = str_comp(c1, c2, sk, cc);
    LWEPlaintext result;
    cc.Decrypt(sk, res, &result);
    std:: cout << result << std::endl;
    
    return 0;
}*/


