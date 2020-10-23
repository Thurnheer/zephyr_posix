#include <zephyr.h>
#include <sys/printk.h>
#include <drivers/uart.h>
#include <cop/TransportLinkLayer.hpp>
#include <cop/DataLinkLayer.hpp>
#include <array>
#include "uart.hpp"

enum Events {
    eHelloWorld
};

struct HelloWorld : cop::Event<eHelloWorld> {
    char H = 'H';
    char e = 'e';
    char l = 'l';
    char ll = 'l';
    char o = 'o';
    char s = ' ';
    char W = 'W';
    char oo = 'o';
    char r = 'r';
    char lll = 'l';
    char d = 'd';
    char n = '\n';

    template<class Coder>
    auto parse(Coder coder) {
        return coder | H | e | l | ll | o | s | W | o | r | lll | d | n;
    }
};

class Handler {
public:
    void handle(HelloWorld& hw) {
        printk("hw reseived\n");
    }
};

const static size_t BUF_SIZE = 12;
const std::array<std::byte, BUF_SIZE> buf = {
    std::byte('H'), std::byte('e'), std::byte('l'), std::byte('l'),
    std::byte('o'), std::byte(' '), std::byte('W'), std::byte('o'),
    std::byte('r'), std::byte('l'), std::byte('d'), std::byte('\n')
};

class Channel {
public:
    Channel(Handler& handler) : buffer_(), uart_(), tll_(handler) {}

    void sendEvent(HelloWorld& hw) {
        auto it = buffer_.begin(); auto end = buffer_.end();
        tll_.sendEvent(hw, it, end);
        cop::DataLinkLayer<ReadIt> dll_(it, end);
        dll_.send(uart_);
    }
        
private:
    static constexpr size_t size_ = 128;
    std::array<std::byte, size_> buffer_;
    using ReadIt = std::array<std::byte, size_>::iterator;
    using Itr = std::array<std::byte, size_>::const_iterator;
    Uart<ReadIt> uart_;
    cop::TransportLinkLayer<Handler, ReadIt, std::tuple<HelloWorld> >tll_;

};

int main() {
    k_sleep(K_MSEC(500));
    Handler h;
    Channel c(h);
    HelloWorld hw;
    hw.r = 'R';
    c.sendEvent(hw);
    
    while(1){
        k_sleep(K_MSEC(100));
    }

    return 0;
}

