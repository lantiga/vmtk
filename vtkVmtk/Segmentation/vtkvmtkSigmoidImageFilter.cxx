/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkbvsSigmoidImageFilter.cxx,v $
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

#include "vtkvmtkSigmoidImageFilter.h"
#include "vtkImageData.h"
#include "vtkObjectFactory.h"

#include "vtkvmtkITKFilterUtilities.h"

#include "itkSigmoidImageFilter.h"

vtkCxxRevisionMacro(vtkvmtkSigmoidImageFilter, "$Revision: 1.3 $");
vtkStandardNewMacro(vtkvmtkSigmoidImageFilter);

vtkvmtkSigmoidImageFilter::vtkvmtkSigmoidImageFilter() 
{
  this->Alpha = 1.0;
  this->Beta = 0.5;
  this->OutputMinimum = 0.0;
  this->OutputMaximum = 1.0;
}

void vtkvmtkSigmoidImageFilter::SimpleExecute(vtkImageData *input, vtkImageData *output)
{
  typedef itk::Image<float,3> ImageType;

  ImageType::Pointer inImage = ImageType::New();

  vtkvmtkITKFilterUtilities::VTKToITKImage<ImageType>(input,inImage);

  typedef itk::SigmoidImageFilter<ImageType,ImageType> ImageFilterType;

  ImageFilterType::Pointer imageFilter = ImageFilterType::New();
  imageFilter->SetInput(inImage);
  imageFilter->SetAlpha(this->Alpha);
  imageFilter->SetBeta(this->Beta);
  imageFilter->SetOutputMinimum(this->OutputMinimum);
  imageFilter->SetOutputMaximum(this->OutputMaximum);
  imageFilter->Update();

  vtkvmtkITKFilterUtilities::ITKToVTKImage<ImageType>(imageFilter->GetOutput(),output);
}

