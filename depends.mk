CANInterface.o: CANInterface.c CANInterface.h
CANIOThread.o: CANIOThread.c CANInterface.h CANIOThread.h
HTTPServer.o: HTTPServer.c HTTPServer.h WebSocketServer.h \
 WebSocketHTTPConfig.h
main.o: main.c main.h mainconfig.h HTTPServer.h UserInterfaceServer.h \
 WebSocketServer.h WebSocketHTTPConfig.h
UserInterfaceServer.o: UserInterfaceServer.c UserInterfaceServer.h
WebConnection.o: WebConnection.c WebConnection.h WebSocketHTTPConfig.h
WebSocketHTTPConfig.o: WebSocketHTTPConfig.c WebSocketHTTPConfig.h
WebSocketServer.o: WebSocketServer.c WebSocketServer.h WebConnection.h \
 UserInterfaceServer.h main.h WebSocketHTTPConfig.h
