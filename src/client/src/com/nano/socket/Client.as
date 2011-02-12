package com.nano.socket {
    import flash.events.*;
    import flash.net.Socket;
    import flash.system.Security;
    import flash.utils.ByteArray;
	
    public class Client extends EventDispatcher{
        private var host:String;
        private var port:int;
        private var socket:Socket;
        private var state:int = 0;
		private var isReadHead:Boolean = false;
		
		
		private var headLen:uint = 4;
		private var bodyLen:uint;
		private var headerBuffer:ByteArray = new ByteArray();
		private var bodyBuffer:ByteBuffer = new ByteBuffer();
        private var opcode:uint;
        
        public function Client() {
        }
		
		public function connect(server:String, port:int):void {
			
			// set class variables to the values passed to the constructor.
			host = server;
			port = port;
			
			// Create a new Socket object and assign event listeners.
			socket = new Socket();
			socket.addEventListener(Event.CONNECT, connectHandler);
			socket.addEventListener(Event.CLOSE, closeHandler);
			socket.addEventListener(ErrorEvent.ERROR, errorHandler);
			socket.addEventListener(IOErrorEvent.IO_ERROR, ioErrorHandler);
			socket.addEventListener(ProgressEvent.SOCKET_DATA, dataHandler);
			
			// Load policy file from remote server.
			Security.loadPolicyFile("http://" + host + "/crossdomain.xml");
			
			// Attempt to connect to remote socket server.
			try {
				trace("Trying to connect to " + host + ":" + port);
				socket.connect(host, port);
			} catch (error:Error) {
				/*
				Unable to connect to remote server, display error 
				message and close connection.
				*/
				trace(error.message);
				socket.close();
			}
		}
        
        /**
         * This method is called if the socket encounters an ioError event.
         */
        public function ioErrorHandler(event:IOErrorEvent):void {
            trace("Unable to connect: socket error.");
        }
        
        /**
         * This method is called by our application and is used to send data
         * to the server.
         * TODO 修复发送失败的情况
         */
        public function send(opcode:uint, ba:ByteBuffer):void {
			var allBytes:ByteArray = new ByteArray();
			allBytes.writeShort(ba.length);
			allBytes.writeShort(opcode);
			allBytes.writeBytes(ba);
			
            socket.writeBytes(allBytes);
            socket.flush();
        }
        
        private function connectHandler(event:Event):void {
            if (socket.connected) {
                trace("connected...and send auth info");
				// 开始发送认证信息
				var authBodyBytes:ByteBuffer = new ByteBuffer();
				authBodyBytes.writeInt(1);
				send(Opcode.CMSG_AUTH_SESSION, authBodyBytes);
            } else {
                trace("unable to connect");
            }
        }
        
        /**
         * This method is called when the socket connection is closed by 
         * the server.
         */
        private function closeHandler(event:Event):void {
            trace("closed...");
        }
        
        /**
         * This method is called if the socket throws an error.
         */
        private function errorHandler(event:ErrorEvent):void {
            trace(event.text);
        }
        
        /**
         * This method is called when the socket receives data from the server.
         */
        private function dataHandler(event:ProgressEvent):void {
			var readLen:uint = 0;
			
			// 如果消息头长度还不够
			if (headerBuffer.length < headLen) {
				readLen = socket.bytesAvailable > (headLen - headerBuffer.length) ? (headLen - headerBuffer.length) : socket.bytesAvailable;
				if (readLen > 0) {
					//处理数据
					socket.readBytes(headerBuffer, headerBuffer.length, readLen);                   
					
					if (headerBuffer.length < headLen)
						return;
					
					bodyLen = headerBuffer.readShort();
                    opcode = headerBuffer.readShort();
					headerBuffer.clear();
				}
			}
			
			// 如果消息体长度不够
			if (bodyBuffer.length < bodyLen) {
				readLen = socket.bytesAvailable > (bodyLen - bodyBuffer.length) ? (bodyLen - bodyBuffer.length) : socket.bytesAvailable;
				if (readLen > 0) {
					//处理数据
					socket.readBytes(bodyBuffer, bodyBuffer.length, readLen);
					
					if (bodyBuffer.length < bodyLen)
						return;
					
                    dispatchEvent(new OpcodeEvent(opcode, bodyBuffer));
					
					bodyBuffer.clear();
				}
			}
        }
    }
}
