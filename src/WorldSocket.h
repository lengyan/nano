#include "ace/Message_Block.h"
#include "ace/SOCK_Stream.h"
#include "ace/Svc_Handler.h"
#include "ace/OS.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/Acceptor.h"

class WorldSocket : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH> {
public:
    WorldSocket();
    ~WorldSocket();
    typedef ACE_Acceptor<WorldSocket, ACE_SOCK_ACCEPTOR> Acceptor;
	int open(void * = 0);
	virtual int handle_input(ACE_HANDLE fd = ACE_INVALID_HANDLE);
	virtual int handle_output(ACE_HANDLE fd = ACE_INVALID_HANDLE);
	virtual int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask);
    int handle_input_header(void);
    int handle_input_body(void);
private:
    typedef ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH> super;
    ACE_Message_Block headerBuffer;
    ACE_Message_Block *bodyBuffer;
};
