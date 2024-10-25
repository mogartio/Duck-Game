#ifndef GENERIC_MSG_H
#define GENERIC_MSG_H

template<typename HandlerType>

class GenericMsg {
public:
    virtual void accept(HandlerType& handler) = 0;
    virtual ~GenericMsg() = default;
};

#endif 
