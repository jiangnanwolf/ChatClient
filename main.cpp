#include <iostream>
#include <string>
#include <cstring> // For std::strerror()
#include <sys/socket.h>
#include <arpa/inet.h> // For inet_addr()
#include <unistd.h> // For close()

int main() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    std::cerr << "Could not create socket: " << std::strerror(errno) << '\n';
  }

  sockaddr_in server;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_family = AF_INET;
  server.sin_port = htons(12345);

  if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
    std::cerr << "Connect failed: " << std::strerror(errno) << '\n';
    return 1;
  }

  std::cout << "Connected\n";


  std::string message;
  std::cout << "Enter message: ";
  std::getline(std::cin, message);

  if (send(sock, message.c_str(), message.size(), 0) < 0) {
    std::cerr << "Send failed: " << std::strerror(errno) << '\n';
    return 1;
  }

  char buffer[1024] = {0};
  ssize_t valread = recv(sock, buffer, 1024, 0);
  std::cout << "Server: " << buffer << '\n';

  close(sock);

  return 0;
}