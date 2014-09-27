// Copyright (c) 2014-.... f0o / The Cryptocoin Revival Foundation
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef RPCPULSE_H
#define RPCPULSE_H 1

#include "json/json_spirit_reader_template.h"
#include "json/json_spirit_writer_template.h"
#include "json/json_spirit_utils.h"
#include "pulse.h"

extern json_spirit::Value getpulseinfo(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Object JSONRPCError(int code, const std::string& message);

#endif