/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkbvsFWHMFeatureImageFilter.cxx,v $
Language:  C++
Date:      $Date: 2006/04/06 16:48:25 $
Version:   $Revision: 1.1 $

  Copyright (c) Luca Antiga, David Steinman. All rights reserved.
  See LICENCE file for details.

  Portions of this code are covered under the VTK copyright.
  See VTKCopyright.txt or http://www.kitware.com/VTKCopyright.htm 
  for details.

  Portions of this code are covered under the ITK copyright.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm
  for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "vtkvmtkFWHMFeatureImageFilter.h"
#include "vtkImageData.h"
#include "vtkObjectFactory.h"

#include "vtkvmtkITKFilterUtilities.h"

#include "itkFWHMFeatureImageFilter.h"

vtkCxxRevisionMacro(vtkvmtkFWHMFeatureImageFilter, "$Revision: 1.3 $");
vtkStandardNewMacro(vtkvmtkFWHMFeatureImageFilter);

vtkvmtkFWHMFeatureImageFilter::vtkvmtkFWHMFeatureImageFilter()
{
  this->UseImageSpacing = 1;
  this->BackgroundValue = 0.0;
  this->Radius = NULL;
}

vtkvmtkFWHMFeatureImageFilter::~vtkvmtkFWHMFeatureImageFilter()
{
  if (this->Radius)
    {
    delete[] this->Radius;
    this->Radius = NULL;
    }
}

void vtkvmtkFWHMFeatureImageFilter::SimpleExecute(vtkImageData *input, vtkImageData *output)
{
  typedef itk::Image<float,3> ImageType;

  ImageType::Pointer inImage = ImageType::New();

  vtkvmtkITKFilterUtilities::VTKToITKImage<ImageType>(input,inImage);

  typedef itk::FWHMFeatureImageFilter<ImageType,ImageType> ImageFilterType;

  ImageFilterType::Pointer imageFilter = ImageFilterType::New();
  imageFilter->SetInput(inImage);

  typedef ImageFilterType::StructuringElementRadiusType RadiusType;
  long unsigned int radiusValue[3];
  radiusValue[0] = static_cast<long unsigned int>(this->Radius[0]);
  radiusValue[1] = static_cast<long unsigned int>(this->Radius[1]);
  radiusValue[2] = static_cast<long unsigned int>(this->Radius[2]);

  RadiusType radius;
  radius.SetSize(radiusValue);
  imageFilter->SetRadius(radius);
  imageFilter->SetUseImageSpacing(this->UseImageSpacing);
  imageFilter->SetBackgroundValue(this->BackgroundValue);
  imageFilter->Update();

  vtkvmtkITKFilterUtilities::ITKToVTKImage<ImageType>(imageFilter->GetOutput(),output);
}

