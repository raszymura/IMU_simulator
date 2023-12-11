#include "SocketClient.h"


SocketClient::SocketClient(const std::string& serverAddress, const std::string& serverPort)
    : socket(ioContext) {
    try {
        asio::ip::tcp::resolver resolver(ioContext);
        asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(serverAddress, serverPort);
        asio::connect(socket, endpoints);
    } catch (const std::exception& e) {
        std::cerr << "Error connecting to the server: " << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

SocketClient::~SocketClient() {
    if (socket.is_open()) {
        socket.close();
    }
}

void SocketClient::sendRegisters(const IMURegisters& imuRegisters) {
    try {
        // Serialization
        //std::ostringstream serializedData;
        //serializedData.write(reinterpret_cast<const char*>(&imuRegisters), sizeof(IMURegisters));
        //asio::write(socket, asio::buffer(serializedData.str()));
        int messageType = 1;
        asio::write(socket, asio::buffer(&messageType, sizeof(messageType)));

        asio::write(socket, asio::buffer(&imuRegisters, sizeof(imuRegisters)));
    } catch (const std::exception& e) {
        std::cerr << "Error sending data: " << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}


void SocketClient::sendData(const IMUData& imuData) {
    try {
        // Serialization
        //std::ostringstream serializedData;
        //serializedData.write(reinterpret_cast<const char*>(&imuData), sizeof(IMUData));
        //asio::write(socket, asio::buffer(serializedData.str()));
        int messageType = 2;
        asio::write(socket, asio::buffer(&messageType, sizeof(messageType)));

        asio::write(socket, asio::buffer(&imuData, sizeof(imuData)));
    } catch (const std::exception& e) {
        std::cerr << "Error sending data: " << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}


void SocketClient::sendEND() {
    try {
        int messageType = 3;
        asio::write(socket, asio::buffer(&messageType, sizeof(messageType)));
    } catch (const std::exception& e) {
        std::cerr << "Error sending data: " << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}