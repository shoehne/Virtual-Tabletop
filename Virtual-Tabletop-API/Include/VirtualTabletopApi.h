#pragma once
#ifndef VIRTUAL_TABLETOP_API_H
#define VIRTUAL_TABLETOP_API_H

//------Core---------------------------------------------------------------
#include "Core/Application.h"
#include "Core/Log.h"
//-------------------------------------------------------------------------

//------Events-------------------------------------------------------------
#include "Events/Event.h"
//-------------------------------------------------------------------------

//------Network------------------------------------------------------------
#include "Network/HostInformation.h"
#include "Network/Socket/UdpSocket.h"
#include "Network/Protocol/PacketAssembler.h"
#include "Network/Protocol/PacketReader.h"
//-------------------------------------------------------------------------

#endif
