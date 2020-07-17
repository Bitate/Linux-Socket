#include <string.h>

#define LITTLE_ENDIAN_BITFIELD

struct tcp_header
{
    unsigned short source;
    unsigned short dest;
    
    unsigned int seq;
    unsigned int ack_seq;

    // we need to check little endian or big endian
#if defined(LITTLE_ENDIAN_BITFIELD)
    unsigned short resv:4,
                   fin:1,
                   syn:1,
                   rst:1,
                   psh:1,
                   ack:1,
                   urg:1,
                   ece:1,
                   cwr:1;
#elif defined(BIG_ENDIAN_BITFIELD)
    unsigned short resv:4,// Reserved
                   cwr:1, // Congestion Window Reduced
                   ece:1, // ECN Echo
                   urg:1, // Urgent
                   ack:1, // Acknowledgment
                   psh:1, // Push
                   rst:1, // Reset the connection
                   syn:1, // Synchronize Sequence numbers
                   fin:1; // Finished sending data.
#endif

    unsigned short window;
    unsigned short check;
    unsigned short urg_ptr;
};

// TCP states
enum
{
    TCP_ESTABLISHED = 1,
    TCP_SYN_SENT,
    TCP_SYN_RECV,
    TCP_FIN_WAIT1,
    TCP_FIN_WAIT2,
    TCP_TIME_WAIT,
    TCP_CLOSE,
    TCP_CLOSE_WAIT,
    TCP_LAST_ACK,
    TCP_LISTEN,
    TCP_CLOSING,

    TCP_MAX_STATES
};

