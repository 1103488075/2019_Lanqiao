#include "Key16.h"
#include "Display.h"
uchar KeyValue = 0;
uchar Pasworld = 0;//interface switchover
uchar sum = 0;
uchar InputPsworld[6];//save input key value
uchar Affima = 0;//passworld affima key
uchar Seting = 0;//
void ScanKey16()
{
    P42 = 0,P44 = 0;P3 = 0x0f;//P42 = P36 P44 = P37

    if(P3 != 0x0f)
    {
        Delay2ms();
        if(P3 != 0x0f)//is list
        {
            Pasworld = 1;

            P42 = 1;P44 = 1;P3 = 0x30;//P3 = 0000 1111
            if((P3 == 0x30)&&(P44 == 0)&&(P42 == 1))//0111 1111
                KeyValue = 0;
            else if((P3 == 0x30)&&(P44 == 1)&&(P42 == 0))//1011 1111
                KeyValue = 1;
            else if((P3 == 0x10)&&(P44 == 1)&&(P42 == 1))
                KeyValue = 2;
            else if((P3 == 0x20)&&(P44 == 1)&&(P42 == 1))
                KeyValue = 3;

            P42 = 0; P44 = 0; P3 = 0x0f;
            switch (P3)
            {
                case(0x0e):KeyValue +=0;break;
                case(0x0d):KeyValue +=4;break;
                case(0x0b):KeyValue +=8;break;
                case(0x07):KeyValue +=12;break;
            }             
            switch (KeyValue)
            {
                case(0):sum = 0;break;  
                case(1):sum = 1;break; 
                case(2):sum = 2;break; 
                case(3):sum = 3;break; 
                case(4):sum = 4;break; 
                case(5):sum = 5;break; 
                case(6):sum = 6;break; 
                case(7):sum = 7;break; 
                case(8):sum = 8;break; 
                case(9):sum = 9;break; 
                case(10):Seting = 1;
                break; //seting key
                case(11):sum = 11;break;//restoration key
                case(14):
                if(Pasworld == 1)//affima key.return interface display Time
                 Pasworld = 0;  
                else
                Pasworld = 0; break;
            

            }
            while(P3 != 0x0f); 
            InputPsworld[i] = sum;//monitor and save key value
            i++;
            if(i>6)
            i = 7;  
            // if(Seting == 1)
            // {

            // } 
        }
    }
}