#pragma once

#include <iostream>
#include <asio.hpp>
#include "IMU.h"

class SocketClient {
private:
    asio::io_context ioContext;
    asio::ip::tcp::socket socket;

public:
    SocketClient(const std::string& serverAddress, const std::string& serverPort);
    ~SocketClient();

    bool isConnected();
    
    void sendData(const IMUData& imuData);
    void sendRegisters(const IMURegisters& imuRegisters);
};