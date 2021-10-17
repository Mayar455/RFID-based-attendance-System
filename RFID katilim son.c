#include <reg51.h>     // microcontrollerin fileleri hep burada saklanir
#include <string.h>			// string fonksiyonu LCD ye giris icin kullanilir.


sbit rs = P2^0;	// LCD nin rs komutu verileri / komutlari gonderme islemi yapar
sbit e = P2^1;	// high levelden low levele sinyal gonderen e komutu , yine LCD ye ait baska bir komut

void init ();	// baslama fonksiyonu

void delay(int a)
{
	int i,j;
	for(i=0;i<a;i++)
	for(j=0;j<a;j++);
}

void lcd_cmd(int a)
{
	P1=a; 		//   parametre olarak a degerini alan P1 portu, cikti islemini goruyor. lcd den ciktilari aliyor
	rs=0; 		//   LCD ye komut gondermek icin rs degeri =0 olmali
	e=1; 			//   enable high olacak
	delay(10);  // enable high ve low arasinda bir delay gerceklesecek.
	e=0;  			 //      enable low olck
}

void lcd_data(int a)
{
	P1=a;
	rs=1;   // LCD ye veri / komutlar gondermek istedigimizde RS =0 olmali burada 
	e=1;
	delay(10);
	e=0;
}

void lcd_string( char *str)
{
		while(*str)
		{
			lcd_data(*str);
			delay(100);
			str++;
		}
}

void main()
{
	int i;
	unsigned char a2[8]; // 8 boyut buyuklugune sahip bir dizi tanimliyoruz
	// baslatmak amaciyle LCD ye gonderilen komutlar
	lcd_cmd(0x38);     //  2 satir ve 5×7 matris boyunta verileri LCD ye aktariyor.
	lcd_cmd(0x0E);		// 
	lcd_cmd(0x01);		//  ekran temizleme icin kullanilir.
	lcd_cmd(0x80);	  //  ilk satir gosteren komutumuzdur.
	init();
		lcd_string("HOS GELDINIZ");
		lcd_cmd(0xC0); // ikinci satirdaki ilk cumleyi gosteren komut
		lcd_string("ID NO GIRINIZ");
		lcd_cmd(0x01); //
	while(1) // while 1 de iken, kosulun her daim dogru oldugu anlami verir.
					//	bu da govdesinde kodlarin kosulu sagalandigi 
					//	takdirde calistirmasini anlami veriyor
	{
		for( i=0;i<4;i++);    //4 rakamli ( bit)  bir ID girilmesi icin for dongusu uzerinden string sayisini kontrol edilir.
		{
				while (RI ==0); // interupt komutunu enable ediyoruz burada. EA=1 sayesinde bu islem aktif hale geliyor
													// bufferden bir komut saklanmasi gerektiginde Reciever interupt ( RI) = 1 olacak
					a2[i]=SBUF; //stringlerin a2 dizisinde sakladigini kontrol ediyor.
					RI=0; 	//saklam islemi gerceklestiken sonra RI = 1 yerine tekrar 0 esit oluyor.
				
		}
		
		if (strcmp (a2,"0513")==0)  //a2 dizisinde atanan bu deger , strcmp methodu sayesinde karsilastirilir. dogru ise govdesindeki komutu donduruyor. 
		{
			lcd_string ("Atiq Mayar");
			lcd_cmd(0x01);
			lcd_string ("iyi dersler");
			lcd_cmd(0xc0);
			lcd_string ("Kayitlandiniz");
			delay(200);
		}
		
		else if (strcmp (a2,"0517")==0)
		{
			lcd_string ("Morteza Yosefy");
			lcd_cmd(0x01);
			lcd_string ("iyi dersler");
			lcd_cmd(0xc0);
			lcd_string ("Kayitlandiniz");
			delay(200);
		}
		
		else if (strcmp (a2,"0516")==0)
		{
			lcd_string ("Reza");
			lcd_cmd(0x01);
			lcd_string ("iyi dersler");
			lcd_cmd(0xc0);
			lcd_string ("Kayitlandiniz");
			delay(200);
		}
		
		else {
			lcd_string("YANLIS GIRDINIZ");
			lcd_cmd(0x01);
		}
		
	}
}

void init()
{
	EA=1; // interuptin global olarak enable olmasini gosteren komut
	ES=1; // interuptin serial olarak enable olmasini gosteren komut
	TMOD =0X20; // timer Modlari secmemizde yardimci olan TMOD komutu. burada 8 bit auto reload modu kullandik.
	SCON = 0X50;  // 8bit data , 1 stop bit , REN enabled. serail port kullanarak veriler / sinyaller gonderim ve alimi yapar
	TH1 = -3;  //  baud rate  9600 ulasmasini saglar.
	TR1 = 1; //timer 1 olarak alip baslatiyor.
	
}
	
		