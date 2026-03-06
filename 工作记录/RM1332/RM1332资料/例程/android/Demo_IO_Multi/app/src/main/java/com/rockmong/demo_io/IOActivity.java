package com.rockmong.demo_io;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.rockmong.rockmong.MISC;
import com.rockmong.rockmong.IO;
import com.rockmong.rockmong.UsbDevice;
import com.sun.jna.Memory;
import com.sun.jna.Pointer;
import com.sun.jna.ptr.IntByReference;

public class IOActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        int ret;
        int[] SerialNumbers = new int[16];
        ret = UsbDevice.INSTANTCE.UsbDevice_Scan(SerialNumbers);
        if (0 > ret) {
            System.out.println("Error: " + ret);
            return;
        }
        else if (0 == ret){
            System.out.println("No Device!");
            return;
        }
        else{
            for (int i = 0; i < ret; i++){
                System.out.println("Dev" + i + " SN: " + SerialNumbers[i]);
            }
        }

        int SerialNumber = SerialNumbers[0];

        //初始化P0~P15为输出模式
        int io_init_num = 16;
        IO.IO_InitStruct_Tx io_initStruct_tx = new IO.IO_InitStruct_Tx();
        IO.IO_InitStruct_Rx io_initStruct_rx = new IO.IO_InitStruct_Rx();
        IO.IO_InitStruct_Tx[] io_initStruct_tx_list = (IO.IO_InitStruct_Tx[])io_initStruct_tx.toArray(io_init_num);
        IO.IO_InitStruct_Rx[] io_initStruct_rx_list = (IO.IO_InitStruct_Rx[])io_initStruct_rx.toArray(io_init_num);
        for (int i = 0; i < io_init_num; i++) {
            io_initStruct_tx_list[i].Pin = (byte) i;
            io_initStruct_tx_list[i].Mode = 1;
            io_initStruct_tx_list[i].Pull = 0;
        }
        ret = IO.INSTANTCE.IO_InitMultiPin(SerialNumber, io_initStruct_tx_list[0], io_initStruct_rx_list[0], io_init_num);
        if (0 > ret) {
            System.out.println("Error: " + ret);
        }

        //控制P0~P7输出高电平
        int io_write1_num = 8;
        IO.IO_WriteStruct_Tx io_writeStruct_tx = new IO.IO_WriteStruct_Tx();
        IO.IO_WriteStruct_Rx io_writeStruct_rx = new IO.IO_WriteStruct_Rx();
        IO.IO_WriteStruct_Tx[] io_writeStruct_tx_list = (IO.IO_WriteStruct_Tx[])io_writeStruct_tx.toArray(io_write1_num);
        IO.IO_WriteStruct_Rx[] io_writeStruct_rx_list = (IO.IO_WriteStruct_Rx[])io_writeStruct_rx.toArray(io_write1_num);
        for (int i = 0; i < io_write1_num; i++) {
            io_writeStruct_tx_list[i].Pin = (byte) i;
            io_writeStruct_tx_list[i].PinState = 1;
        }
        ret = IO.INSTANTCE.IO_WriteMultiPin(SerialNumber, io_writeStruct_tx_list[0], io_writeStruct_rx_list[0], io_write1_num);
        if (0 > ret) {
            System.out.println("Error: " + ret);
        }

        //控制P8~P15输出低电平
        int io_write0_num = 8;
        io_writeStruct_tx_list = (IO.IO_WriteStruct_Tx[])io_writeStruct_tx.toArray(io_write0_num);
        io_writeStruct_rx_list = (IO.IO_WriteStruct_Rx[])io_writeStruct_rx.toArray(io_write0_num);
        for (int i = 0; i < io_write0_num; i++) {
            io_writeStruct_tx_list[i].Pin = (byte) (i + 8); //从P8开始
            io_writeStruct_tx_list[i].PinState = 0;
        }
        ret = IO.INSTANTCE.IO_WriteMultiPin(SerialNumber, io_writeStruct_tx_list[0], io_writeStruct_rx_list[0], io_write0_num);
        if (0 > ret) {
            System.out.println("Error: " + ret);
        }

        //初始化P0~P15为输入模式
        io_init_num = 16;
        io_initStruct_tx_list = (IO.IO_InitStruct_Tx[])io_initStruct_tx.toArray(io_init_num);
        io_initStruct_rx_list = (IO.IO_InitStruct_Rx[])io_initStruct_rx.toArray(io_init_num);
        for (int i = 0; i < io_init_num; i++) {
            io_initStruct_tx_list[i].Pin = (byte) i;
            io_initStruct_tx_list[i].Mode = 0;
            io_initStruct_tx_list[i].Pull = 0;
        }
        ret = IO.INSTANTCE.IO_InitMultiPin(SerialNumber, io_initStruct_tx_list[0], io_initStruct_rx_list[0], io_init_num);
        if (0 > ret) {
            System.out.println("Error: " + ret);
        }

        //读取P0~P15输入状态
        int io_read_num = 16;
        IO.IO_ReadStruct_Tx io_readStruct_tx = new IO.IO_ReadStruct_Tx();
        IO.IO_ReadStruct_Rx io_readStruct_rx = new IO.IO_ReadStruct_Rx();
        IO.IO_ReadStruct_Tx[] io_readStruct_tx_list = (IO.IO_ReadStruct_Tx[])io_readStruct_tx.toArray(io_read_num);
        IO.IO_ReadStruct_Rx[] io_readStruct_rx_list = (IO.IO_ReadStruct_Rx[])io_readStruct_rx.toArray(io_read_num);
        for (int i = 0; i < io_read_num; i++) {
            io_readStruct_tx_list[i].Pin = (byte) i;
        }
        ret = IO.INSTANTCE.IO_ReadMultiPin(SerialNumber, io_readStruct_tx_list[0], io_readStruct_rx_list[0], io_read_num);
        if (0 > ret) {
            System.out.println("Error: " + ret);
        }
        System.out.println("PinState: ");
        for (int i = 0; i < io_read_num; i++) {
            System.out.print("P" + i + ": " + io_readStruct_rx_list[i].PinState + "   ");
        }
        System.out.println("");
    }

}
