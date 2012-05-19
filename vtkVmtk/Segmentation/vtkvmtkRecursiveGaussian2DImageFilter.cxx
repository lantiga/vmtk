/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkbvsRecursiveGaussian2DImageFilter.cxx,v $
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

#include "vtkvmtkRecursiveGaussian2DImageFilter.h"
#include "vtkImageData.h"
#include "vtkObjectFactory.h"

#include "vtkvmtkITKFilterUtilities.h"

#include "itkRecursiveGaussianImageFilter.h"

vtkCxxRevisionMacro(vtkvmtkRecursiveGaussian2DImageFilter, "$Revision: 1.3 $");
vtkStandardNewMacro(vtkvmtkRecursiveGaussian2DImageFilter);

vtkvmtkRecursiveGaussian2DImageFilter::vtkvmtkRecursiveGaussian2DImageFilter() 
{
  this->Sigma = 0.0;
  this->NormalizeAcrossScale = 0;
}

void vtkvmtkRecursiveGaussian2DImageFilter::SimpleExecute(vtkImageData *input, vtkImageData *output)
{
  typedef itk::Image<float,2> ImageType;

  ImageType::Pointer inImage = ImageType::New();

  vtkvmtkITKFilterUtilities::VTKToITKImage2D<ImageType>(input,inImage);

  typedef itk::RecursiveGaussianImageFilter<ImageType,ImageType> ImageFilterType;

  ImageFilterType::Pointer imageFilter = ImageFilterType::New();
  imageFilter->SetInput(inImage);
  imageFilter->SetSigma(this->Sigma);
  imageFilter->SetNormalizeAcrossScale(this->NormalizeAcrossScale);
  imageFilter->Update();

  vtkvmtkITKFilterUtilities::ITKToVTKImage<ImageType>(imageFilter->GetOutput(),output);
}

