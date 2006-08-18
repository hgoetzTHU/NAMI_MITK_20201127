/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Module:    $RCSfile$
Language:  C++
Date:      $Date$
Version:   $Revision$

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/


#ifndef IMAGETIMESELECTOR_H_HEADER_INCLUDED_C1E4861D
#define IMAGETIMESELECTOR_H_HEADER_INCLUDED_C1E4861D

#include "mitkCommon.h"
#include "mitkSubImageSelector.h"

namespace mitk {

//##ModelId=3DCBFE4C006F
//##Documentation
//## @brief Provides access to a volume at a specific time of the input image
//##
//## If the input is generated by a ProcessObject, only the required data is
//## requested.
//## @ingroup Process
class ImageTimeSelector : public SubImageSelector
{
public:
	mitkClassMacro(ImageTimeSelector,SubImageSelector);

	itkNewMacro(Self);  

	itkGetConstMacro(TimeNr,int);
	itkSetMacro(TimeNr,int);

	itkGetConstMacro(ChannelNr,int);
	itkSetMacro(ChannelNr,int);

protected:
	//##ModelId=3E1B1975031E
	ImageTimeSelector();

	//##ModelId=3E1B1975033C
	virtual ~ImageTimeSelector();

	//##ModelId=3E3BD0CC0232
    virtual void GenerateOutputInformation();

  virtual void GenerateInputRequestedRegion();

	//##ModelId=3E3BD0CE0194
    virtual void GenerateData();

  //##ModelId=3E1B1A0501C7
	int m_TimeNr;

	//##ModelId=3E1B1A08024D
	int m_ChannelNr;
};

} // namespace mitk



#endif /* IMAGETIMESELECTOR_H_HEADER_INCLUDED_C1E4861D */
