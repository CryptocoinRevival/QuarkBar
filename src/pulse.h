// Copyright (c) 2014-.... f0o / The Cryptocoin Revival Foundation
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PULSE_H
#define PULSE_H 1

class CBlock;
class CBlockIndex;
class CCoinsView;
class CCoinsViewCache;
static int64 GetBlockValue(int nHeight, int64 nFees, unsigned int nBits);
extern CCoinsViewCache *pcoinsTip;

static const          int PULSE_HEIGHT[]    = { 625000 }; /** Height to start Pulse */
static const          int PULSE_RATE[]      = {    300 }; /** Rate to Pulse in seconds */
static const          int PULSE_MIN_RATE[]  = {     30 }; /** Rate to Pulse in seconds */
static const unsigned int PULSE_MIN_TX[]    = {      0 }; /** Minimum amount (not value of!) of TX in a block to bypass Pulse-Rate */
static const          int PULSE_MIN_VALUE[] = {     10 }; /** Minimum value of the TX in a block to bypass Pulse-Rate (without COIN base) */
static const          int PULSE_MIN_FEE[]   = {      0 }; /** Minimum value of accumulated fees of the TX in a block to bypass Pulse-Rate (without COIN base) */
static const         bool PULSE_FACTOR[]    = {  false }; /** Treat Switches as factors of BlockReward */
static const         bool PULSE_EXPLICIT[]  = {  false }; /** Require all switches to trigger a block */

static bool Pulse(int nHeight);
static bool Pulse(CBlockIndex* prevBlock, CBlock* block);

/* PulseI(int nHeight) ? i : -1
   Returns i or -1 if not found */
static int PulseI(int nHeight) {
	int i = -1;
	BOOST_FOREACH(int h, PULSE_HEIGHT)
		if( nHeight >= h )
			i++;
	return i;
}

#endif
