#include <iostream>
#include <cmath>
#include <functional>
#include <ctime>
#include <chrono>

using namespace std;

//funkcja zaokrąglająca
double apr(double x){
  double d=round(x*100);
  x=d/100;
  return x;
}

//funkcja wielomianowa
template<class T>
T funkcja(double x){
  T y=0;
  const int s=2; //stopień wielomianu
  double w[s+1]={0,1,0}; //tablica współczynników {a,b,c,...}
  for (int i=0; i<s+1; i++){
    y+=pow(x,i)*w[s-i];
  }
  return y;
}

//sinus
double sinus(double x)
{
  return sin(x);
}

// cosinus
double cosinus(double x)
{
  return cos(x);
}

//logarytm naturalny
double ln(double x)
{
  return log(x);
}

//całka
template<class T, class V, class R>
R integral(function<T(V)> funkcja,double x_1, double x_2, double d){
  R integ=0;
  for (double x=x_1; x<x_2-d; x+=d)
    {
      integ+=(funkcja(x)+funkcja(x+d))*0.5*d;
    }
  integ=apr(integ);
  return integ;
}

int main() {
  //mierzenie czasu działania całego programu
  std::chrono::steady_clock::time_point t_start = std::chrono::steady_clock::now();

  
  double pi=M_PI;
  double x_1=-1,x_2=2; //granice całkowania
  double d=0.001; //krok w całce
  double r1, r2,r3;

  //przykładowe całki i mierzony execution time
  //f. wielomianowa
  std::chrono::steady_clock::time_point s_r1 = std::chrono::steady_clock::now();
  
  r1=integral<double,double,double>(funkcja<double>,x_1, x_2, d);
  
  std::chrono::steady_clock::time_point e_r1 = std::chrono::steady_clock::now();

  // f. sinsus
  std::chrono::steady_clock::time_point s_r2 = std::chrono::steady_clock::now();
  
  r2=integral<double,double,double>(sinus,0.,2*pi,d);
  
  std::chrono::steady_clock::time_point e_r2 = std::chrono::steady_clock::now();

  // f. cosinus
  std::chrono::steady_clock::time_point s_r3 = std::chrono::steady_clock::now();
  
  r3=integral<double,double,double>(cosinus,-pi/2,pi/2,d);
  
  std::chrono::steady_clock::time_point e_r3 = std::chrono::steady_clock::now();

  
  //drukujemy
  cout<<"Calka z f. wielomianowej w granicach ("<<x_1<<","<<x_2<<") wynosi = "<<r1<<endl;
  cout<<"Czas wykonania: "<< chrono::duration_cast<chrono::microseconds> (e_r1 - s_r1).count() << " us"<<endl<<endl;
  
  cout<<"Calka z f. sinusoidalnej w granicach ("<<0<<","<<2*pi<<") wynosi = "<<r2<<endl;
  cout<<"Czas wykonania: "<< chrono::duration_cast<chrono::microseconds> (e_r2 - s_r2).count() << " us"<<endl<<endl;
  
  cout<<"Calka z f. cosinusoidalnej w granicach ("<<-pi/2<<","<<pi/2<<") wynosi = "<<r3<<endl;
  cout<<"Czas wykonania: "<< chrono::duration_cast<chrono::microseconds> (e_r3 - s_r3).count() << " us"<<endl<<endl;

  //drukujemy cały czas działania programu
  std::chrono::steady_clock::time_point t_end = std::chrono::steady_clock::now();
  cout<<"Calkowity czas dzialania programu "<< chrono::duration_cast<chrono::microseconds> (t_end - t_start).count() << " us"<<endl<<endl;
  
  return 0;
}