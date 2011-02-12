package com.nano.socket
{
	public final class Opcode
	{
		// 认证
		public static const CMSG_AUTH_SESSION:uint          = 0x0000;
        
		// 聊天
		public static const CMSG_CHAT_SAY:uint              = 0x0001;
		public static const SMSG_CHAT_SAY:uint              = 0x0002;
		public static const CMSG_CHAT_WHISPER:uint          = 0x0003;
		public static const SMSG_CHAT_WHISPER:uint          = 0x0004;
		public static const CMSG_CHAT_CHANNEL:uint          = 0x0005;
		public static const SMSG_CHAT_CHANNEL:uint          = 0x0006;
		public static const CMSG_CHAT_CHANNEL_JOIN:uint     = 0x0007;
		public static const SMSG_CHAT_CHANNEL_JOIN:uint     = 0x0008;
		public static const CMSG_CHAT_CHANNEL_LEAVE:uint    = 0x0009;
		public static const SMSG_CHAT_CHANNEL_LEAVE:uint    = 0x000A;
		public static const CMSG_CHAT_CHANNEL_LIST:uint     = 0x000B;
		public static const SMSG_CHAT_CHANNEL_LIST:uint     = 0x000C;
		
        
        public static const EventTypes:Array = [
            "CMSG_AUTH_SESSION",
            "CMSG_CHAT_SAY",
            "SMSG_CHAT_SAY",
            "CMSG_CHAT_WHISPER",
            "SMSG_CHAT_WHISPER",
            "CMSG_CHAT_CHANNEL",
            "SMSG_CHAT_CHANNEL",
            "CMSG_CHAT_CHANNEL_JOIN",
            "SMSG_CHAT_CHANNEL_JOIN",
            "CMSG_CHAT_CHANNEL_LEAVE",
            "SMSG_CHAT_CHANNEL_LEAVE",
            "CMSG_CHAT_CHANNEL_LIST",
            "SMSG_CHAT_CHANNEL_LIST"
        ];
        
            
		public function Opcode()
		{
		}
	}
}