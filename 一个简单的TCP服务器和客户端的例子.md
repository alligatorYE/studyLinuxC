一个简单的TCP服务器和客户端的例子：

服务器端代码：

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8888

int main(int argc, char *argv[]) {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buf[1024];

    // 创建socket文件描述符
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 设置socket选项，允许地址重用
    int optval = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // 绑定地址和端口
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // 监听端口
    if (listen(server_fd, 10) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is running on port %d...\n", PORT);

    while (1) {
        // 接受客户端连接
        if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len)) == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        printf("New connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // 读取客户端发送的数据
        memset(buf, 0, sizeof(buf));
        if (read(client_fd, buf, sizeof(buf)) == -1) {
            perror("read");
            close(client_fd);
            continue;
        }

        printf("Received data from client: %s\n", buf);

        // 发送数据给客户端
        if (write(client_fd, "Hello, client!", 14) == -1) {
            perror("write");
            close(client_fd);
            continue;
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}
```

客户端代码：

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8888

int main(int argc, char *argv[]) {
    int client_fd;
    struct sockaddr_in server_addr;
    char buf[1024];

    // 创建socket文件描述符
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址和端口
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) != 1) {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    // 连接服务器
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server %s:%d.\n", SERVER_IP, PORT);

    // 发送数据给服务器
    if (write(client_fd, "Hello, server!", 14) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    // 读取服务器发送的数据
    memset(buf, 0, sizeof(buf));
    if (read(client_fd, buf, sizeof(buf)) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    printf("Received data from server: %s\n", buf);

    close(client_fd);
    return 0;
}
```

使用方法：

1. 编译服务器端代码：`gcc server.c -o server`
2. 启动服务器：`./server`
3. 编译客户端代码：`gcc client.c -o client`
4. 启动客户端：`./client`