/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkTimeProbe.cxx,v $
  Language:  C++
  Date:      $Date: 2005/11/29 14:51:11 $
  Version:   $Revision: 1.6 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "itkTimeProbe.h"
#include "itkNumericTraits.h"

namespace itk
{

TimeProbe
::TimeProbe()
{
  m_RealTimeClock   = RealTimeClock::New();
  m_RealTimeClockValues.clear();
  m_ClockValues.clear();
}


TimeProbe
::~TimeProbe()
{
}



void 
TimeProbe
::Start(void)
{
  m_ClockStart = clock();
  m_RealTimeClockStart = m_RealTimeClock->GetTimeStamp();
}
 


void 
TimeProbe
::Stop(void)
{
  double c = ((double)( clock() - m_ClockStart )) / CLOCKS_PER_SEC;
  double rtc = m_RealTimeClock->GetTimeStamp() - m_RealTimeClockStart;
  m_ClockValues.push_back( c );
  m_RealTimeClockValues.push_back( rtc );
}



TimeProbe::TimeStampType
TimeProbe
::GetMean(ListType list)
{
  double mean = 0;
  for( ListType::const_iterator it = list.begin(); it!=list.end(); it++ )
    {
    mean += *it;
    }
  return mean / list.size();
}

TimeProbe::TimeStampType
TimeProbe
::GetRealTimeClockMean()
{
  return GetMean( m_RealTimeClockValues );
}

TimeProbe::TimeStampType
TimeProbe
::GetClockMean()
{
  return GetMean( m_ClockValues );
}




TimeProbe::TimeStampType
TimeProbe
::GetMedian(ListType list)
{
  double mean = 0;
  for( ListType::const_iterator it = list.begin(); it!=list.end(); it++ )
    {
    mean += *it;
    }
  return 0;
}

TimeProbe::TimeStampType
TimeProbe
::GetRealTimeClockMedian()
{
  return GetMedian( m_RealTimeClockValues );
}

TimeProbe::TimeStampType
TimeProbe
::GetClockMedian()
{
  return GetMedian( m_ClockValues );
}



TimeProbe::TimeStampType
TimeProbe
::GetMax(ListType list)
{
  double max = 0;
  for( ListType::const_iterator it = list.begin(); it!=list.end(); it++ )
    {
    max = std::max( *it, max );
    }
  return max;
}

TimeProbe::TimeStampType
TimeProbe
::GetRealTimeClockMax()
{
  return GetMax( m_RealTimeClockValues );
}

TimeProbe::TimeStampType
TimeProbe
::GetClockMax()
{
  return GetMax( m_ClockValues );
}





TimeProbe::TimeStampType
TimeProbe
::GetMin(ListType list)
{
  double min = NumericTraits<double>::max();
  for( ListType::const_iterator it = list.begin(); it!=list.end(); it++ )
    {
    min = std::min( *it, min );
    }
  return min;
}

TimeProbe::TimeStampType
TimeProbe
::GetRealTimeClockMin()
{
  return GetMin( m_RealTimeClockValues );
}

TimeProbe::TimeStampType
TimeProbe
::GetClockMin()
{
  return GetMin( m_ClockValues );
}



TimeProbe::TimeStampType
TimeProbe
::GetSigma(ListType list)
{
  double min = 0;
  for( ListType::const_iterator it = list.begin(); it!=list.end(); it++ )
    {
    min = std::min( *it, min );
    }
  return 0;
}

TimeProbe::TimeStampType
TimeProbe
::GetRealTimeClockSigma()
{
  return GetSigma( m_RealTimeClockValues );
}

TimeProbe::TimeStampType
TimeProbe
::GetClockSigma()
{
  return GetSigma( m_ClockValues );
}


} // end namespace itk


