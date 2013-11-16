/**
 * MicrosonicBot an IRC Bot
 *
 * (C) 2010 DENNIS J. MCWHERTER JR. All Rights Reserved.
 */

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "IRC.h"

int main(int argc,char* argv[])
{
	IRC * irc = new IRC();
	if(irc->ConnectToIRC())
	{
		while(!irc->FatalError)
		{
			recv(irc->dataSock, irc->recvBuf, 512, 0);
			irc->HandleIRCMsg();
		}
	}

	irc->QuitIRC();
	delete irc;
	
	printf("\r\n\r\nPlease hit return to exit...\n");
	std::getchar();

	return 0;
}
