# QUdpPing
 a udp ping app based on qt
 
## How to Use
1. Run this application both on client and server.
2. Bind port(both on client and server) by clicking the 'listen' button.
3. Then ping!

 If you want to ping your remote server without GUI, you need to use other ways to response to client.  
 My way to handle it is to write a python script and run it on my server.
```
#!/usr/bin/python3
import socket


s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(('0.0.0.0', 8888))

while True:
    data, addr = s.recvfrom(32)
    s.sendto("return".encode('utf-8'), addr)

```
 Don't forget to check the firewall status on your server!
