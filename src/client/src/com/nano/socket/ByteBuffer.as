package com.nano.socket
{
	import flash.utils.ByteArray;
	
	public class ByteBuffer extends ByteArray
	{
		public function ByteBuffer()
		{
			//TODO: implement function
			super();
		}
		
		public function writeString(s:String):void {
			this.writeUTFBytes(s);
            this.writeByte(0);
		}
		
		public function readString():String {
			// 记录初始位置
			var oldp:uint = this.position,
				len:uint = 0;
			// 读取结束字符串
			while (0 != this.readByte()) {
				len++;
			}
			this.position = oldp;
			return this.readUTFBytes(len);
		}
	}
}