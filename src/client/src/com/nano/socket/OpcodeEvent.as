package com.nano.socket
{
    import flash.events.Event;

    public class OpcodeEvent extends Event
    {
        public var packet:ByteBuffer;
        public var opcode:uint;
        
        public function OpcodeEvent(opcode:uint, packet:ByteBuffer) {
            this.packet = packet;
            this.opcode = opcode;
            super(Opcode.EventTypes[opcode]);
        }
    }
}