#include <zephyr.h>
#include <sys/printk.h>
#include <drivers/uart.h>
#include <cop/TransportLinkLayer.hpp>
#include <cop/DataLinkLayer.hpp>
#include <array>

class Adapter {
public:
    void send(std::byte& data) noexcept {
        buffer_[pos_++] = data;
        if(pos_ == size_)
            pos_ = 0;
    }
private:
    static constexpr size_t size_ = 512;
    std::array<std::byte, size_> buffer_;
    int pos_ = 0;
};

enum Events {
    eHelloWorld
};

struct HelloWorld : cop::Event<eHelloWorld> {
    int data = 0;

    template<class Coder>
    auto parse(Coder coder) {
        return coder | data;
    }
};

class Handler {
public:
    void handle(HelloWorld& hw) {
        printk("hw reseived\n");
    }
};

class Channel {
public:
    Channel(Handler& handler) : buffer_(), adapter_(), tll_(handler) {}

    void sendEvent(HelloWorld& hw) {
        auto it = buffer_.begin(); auto end = buffer_.end();
        tll_.sendEvent(hw, it, end);
        cop::DataLinkLayer<ReadIt> dll_(it, end);
        dll_.send(adapter_);
    }
        
private:
    static constexpr size_t size_ = 512;
    std::array<std::byte, size_> buffer_;
    using ReadIt = std::array<std::byte, size_>::iterator;
    Adapter adapter_;
    cop::TransportLinkLayer<Handler, ReadIt, std::tuple<HelloWorld> >tll_;

};

int main() {

    HelloWorld hw;
    Handler h;
    Channel c(h);
    while(1) {
        hw.data++;
        c.sendEvent(hw);
        k_msleep(1000);
    }

    return 0;
}

