/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkbvsUpwindGradientMagnitudeImageFilter.cxx,v $
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

#include "vtkvmtkUpwindGradientMagnitudeImageFilter.h"
#include "vtkImageData.h"
#include "vtkObjectFactory.h"

#include "vtkvmtkITKFilterUtilities.h"

#include "itkUpwindGradientMagnitudeImageFilter.h"

vtkCxxRevisionMacro(vtkvmtkUpwindGradientMagnitudeImageFilter, "$Revision: 1.3 $");
vtkStandardNewMacro(vtkvmtkUpwindGradientMagnitudeImageFilter);

vtkvmtkUpwindGradientMagnitudeImageFilter::vtkvmtkUpwindGradientMagnitudeImageFilter() 
{
  this->UpwindFactor = 1.0;
}

void vtkvmtkUpwindGradientMagnitudeImageFilter::SimpleExecute(vtkImageData *input, vtkImageData *output)
{
  typedef itk::Image<float,3> ImageType;

  ImageType::Pointer inImage = ImageType::New();

  vtkvmtkITKFilterUtilities::VTKToITKImage<ImageType>(input,inImage);

  typedef itk::UpwindGradientMagnitudeImageFilter<ImageType,ImageType> ImageFilterType;

  ImageFilterType::Pointer imageFilter = ImageFilterType::New();
  imageFilter->SetInput(inImage);
  imageFilter->SetUpwindFactor(this->UpwindFactor);
  imageFilter->Update();

  vtkvmtkITKFilterUtilities::ITKToVTKImage<ImageType>(imageFilter->GetOutput(),output);
}

