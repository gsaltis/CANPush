CC				       = gcc
LINK				       = gcc
CC_OPTS				       = -c -g -Wall
CC_INCS				       = 
LINK_OPTS			       = -g 
LINK_LIBS			       = -lutils -llinenoise -lmongoose -lpthread -lm

include					 app.mk

OBJS				       = $(sort					\
					   main.o				\
					   CANInterface.o			\
					   CANIOThread.o			\
					   HTTPServer.o				\
					   UserInterfaceServer.o		\
					   WebSocketServer.o			\
					   WebConnection.o			\
					   WebSocketHTTPConfig.o		\
					  )
LIBS				       = 

%.o				      : %.c
					 @echo [CC] $<
					 @$(CC) $(CC_OPTS) $(CC_INCS) $<

$(TARGET)			       : $(OBJS)
					 @echo [LD] $(TARGET)
					 @$(LINK) $(LINK_OPTS) -o $(TARGET) $(OBJS) $(LINK_LIBS) $(LIBS)

include					 depends.mk

.PHONY				       : junkclean
junkclean			       :
					 rm -rf $(wildcard *~ *-bak www/*~)

.PHONY				       : clean
clean				       : junkclean
					 rm -rf $(wildcard $(OBJS) $(TARGET))
