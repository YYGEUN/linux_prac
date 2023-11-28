import socket, threading # 소켓 : 네트워크 기반
                         # 쓰레드 : 클라이언트와 통신이 하기 위한 쓰레드 (추가된 쓰레드)
                                #    다른 클라이언트 접속하는 것을 확인 쓰레드 (main)

def connected(client_socket, addr):
    print('Connected by', addr);

    try:
        while True:
            data = client_socket.recv(4);
            length = int.from_bytes(data, "little");
            data = client_socket.recv(length);
            msg = data.decode();
            print('Received from', addr, msg);
            msg = "echo : " + msg;
            data = msg.encode();
            length = len(data);
            client_socket.sendall(length.to_bytes(4, byteorder="little"));
            client_socket.sendall(data);
    except:
        print("except : " , addr);
    finally:
        client_socket.close();

# 소켓을 생성하는 코드,                                 TCP, datagram (UDP)
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
# 소켓 옵션
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1);
# 바인딩 작업 - 127.0.0.1, port = 9999
server_socket.bind(('', 9999));
# listen 상태로 전환
server_socket.listen(); 

try:
    while True:
        client_socket, addr = server_socket.accept(); #접속을 기다림
        th = threading.Thread(target=connected, args = (client_socket,addr));
        th.start();
except:
    print("server");
finally:
    server_socket.close();
