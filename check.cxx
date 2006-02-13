#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkGrayscaleDilateImageFilter.h"
#include "itkBinaryBallStructuringElement.h"
#include "itkTimeProbe.h"
#include <vector>
#include <iomanip>

int main(int, char * argv[])
{
  const int dim = 2;
  typedef unsigned char PType;
  typedef itk::Image< PType, dim >    IType;
  
  // read the input image
  typedef itk::ImageFileReader< IType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );
  
  typedef itk::BinaryBallStructuringElement< PType, dim > SRType;
  SRType kernel;
  kernel.SetRadius( 4 );
  kernel.CreateStructuringElement();
  
  typedef itk::GrayscaleDilateImageFilter< IType, IType, SRType > DilateType;
  DilateType::Pointer dilate = DilateType::New();
  dilate->SetInput( reader->GetOutput() );
  dilate->SetKernel( kernel );
  
/*  // write 
  typedef itk::ImageFileWriter< IType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( dilate->GetOutput() );
  writer->SetFileName( argv[2] );*/
  
  reader->Update();
  
  std::cout << "#nb" << "\t" 
            << "min" << "\t" 
            << "max" << "\t" 
            << "mean" << "\t" 
            << "median" << "\t" 
            << "sigma" << "\t" 
            << "rmin" << "\t" 
            << "rmax" << "\t" 
            << "rmean" << "\t" 
            << "rmedian" << "\t" 
            << "rsigma" << "\t" 
            << std::endl;

  for( int t=1; t<=10; t++ )
    {
    itk::TimeProbe time;
  
    dilate->SetNumberOfThreads( t );
    
    for( int i=0; i<50; i++ )
      {
      time.Start();
      dilate->Update();
      time.Stop();
      
      dilate->Modified();
      }
      
    std::cout << std::setprecision(3)
              << t << "\t" 
              << time.GetClockMin() << "\t"
              << time.GetClockMax() << "\t"
              << time.GetClockMean() << "\t"
              << time.GetClockMedian() << "\t"
              << time.GetClockSigma() << "\t"
              << time.GetRealTimeClockMin() << "\t"
              << time.GetRealTimeClockMax() << "\t"
              << time.GetRealTimeClockMean() << "\t"
              << time.GetRealTimeClockMedian() << "\t"
              << time.GetRealTimeClockSigma() << "\t"
              << std::endl;
    }
  
  
  return 0;
}

