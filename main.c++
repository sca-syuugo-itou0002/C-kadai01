#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
   string username;
   srand(static_cast<unsigned int> (time(0)));
  int num=0;
  cout<<"名前を入力 ";
  cin>>username;
  cout<<"20XX年隕石の接近により地球は滅亡の危機に瀕していた\n\n";
  cout<<"プレイヤーである"<<username<<"はダイスを振り地球を救うことを強いられる"<<endl;
  cout<<"1か2を入力してください。1はダイス1つ、2はダイス2つ"<<endl;
  cin>>num;
  switch(num){
    case 1:{
      int Dies =  rand()% 6 + 1;
      cout<<"出た数は"<<Dies<<endl;
      if( Dies % 2 == 0){
      cout<<"地球は守られた！"<<endl;
      }
      else{
      cout<<"地球は滅亡した..."<<endl;
      }
    }
    break;
    case 2:{
      int Dies2 = rand()%18+2;
      cout<<"出た数は"<<Dies2<<endl;
      if( Dies2 % 3 == 0){
      cout<<"地球は守られた！"<<endl;
      }
      else{
      cout<<"地球は滅亡した..."<<endl;
      }
    }
    break;
  }
  return 0;
}