/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkTimeProbe.h,v $
  Language:  C++
  Date:      $Date: 2006/02/05 20:57:46 $
  Version:   $Revision: 1.6 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkTimeProbe_h
#define __itkTimeProbe_h


#include "itkRealTimeClock.h"
#include <time.h>
#include "itkWin32Header.h"


namespace itk 
{
 
  /** \class TimeProbe 
   * 
   *  \brief Class for computing the time passed between two points in the code.
   *   
   *   This class allows the user to trace the time passed between the execution of two pieces of code.
   *   It can be started and stopped in order to evaluate the execution over multiple passes.
   *   The values of time are taken from the RealTimeClock.
   *
   *   \sa RealTimeClock
   *
   */
class ITKCommon_EXPORT TimeProbe
{

public:

  /** Type for counting how many times the probe has been started and stopped. */
  typedef unsigned long CountType;

  /** Type for measuring time. See the RealTimeClock class for details on the
   * precision and units of this clock signal */
  typedef RealTimeClock::TimeStampType  TimeStampType;
  typedef clock_t       ClickType;

  typedef std::vector<double> ListType;

public:

  /** Constructor */
  TimeProbe();

  /** Destructor */
  ~TimeProbe();

  /** Start counting the time */
  void Start(void);

  /** Stop counting the time */
  void Stop(void);

  CountType     GetSize(void) const;

  double GetRealTimeClockMean();
  double GetRealTimeClockMedian();
  double GetRealTimeClockMax();
  double GetRealTimeClockMin();
  double GetRealTimeClockSigma();
//   itkGetConstMacro(RealTimeClockValues, ListType);


  double GetClockMean();
  double GetClockMedian();
  double GetClockMax();
  double GetClockMin();
  double GetClockSigma();
//   itkGetConstMacro(ClockValues, ListType);

  double GetMean(ListType);
  double GetMedian(ListType);
  double GetMax(ListType);
  double GetMin(ListType);
  double GetSigma(ListType);

  /** Returns the average times passed between the starts and stops of the
   * probe. See the RealTimeClock for details on the precision and units of
   * this time value. */
  TimeStampType GetMeanTime(void) const;

private:

  ListType  m_RealTimeClockValues;
  ListType  m_ClockValues;

  double m_RealTimeClockStart;
  ClickType m_ClockStart;

  RealTimeClock::Pointer   m_RealTimeClock;
};


}

#endif
