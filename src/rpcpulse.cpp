// Copyright (c) 2014-.... f0o / The Cryptocoin Revival Foundation
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "main.h"
#include "rpcpulse.h"
#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost;
using namespace boost::assign;
using namespace json_spirit;

/* Patches
   - bitcoinrpc.cpp:
      #include "rpcpulse.h"
      CRPCCommand:
       { "getpulseinfo",           &getpulseinfo,           true,      false },
*/

/* getpulseinfo(const Array& params, bool fHelp) : Object
   Expose Pulse-Settings via RPC */
json_spirit::Value getpulseinfo(const Array& params, bool fHelp) {
	if (fHelp || params.size() != 0)
		throw std::runtime_error("getpulseinfo\nReturns an object containing various pulse info.");
	int i = PulseI(nBestHeight);
	if( i == -1 )
		throw JSONRPCError(-32601, "Pulse not active");
	json_spirit::Object obj;
	obj.push_back(json_spirit::Pair("height",       (int)PULSE_HEIGHT[i]));
	obj.push_back(json_spirit::Pair("rate",         (int)PULSE_RATE[i]));
	if( PULSE_MIN_RATE[i] > 0 )
		obj.push_back(json_spirit::Pair("min-rate",   (int)PULSE_MIN_RATE[i]));
	if( PULSE_MIN_TX[i] > 0 )
		obj.push_back(json_spirit::Pair("min-tx",     (int)PULSE_MIN_TX[i]));
	if( PULSE_MIN_VALUE[i] > 0 )
		obj.push_back(json_spirit::Pair("min-value",  (int)PULSE_MIN_VALUE[i]));
	if( PULSE_MIN_FEE[i] > 0 )
		obj.push_back(json_spirit::Pair("min-fee",    (int)PULSE_MIN_FEE[i]));
	if( PULSE_MIN_TX[i] > 0 )
		obj.push_back(json_spirit::Pair("min-tx",     (int)PULSE_MIN_TX[i]));
	obj.push_back(json_spirit::Pair("factor",       PULSE_FACTOR[i]));
	obj.push_back(json_spirit::Pair("explicit",     PULSE_EXPLICIT[i]));
	return obj;
}
