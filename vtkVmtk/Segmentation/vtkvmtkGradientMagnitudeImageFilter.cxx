/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkbvsGradientMagnitudeImageFilter.cxx,v $
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

#include "vtkvmtkGradientMagnitudeImageFilter.h"
#include "vtkImageData.h"
#include "vtkObjectFactory.h"

#include "vtkvmtkITKFilterUtilities.h"

#include "itkGradientMagnitudeImageFilter.h"

vtkCxxRevisionMacro(vtkvmtkGradientMagnitudeImageFilter, "$Revision: 1.3 $");
vtkStandardNewMacro(vtkvmtkGradientMagnitudeImageFilter);

void vtkvmtkGradientMagnitudeImageFilter::SimpleExecute(vtkImageData *input, vtkImageData *output)
{
  typedef itk::Image<float,3> ImageType;

  ImageType::Pointer inImage = ImageType::New();

  vtkvmtkITKFilterUtilities::VTKToITKImage<ImageType>(input,inImage);

  typedef itk::GradientMagnitudeImageFilter<ImageType,ImageType> ImageFilterType;

  ImageFilterType::Pointer imageFilter = ImageFilterType::New();
  imageFilter->SetInput(inImage);
  imageFilter->Update();

  vtkvmtkITKFilterUtilities::ITKToVTKImage<ImageType>(imageFilter->GetOutput(),output);
}
