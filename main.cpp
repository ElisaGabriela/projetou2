#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip> 

using namespace std;

struct Voxel {
  float r,g,b; // Colors
  float a; // Transparency
  bool isOn; // Included or not
};

class Sculptor {
protected:
  Voxel ***v; // 3D matrix
  int nx,ny,nz; // Dimensions
  float r,g,b,a; // Current drawing color
public:
  Sculptor(int _nx, int _ny, int _nz);
  ~Sculptor();
  void setColor(float red, float green, float blue, float alpha);
  void putVoxel(int x, int y, int z);
  void cutVoxel(int x, int y, int z);
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  void writeOFF(char* filename);
};

int main() {
    Sculptor Voxel(8,8,8);
    Voxel.setColor(1,1,0,1);
    Voxel.putBox(0,4,0,4,0,4);
    Voxel.cutBox(0,3,0,3,0,4);


    Voxel.writeOFF((char*)"tabua.off");

    return 0;
}

Sculptor::Sculptor(int _nx, int _ny, int _nz) {
  nx = _nx; ny = _ny; nz = _nz;
  r=g=b=a=0.5;

  v = new Voxel**[nx];

  for (int i = 0; i < nx; i++) {
    v[i] = new Voxel*[ny];
  }

  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      v[i][j] = new Voxel[nz];
    }
  } 

  for (int i = 0; i < nx; i++) {
      for (int j = 0; j < ny; j++) {
          for (int k = 0; k < nz; k++) {
              v[i][j][k].r = r;
              v[i][j][k].g = g; 
              v[i][j][k].b = b; 
              v[i][j][k].a = a; 
              v[i][j][k].isOn = false;
          }
      }
  }   
}

Sculptor::~Sculptor() {
  cout << "sera que foi?" << endl;

  
  // //deallocate memory
  // for (int i = 0; i < nx; i++)
  //   {
  //     for (int j = 0; j < ny; j++)
  //     {
  //       delete[] v[i][j];
  //     }
  //     delete[] v[i];
  //   }
  //   delete[] v;
}

void Sculptor::setColor(float red, float green, float blue, float alpha) {
  cout << "chegou aqui..." << endl;
  r = red; g = green; b = blue; a = alpha;
}

void Sculptor::cutVoxel(int x, int y, int z) {
  v[x][y][z].isOn = false;
} 

void Sculptor::putVoxel(int x, int y, int z){
  cout << "chegou aqui..." << endl;
  v[x][y][z].isOn = true;
  v[x][y][z].r = r;
  v[x][y][z].g = g;
  v[x][y][z].b = b;
  v[x][y][z].a = a;

}

void Sculptor::writeOFF(char* filename){
  cout << "chegou aqui..." << endl;
  int total, index, x, y, z;
  float lado = 0.5;
  ofstream f;
  total = 0;
  f.open(filename);
  f << "OFF\n";

  for (x = 0; x < nx; x++)
  {
    for (y = 0; y < ny; y++)
    {
      for (z = 0; z < nz; z++)
      {
        if (v[x][y][z].isOn) {
          total++;
        }
      }
      
    }
    
  }

  f << total * 8 << " " << total * 6 << " 0 \n";

  for (x = 0; x < nx; x++)
  {
    for (y = 0; y < ny; y++)
    {
      for (z = 0; z < nz; z++)
      {
        if (v[x][y][z].isOn) {
          f << x - lado << " " << y + lado << " " << z - lado << "\n" << flush;
          f << x - lado << " " << y - lado << " " << z - lado << "\n" << flush;
          f << x + lado << " " << y - lado << " " << z - lado << "\n" << flush;
          f << x + lado << " " << y + lado << " " << z - lado << "\n" << flush;
          f << x - lado << " " << y + lado << " " << z + lado << "\n" << flush;
          f << x - lado << " " << y - lado << " " << z + lado << "\n" << flush;
          f << x + lado << " " << y - lado << " " << z + lado << "\n" << flush;
          f << x + lado << " " << y + lado << " " << z + lado << "\n" << flush;
  
        }
      }
    }
      
  }

  total = 0;  
  for (x = 0; x < nx; x++)
  {
    for (y = 0; y < ny; y++)
    {
      for (z = 0; z < nz; z++)
      {
        if (v[x][y][z].isOn) {
          index = total * 8;

          f << std::fixed;
          f << 4 << " " << index + 0 << " " << index + 3 << " " << index + 2 << " " 
            << index + 1 << " ";
          f << std::setprecision(2) << v[x][y][z].r << " "
            << std::setprecision(2) << v[x][y][z].g << " "
            << std::setprecision(2) << v[x][y][z].b << " "
            << std::setprecision(2) << v[x][y][z].a << "\n";

          f << 4 << " " << index + 4 << " " << index + 5 << " " << index + 6 << " " 
            << index + 7 << " ";
          f << std::setprecision(2) << v[x][y][z].r << " "
            << std::setprecision(2) << v[x][y][z].g << " "
            << std::setprecision(2) << v[x][y][z].b << " "
            << std::setprecision(2) << v[x][y][z].a << "\n";

          f << 4 << " " << index + 0 << " " << index + 1 << " " << index + 5 << " " 
            << index + 4 << " ";
          f << std::setprecision(2) << v[x][y][z].r << " "
            << std::setprecision(2) << v[x][y][z].g << " "
            << std::setprecision(2) << v[x][y][z].b << " "
            << std::setprecision(2) << v[x][y][z].a << "\n";
          
          f << 4 << " " << index + 0 << " " << index + 4 << " " << index + 7 << " " 
            << index + 3 << " ";
          f << std::setprecision(2) << v[x][y][z].r << " "
            << std::setprecision(2) << v[x][y][z].g << " "
            << std::setprecision(2) << v[x][y][z].b << " "
            << std::setprecision(2) << v[x][y][z].a << "\n";

          f << 4 << " " << index + 3 << " " << index + 7 << " " << index + 6 << " " 
            << index + 2 << " ";
          f << std::setprecision(2) << v[x][y][z].r << " "
            << std::setprecision(2) << v[x][y][z].g << " "
            << std::setprecision(2) << v[x][y][z].b << " "
            << std::setprecision(2) << v[x][y][z].a << "\n";

          f << 4 << " " << index + 1 << " " << index + 2 << " " << index + 6 << " " 
            << index + 5 << " ";
          f << std::setprecision(2) << v[x][y][z].r << " "
            << std::setprecision(2) << v[x][y][z].g << " "
            << std::setprecision(2) << v[x][y][z].b << " "
            << std::setprecision(2) << v[x][y][z].a << "\n";

          total++;
        }
      } 
    } 
  }
  f.close();
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){

    for (int i = x0; i < x1; i++){
        for (int j = y0; j < y1; j++){
            for (int k = z0; k < z1; k++){

                v[i][j][k].r = r;
                v[i][j][k].g = g;
                v[i][j][k].b = b;
                v[i][j][k].a = a;
                v[i][j][k].isOn = true;

            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for (int i = x0; i<x1; i++){
        for (int j = y0; j<y1; j++){
            for (int k = z0; k<z1; k++){
                v[i][j][k].r = r;
                v[i][j][k].g = g;
                v[i][j][k].b = b;
                v[i][j][k].a = a;
                v[i][j][k].isOn = false;

            }}}}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    for(int i=0; i< xcenter; i++)
    {
        for(int j=0; j< ycenter; j++)
        {
            for(int k=0; k< zcenter; k++)
            {

                //esfera
                if (((i-xcenter)*(i-xcenter)) + ((j-ycenter)*(j-ycenter)) + ((k-zcenter)*(k-zcenter)) <= ((radius)*(radius)))
                {
                    v[i][j][k].isOn = true;
                    v[i][j][k].r = r;
                    v[i][j][k].g = g;
                    v[i][j][k].b = b;
                    v[i][j][k].a = a;
                }}}}}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){

    for(int i=0; i< xcenter; i++)
    {
        for(int j=0; j< ycenter; j++)
        {
            for(int k=0; k< zcenter; k++)
            {
                //Equacao da esfera
                if (((i-xcenter)*(i-xcenter)) + ((j-ycenter)*(j-ycenter)) + ((k-zcenter)*(j-ycenter)) <= ((radius)*(radius)))
                {
                    v[i][j][k].r = r;
                    v[i][j][k].g = g;
                    v[i][j][k].b = b;
                    v[i][j][k].a = a;
                    v[i][j][k].isOn = false;

                }}}}}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    for(int i=0; i< rx; i++)
    {
        for(int j=0; j< ry; j++)
        {
            for(int k=0; k< rz; k++)
            {
                //Equacao da Elipse
                if ((((i-xcenter)*(i-xcenter))/((float)((xcenter)*(xcenter)))) + (((j-ycenter)*(j-ycenter))/((float)((ycenter)*(ycenter))))
                        + (((k-zcenter)*(k-zcenter))/((float)((zcenter)*(zcenter)))) <=1.0)
                {
                    v[i][j][k].r = r;
                    v[i][j][k].g = g;
                    v[i][j][k].b = b;
                    v[i][j][k].a = a;
                    v[i][j][k].isOn = true;

                }}}}}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    for(int i=0; i< rx; i++)
    {
        for(int j=0; j< ry; j++)
        {
            for(int k=0; k< rz; k++)
            {
                //equacao da Elipse
                if ((((i-xcenter)*(i-xcenter))/((float)((xcenter)*(xcenter)))) +
                        ((((j-ycenter)*(j-ycenter)))/((float)((ycenter)*(ycenter)))) +
                        ((((k-zcenter)*(k-zcenter)))/((float)((zcenter)*(zcenter)))) <=1.0)
                {
                    v[i][j][k].r = r;
                    v[i][j][k].g = g;
                    v[i][j][k].b = b;
                    v[i][j][k].a = a;
                    v[i][j][k].isOn = false;

                }}}}}

