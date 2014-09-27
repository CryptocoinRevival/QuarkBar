// Copyright (c) 2014-.... f0o / The Cryptocoin Revival Foundation
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "main.h"
#include "pulse.h"

/* Pulse(int64 value, int64 fee, int nHeight, unsigned int nBits) : int64 >= 0
   Returns value of proposed Block using algoritmic aproaches */
static int64 Pulse(int64 value, int64 fee, int nHeight, unsigned int nBits) {
	return value - GetBlockValue(nHeight, fee, nBits);
}

/* Pulse(int nHeight) ? true : false
   Returns true if nHeight is higher or equal to PULSE_HEIGHT */
static bool Pulse(int nHeight) {
	printf("Checking for Pulse on %u: ",nHeight);
	if( PulseI(nHeight) >= 0 ) {
		printf("True\n");
		return true;
	}
	printf("False\n");
	return false;
}

/* Pulse(CBlockIndex* prevBlock, CBlock* block) ? true : false
   Goes close to the top of CBlock::AcceptBlock
   Returns true if proposed Block matches constrains */
static bool Pulse(CBlockIndex* prevBlock, CBlock* block) {
	CBlockHeader blockHead = block->GetBlockHeader();
	CBlockIndex blockIndex = CBlockIndex(blockHead);
	CCoinsViewCache view(*pcoinsTip, true);
	int nHeight = prevBlock->nHeight+1;
	int rate = block->GetBlockTime() - prevBlock->GetBlockTime();
	int score = 0;
	int i = PulseI(nHeight);
	if( PULSE_RATE[i] > 0 && rate > PULSE_RATE[i] ) {
		return true;
	} else if( PULSE_MIN_RATE[i] > 0 && rate < PULSE_MIN_RATE[i] ) {
		return false;
	} else {
		if( PULSE_MIN_TX[i] > 0 && block->vtx.size() > PULSE_MIN_TX[i] ) {
			score++;
		}
		if( PULSE_MIN_VALUE[i] > 0 || PULSE_MIN_FEE[i] > 0 ) {
			int64 value = 0;
			int64 fee = 0;
			BOOST_FOREACH(const CTransaction& tx, block->vtx) {
				if( PULSE_MIN_FEE[i] > 0 && value > 0 ) {
					BOOST_FOREACH(const CTxIn txin, tx.vin)
						if( !view.HaveCoins(txin.prevout.hash) ) {
							return false;
						}
					fee += tx.GetValueIn(view) - tx.GetValueOut();
				}
				value += tx.GetValueOut();
			}
			value = Pulse(value, fee, nHeight, blockIndex.nBits);
			if( PULSE_FACTOR[i] == true ) {
				int64 bvalue = GetBlockValue(nHeight, 0, blockIndex.nBits);
				if( PULSE_MIN_VALUE[i] > 0 && value >= (PULSE_MIN_VALUE[i] * bvalue) ) {
					score++;
				}
				if( PULSE_MIN_FEE[i] > 0 && fee >= (PULSE_MIN_FEE[i] * bvalue) ) {
					score++;
				}
			} else {
				if( PULSE_MIN_VALUE[i] > 0 && value >= (PULSE_MIN_VALUE[i] * COIN) ) {
					score++;
				}
				if( PULSE_MIN_FEE[i] > 0 && fee >= (PULSE_MIN_FEE[i] * COIN) ) {
					score++;
				}
			}
		}
	}
	if( PULSE_EXPLICIT[i] ) {
		score++;
		if( PULSE_MIN_TX[i] > 0 )
			score--;
		if( PULSE_MIN_VALUE[i] > 0 )
			score--;
		if( PULSE_MIN_FEE[i] > 0 )
			score--;
	}
	if( score > 0 )
		return true;
	else
		return false;
}
