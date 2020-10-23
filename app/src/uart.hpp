#ifndef COP_ON_ZEPHYR_UART_HPP
#define COP_ON_ZEPHYR_UART_HPP

#include <zephyr.h>
#include <cstddef>
#include <drivers/uart.h>

template<class Iterator>
class Uart {
public:
    Uart()
    : uart_(device_get_binding(CONFIG_UART_CONSOLE_ON_DEV_NAME))
    , begin_()
    , end_()
    {
        uart_irq_callback_user_data_set(uart_, tx_callback, this);
        tx_callback(uart_, this);
    }

    ~Uart(){
        uart_irq_tx_disable(uart_);
        uart_irq_rx_disable(uart_);
    }

    void send(Iterator begin, Iterator end)
    {
        begin_ = begin;
        end_ = end;
        uart_irq_tx_enable(uart_);
    }

private:
    static void tx_callback(const struct device* dev, void* uart)
    {
        Uart* this_ = reinterpret_cast<Uart*>(uart);
        if(!uart_irq_update(dev)) {
            return;
        }
        if(uart_irq_tx_ready(dev) && this_->begin_ != this_->end_) {
            uart_fifo_fill(dev, (uint8_t*)&(*this_->begin_), 1);
            this_->begin_++;
            if(this_->begin_ == this_->end_) {
                uart_irq_tx_disable(dev);
            }
        }
        if(uart_irq_rx_ready(dev)) {
            uint8_t recData;
            uart_fifo_read(dev, &recData, 1);
            this_->receive(std::byte(recData));
        }
    }

    void receive(std::byte data){
    }
    const struct device* uart_;
    Iterator begin_;
    Iterator end_;

};

#endif // COP_ON_ZEPHYR_UART_HPP

