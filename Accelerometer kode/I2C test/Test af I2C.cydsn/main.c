//#include "project.h"
//#include <stdio.h>
//
//#define BNO085_ADDR 0x4A
//
//uint8 buffer[64];
//uint8 seq = 0;
//
//// -------------------------
//// I2C write
//// -------------------------
//void I2C_Write(uint8 *data, uint8 len)
//{
//    I2C_MasterSendStart(BNO085_ADDR, I2C_WRITE_XFER_MODE);
//
//    for(uint8 i = 0; i < len; i++)
//        I2C_MasterWriteByte(data[i]);
//
//    I2C_MasterSendStop();
//}
//
//// -------------------------
//// Read EXACT number of bytes
//// -------------------------
//void I2C_Read(uint8 *buf, uint16 len)
//{
//    I2C_MasterSendStart(BNO085_ADDR, I2C_READ_XFER_MODE);
//
//    for(uint16 i = 0; i < len; i++)
//    {
//        buf[i] = I2C_MasterReadByte(
//            (i < len - 1) ? I2C_ACK_DATA : I2C_NAK_DATA
//        );
//    }
//
//    I2C_MasterSendStop();
//}
//
//// -------------------------
//// Enable Rotation Vector (CORRECT LENGTH)
//// -------------------------
//void EnableRotationVector(void)
//{
//    uint8 cmd[] =
//    {
//        0x02, 0x00, 0x11, 0x00,  // channel 2 (sensor hub), seq filled later
//        0xFD, 0x01,
//        0x05,
//        0x00, 0x00, 0x64, 0x00,  // 100 ms
//        0x00, 0x00, 0x00, 0x00,
//        0x00, 0x00
//    };
//
//    cmd[1] = seq++;  // sequence number
//
//    I2C_Write(cmd, sizeof(cmd));
//}
//
//// -------------------------
//// Read one full SHTP packet
//// -------------------------
//uint16 ReadPacket(uint8 *buf)
//{
//    uint8 header[4];
//
//    // 1. Read header
//    I2C_Read(header, 4);
//
//    uint8 channel = header[0];
//    uint16 length = header[2] | (header[3] << 8);
//
//    // 2. Basic sanity check
//    if(length == 0 || length > 60)
//        return 0;
//
//    //3. FILTER HERE
//    if(channel != 2)
//    {
//        // still need to clear the packet from the sensor!
//        uint8 dump[64];
//        I2C_Read(dump, length - 4);
//        return 0;
//    }
//
//    // 4. Only now read useful payload
//    I2C_Read(buf, length - 4);
//
//    return length;
//}
//
//// -------------------------
//// MAIN
//// -------------------------
//
//
//int main(void)
//{
//    CyGlobalIntEnable;
//
//    I2C_Start();
//
//    USBUART_Start(0, USBUART_5V_OPERATION);
//    while(!USBUART_GetConfiguration());
//
//    CyDelay(500);  // 🔥 VERY IMPORTANT (sensor boot)
//
//    CyDelay(500);
//
//    // Read and discard a few startup packets
//    for(int i = 0; i < 5; i++)
//    {
//        uint8 header[4];
//        I2C_Read(header, 4);
//
//        uint16 len = header[2] | (header[3] << 8);
//
//        if(len > 4 && len < 64)
//        {
//            uint8 dump[64];
//            I2C_Read(dump, len - 4);
//        }
//
//    CyDelay(50);
//    }
//    
//    EnableRotationVector();
//
//    CyDelay(300);  // 🔥 allow sensor to start streaming
//
//    for(;;)
//    {
//        uint16 len = ReadPacket(buffer);
//
//        if(len > 0)
//        {
//            for(uint16 i = 0; i < len - 4; i++)
//            {
//                char msg[6];
//                sprintf(msg, "%02X ", buffer[i]);
//                USBUART_PutString(msg);
//            }
//            USBUART_PutString("\r\n");
//        }
//
//        CyDelay(20);
//    }
//}
#include "project.h"
#include <stdio.h>

#define BNO085_ADDR 0x4A

// sequence numbers per channel
uint8_t seq[6] = {0};

// buffer for incoming packets
uint8_t buffer[128];

// -------------------------
// I2C WRITE
// -------------------------
void I2C_Write(uint8_t *data, uint16_t len)
{
    I2C_MasterSendStart(BNO085_ADDR, I2C_WRITE_XFER_MODE);

    for(uint16_t i = 0; i < len; i++)
        I2C_MasterWriteByte(data[i]);

    I2C_MasterSendStop();
}

// -------------------------
// I2C READ
// -------------------------
void I2C_Read(uint8_t *buf, uint16_t len)
{
    I2C_MasterSendStart(BNO085_ADDR, I2C_READ_XFER_MODE);

    for(uint16_t i = 0; i < len; i++)
    {
        buf[i] = I2C_MasterReadByte(
            (i < len - 1) ? I2C_ACK_DATA : I2C_NAK_DATA
        );
    }

    I2C_MasterSendStop();
}

// -------------------------
// READ ONE SHTP PACKET
// -------------------------
uint16_t ReadPacket(uint8_t *channel)
{
    uint8_t header[4];

    // read header
    I2C_Read(header, 4);

    uint16_t length = header[0] | (header[1] << 8);
    *channel = header[2];

    if(length < 4 || length > 128)
        return 0;

    // read payload
    I2C_Read(buffer, length - 4);

    return length;
}

// -------------------------
// HANDSHAKE (SYNC)
// -------------------------
void BNO085_Handshake(void)
{
    uint8_t ch;

    CyDelay(500);  // sensor boot time

    // flush startup packets
    for(int i = 0; i < 15; i++)
    {
        ReadPacket(&ch);
        CyDelay(20);
    }
}

// -------------------------
// ENABLE ROTATION VECTOR
// -------------------------
void EnableRotationVector(void)
{
    uint8_t cmd[17];

    // --- SHTP HEADER ---
    cmd[0] = 17;          // Length LSB
    cmd[1] = 0;           // Length MSB
    cmd[2] = 2;           // Channel 2 (sensor hub)
    cmd[3] = seq[2]++;    // Sequence number

    // --- SH-2 PAYLOAD ---
    cmd[4] = 0xFD;        // SET_FEATURE
    cmd[5] = 0x01;

    cmd[6] = 0x05;        // Rotation Vector report

    // Report interval = 100 ms (10 Hz)
    cmd[7]  = 0x00;
    cmd[8]  = 0x00;
    cmd[9]  = 0x64;
    cmd[10] = 0x00;

    // Latency
    cmd[11] = 0x00;
    cmd[12] = 0x00;
    cmd[13] = 0x00;
    cmd[14] = 0x00;

    // Flags
    cmd[15] = 0x00;
    cmd[16] = 0x00;

    I2C_Write(cmd, 17);
}

// -------------------------
// PROCESS INCOMING DATA
// -------------------------
void ProcessPackets(void)
{
    uint8_t ch;
    uint16_t len = ReadPacket(&ch);

    if(len > 0 && ch == 2)   // only sensor data channel
    {
        // check report ID (Rotation Vector = 0x05)
        if(buffer[0] == 0x05)
        {
            USBUART_PutString("ROT: ");

            for(uint16_t i = 0; i < len - 4; i++)
            {
                char msg[6];
                sprintf(msg, "%02X ", buffer[i]);
                USBUART_PutString(msg);
            }

            USBUART_PutString("\r\n");
        }
    }
}

// -------------------------
// MAIN
// -------------------------
int main(void)
{
    CyGlobalIntEnable;

    I2C_Start();

    USBUART_Start(0, USBUART_5V_OPERATION);
    while(!USBUART_GetConfiguration());

    // 1. Handshake (sync with sensor)
    BNO085_Handshake();

    // 2. Enable rotation vector
    EnableRotationVector();

    CyDelay(200);

    // 3. Main loop
    for(;;)
    {

        ProcessPackets();
        CyDelay(100);
    }
}