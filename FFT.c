#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>

#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])



int main ()
{
  //int i; double data[2*128];

  int n = 65536;

  FILE* fdata = fopen("/home/ensta/in104/data.dat", "r");
  FILE* famplitudes = fopen("/home/ensta/in104/amplitudes.dat", "wb");



  float reel;
  float imag;
  double data[2*n];

  fscanf(fdata, "%f", &reel);
  fscanf(fdata, "%f", &imag);
  REAL(data,0) = reel;
  IMAG(data,0) = imag;
  int i = 1;
  
  while (!feof(fdata)){
    fscanf(fdata, "%f", &reel);
    fscanf(fdata, "%f", &imag);
    REAL(data,i) = reel;
    IMAG(data,i) = imag;
    i=i+1;
  }


  gsl_fft_complex_radix2_forward (data, 1, n);

  for (i = 0; i < n; i++)
    {
      /*printf ("%d %e %e\n", i,
              REAL(data,i)/sqrt(n),
              IMAG(data,i)/sqrt(n));*/

      fprintf(famplitudes, "%f\n", sqrt(pow(REAL(data,i),2)+pow(IMAG(data,i),2)));
    }


    double amplitude[n];
    for (int i = 0 ; i<n ; i=i+1){
      amplitude[i]=sqrt(pow(REAL(data,i),2)+pow(IMAG(data,i),2));
      //printf ("%f\n",amplitude[i]);
    }




    /*int p = 26262;
    int indice = 0;
    float ampli_max = amplitude[p];

    if (amplitude[p]>ampli_max){
      ampli_max=amplitude[p];
      p=p+1;
      indice=p;
      printf("%d",indice);
    }
    else {
      p=p+1;
    }
*/

    int position, longueur=n;
    float ampli_max=0;
      for (int i=0 ; i< longueur ; i++)
      {
        if(amplitude[i]>ampli_max){
          ampli_max=amplitude[i];
          position=i;
          }
      }


    float frequence = (11025.0/65536)*position;

    printf("%f\n",ampli_max);
    printf("%f\n",frequence);



  fclose(fdata);
  fclose(famplitudes);


  return 0;
}