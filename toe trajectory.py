#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import time as time

def dynamixelWrite(motor_id, angle):
        val = (int) (OFFSET[motor_id] + angle*4096/360)
         dxl_comm_result, dxl_error = packetHandler.write4ByteTxRx(portHandler1, motor_id, ADDR_PRO_GOAL_POSITION, val)

def torqueEnable(motor_id):
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler1, motor_id, ADDR_PRO_TORQUE_ENABLE, TORQUE_ENABLE)
        if dxl_comm_result != COMM_SUCCESS:
                print("%s" % packetHandler.getTxRxResult(dxl_comm_result))
        elif dxl_error != 0:
                print("%s" % packetHandler.getRxPacketError(dxl_error))
        else:
                print("Dynamixel#%d has been successfully connected" % motor_id)

def torqueDisable(motor_id):
        dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler1, motor_id, ADDR_PRO_TORQUE_ENABLE, TORQUE_DISABLE)
        if dxl_comm_result != COMM_SUCCESS:
                print("%s" % packetHandler.getTxRxResult(dxl_comm_result))
        elif dxl_error != 0:
                print("%s" % packetHandler.getRxPacketError(dxl_error))
        else:
                print("Dynamixel#%d has been successfully connected" % motor_id)

def setPIDGains():
        p_gain = 10
        d_gain = 5
        i_gain = 15
        for x in range(1,9):
                dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler1, x, ADDR_P_GAIN, p_gain)
                dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler1, x, ADDR_D_GAIN, d_gain)
                dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler1, x, ADDR_I_GAIN, i_gain)

if os.name == 'nt':
    import msvcrt
    def getch():
        return msvcrt.getch().decode()
else:
    import sys, tty, termios
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    def getch():
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch

from dynamixel_sdk import *                    # Uses Dynamixel SDK library

# Control table address
ADDR_PRO_TORQUE_ENABLE      = 24               # Control table address is different in Dynamixel model
ADDR_PRO_GOAL_POSITION      = 30
ADDR_PRO_PRESENT_POSITION   = 36
ADDR_P_GAIN                                     = 28
ADDR_D_GAIN                                     = 26
ADDR_I_GAIN                                     = 27

# Protocol version
PROTOCOL_VERSION            = 1.0               #  See which protocol version is used in the Dynamixel

# Default setting
DXL1_ID                     = 1                 # Dynamixel#1 ID : 1
DXL2_ID                     = 2                 # Dynamixel#2 ID : 2
BAUDRATE                    = 2000000             # Dynamixel default baudrate : 57600
DEVICENAME1                 = '/dev/tty.usbserial-FT2KQCMU'    # Check which port is being used on your controller

TORQUE_ENABLE               = 1                 # Value for enabling the torque
TORQUE_DISABLE              = 0                 # Value for disabling the torque
DXL_MINIMUM_POSITION_VALUE  = 0          # Dynamixel will rotate between this value
DXL_MAXIMUM_POSITION_VALUE  = 4095            # and this value (note that the Dynamixel would not move when the position value is out of movable range. Check e-manual about the range of the Dynamixel you use.)
DXL_MOVING_STATUS_THRESHOLD = 20                # Dynamixel moving status threshold

#Motor
L1M1 = 1
L1M2 = 2
L2M1 = 3
L2M2 = 4
L3M1 = 5
L3M2 = 6
L4M1 = 7
L4M2 = 8

OFFSET = [0 for x in range(9)]
# OFFSET[0] = 0
# OFFSET[1] = 2288
# OFFSET[2] = 760
# OFFSET[3] = 224
# OFFSET[4] = 1310
# OFFSET[5] = 1574
# OFFSET[6] = 758
# OFFSET[7] = 1036
# OFFSET[8] = 3233
OFFSET[0] = 0
OFFSET[1] = 1991 # old: 2388
OFFSET[2] = 833  # old: 760
OFFSET[3] = 2510
OFFSET[4] = 3240
OFFSET[5] = 1310 # old: 1574
OFFSET[6] = 921  # old: 758
OFFSET[7] = 1000
OFFSET[8] = 3779

index = 0
dxl_goal_position = [DXL_MINIMUM_POSITION_VALUE, DXL_MAXIMUM_POSITION_VALUE]         # Goal position


# Initialize PortHandler instance
# Set the port path
# Get methods and members of PortHandlerLinux or PortHandlerWindows
portHandler1 = PortHandler(DEVICENAME1)

# Initialize PacketHandler instance
# Set the protocol version
# Get methods and members of Protocol1PacketHandler or Protocol2PacketHandler
packetHandler = PacketHandler(PROTOCOL_VERSION)

# Open port1
if portHandler1.openPort():
    print("Succeeded to open the port")
else:
    print("Failed to open the port")
    print("Press any key to terminate...")
    getch()
    quit()

# Set port1 baudrate
if portHandler1.setBaudRate(BAUDRATE):
    print("Succeeded to change the baudrate")
else:
    print("Failed to change the baudrate")
    print("Press any key to terminate...")
    getch()
    quit()

ang1 = [0 for x in range(100)]
ang2 = [0 for x in range(100)]

f = open("new_24_8.txt","r")
for t in range(100):
    str =  f.readline()
    val = str.split()
    ang1[t] = float(val[0])
    ang2[t] = float(val[1])

torqueEnable(L1M1)
torqueEnable(L1M2)
torqueEnable(L2M1)
torqueEnable(L2M2)
torqueEnable(L3M1)
torqueEnable(L3M2)
torqueEnable(L4M1)
torqueEnable(L4M2)


setPIDGains()


while 1:

    for t in range(99):

        dynamixelWrite(L1M1, ang1[t])
        dynamixelWrite(L1M2, 180+ang2[t])
        dynamixelWrite(L2M1, -ang1[(t+50)%100])
        dynamixelWrite(L2M2, -180-ang2[(t+50)%100])
        dynamixelWrite(L3M1, ang1[(t+75)%100])
        dynamixelWrite(L3M2, 180+ang2[(t+75)%100])
        dynamixelWrite(L4M1, -ang1[(t+25)%100])
        dynamixelWrite(L4M2, -180-ang2[(t+25)%100])

# Close port1
portHandler1.closePort()
