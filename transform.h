#include <iostream>
#include <cstdlib>
#include <cstring>
// feel free to explore what has been added to C++ since C++11!
#include <tuple>
// use assert to comsolidate your programe!
#include <cassert>
#include <fstream>
using namespace std;
class Image;

class Array2d {
//protected:
public:
    double** data;
    int32_t h, w;
public:
    // dummy constructor
    Array2d(): data(nullptr), h(-1), w(-1) {}
    // destructor
    ~Array2d() {
        // TODO
        // deallocate memory on heap
        if ( data!=nullptr )
        for ( int i = 0; i < 2000; i++ )
    		delete [] data[i];
    	delete [] data;
    }
    // allocate memory to data with spectified size
    void create(const int32_t hh, const int32_t ww) {
        // TODO
        // !NOTICE
        // Don't forget to free previous allocated memory
        if ( empty() ) {
        	for ( int i = 0; i < 2000; i++) {
	        	delete [] (data[i]);
			}
	        delete [] data;
		}
        data = new double* [2000];
        for ( int i = 0; i <2000; i++) {
        	data[i] = new double [2000];
        	for ( int j = 0; j <2000; j++) {
        		data[i][j] = 0;
			}
		}
    }
    // helper functions
    bool empty() const { return data != nullptr; }
    // URL of reference to std::tuple
    // https://en.cppreference.com/w/cpp/utility/tuple
    std::tuple<int32_t, int32_t> getSize() const {
        return std::make_tuple(h, w);
    }
    // *BONUS: use copy constructor like follows
    // Array2d(const Array2d& other) {
        // TODO
    // }
};
class Mask: public Array2d {
public:
Mask() ;
friend class Image;
Image operator *(const Image& image) const ;
};
class Image: public Array2d {
	public:
    // default constructor
    Image() {}
    // constructor from Array2d instance
    Image(const Array2d& array2) {
        // TODO
        h = array2.h;
		w = array2.w;
		data = new double* [2000];
        for ( int i = 0; i <2000; i++) {
        	data[i] = new double[2000];
        	for ( int j = 0; j <2000; j++) {
        		data[i][j] = 0;
			}
		}
		for (int i = 2; i <=h+1; ++i) {
			for ( int j = 2; j <=w+1; j++) {
				data[i][j] = array2.data[i][j];
			}
		}
    }
    // constructor from intermediate file
    Image(const char* filename) {
        // TODO
        // open and read intermediate file, get image information
        // !NOTICE
        // call create() method to set intrinsic value
	    ifstream in;
        in.open(filename);
		in>> h >> w;
		create(h, w);
		for ( int i =2; i <=h+1; i++) {
			for ( int j =2; j <=w+1; j++) {
				in>> data[i][j];
			}
		}
		in.close();
    }
    // *BONUS: add a copy constructor
    // destructor
    // destructor of Array2d will deallocate memory, which is called automatically

    Image (const Image& image)
    {
        h=image.h;
        w=image.w;
        create (h,w);
        for ( int i =2; i <=h+1; i++) {
			for ( int j =2; j <=w+1; j++) {
				 data[i][j]=image.data[i][j];
			}
		}

    }
    Image operator =(const Image& image)
    {
        h=image.h;
        w=image.w;
        create (h,w);
        for ( int i =2; i <=h+1; i++) {
			for ( int j =2; j <=w+1; j++) {
				 data[i][j]=image.data[i][j];
			}
		}
		 return *this;
    }
    ~Image() {}
    // method performing Histogram Equalization
    Image equalizeHist() const {
        // TODO
        // return a newly constructed Image instance
        Image s ;
        s.h=h;
        s.w=w;
        s.create(h,w);
        int b[300]={0},pp[300]={0};
        for (int i=2;i<=h+1;i++)
          for (int j=2;j<=w+1;j++)
              b[int (data[i][j])]++;

        pp[0]=b[0];
        for (int i=1;i<=255;i++)
        pp[i]=pp[i-1]+b[i];
        for (int i=2;i<=h+1;i++)
           for (int j=2;j<=w+1;j++)
               s.data[i][j]=255*pp[int (data[i][j])]/h/w;
        return s; 									           //���Image����
    }
    // method showing Histogram
    void drawHist(const char* filename) const {
        // TODO
        // open/create a file to draw histograme
        // return the filename
       /* equalizeHist();*/
        int k;

    	int n[256] = {0};
    	for ( int i = 2; i <=h+1; i++) {
    		for (int j = 2; j <= w+1; j++) {
    			n[int (data[i][j])]++;
			}
		}


        ofstream out1;
        out1.open(filename);
        for ( int i = 0; i < 256; i++) {
        	out1 << i << ' ' << '|' << ' ' << n[i] << ' ' << '|' << ' ';
        	for ( int j = 1; j <= n[i]; j++) out1 << '=';
        	out1<<endl;
		}
		out1.close();
        return;
    }
    // dump array2d into intermediate file
    void dump2File(const char* filename = "out.txt") const {
        // TODO
        // format: first line: h w
        //         other line: a number of gray scale
        // please refer to annotations in python scripts
        // for more information
        /*equalizeHist();*/

        ofstream out;
        out.open(filename);
        out << h << ' ' << w << endl;

        for ( int i =2; i <= h+1; i++) {
        	for ( int j =2; j <= w+1; j++) {
        		out <<int (data[i][j]) <<endl;
			}
		}

		out.close();
    }
    // operator override to perform a convolution
    friend class Mask;
    Image operator *(const Mask& mask) const {
        // TODO
        // return a newly constructed image instance
        // after convolution operation
        Image t;
        t.h=this->h;
        t.w=this->w;
        t.create(h,w);
        for (int i=2;i<=h+1;i++)
           for (int j=2;j<=w+1;j++)
             {
              t.data[i][j]=int (mask.data[1][1]*data[i][j]+mask.data[0][1]*data[i-1][j]+mask.data[2][1]*data[i+1][j]+
                            mask.data[1][0]*data[i][j-1]+mask.data[1][2]*data[i][j+1]+mask.data[0][0]*data[i-1][j-1]+
                            mask.data[2][0]*data[i+1][j-1]+mask.data[0][2]*data[i-1][j+1]+mask.data[2][2]*data[i+1][j+1]);
              if (t.data[i][j]>255)
              t.data[i][j]=255;
              if (t.data[i][j]<0)
              t.data[i][j]=0;
             }
        return t;
    }
};

    // you can use Mask::create() to construct
    Mask::Mask() {
        // TODO
         create(3,3) ;
         data[0][0]=0;
         data[0][1]=-0.1238;
         data[0][2]=0;
         data[1][0]=-0.1238;
         data[1][1]=1.0210;
         data[1][2]=-0.1238;
         data[2][0]=0;
         data[2][1]=-0.1238;
         data[2][2]=0;
    }
    // *BONUS: use initializer_list after C++11 to
    // *build another parameterized constructor
    // URL to std::initializer_list
    // https://en.cppreference.com/w/cpp/utility/initializer_list
    // operator override to perform a convolution

    Image Mask::operator *(const Image& image) const {
        // TODO
        // similar in what you have previously done
        Image t;
        t.h=image.h;
        t.w=image.w;
        t.create(h,w);
        for (int i=2;i<=h+1;i++)
           for (int j=2;j<=w+1;j++)
             {
              t.data[i][j]=int (data[1][1]*image.data[i][j]+data[0][1]*image.data[i-1][j]+data[2][1]*image.data[i+1][j]+
                            data[1][0]*image.data[i][j-1]+data[1][2]*image.data[i][j+1]+data[0][0]*image.data[i-1][j-1]+
                            data[2][0]*image.data[i+1][j-1]+data[0][2]*image.data[i-1][j+1]+data[2][2]*image.data[i+1][j+1]);
              if (t.data[i][j]>255)
              t.data[i][j]=255;
              if (t.data[i][j]<0)
              t.data[i][j]=0;
             }
        return t;
    }
