#include "SocketClient.h"

SocketClient::SocketClient(const std::string& serverAddress, const std::string& serverPort)
    : socket(ioContext) {
    try {
        asio::ip::tcp::resolver resolver(ioContext);
        asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(serverAddress, serverPort);
        asio::connect(socket, endpoints);
    } catch (const std::exception& e) {
        std::cerr << "Error connecting to the server: " << e.what() << std::endl;
    }
}

SocketClient::~SocketClient() {
    if (socket.is_open()) {
        socket.close();
    }
}


bool SocketClient::isConnected() {
    return socket.is_open();
}

void SocketClient::sendData(const IMUData& imuData) {
    /*try {
        std::ostringstream serializedData;
        serializedData.write(reinterpret_cast<const char*>(&imuData), sizeof(IMUData));

        asio::write(socket, asio::buffer(serializedData.str()));
    } catch (const std::exception& e) {
        std::cerr << "Error sending data: " << e.what() << std::endl;
    }*/
    asio::write(socket, asio::buffer(&imuData, sizeof(imuData)));
}