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
#include "vnl/vnl_math.h"
#include <algorithm>

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
  TimeStampType c = ((TimeStampType)( clock() - m_ClockStart )) / CLOCKS_PER_SEC;
  TimeStampType rtc = m_RealTimeClock->GetTimeStamp() - m_RealTimeClockStart;
  m_ClockValues.push_back( c );
  m_RealTimeClockValues.push_back( rtc );
}



TimeProbe::TimeStampType
TimeProbe
::GetMean(const ListType &list)
{
  TimeStampType mean = 0;
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
::GetMedian(const ListType &list)
{
  ListType tmpList(list);
  const ListType::iterator medianIterator = tmpList.begin() +  tmpList.size() / 2;
  std::nth_element(tmpList.begin(), medianIterator, tmpList.end() );
  return *medianIterator;
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
::GetMax(const ListType &list)
{
  TimeStampType max = 0;
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
::GetMin(const ListType &list)
{
  TimeStampType min = NumericTraits<TimeStampType>::max();
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
::GetSigma(const ListType &list)
{
  TimeStampType mean = GetMean( list );
  TimeStampType squaredSum = NumericTraits<TimeStampType>::Zero;
  for( ListType::const_iterator it = list.begin(); it!=list.end(); it++ )
      {
      squaredSum += vnl_math_sqr(*it - mean);
      }
    return vcl_sqrt( squaredSum / ( list.size() - 1) );
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


