/*
 *  Copyright 2016 Bjango Pty Ltd. All rights reserved.
 *  Copyright 2010 William Tisäter. All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *    1.  Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *
 *    2.  Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *
 *    3.  The name of the copyright holder may not be used to endorse or promote
 *        products derived from this software without specific prior written
 *        permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER ``AS IS'' AND ANY
 *  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL WILLIAM TISÄTER BE LIABLE FOR ANY
 *  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _DAEMON_H
#define _DAEMON_H

#include <iostream>
#include <signal.h>

#include "Socket.h"
#include "Socketset.h"
#include "Clientset.h"
#include "Stats.h"
#include "Avahi.h"

class Daemon
{
	public:
		Daemon(const std::string &_pidfile, const std::string &_sockfile) : pidfile(_pidfile), sockfile(_sockfile) {}
		
		void create(bool _back, const std::string &_user, const std::string &_group);
		void destroy();
		void publish(int port, int protocol, std::string name, std::string uuid, int platform);		
	private:
		std::string pidfile;
		std::string sockfile;
};

class SignalResponder
{
	public:
		SignalResponder(SocketSet *_sockets, Socket *_listener, Daemon *_unixdaemon, Stats *_stats) : listener(_listener), sockets(_sockets), unixdaemon(_unixdaemon), stats(_stats) {}
		
		void destroy();
		void on_sigint();
		void on_sigterm();
		void on_sighup();

	private:
		Socket * listener;
		SocketSet * sockets;
		Daemon * unixdaemon;
		Stats * stats;
};

#endif
