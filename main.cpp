/*#include <iostream>
#include <fstream>
using namespace std;
int a[300][300],aa[300][300],b[300],bb[300],p[300],pp[300];
int main()
{
  ifstream in;
  ofstream out;
  ofstream  outt;
  in.open("in.txt");
  out.open("out.txt");
  outt.open("comp.txt");
  int h,w;
  in>>h>>w;
  for (int i=2;i<=h+1;i++)
    for (int j=2;j<=w+1;j++)
  {
      in>>a[i][j];
      b[a[i][j]]++;
  }
  pp[0]=b[0];
  for (int i=1;i<=255;i++)
    pp[i]=pp[i-1]+b[i];
  for (int i=2;i<=h+1;i++)
    for (int j=2;j<=w+1;j++)
        a[i][j]=255*pp[a[i][j]]/h/w,
        cout<<a[i][j]<<endl;
    out<<h<<' '<<w<<endl;

  for (int i=2;i<=h+1;i++)
    for (int j=2;j<=w+1;j++)
  {
    aa[i][j]=int (0.2042*a[i][j]+0.1238*(a[i-1][j]+a[i+1][j]+a[i][j-1]+a[i][j+1])+0.0751*(a[i-1][j-1]+a[i+1][j-1]+a[i-1][j+1]+a[i+1][j+1]));
    if (aa[i][j]>255)
        aa[i][j]=255;
      if (aa[i][j]<0)
        aa[i][j]=0;
  }
  for (int i=2;i<=h+1;i++)
    for (int j=2;j<=w+1;j++)
    p[aa[i][j]]++;

  pp[0]=p[0];
  for (int i=1;i<=255;i++)
    pp[i]=pp[i-1]+p[i];

  for (int i=2;i<=h+1;i++)
    for (int j=2;j<=w+1;j++)
  {
      a[i][j]=255*pp[a[i][j]]/h/w;
      bb[a[i][j]]++;
  }

  for (int i=2;i<=h+1;i++)
    for (int j=2;j<=w+1;j++)
    out<<a[i][j]<<endl;

  for (int i=0;i<=255;i++)
    outt<<b[i]<<endl<<bb[i]<<endl;

  in.close();
  out.close();
  outt.close();
    return 0;
}*/




#include <iostream>
#include "transform.hpp"
#include <fstream>
int main()
{
  Image a("in.txt");
  Image s;
  s=a.equalizeHist();
  s.drawHist("out1.txt");
  Mask m;
  Image t=a*m;
  Image x=t.equalizeHist();
  x.dump2File("out.txt");
  return 0;

}
