#include <termios.h>
#include <unistd.h>

struct termios original_terminal_config;

void enable_raw_mode(void)
{
    // copies the current terminal configuration to original_terminal_config
    tcgetattr(STDIN_FILENO, &original_terminal_config);
    
    // deep copy is not needed
    struct termios raw = original_terminal_config;
    
    /*
        ISIG      Enable SIGINTR, SIGSUSP, SIGDSUSP, and SIGQUIT signals
        ICANON    Enable canonical input (else raw)
        ECHO      Enable echoing of input characters
        ECHOE     Echo erase character as BS-SP-BS
        IEXTEN    Enable extended functions
        
        &= ~(...) means disable, not enable
    */
    raw.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG | IEXTEN);
    
    /*
        Sets the character size to 8 bits (CS8)
    */
    raw.c_cflag &= ~CSIZE;
    raw.c_cflag |= CS8;
    
    /*
        INPCK      Enable parity check
        ISTRIP     Strip parity bits
        IXON       Enable software flow control (outgoing)
        IGNBRK     Ignore break condition
        BRKINT     Send a SIGINT when a break condition is detected
        
        &= ~(...) means disable, not enable
    */
    raw.c_iflag &= ~(IXON | BRKINT | ICRNL | INPCK | ISTRIP);
    
    
    /*
        OPOST    Postprocess output (not set = raw output)
    */
    raw.c_oflag &= ~(OPOST);
    
    
    /*
        VMIN     Minimum number of characters to read
        VTIME    Time to wait for data (tenths of seconds)
        
        If no key is pressed after 1/10 of second, then 'read' will return 0
    */
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_terminal_config);
}

