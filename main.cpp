#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct Brush {  //brush structı ad en ve boy değerlerini tutar
  string ad;
  int en;
  int boy;
};

//strıngin sayı olup olmadığını soyleyen fonksiyon
bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

int main() {

string input = "",str,str2,str3,str4,str5,str6,str7;
int canvasx=0,canvasy=0,cursorx=0,cursory=0;

srand(time(NULL));
int paintNumberWant=1+rand()%3;  //paint canvas number minimalize edilmesi icin rastgele 1 ile 3 arası değer alır ,3 dahil

int paintNum=0;  //bu değer kac tane paint yaptığını bulmak icin
char** Canvas;  //CAnvas matriximiz
vector<Brush> brs; //bu vector brush  structu alır yani her bir brushun ismi eni ve boyunu
int a=0;

int myNumber = 0;
cout <<"PROGRAM mypeakasso; !! The number of PAINT-CANVAS statements is " <<paintNumberWant<<endl;
cout<<"CANVAS-INIT-SECTION"<<endl;
 while (true) {  //bütün inputları almak icin sonsuz döngü ama exhibit yapıldığında
   getline(cin, input);


   istringstream myStream(input);

  while(getline(myStream,str, ';')) // noktalı virgüle kadar once alınır
{
 istringstream myStream2(str);
  myStream2>>str3;

  if(str3=="CONST") //eger CONST LA başlıyorsa
  {
     getline(myStream2,str4, '=');  //eşitliğe kadar alınır
     istringstream myStream3(str4);
     myStream3>>str4;

      if(str4=="CanvasX") //eşitlikten önckei CanvasX se
      {
         myStream2>>canvasx; //eşitlikten sonra gelen sayı canvas x olur
      }
      else if (str4 =="CanvasY")//eşitlikten önckei CanvasY se
      {
          myStream2>>canvasy; //eşitlikten sonra gelen sayı canvas y olur
      }

     else
     {
         cout<<"Wrong input try again"<<endl;
     }

  }

 else if(str3=="CursorX") //eger CursorX le başlıyorsa
 {
     //canvasx ve canvasy belli olduğu icin canvas matrixi initilaze edilir
 Canvas=new char*[canvasy];
 for(int i = 0; i < canvasy; ++i)
    Canvas[i] = new char[canvasx];

  for(int i=0;i<canvasy;i++) //ve ici boşlukla doldurulur
   for(int j=0;j<canvasx;j++)
     Canvas[i][j]=' ';



     getline(myStream2,str4, '=');
     istringstream myStream3(str4);
     myStream3>>str4;
     myStream2>>cursorx; //eşitlikten sonrası cursor x dir


 }
 else if(str3=="CursorY")
 {

    getline(myStream2,str4, '=');
     istringstream myStream3(str4);
     myStream3>>str4;
     myStream2>>cursory;//eşitlikten sonrası cursor y dir


     cout <<"BRUSH-DECLARE-SECTION: !!  Declare brushes"<<endl; //sonra brush declare kısmı geldği icin

 }
 else if(str3=="BRUSH") //BRUSH LA başlarsa
 {
     int en,boy;
     string ad;
     Brush brush; //bir struct tanımlanır

     while(getline(myStream2,str4, ',')){ //herbir brush icin virgüle kadar alınır

     istringstream myStream3(str4);
     getline(myStream3,str5, '='); //eşitliğe kadar alınır
     istringstream myStream4(str5);

     myStream4>>ad;  //eşitlikten öncesi addır
     myStream3>>en>>boy; //eşitlikten sonrası en ve boy
     //structta eşitlenir ve vectore atılır
      brush.ad = ad;
    brush.en= en;
    brush.boy=boy;
    brs.push_back(brush);
  }

   cout <<"DRAWING-SECTION: !!  Start drawing"<<endl; //paint kısmına gecildği icin

 }
 else if(str3=="MOVE") //MOVE LA başlarsa
 {

   myStream2>>str4>>str5;
   if(str4=="CursorX"&&str5=="TO") //diger iki kelime CursorX TO ise diğer gelene bakılır
   {
       if(myStream2>>str6)
        {
           if(is_digits(str6))
           {  //eger gelen sayıysa başka işleme gerek kalmaz
              cursorx=stoi(str6); //sayi cursorx dir
           }
           else //ama sayı degilse
            {
                if(str6=="CursorX") //sonra gelen cursorX ise ve mınus yada plus a göre
                 {
                    myStream2>>str7;
                    if(str7=="MINUS")
                    {
                         myStream2>>myNumber;
                         cursorx = cursorx - myNumber; //mınus ise cursox den sayı cıkarılır
                    }
                    else if(str7=="PLUS")
                    {
                     myStream2>>myNumber;
                        cursorx = cursorx + myNumber; //plus ise cursorx e sayı eklenir
                    }
                    else
                    {
                     cout<<"Wrong input try again"<<endl;
                    }
                 }
                else  if(str6=="CursorY") //eger sorna gelen cursor Y ise
                 {
                    myStream2>>str7;
                    if(str7=="MINUS")
                    {
                        myStream2>>myNumber;
                        cursorx=cursory - myNumber; //minus ve plusa göre cursor y den o sayı cıkarılır yada eklenir cursor x e
                    }
                    else if(str7=="PLUS")
                    {
                     myStream2>>myNumber;
                     cursorx=cursory + myNumber;
                    }
                    else
                    {
                     cout<<"Wrong input try again"<<endl;
                    }
                 }
                else
                {
                     cout<<"Wrong input try again"<<endl;
                }


            }

        }


   }
   else if(str4=="CursorY"&&str5=="TO") //eger move dan sonra CursorY ve to gelirse yukardaki işlemelerin hemen hemen aynısıdır
     {
         if(myStream2>>str6)
        {
           if(is_digits(str6)){
              cursory=stoi(str6);
           }
            else
            {
                if(str6=="CursorX")
                 {
                    myStream2>>str7;
                    if(str7=="MINUS")
                    {
                         myStream2>>myNumber;
                           cursory = cursorx - myNumber;
                    }
                    else if(str7=="PLUS")
                    {
                     myStream2>>myNumber;
                       cursory = cursorx + myNumber;
                    }
                    else
                    {
                     cout<<"Wrong input try again"<<endl;
                    }
                 }
                else  if(str6=="CursorY")
                 {
                    myStream2>>myNumber;
                    if(str7=="MINUS")
                    {
                        myStream2>>myNumber;
                         cursory = cursory - myNumber;
                    }
                    else if(str7=="PLUS")
                    {
                     myStream2>>myNumber;
                       cursory = cursory + myNumber;
                    }
                     else
                    {
                     cout<<"Wrong input try again"<<endl;
                    }
                 }
                 else
                {
                cout<<"Wrong input try again"<<endl;
                }


            }

        }



     }
     else
    {
    cout<<"Wrong input try again"<<endl;
    }

 }
 else if(str3=="PAINT-CANVAS") //eğer PAINT-CANVAS ise
 {

     paintNum++; //her bir painte gelişte bu paint sayısı artırılır ve bunun başta belirlenen paint canvas statement sayısını gecmemesi iicn
     myStream2>>str4;

    if(paintNum<=paintNumberWant)  //burda ona bakılır paint sayısı paint canvas statement sayısını gecmmemek şartıyla
    {
      for(int count=0;count<brs.size();count++) //vectordeki brushlara bakılır ve hangisyse
       {
           if(str4==brs[count].ad) //adı bulunduğunda onun en ve boyuna göre canvasa basılır
           {

                 int a=cursorx-1;
                 int b= cursory-1;
                 int i=0;
                 int j=0;

                 while(b<canvasy&&i<brs[count].boy) //öncelikle boy kadar cizilceek canvas y gecmeyecek şekilde
                   {
                  while(a<canvasx&&j<brs[count].en) //her boy icin en cizilecek brush boyu kadar yapacak ekstara olarak canvas x i gecemez
                   {
                      Canvas[b][a] = '*';    //* ifadesi canvas a yazılacak en cizerken x tarafında ilerleyecek
                      a++;
                      j++; //j kadar yapması icin yani brush eni kada
                   }
                 a=cursorx-1;   //bir tane daha cizerken cursorx tekrar eşitlenir aynı hziada cizmesi icin
                 i++;
                 b++;
                 j=0;
                   }


           }

       }


    }
    else //eger paint canvas statement sayısını gecerse programdan cıkılır
    {
        cout <<"Painting is full exiting"<<endl;
        a=1;
        break;
    }

 }
 else if(str3=="EXHIBIT-CANVAS") //sadece canvası ekrana getirme ve son komut olduğu icin programdan acilir
 {

  for(int i=0; i<canvasy;i++){
     for(int j=0;j<canvasx;j++)
      cout<<Canvas[i][j];
    cout<<endl;
   }

   a=1;
   break;

 }
 else //eger bunların  dışında bir komut girilirse kullanıcı bilgilendirilir ve baştan girmesi sağlanır
{
    cout<<"Wrong input try again"<<endl;
}

}

if(a==1) //yukaridaki ilk cıkışın devamıdır
 break;
}




 return 0;
}
